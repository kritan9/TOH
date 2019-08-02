#include "disc.hpp"
#include "TOH.hpp"

float disc::speed =2.0f;
float disc::scale=1.0f;

void disc::Create( sf::Vector2f pos,sf::Vector2f siz,int i)
{   //texture.loadFromFile("");
    font.loadFromFile("ariali.ttf");
    num.setFont(font);
    std::string a;
    position=pos; size=scale * siz; 
    num.setCharacterSize(15*scale);
    num.setOrigin(sf::Vector2f(7.0f*scale,10.0f*scale));
    num.setPosition(pos);
    rect.setSize(size);
    rect.setOrigin(sf::Vector2f(size.x*0.5,size.y*0.5));
    rect.setPosition(position);
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineThickness(2*scale);
    rect.setOutlineColor(sf::Color(255,255,255));
    ss.clear();
    ss<<i;
    ss>>a;
    num.setString(a);
}
void disc::draw(sf::RenderWindow& window)
{
    window.draw(rect);
    window.draw(num);
}

void disc::move(sf::Vector2f pos)
{
    position+= pos;
    rect.setPosition(position);
    num.setPosition(position);
    
}

void disc::changeScale(float sc)
{
      size=(sc/scale)*size;
      scale=sc;
      rect.setOrigin(sf::Vector2f(size.x*0.5,size.y*0.5));
    rect.setPosition(position);
    rect.setOutlineThickness(3*scale);
 }