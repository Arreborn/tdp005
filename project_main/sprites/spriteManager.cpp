#include "spriteManager.h"
#include <stdexcept>

sf::Texture *SpriteManager::get(const string &name) {
  auto found{instance.sprites.find(name)};
  if (found != instance.sprites.end()){
    return found->second.get();
  }

  sf::Texture *t = new sf::Texture();
  if (!t->loadFromFile(name)){
    throw std::logic_error("Failed to load texture!");
  }
  instance.sprites.insert(std::make_pair(name, std::unique_ptr<sf::Texture>(t)));
  return t;
}

SpriteManager SpriteManager::instance;