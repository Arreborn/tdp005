#include "menuState.h"
#include "gameState.h"

MenuState::MenuState(shared_ptr<State> resume) 
  : selected(0), isEnterPressed(false), delay(sf::milliseconds(300)) {
  
  font.loadFromFile("static/font.ttf");

  if (resume) {
    add("Resume", [resume]() { return resume; });
    bg = resume;
  }

  add("New game", []() { return std::make_shared<GameState>(); });
}