#pragma once
#include "segmentManager.h"
#include "../common.h"
#include "../world.h"
#include "../staticEntity/block.h"
#include "../entity/entity.h"
#include "../hostile/hostile.h"

// TODO:
// Check viability of shared_ptr for the vector thingys
// Might be able to return that from selector

/**
 * @brief This class manages construction of levels from segments.
 * 
 */
class LevelConstructor{
private:
   /**
   * @brief General switch function that creates a new object depending on the
   * character designated in the segment. This is separate to simplify
   * expansion with more objects.
   * 
   * @param x 
   * @return TexturedEntity 
   */
  static void selector(char a, int x, int y, World &world);

  /**
   * @brief Construct a new level with the designated number of segments.
   * 
   * @param numberOfSegments 
   */
  LevelConstructor(int numberOfSegments);

  /**
   * @brief Destroys the level.
   * 
   */
  ~LevelConstructor() = default;

  static LevelConstructor instance;

public:
  static void generateLevel(World &world);

};