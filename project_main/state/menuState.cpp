#include "menuState.h"
#include "gameState.h"

MenuState::MenuState(shared_ptr<State> resume) 
  : selected(0), isEnterPressed(false), delay(sf::milliseconds(300)) {
  
  font.loadFromFile("state/static/font.ttf");

  if (resume) {
    add("Resume", [resume]() { return resume; });
    bg = resume;
  }

  add("New game", []() { return std::make_shared<GameState>(); });
  add("Exit", []() { return std::make_shared<ExitState>(); });

}

void MenuState::add(const string &text, Action action){
  entries.push_back({ sf::Text{text, font, 60}, 0.0f, action });
}

void MenuState::keyPress(sf::Keyboard::Key key){
  switch (key) {
  case sf::Keyboard::S:
    if (selected + 1 < entries.size()){
      selected++;
    }
    break;
  case sf::Keyboard::W:
    if (selected > 0){
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

shared_ptr<State> MenuState::tick(sf::Time time) {
  float diff{float(time.asMicroseconds()) / float(delay.asMicroseconds())};

  for (size_t i{0}; i < entries.size(); ++i){
    Entry &e{entries[i]};

    if (i == selected) {
      e.state += diff;
      if (e.state > 1.0f){
        e.state = 1.0f;
      }
    } else {
      e.state -= diff;
      if (e.state < 0.0f){
        e.state = 0.0f;
      }
    }
  }

  if (isEnterPressed){
    return entries[selected].action();
  } else {
    return nullptr;
  }
}

void MenuState::render(sf::RenderWindow &drawTo){
  if (bg){
    bg->render(drawTo);
  }

  float y{100};
  auto windowSize{drawTo.getSize()};

  for (auto &e : entries) {
    auto bounds{e.text.getLocalBounds()};
    e.text.setPosition((windowSize.x - bounds.width) / 2, y);
    y += bounds.height * 2.0f;

    int state = static_cast<int>(255 * e.state);
    e.text.setFillColor(sf::Color(state, 255, state));
    drawTo.draw(e.text);
  }
}