#pragma once
#include "../common.h"
#include <SFML/Graphics/Rect.hpp>

class World;

/**
 * @brief An abstract game object.
 *
 */
class Entity {
public:
  /**
   * @brief Construct a new Entity bject.
   *
   * @param center
   * @param radius
   */
  Entity(sf::Vector2f center, string const &sprite);

  /**
   * @brief Destroy the Entity object.
   *
   */
  virtual ~Entity() = default;

  /**
   * @brief Position of the objects center.
   *
   */
  sf::Vector2f center;

  /**
   * @brief Radius of this object.
   *
   */
  float radius; // may need to change?

  /**
   * @brief Updates the object for each frame, returns
   * 'false' if the object is to be removed.
   *
   * @param time
   * @param world
   * @return true
   * @return false
   */
  virtual bool tick(sf::Time time, World &world) = 0;

  /**
   * @brief Renders the object.
   *
   * @param window
   */
  virtual void render(sf::RenderWindow &window) = 0;

  virtual sf::Sprite *getBorder();

protected:
  /**
   * @brief This is the shape to render.
   *
   */
  sf::Sprite sprite;
};

/* 
class TexturedEntity : public Entity {
public:
  /**
   * @brief Construct a new Textured Entity object.
   *
   * @param center
   * @param texture
   */
  /*
  TexturedEntity(sf::Vector2f center, const string &sprite);

  /**
   * @brief Override for the rendering of the object.
   *
   * @param window
   */
  /*
  void render(sf::RenderWindow &window) override;

  sf::RectangleShape *getBorder() override;

protected:
  /**
   * @brief This is the shape to render.
   *
   */
  /*
  sf::RectangleShape shape;
};
 */