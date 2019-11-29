#pragma once
#include "image.h"
#include "rectangle.h"
#include <memory>

namespace albinjohansson::wanderer {

struct Range {
  int min;
  int max;
};

class SpriteSheet final {
 private:
  Image_sptr sheet = nullptr;
  const Range range;
  const float size;

  int nRows;
  int nCols;
  int nSprites;

 public:
  SpriteSheet(Image_sptr sheet, Range range, int size);

  ~SpriteSheet();

  [[nodiscard]] Rectangle GetSource(int index) const;

  [[nodiscard]] int GetMinID() const noexcept { return range.min; }

  [[nodiscard]] int GetMaxID() const noexcept { return range.max; }

  [[nodiscard]] int GetTileCount() const noexcept { return range.max - range.min; }

  [[nodiscard]] bool Contains(int tileId) const noexcept {
    return tileId >= range.min && tileId <= range.max;
  }

  [[nodiscard]] float GetSpriteSize() const noexcept { return size; }

  [[nodiscard]] Image_sptr GetImage() noexcept { return sheet; }
};

using SpriteSheet_uptr = std::unique_ptr<SpriteSheet>;
using SpriteSheet_sptr = std::shared_ptr<SpriteSheet>;
using SpriteSheet_wptr = std::weak_ptr<SpriteSheet>;

}
