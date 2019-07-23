#include "disc.hpp"

float disc::speed =1.0f;

void disc::Create( sf::Vector2f pos,sf::Vector2f siz)
{   //texture.loadFromFile("");
    
    position=pos; size=siz; 
    rect.setSize(size);
    rect.setOrigin(sf::Vector2f(size.x*0.5,size.y*0.5));
    rect.setPosition(position);
    rect.setFillColor(sf::Color::Blue);
    rect.setOutlineThickness(3);
    rect.setOutlineColor(sf::Color(255,255,255));
}
void disc::draw(sf::RenderWindow& window)
{
    window.draw(rect);
}

void disc::move(sf::Vector2f pos)
{
    position+= pos;
    rect.setPosition(position);
    
}