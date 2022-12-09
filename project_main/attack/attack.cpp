#include "attack.h"

Attack::Attack(sf::Vector2f center, float damage, shared_ptr<Entity> attacker)
    : Entity{center, "sprites/swoosh.png", 'a'}, damage{damage}, attackDuration{sf::seconds(2.f)}, attacker{attacker}
{
    sprite.setTextureRect(sf::IntRect(0, 0, 30, 30));
}

bool Attack::tick(sf::Time time, World &world)
{

    for (auto &collision : world.collidesWith(*this))
    {
        if (dynamic_cast<Entity *>(collision.get()) != attacker->type && !(dynamic_cast<Block *>(collision.get())))
        {
            collision->takeDamage(damage);
        }
    }
    if (attackDuration != sf::seconds(0))
    {
        // do attack
        attackDuration -= time;
        if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f))
        {
            sprite.setTextureRect(sf::IntRect(32, 0, 30, 30));
        }
        else if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f) * 2)
        {
            sprite.setTextureRect(sf::IntRect(60, 0, 30, 30));
        }
        else if (attackDuration.asSeconds() <= (attackDuration.asSeconds() / 4.f) * 3)
        {
            sprite.setTextureRect(sf::IntRect(90, 0, 30, 30));
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
    cout << "Rendering" << endl;
}