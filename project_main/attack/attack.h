#include "../common.h"
#include "../entity/entity.h"
#include "../hostile/hostile.h"
#include "../staticEntity/block.h"
#include "../player/player.h"
#include "../world.h"
#include <SFML/Graphics.hpp>

class Attack : public Entity
{
public:
    Attack(sf::Vector2f center, float const damage, shared_ptr<Entity> attacker);

    bool tick(sf::Time time, World &world) override;
    void render(sf::RenderWindow &window) override;

protected:
    float damage{};
    sf::Time attackDuration{};
    Entity* thisAttacker{};
};