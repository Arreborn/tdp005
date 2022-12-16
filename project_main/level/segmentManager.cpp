#include "segmentManager.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <random>
#include <sstream>

vector<string> SegmentManager::get(size_t numberOfLevels) {
  vector<string> storedSegments;
  while (storedSegments.size() < numberOfLevels) {
    string path{"segments/"};
    std::stringstream ss{};

    // stores path to all segments in the container
    for (const std::filesystem::directory_entry &entry :
         std::filesystem::directory_iterator(path)) {
      ss << entry;
      storedSegments.push_back(ss.str());
      ss.str("");
    }
  }

  while (storedSegments.size() != numberOfLevels) {
    storedSegments.pop_back();
  }

  std::random_device device;
  std::default_random_engine engine(device());
  shuffle(begin(storedSegments), end(storedSegments), engine);
  return storedSegments;
}
