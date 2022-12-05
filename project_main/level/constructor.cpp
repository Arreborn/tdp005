#include "constructor.h"

LevelConstructor::LevelConstructor(int numberOfSegments){
  for (int i{}; i < numberOfSegments; ++i){
    
  }
}

vector<TexturedEntity *> LevelConstructor::generateLevel(string &segment){
  vector<TexturedEntity *> loadedLevel{};
  int x{};
  int y{};

  for (string::size_type i{}; i < segment.length(); ++i){
    if (segment[i] != '.'){
      loadedLevel.push_back(selector(segment[i], x, y));
    }
    x += 16;
    if (x == 1280){
      x = 0;
      y += 16;
    }
  }
}