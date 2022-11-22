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

// this function returns the direction the object should move
sf::Vector2f direction() {
  sf::Vector2f direction;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
    direction.y -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
  direction.y += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
  direction.x -= 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
  direction.x += 1;
  }
  return normalize(direction);
}



int main() {

  // windows in SFML are handled like instances of a class, where this is the first instance of said class
  sf::RenderWindow window{sf::VideoMode(1024, 768), "Hello World!"};

  // keeps window open for five seconds
  // sf::sleep(sf::seconds(5));

  bool is_running{true};
  sf::Event event;
  sf::CircleShape circle{40};
  circle.setPosition(sf::Vector2f{300, 300});

  //runs a continuous loop
  while (window.waitEvent(event)) {
    // checks the event types
    switch (event.type) {
    case sf::Event::Closed:
      is_running = false;
      break;
      
    default:
      break;
    }


    // draws the stored shape in the position noted in the circle object
    window.draw(circle);
    window.display();
      
    if (!is_running) { break; }
  }

  
  return 0;
}