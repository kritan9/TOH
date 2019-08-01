
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class DiscInput 
{
	int flag;
	sf::Text nameEntered;
public:
	DiscInput();
	~DiscInput(){};
	std::string name;
	void Draw(sf::RenderWindow &);
	int Update(sf::RenderWindow &);
	int setNumber(int &a);
	void Clear()
	{
		name="";
	}
};

