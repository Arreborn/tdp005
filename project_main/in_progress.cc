#include "common.h"

const size_t width = 1280;
const size_t height = 800;

int main() {
    sf::RenderWindow window{sf::VideoMode{width, height}, "Gaming Mode: Enbled"};
    window.setKeyRepeatEnabled(false);
    window.setVerticalSyncEnabled(true);
    bool is_running{true};

    sf::Event event{};
    while(window.waitEvent(event)){

      switch (event.type){
        case sf::Event::Closed:
          is_running = false;
          break;
          
        default:
          break;

      }

      if (!is_running) { break; }
    }

    return 0;
}
