#include "segmentManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>

void SegmentManager::get(size_t numberOfLevels, vector<string> &levels) {
  while (levels.size() < numberOfLevels) {
    string path{"segments/"};
    std::stringstream ss{};

    // stores path to all segments in the container
    for (const std::filesystem::directory_entry &entry :
         std::filesystem::directory_iterator(path)) {
      ss << entry;
      levels.push_back(ss.str());
      ss.str("");
    }
  }

  while (levels.size() != numberOfLevels) {
    levels.pop_back();
  }

  std::random_device device;
  std::default_random_engine engine(device());
  shuffle(begin(levels), end(levels), engine);
}
