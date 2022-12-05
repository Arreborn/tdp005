#pragma once
#include "../common.h"
#include "segmentManager.h"
#include "../components/component.h"

class LevelConstructor{
private:
  /**
   * @brief Stores the loaded level.
   * 
   */
  vector<vector<TexturedEntity *>> level{};

    /**
   * @brief General switch function that creates a new object depending on the
   * character designated in the segment.
   * 
   * @param x 
   * @return TexturedEntity 
   */
  TexturedEntity* selector(char a, int x, int y);

  vector<TexturedEntity *>generateLevel(string &segment);

public:
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

};