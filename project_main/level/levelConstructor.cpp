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
  file.open("segments/seg1.txt"); // temporary until segment manager works
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
    case 'B': case 'b': //Top block
       world.add(std::make_shared<Block>(sf::Vector2f(x, y),sf::IntRect(16,0,16,16)));
       break;
    case 'F':case 'f': //Bottom right corner block
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(32,32,16,16)));
      break;
    case 'O':case 'o': // Bottom left corner block
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(0,32,16,16)));
      break;
    case 'R':case 'r': // Top right corner block
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(16,0,16,16)));
      break;
    case 'L':case 'l': // Top left corner block
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(0,0,16,16)));
      break;
    case 'E':case 'e': // Side block right
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(32,16,16,16)));
      break;
    case 'K':case 'k': // Side block left
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(0,16,16,16)));
      break;
    case 'D':case 'd': // Bottom block ground
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(16,32,16,16)));
      break;
    case 'G':case 'g':
      world.add(std::make_shared<Block>(sf::Vector2f(x,y), sf::IntRect(16,16,16,16)));
      break;
    default:
      break;
  }
}