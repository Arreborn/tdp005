#include "attack.h"

Attack::Attack(sf::Vector2f center, float damage, Entity *attacker)
    : Entity{center, "sprites/swoosh.png", 'a'}, damage{damage}, attackDuration{sf::seconds(2.f)}, attacker{attacker}
{
    sprite.setTextureRect(sf::IntRect(0, 0, 28, 28));
}

bool Attack::tick(sf::Time time, World &world)
{

    for (auto &collision : world.collidesWith(*this))
    {
        if (dynamic_cast<Entity *>(collision.get())->getType() != attacker->getType() && !(dynamic_cast<Block *>(collision.get())))
        {
            collision->takeDamage(damage);
            if (!isAlive())
            {
                // Remove entity
            }
        }
    }
    if (attackDuration != sf::seconds(0))
    {
        // do attack
        attackDuration -= time;
        if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f))
        {
            sprite.setTextureRect(sf::IntRect(32, 0, 28, 28));
        }
        else if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f) * 2)
        {
            sprite.setTextureRect(sf::IntRect(60, 0, 28, 28));
        }
        else if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f) * 3)
        {
            sprite.setTextureRect(sf::IntRect(90, 0, 28, 28));
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Attack::render(sf::RenderWindow &render)
{
    Entity::render(render);
}

void Attack::takeDamage(float)
{
    cout << "Collided with itself" << endl;
}