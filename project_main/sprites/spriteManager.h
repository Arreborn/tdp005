#pragma once
#include "../common.h"
#include <map>

/**
 * @brief This class keeps track of loaded
 * sprites to ensure a sprite is not loaded 
 * into the game twice.
 * 
 */
class SpriteManager {
public:

  /**
   * @brief Fetches a sprite. This may either load a sprite, 
   * or return a previously loaded sprite.
   * 
   * @param name 
   * @return sf::Texture* 
   */
  static sf::Texture *get(const string &name);

private:

  /**
   * @brief Private constructor, as only 
   * we can create an instance of this object.
   */
  SpriteManager() = default;

  /**
   * @brief This is the only instance of this object.
   * 
   */
  static SpriteManager instance;

  /**
   * @brief Keeps track of previously loaded sprites.
   * 
   */
  std::map<string, std::unique_ptr<sf::Texture>> sprites;
};