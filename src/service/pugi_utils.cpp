#include "pugi_utils.h"

#include "wanderer_exception.h"

namespace wanderer {

pugi::xml_document PugiUtils::load_document(const std::string& path)
{
  pugi::xml_document doc;
  pugi::xml_parse_result result = doc.load_file(path.c_str());
  if (!result) {
    throw WandererException{"Failed to load: " + path +
                            ", Error:" + result.description()};
  }
  return doc;
}

}  // namespace wanderer
