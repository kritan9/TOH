
#include "DiscInput.h"
#include "TOH.hpp"


DiscInput::DiscInput()
{
	nameEntered.setFont(TOH::font);
	nameEntered.setCharacterSize(25.0f);
	nameEntered.setPosition(sf::Vector2f(450.0f+20.0f,300.0f+56.0f));
	flag = 0;
}
int DiscInput::setNumber(int &a)
{
	int temp;
	std::stringstream ss;
	ss<<name;
	ss>>temp;
	if(temp>0 && temp<=MAX)
	{
		a=temp;
		return 1;
	}
	else return 0;
}
void DiscInput::Draw(sf::RenderWindow& window)
{
	window.draw(nameEntered);
}
int DiscInput::Update(sf::RenderWindow& window)
{
	while(window.pollEvent(TOH::event))
	{
		if(TOH::event.type == sf::Event::Closed) { TOH::state=TOH::Close; break;}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			return 1;
		}
	
		if (TOH::event.type == sf::Event::TextEntered )
		{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
		{
			name.pop_back();flag=1;
		}
		else
		name += static_cast<char>(TOH::event.text.unicode);
		}
		else if (TOH::event.type == sf::Event::KeyReleased)
		{
			flag = 0;
		}
		
	}
	   
	nameEntered.setString(name.c_str());
	return 0;
}


