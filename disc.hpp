#include "TOH.hpp"

class disc
{
    
  

    int pegnum;
    sf::Vector2f scale;
    sf::RectangleShape rect;
    sf::Sprite sprite;
    sf::Texture texture;
    
    public:
      
      sf::Vector2f size;
    static float speed;
    sf::Vector2f position;
    disc(){};
    void Create(sf::Vector2f pos,sf::Vector2f siz);
    void draw(sf::RenderWindow& window);
    void move(sf::Vector2f pos);
    ~disc(){};

};