#include "menuState.h"
#include "gameState.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

MenuState::MenuState(shared_ptr<State> resume)
    : selected(0), isEnterPressed(false), delay(sf::milliseconds(300)) {

  font.loadFromFile("state/static/font.ttf");

  string menuText{"New game"};
  if (resume) {
    if (!(resume->isGameOver())) {
      add("Resume", [resume]() { return resume; });
      bg = resume;
    } else {
      menuText = "Game over! Play again?";
    }
  }

  add(menuText, []() { return std::make_shared<GameState>(); });
  add("Exit", []() { return std::make_shared<ExitState>(); });
}

void MenuState::add(const string &text, Action action) {
  entries.push_back({sf::Text{text, font, 60}, 0.0f, action});
}

void MenuState::keyPress(sf::Keyboard::Key key) {
  switch (key) {
  case sf::Keyboard::S:
  case sf::Keyboard::Down:
    if (selected + 1 < entries.size()) {
      selected++;
    }
    break;
  case sf::Keyboard::W:
  case sf::Keyboard::Up:
    if (selected > 0) {
      selected--;
    }
    break;

  case sf::Keyboard::Return:
    isEnterPressed = true;
    break;

  default:
    break;
  }
}

shared_ptr<State> MenuState::tick(sf::Time time, sf::RenderWindow &) {
  float diff{float(time.asMicroseconds()) / float(delay.asMicroseconds())};

  for (size_t i{0}; i < entries.size(); ++i) {
    Entry &e{entries[i]};

    if (i == selected) {
      e.state += diff;
      if (e.state > 1.0f) {
        e.state = 1.0f;
      }
    } else {
      e.state -= diff;
      if (e.state < 0.0f) {
        e.state = 0.0f;
      }
    }
  }

  if (isEnterPressed) {
    return entries[selected].action();
  } else {
    return nullptr;
  }
}

void MenuState::render(sf::RenderWindow &drawTo) {
  if (bg) {
    bg->render(drawTo);
  }
  float y{100};
  auto windowSize{drawTo.getSize()};

  for (Entry &e : entries) {
    sf::FloatRect bounds{e.text.getLocalBounds()};
    e.text.setPosition((windowSize.x - bounds.width) / 2, y);
    y += bounds.height * 2.0f;

    int state = static_cast<int>(255 * e.state);
    e.text.setFillColor(sf::Color(state, state, 100));
    drawTo.draw(e.text);
  }
}
