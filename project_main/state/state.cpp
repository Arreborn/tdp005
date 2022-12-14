#include "state.h"
#include "../sprites/spriteManager.h"
#include "menuState.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

State::State() {}

State::~State() {}

void State::keyPress(sf::Keyboard::Key) {}

void State::keyRelease(sf::Keyboard::Key) {}

void State::run(sf::RenderWindow &window, shared_ptr<State> state) {
  sf::Clock clock;

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

    window.clear(sf::Color::Black);
    if (shared_ptr<State> new_state = state->tick(clock.restart(), window)) {
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
    // view.setCenter(sf::Vector2f(520.0f, 400.0f));
  }
}

bool State::isGameOver() { return gameOver; }

shared_ptr<State> ExitState::tick(sf::Time, sf::RenderWindow &) {
  return nullptr;
}