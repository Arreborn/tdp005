#include <SFML/Graphics/Color.hpp>
#include "state.h"
#include "../sprites/spriteManager.h"
#include "menuState.h"


State::State() {} 

State::~State() {}

void State::keyPress(sf::Keyboard::Key) {}

void State::keyRelease(sf::Keyboard::Key) {}

void State::run(sf::RenderWindow &window, shared_ptr<State> state) {
  sf::Clock clock;
  // sf::View view{sf::Vector2f(300.0f,175.0f),sf::Vector2f(640.0f,400.0f)};

  while (state) {
    sf::Event event{};
    while (window.pollEvent(event)) {
      switch (event.type) {
      case sf::Event::Closed:
        return;
      case sf::Event::KeyPressed:
        state->keyPress(event.key.code);
        break;
      case sf::Event::KeyReleased:
        state->keyRelease(event.key.code);
        break;
      default:
        break;
      }
    }

    window.clear(sf::Color::Cyan);
    if (auto new_state = state->tick(clock.restart())) {
      if (std::dynamic_pointer_cast<ExitState>(new_state)) {
        return;
      } else {
        window.clear();
        state = new_state;
      }
      continue;
    }
    state->render(window);
    window.display();
    // window.setView(view);
    // view.setCenter(sf::Vector2f(600.0f, 600.0f));
  }
}