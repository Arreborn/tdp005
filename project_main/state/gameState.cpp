#include "gameState.h"

void updateHud(std::shared_ptr<Player> player, sf::Sprite &hpBar);

GameState::GameState() {
  // Loading textures
  loadTextures();
  // Creating objects
  player = std::make_shared<Player>(
      sf::Vector2f(1100, 1100)); // these coordinates are set to ensure the
                                 // player starts at the left
  world.add(player);             // adds the player object into the game world
  world.getLevel(true, player);  // generates a first level
}

shared_ptr<State> GameState::tick(sf::Time time, sf::RenderWindow &window) {

  updateHud(player, hpBar);

  gameOver = !player->isAlive();

  // zooms camera when in gamestate
  view.setCenter(world.getCenter());
  view.setSize(640.0f, 400.0f);
  sf::Vector2f hpPos{world.getCenter()};
  hpBarBackground.setPosition(hpPos.x - 150, hpPos.y - 150);
  hpBar.setPosition(hpPos.x - 150, hpPos.y - 162);
  world.tick(time);

  //
  // resets viewport
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    view.setCenter(640.0f, 400.0f);
    view.setSize(1280.0, 800.0);
    hpBar.setPosition(2000, 2000);
    hpBarBackground.setPosition(2000, 2000);
    return std::make_shared<MenuState>(shared_from_this());
  }

  if (world.levelCleared() && player->hittingBorder()) {
    if (world.victory()) {
      victory = true;
      view.setCenter(640.0f, 400.0f);
      view.setSize(1280.0, 800.0);
      window.setView(view);
      return std::make_shared<MenuState>(shared_from_this());
    }
    world.getLevel((player->getCenter().x > 640), player);
  }

  if (gameOver) {
    // resets viewport
    view.setCenter(640.0f, 400.0f);
    view.setSize(1280.0, 800.0);
    window.setView(view);
    return std::make_shared<MenuState>(shared_from_this());
  } else {
    return nullptr;
  }
}

void GameState::loadTextures() {
  // Texture loading
  sf::Texture *hpText = SpriteManager::get("sprites/Healthbar.png");
  sf::Texture *hpBg = SpriteManager::get("sprites/uiBackground.png");
  sf::Texture *bg = SpriteManager::get("sprites/bg.png");
  sf::Texture *bgT = SpriteManager::get("sprites/bgTrees.png");
  sf::Texture *bgF = SpriteManager::get("sprites/bgForeground.png");
  sf::Texture *bgL = SpriteManager::get("sprites/bgLights.png");
  // Texture assignment
  hpBar.setTexture(*hpText);
  hpBarBackground.setTexture(*hpBg);
  bgBack.setTexture(*bg);
  bgTree.setTexture(*bgT);
  bgFore.setTexture(*bgF);
  bgLights.setTexture(*bgL);
  auto size = hpText->getSize();
  auto sizeBg = hpBg->getSize();
  hpBar.setOrigin(size.x, size.y);
  hpBarBackground.setOrigin(sizeBg.x, sizeBg.y);

  // Setting default positions and scaling
  hpBar.setScale(2.0f, 2.0f);
  hpBarBackground.setScale(2.0f, 2.0f);
  hpBar.setPosition(sf::Vector2f(
      240.0f,
      268.0f)); // Background and foreground should differ 12 pixels in y
  hpBarBackground.setPosition(sf::Vector2f(240.0f, 280.0f));
  // Background
  bgBack.setScale(5.0f, 5.0f);
  bgBack.setPosition(sf::Vector2f(0.0f, 0.0f));
  bgTree.setScale(5.0f, 5.0f);
  bgTree.setPosition(sf::Vector2f(0.0f, 0.0f));
  bgLights.setScale(3.0f, 3.0f);
  bgLights.setPosition(sf::Vector2f(400.0f, 0.0f));
  bgFore.setScale(5.0f, 5.0f);
  bgFore.setPosition(sf::Vector2f(0.0f, 0.0f));
}

void GameState::render(sf::RenderWindow &drawTo) {
  drawTo.draw(bgBack);
  drawTo.draw(bgLights);
  drawTo.draw(bgTree);
  drawTo.draw(bgFore);
  world.render(drawTo);
  drawTo.setView(view);
  drawTo.draw(hpBarBackground);
  drawTo.draw(hpBar);
};

void updateHud(shared_ptr<Player> player, sf::Sprite &hpBar) {
  int currFrame{};
  if (player->getHealth() % 2 == 0) {
    currFrame =
        ((player->getHealth() / 2) * 9 + ((player->getHealth() / 2)) * 3);
    hpBar.setTextureRect(sf::IntRect(0, 0, currFrame, 8));
  } else {
    currFrame = ((player->getHealth() - 1) / 2) * 9 + 5 +
                (((player->getHealth() + 1) / 2) - 1) * 3;
    hpBar.setTextureRect(sf::IntRect(0, 0, currFrame, 8));
  }
}