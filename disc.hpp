#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class disc
{
  sf::Font font;
    int pegnum;
    sf::Vector2f _scale;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Texture texture;
    std::stringstream ss;
    sf::Text num;
    
    public:
      
    sf::Vector2f size;
    static float speed;
    static float scale;
    sf::Vector2f position;
    disc(){};
    void Create(sf::Vector2f pos,sf::Vector2f siz,int);
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f pos);
    void changeScale(float sc);
    void setPos()
    {
      rect.setPosition(position);
      num.setPosition(position);
    }
    ~disc(){};

};