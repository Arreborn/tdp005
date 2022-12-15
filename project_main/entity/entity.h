#pragma once
#include "../common.h"

class World;

/**
 * @brief An abstract game object for all types of entities that will be drawn
 * in the game world.
 *
 */
class Entity : public std::enable_shared_from_this<Entity> {
public:
  /**
   * @brief Construct a new Entity object. As this is an interface,
   * constructing a pure entity object is impossible.
   *
   * @param center
   * @param radius
   */
  Entity(sf::Vector2f center, string const &sprite, char const type);

  /**
   * @brief Destroy the Entity object. Default destructor for all
   * entities.
   *
   */
  virtual ~Entity() = default;

  /**
   * @brief Position of the objects center. Will be manipulated in order
   * to move different entities.
   *
   */
  sf::Vector2f center;

  /**
   * @brief Radius of this object.
   *
   */
  float radius; // may need to change? what are you used for!?

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

  /**
   * @brief Returns the border of the object, in order to check collision.
   *
   * @return sf::Sprite*
   */
  virtual sf::Sprite *getBorder();

  /**
   * @brief Gets the bounds for the object.
   *
   * @return sf::FloatRect
   */
  sf::FloatRect getBounds();

  /**
   * @brief Gets the center of the object, when manipulating of position
   * needs to be managed outside the class.
   *
   * @return sf::Vector2f const
   */
  sf::Vector2f const getCenter();

  /**
   * @brief Checks if the object is alive (when applicable):
   *
   * @return true
   * @return false
   */
  virtual bool isAlive();

  /**
   * @brief Returns the type of the object. (DEPRECATED?)
   *
   * @return char
   */
  char getType();

  /**
   * @brief A pure virtual function that allows entities to take damage.
   *
   * @param damage
   */
  virtual void takeDamage(float damage) = 0;

  /**
   * @brief Set the Frame object. DEPRECATED?
   *
   * @param frame
   */
  virtual void setFrame(sf::IntRect frame);

  /**
   * @brief Gets a shared pointer from this entity to ensure no friendly fire
   * when attacking.
   *
   * @return shared_ptr<Entity>
   */
  virtual shared_ptr<Entity> ptrGet();

  /**
   * @brief Returns the direction the entity is facing.
   *
   * @return char
   */
  char getDirection();

protected:
  /**
   * @brief This is the sprite to render.
   *
   */
  sf::Sprite sprite;

  /**
   * @brief The entity type, used for some collisions. 'p' for player.
   *
   */
  char type{};

  /**
   * @brief The direction the entity is looking.
   *
   */
  char direction{};
};
