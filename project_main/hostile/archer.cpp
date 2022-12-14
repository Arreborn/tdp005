#include "archer.h"
#include "../staticEntity/block.h"
#include "../world.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

Archer::Archer(sf::Vector2f center) : Hostile(center) {
  type = 'a';
  health = 60;
  speed = 6.0;
  sprite.setTextureRect(sf::IntRect(32, 0, 16, 16));
  sprite.setOrigin(0, 0);
}

bool Archer::tick(sf::Time time, World &world) {
  return Hostile::tick(time, world);
}

void Archer::render(sf::RenderWindow &drawTo) { Hostile::render(drawTo); }

void Archer::verticalPosition() { cout << "slide to the left" << endl; }

void Archer::horizontalPosition(sf::Time const &, World &) {
  cout << "slide to the right" << endl;
}

void Archer::attack() { cout << "pew" << endl; }
