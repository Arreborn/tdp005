#pragma once
#include "../common.h"
#include "hostile.h"
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

class Flying : public Hostile
{
public:
    Flying(sf::Vector2f center);
    bool tick(sf::Time time, World &world) override;
    void render(sf::RenderWindow &drawto) override;

    void verticalPosition(sf::Time const &time, World &world) override;
    void horizontalPosition(sf::Time const &time, World &world) override;
    void attack(World &world) override;

protected:
    int health{};

    float speed{};

    sf::Vector2f acceleration{0, 2};

    /**
     * @brief When taking damage, the hostile will turn red momentarily. This
     * variable stores the current color.
     *
     */
    sf::Time blinkDuration{};
    sf::Time movementDuration{};
};