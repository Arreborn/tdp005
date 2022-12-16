#pragma once
#include "../common.h"
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>

/**
 * @brief This class manages all segments in order to generate random maps.
 * This class also ensures manipulated random segments in order to avoid
 * duplicate segments per map.
 *
 */
class SegmentManager {
private:
  /**
   * @brief Default constructor, as only we can create an instance of this
   * object. The constructor will load all existing segment names into its
   * container when constructed. Segments should be placed in segments/.
   *
   */
  SegmentManager() = default;

  /**
   * @brief Destroy the Segment Manager object.
   *
   */
  ~SegmentManager() = default;

  /**
   * @brief This is the only instance of this object.
   *
   */
  static SegmentManager instance;

public:
  /**
   * @brief Fecthes a random segment when called upon, and returns a shuffled
   * vector with all paths. Static function to be able to use this outside of
   * the class.
   *
   * @return string
   */
  static void get(size_t numberOfLevels, vector<string> &levels);
};