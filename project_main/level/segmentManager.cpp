#include "segmentManager.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>

SegmentManager::SegmentManager(){
  string path{"segments/"};
  std::stringstream ss{};
  string toVector{};

  // stores path to all segments in the container
  for (const auto & entry : std::filesystem::directory_iterator(path)){
    ss << entry;
    storedSegments.push_back(ss.str());
    ss.clear();
  }
}

string SegmentManager::get(){
  std::ifstream fs{};
  string result{};
  string buffer{};
  // fetches a random segment
  int random = rand() % storedSegments.size();
  if (std::find(alreadyGenerated.begin(), 
                alreadyGenerated.end(), 
                random) == alreadyGenerated.end() 
                || storedSegments.size() == 0){
    // if the index has already been used or this is the first, run the function again
      return get();
  } else {
    alreadyGenerated.push_back(random);
    fs.open(storedSegments[random]);
    while(fs){
      getline(fs, buffer);
      result += buffer;
    }
    fs.close();
    return result;
  }

};