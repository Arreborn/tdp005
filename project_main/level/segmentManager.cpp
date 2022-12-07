#include "segmentManager.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>

vector<string> storedSegments;
vector<int> alreadyGenerated;

string SegmentManager::get(){
  if (storedSegments.size() == 0){
    string path{"segments/"};
    std::stringstream ss{};

    // stores path to all segments in the container
    for (const auto & entry : std::filesystem::directory_iterator(path)){
      cout <<"Path: " << entry << endl;
      ss << entry;
      storedSegments.push_back(ss.str());
      ss.clear(); 
    }

  }
}

