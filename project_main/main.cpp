#include "common.h"
#include "state/menuState.h"

const size_t width = 1280;
const size_t height = 800;

int main() {
  sf::RenderWindow *window =
      new sf::RenderWindow{sf::VideoMode{width, height}, "Duck Souls 3"};

  window->setKeyRepeatEnabled(false);
  window->setVerticalSyncEnabled(true);

  State::run(*window, std::make_shared<MenuState>(nullptr));

  delete window;

  return 0;
}