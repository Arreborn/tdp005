#include "common.h"
#include "state/menuState.h"

const size_t width = 1024;
const size_t height = 768;

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Hello Warrior!"};
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);

	State::run(window, std::make_shared<MenuState>(nullptr));

    return 0;
}