#include "tiled_map_parser.h"
#include "tiled_tile_set.h"
#include "tiled_map.h"
#include "tiled_animation.h"
#include "image_generator.h"
#include "image.h"
#include "bad_state_exception.h"
#include "tile_map_impl.h"
#include "tile_map_layer_impl.h"
#include "tile_object.h"
#include "tile_set.h"

namespace albinjohansson::wanderer {

// TODO entity parsing, item parsing...

TiledMapParser::TiledMapParser(ImageGenerator& imageGenerator, const std::string& file)
    : imageGenerator(imageGenerator), file(file) {
  LoadMap();
}

TiledMapParser::~TiledMapParser() = default;

pugi::xml_document TiledMapParser::LoadDocument(const std::string& path) {
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw BadStateException("Failed to load: " + path + ", Error:"
                                + std::string(result.description()));
  }
  return doc;
}

std::unique_ptr<TileSet> TiledMapParser::LoadTileSet(const pugi::xml_node& mapRoot) {
  auto tileSet = std::make_unique<TileSet>(3000); // FIXME

  for (pugi::xml_node ts : mapRoot.children("tileset")) {
    const std::string tsFileName = ts.attribute("source").as_string();

    const pugi::xml_document tsDocument = LoadDocument("resources/map/world/" + tsFileName);
    const pugi::xml_node tsRoot = tsDocument.child("tileset");

    const auto tileCount = tsRoot.attribute("tilecount").as_int();
    const auto firstgid = static_cast<TileID>(ts.attribute("firstgid").as_uint());
    const auto lastgid = firstgid + static_cast<TileID>(tileCount) - 1;

    const tiled::TiledTileSet tiledTileSet(tsRoot, firstgid, lastgid);

    const int tileWidth = tsRoot.attribute("tilewidth").as_int();
    const int tileSize = tileWidth;

    const std::string path = "resources/img/" + tiledTileSet.GetImageName();
    std::shared_ptr<Image> sheetImage = imageGenerator.Load(path);

    const int sheetCols = tiledTileSet.GetCols();
    const TileID firstId = tiledTileSet.GetFirstTileId();
    const TileID lastId = tiledTileSet.GetLastTileId();

    int i = 0;
    for (TileID id = firstId; id <= lastId; id++, i++) {
      Tile tile;

      tile.SetSheet(sheetImage);
      tile.SetId(id);

      if (tiledTileSet.HasTile(id)) {
        const auto& tiledTile = tiledTileSet.GetTile(id);

        if (tiledTile.HasProperty("depth")) {
          tile.SetDepth(tiledTile.GetIntProperty("depth"));
        }

        if (tiledTile.HasAttribute("type")) {
          tile.SetObject(tiledTile.GetStringAttribute("type") == "Object");
        }

        if (tiledTile.IsAnimated()) {
          tile.SetAnimation(CreateAnimation(tiledTile.GetAnimation()));
          tile.SetAnimated(true);
        }

        if (tiledTile.HasObject("hitbox")) {
          const auto& object = tiledTile.GetObject("hitbox");

          float x = std::stof(object.GetAttribute("x"));
          x = (x / tileSize) * Tile::SIZE;

          float y = std::stof(object.GetAttribute("y"));
          y = (y / tileSize) * Tile::SIZE;

          float w = std::stof(object.GetAttribute("width"));
          w = (w / tileSize) * Tile::SIZE;

          float h = std::stof(object.GetAttribute("height"));
          h = (h / tileSize) * Tile::SIZE;

          tile.SetHitbox(Rectangle(x, y, w, h));
          tile.SetBlocked(true);
        }
      }

      const int x = (i % sheetCols) * static_cast<int>(tileSize);
      const int y = (i / sheetCols) * static_cast<int>(tileSize);
      tileSet->Insert(id, tile, Rectangle(x, y, tileSize, tileSize));
    }
    int ix;
  }

  return tileSet;
}

TileAnimation TiledMapParser::CreateAnimation(tiled::TiledAnimation animation) {
  const auto& frames = animation.GetFrames();
  TileAnimation result(frames.size());

  int i = 0;
  for (const auto frame : frames) {
    result.SetFrame(i, Frame{static_cast<TileID>(frame.tileId),
                             static_cast<uint32_t>(frame.duration)});
    ++i;
  }

  return result;
}

std::vector<TileID> TiledMapParser::CreateTileVector(const std::vector<int>& tiles) {
  std::vector<TileID> result;
  result.reserve(tiles.size());
  for (int i : tiles) {
    result.push_back(static_cast<TileID>(i));
  }
  return result;
}

void TiledMapParser::LoadMap() {
  const auto mapDocument = LoadDocument(file);
  const auto mapNode = mapDocument.child("map");
  const auto nCols = mapNode.attribute("width").as_int();
  const auto nRows = mapNode.attribute("height").as_int();

  tiled::TiledMap tiledMap(mapNode);

  std::shared_ptr<TileSet> tileSet = LoadTileSet(mapNode);
  map = std::make_unique<TileMapImpl>(tileSet, nRows, nCols, imageGenerator);

  for (const auto& tiledLayer : tiledMap.GetLayers()) {
    auto layer = std::make_unique<TileMapLayerImpl>(tileSet,
                                                    nRows,
                                                    nCols,
                                                    CreateTileVector(tiledLayer->GetTiles()));
    layer->SetGroundLayer(tiledLayer->GetBool("ground")); // TODO might be redundant
    map->AddLayer(std::move(layer));
  }
}

std::unique_ptr<ITileMap> TiledMapParser::GetMap() noexcept { return std::move(map); }

}