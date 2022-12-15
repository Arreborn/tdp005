#include "levelConstructor.h"
#include "segmentManager.h"
#include <fstream>
#include <memory>

vector<string> LevelConstructor::loadLevels(int numberOfLevels)
{
  vector<string> loaded{};
  for (int i{}; i < numberOfLevels; ++i)
  {
    loaded.push_back(SegmentManager::get());
  }
  return loaded;
}

string LevelConstructor::generateLevel(World &world, shared_ptr<Player> player,
                                       bool loadHostiles, string str)
{
  str = str.substr(1, str.size() - 2);
  cout << str << endl;
  std::ifstream file{};
  file.open(str);
  string segment{};
  string temp{};
  bool playerSet{false};

  while (getline(file, temp))
  {
    segment += temp;
  }

  int x{};
  int y{};

  for (string::size_type i{}; i < segment.length(); i++)
  {
    if (segment[i] != '.')
    {
      selector(segment[i], x, y, world, player, playerSet, loadHostiles);
    }

    x += 16;
    if (x == 1280)
    {
      x = 0;
      y += 16;
    }
  }
  return segment;
}

void LevelConstructor::selector(char a, int x, int y, World &world,
                                shared_ptr<Player> player, bool &playerSet,
                                bool const loadHostiles)
{
  switch (a)
  {
  /* Diverse blocks */
  case 'B': // Top block
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(16, 0, 16, 16)));
    break;
  case 'F': // Bottom right corner block
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(32, 32, 16, 16)));
    break;
  case 'O': // Bottom left corner block
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(0, 32, 16, 16)));
    break;
  case 'R': // Top right corner block
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(32, 0, 16, 16)));
    break;
  case 'L': // Top left corner block
    world.add(
        std::make_shared<Block>(sf::Vector2f(x, y), sf::IntRect(0, 0, 16, 16)));
    break;
  case 'E': // Side block right
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(32, 16, 16, 16)));
    break;
  case 'K': // Side block left
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(0, 16, 16, 16)));
    break;
  case 'D': // Bottom block ground
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(16, 32, 16, 16)));
    break;
  case 'G': // Ground block
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(16, 16, 16, 16)));
    break;
  case 'H': // Top left inside corner
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(48, 0, 16, 16)));
    break;
  case 'J': // Top right inside corner
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(64, 0, 16, 16)));
    break;
  case 'N': // Bottom left inside corner
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(48, 16, 16, 16)));
    break;
  case 'M': //  Bottom right inside corner
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(64, 16, 16, 16)));
    break;
  case 'T': // A tree place 3 blocks above ground in txt file
    world.add(std::make_shared<Block>(sf::Vector2f(x, y),
                                      sf::IntRect(0, 64, 48, 48)));
    break;

  /* Enemies */
  case 'h':
    if (loadHostiles)
    {
      world.add(std::make_shared<Hostile>(sf::Vector2f(x, y)));
      world.addEnemy();
    }
    break;

  case 'a':
    if (loadHostiles)
    {
      world.add(std::make_shared<Archer>(sf::Vector2f(x, y)));
      world.addEnemy();
    }
    break;
  case 'f':
    world.add(std::make_shared<Flying>(sf::Vector2f(x, y)));
    world.addEnemy();
    break;

  /* Player spawning */
  case 'l':
    if (player->getCenter().x > 640 && !playerSet)
    {
      playerSet = true;
      player->set(x, y);
    }
    break;

  case 'r':
    if (player->getCenter().x < 640 && !playerSet)
    {
      playerSet = true;
      player->set(x, y);
    }
    break;

  default:
    break;
  }
}