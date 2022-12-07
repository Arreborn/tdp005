#include "segmentManager.h"
#include <filesystem>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <random>

vector<string> storedSegments;
vector<int> alreadyGenerated;
const auto rng{std::default_random_engine {}};

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
  shuffle(storedSegments.begin(), storedSegments.end(), rng);
  string pickedSegment{storedSegments.back()};
  cout << "Pre-pop: " << pickedSegment << endl;
  storedSegments.pop_back();
  cout << "Post-pop: " << pickedSegment << endl;
  return pickedSegment;

 }


