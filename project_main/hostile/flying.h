#pragma once
#include "../common.h"
#include "hostile.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Flying : public Hostile {
public:
  Flying(sf::Vector2f center);
  void verticalPosition(sf::Time const &time, World &world) override;
  void horizontalPosition(sf::Time const &time, World &world) override;
  void attack(World &world) override;

private:
  bool canAttack{false};
};