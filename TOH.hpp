
#include <iostream>
#include <sstream>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#define WIDTH 1366
#define HEIGHT 768
#define MAX 100

struct TOH
{
    static int pause;
    enum ProgramState {Menu,DiscInp,ScaleInput,Solve,Finish,Close};
    static ProgramState state;
    static sf::Font font ;
    static sf::Event event;
    static float offset;
    static int steps;
    sf::Texture _left;
    sf::Texture _right;
    sf::Texture _bg;
    sf::Texture _button;
    sf::Texture _button2;
    sf::Texture _number;
    sf::Sprite left;
    sf::Sprite right;
    sf::Sprite bg;
    sf::Sprite but1;
    sf::Sprite but2;
    sf::Sprite number;
    sf::Text speed;
    sf::Text Steps;
    sf::Text s;
    std::string a;
    std::stringstream abc;
    sf::Texture _pole;
    sf::Sprite pole[3];
    sf::Text mainMenu;
    sf::Text solve;
    sf::Text inputDisk;
    sf::Texture _playing;
    sf::Texture _paused;
    sf::Sprite playing;
    sf::Sprite paused;
   TOH()
   {
       _playing.loadFromFile("Images/playing.png");
       _paused.loadFromFile("Images/paused.png");
        paused.setTexture(_paused);
        playing.setTexture(_playing);
        paused.setScale(sf::Vector2f(40.0f/_paused.getSize().x,40.0f/_paused.getSize().y));
        playing.setScale(sf::Vector2f(40.0f/_playing.getSize().x,40.0f/_playing.getSize().y));
        paused.setPosition(sf::Vector2f(WIDTH-50.0f,10.0f));
        playing.setPosition(sf::Vector2f(WIDTH-50.0f,10.0f));
       _pole.loadFromFile("Images/pole.png");
       for(int i=0;i<3;i++)
       { 
           pole[i].setTexture(_pole);
           pole[i].setOrigin(sf::Vector2f(_pole.getSize().x/2.0f,0.0f));
       }
       _number.loadFromFile("Images/number.png");
       _left.loadFromFile("Images/left.png");
       _right.loadFromFile("Images/right.png");
       _bg.loadFromFile("Images/bg.png");
       _button.loadFromFile("Images/button.png");
       _button2.loadFromFile("Images/button2.png");
       number.setTexture(_number);
       number.setPosition(sf::Vector2f(450.0f,300.0f));
       bg.setTexture(_bg);
       left.setTexture(_left);
       right.setTexture(_right);
       left.setPosition(sf::Vector2f(500.0f,20.0f));
       right.setPosition(sf::Vector2f(750.0f,20.0f));
       but1.setTexture(_button); but2.setTexture(_button);
       but1.setPosition(sf::Vector2f(200.0f,680.0f));but2.setPosition(sf::Vector2f(900.0f,680.0f));
       bg.setScale(sf::Vector2f(float(WIDTH)/_bg.getSize().x,float(HEIGHT)/_bg.getSize().y));
       speed.setFont(font);
       speed.setPosition(600.0f,20.0f);
       speed.setCharacterSize(50.0f);
       Steps.setFont(font);
       Steps.setCharacterSize(50.0f);
       Steps.setPosition(900.0f,700.0f);
       Steps.setOutlineThickness(10.0f);
       s.setFont(font);
       s.setString(std::string("Speed:"));
       s.setPosition(sf::Vector2f(600.0f,0.0f));
       mainMenu.setFont(font); inputDisk.setFont(font); solve.setFont(font);
       mainMenu.setOutlineThickness(1.0f); inputDisk.setOutlineThickness(1.0f); solve.setOutlineThickness(1.0f);
       mainMenu.setString("Main Menu"); inputDisk.setString("Number Of Discs"); solve.setString("Solve");
       mainMenu.setPosition(258.0f,695.0f); inputDisk.setPosition(215.0f,695.0f); solve.setPosition(1000.0f,695.0f);
       mainMenu.setColor(sf::Color::Black);inputDisk.setColor(sf::Color::Black); solve.setColor(sf::Color::Black);
       
   }
   void speedAdjust(float b)
   { 
       a.clear(); abc.clear();
       b=static_cast<int>(b*10)*0.1f;
       abc<<b;
       abc>>a;
       a.push_back('x');
       speed.setString(a);
       
   }
   void stepsDraw(sf::RenderWindow& win)
   {
       a.clear(); abc.clear();
       abc<<steps;
       abc>>a;
        a="Step : "+a;
        Steps.setString(a);
        win.draw(Steps);
        if(pause==0)
        {
            win.draw(playing);
        }
        else win.draw(paused);
   }
   void drawPole(sf::RenderWindow& win)
   {
       for(int i=0;i<3;i++) win.draw(pole[i]);
   }
   void adjustPole(float height,float scale)
   {
        for(int i=0;i<3;i++)
        {
            pole[i].setPosition(WIDTH*(i+1)/4.0f,height);
            pole[i].setScale(sf::Vector2f(scale,(HEIGHT-height-offset+10.0f)/_pole.getSize().y));
        }

   }
   void drawString(int a,sf::RenderWindow& win)
   {
       if(a==1)
       {
           win.draw(solve); win.draw(inputDisk);
       }
       if(a==2)
       {
           win.draw(mainMenu); 
       }
   }

};


