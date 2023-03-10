#pragma once
#include "gameState.h"
#include "state.h"
#include <functional>

/**
 * @brief This state handles menu inputs, whether for the main menu, pause menu
 * or if the game is over in any way.
 *
 */
class MenuState : public State {
public:
  /**
   * @brief Creates the state, if 'resume' is set the menu will show a
   * "resume"-option to return to that state.
   *
   */
  MenuState(shared_ptr<State> resume = nullptr);

  /**
   * @brief Handles key-presses.
   *
   * @param key
   */
  void keyPress(sf::Keyboard::Key key) override;

  /**
   * @brief Tick-function override.
   *
   * @param time
   * @return shared_ptr<State>
   */
  shared_ptr<State> tick(sf::Time time, sf::RenderWindow &window) override;

  /**
   * @brief Render-function override.
   *
   * @param drawTo
   */
  void render(sf::RenderWindow &drawTo) override;

private:
  /**
   * @brief Decides what to do when an item is selected.
   *
   */
  using Action = std::function<shared_ptr<State>()>;

  struct Entry {
    /**
     * @brief What text to draw.
     *
     */
    sf::Text text;

    /**
     * @brief Determines the color depending on selection state. 0 - 1.
     *
     */
    float state;

    /**
     * @brief Action to perform when entry is selected.
     *
     */
    Action action;

    /**
     * @brief Destroy the Entry object.
     *
     */
    ~Entry() = default;
  };

  /**
   * @brief Decides font to use for menu selection.
   *
   */
  sf::Font font;

  /**
   * @brief Container for all meny entries.
   *
   */
  vector<Entry> entries;

  /**
   * @brief Which item is currently selected?
   *
   */
  size_t selected;

  /**
   * @brief State of the enter key being pressed.
   *
   */
  bool isEnterPressed;

  /**
   * @brief Decides animation delay.
   *
   */
  sf::Time delay;

  /**
   * @brief What state to use as a background, if any.
   *
   */
  shared_ptr<State> bg;

  sf::Sprite background;

  /**
   * @brief Helper to add an element.
   *
   */
  void add(const string &text, Action action);
};