#pragma once
#include "../common.h"

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
   * @brief Fecthes a random segment when called upon, and returns the segment
   * as a string which can be read into the game. Static function to be able
   * to use this outside of the class.
   *
   * @return string
   */
  static string get();
};