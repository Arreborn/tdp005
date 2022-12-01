#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Network.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <cmath>

int main() {

  // windows in SFML are handled like instances of a class, where this is the first instance of said class
  sf::RenderWindow window{sf::VideoMode(1280, 800), "Hello World!"};

  // keeps window open for five seconds
  // sf::sleep(sf::seconds(5));

  bool is_running{true};
  sf::Event event;
  sf::CircleShape circle{40};
  circle.setPosition(sf::Vector2f{300, 300});
  sf::Clock clock;

  //runs a continuous loop
  while (window.waitEvent(event)) {
    // checks the event types
    switch (event.type) {
    // closes program is the window is closed
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