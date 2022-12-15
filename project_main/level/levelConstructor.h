#pragma once
#include "../common.h"
#include "../entity/entity.h"
#include "../hostile/archer.h"
#include "../hostile/flying.h"
#include "../hostile/hostile.h"
#include "../player/player.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include "segmentManager.h"

/**
 * @brief This class manages construction of levels from segments.
 *
 */
class LevelConstructor {
private:
  /**
   * @brief General switch function that creates a new object depending on the
   * character designated in the segment. This is separate to simplify
   * expansion with more objects.
   *
   * @param x
   * @return TexturedEntity
   */
  static void selector(char a, int x, int y, World &world,
                       shared_ptr<Player> player, bool &playerSet,
                       bool const loadHostiles);

  /**
   * @brief Construct a new level with the designated number of segments.
   *
   * @param numberOfSegments
   */
  LevelConstructor() = default;

  /**
   * @brief Destroys the level.
   *
   */
  ~LevelConstructor() = default;

  /**
   * @brief The only instance of this object.
   *
   */
  static LevelConstructor instance;

public:
  /**
   * @brief Generates a level which will be drawn in the game world.
   *
   * @param world
   * @param player
   */
  static void generateLevel(World &world, shared_ptr<Player> player,
                            bool loadHostiles, string str);

  /**
   * @brief This function utilizes the SegmentManager to construct and return a
   * number of levels in a vector to the game world.
   *
   * @param numberOfLevels
   * @return vector<string>
   */
  static vector<string> loadLevels(int numberOfLevels);
};