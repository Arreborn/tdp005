#pragma once
#include "../common.h"
#include <SFML/Graphics/Rect.hpp>


/**
 * @brief This class contains all objects in the world.
 * 
 */
class World;


class Entity {
public:

  Entity(sf::Vector2f shape, string const &sprite);

  virtual ~Entity() = default;

  sf::Vector2f center;

  virtual bool tick(sf::Time time, World &world);

  virtual void render(sf::RenderWindow &window);

  virtual sf::RectangleShape* getBorder();

  protected:

  sf::RectangleShape shape;
  
};
/*
class TexturedEntity : public Entity {
public:

  TexturedEntity(sf::Vector2f center, const string &sprite);

  void render(sf::RenderWindow &window) override;

  bool tick(sf::Time time, World &world) override;

  sf::RectangleShape* getBorder() override;


};
*/