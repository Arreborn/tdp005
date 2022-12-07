#include "segmentManager.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>

vector<string> storedSegments;

string SegmentManager::get(){
  if (storedSegments.size() == 0){
    string path{"segments/"};
    std::stringstream ss{};

    // stores path to all segments in the container
    for (const std::filesystem::directory_entry &entry : std::filesystem::directory_iterator(path)){
      ss << entry;
      storedSegments.push_back(ss.str());
      ss.str(""); 
    }
    std::random_device device;
    std::default_random_engine engine(device());
    shuffle(begin(storedSegments), end(storedSegments), engine);
  }

  const char* randomSegment{storedSegments.back().c_str()};
  storedSegments.pop_back();
  return randomSegment;
  

 }


