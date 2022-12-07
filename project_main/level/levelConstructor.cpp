#include "levelConstructor.h"
#include <fstream>

LevelConstructor::LevelConstructor(int numberOfSegments){
  string current{};
  for (int i{}; i < numberOfSegments; ++i){
    current = SegmentManager::get();
  }
}

void LevelConstructor::generateLevel(World &world){
  std::ifstream file{}; 
  file.open("segments/seg1"); // temporary until segment manager works
  string segment{};
  string temp{};

  while (getline(file, temp)){
    segment += temp;
  }
  
  int x{};
  int y{};

  for (string::size_type i{}; i < segment.length(); i++){
    if (segment[i] != '.'){
      selector(segment[i], x, y, world);
    }

    x += 16;
    if (x == 1280){
      x = 0;
      y += 16;
    }
  }
}


void LevelConstructor::selector(char a, int x, int y, World &world){
  switch (a){
    case 'B': case 'b':
       world.add(std::make_shared<Block>(sf::Vector2f(x, y)));
       break;

    default:

      break;
  }
}