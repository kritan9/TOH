
#include "TOH.hpp"
#include "disc.hpp"
#include "DiscInput.h"
using namespace std;

int TOH::pause = 0;
int threadTerminate=0;
float TOH::offset=150.0f;
bool mouseIntersect(sf::Sprite& sp,sf::RenderWindow& window,sf::Vector2u size);
struct pThread //parameters for the thread function to solve TOH
{
int *finish;
 disc* d;float& height;int *peg;int &n;int src;int dest;int aux;
pThread ( disc *di,float &heigh,int *pe,int &nu,int sr,int des,int au,int *fin):
d(di),height(heigh),peg(pe),n(nu),src(sr),dest(des),aux(au),finish(fin)
{
}
};
struct dThread//parameters for display thread
{
    int *finish;
    disc *d;int &num;
    dThread(disc *di,int &n,int *fin):d(di),num(n),finish(fin){}
};
void threadToh(pThread& x);//thread Function to solve TOH
void initialDisplayThread(dThread&);
void DiscUpdate(disc* d,int discNum,int srcPeg,int destPeg,float height,int *peg);//peg numbers are 1,2,3
void solveTOH(disc* d,float height,int *peg,int n,int src,int dest,int aux);

int TOH::steps=0;
sf::Event TOH::event;
sf::Font TOH::font;
TOH::ProgramState TOH::state=TOH::ProgramState::Menu;

int main()
{
    TOH::font.loadFromFile("ariali.ttf");
    TOH toh;
    DiscInput di;
    int mouseFlag[5]={0,0,0,0,0};
    int init=0;
    int *finish =new int(0);
    int *finish1=new int(0);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tower Of Hanoi");
    int numOfDisk=0;
    disc disk[MAX];
    float heightOfPole;
    int peg[3]={numOfDisk,0,0};
    pThread _temp(disk,heightOfPole,peg,numOfDisk,1,3,2,finish1);
    dThread _temp2(disk,numOfDisk,finish);
    sf::Thread thread(&threadToh,_temp);
    sf::Thread thread2(&initialDisplayThread,_temp2);
    toh.adjustPole(200.0f,1.0f) ;
    
    while (window.isOpen())
    {
        switch(TOH::state)
        {
            case TOH::Solve:
            {   
            if(init == 0)
            {
                toh.speedAdjust(disc::speed);
                threadTerminate=0;
                toh.but1.setTexture(toh._button);
                toh.but2.setTexture(toh._button);
                for(int i=numOfDisk-1;i>=0;i--)
                {
                    disk[i].Create(sf::Vector2f(WIDTH*1.0f/4.0f,HEIGHT-TOH::offset-(numOfDisk-1-i)*disc::scale*20.0f),sf::Vector2f(40.0f+20*i,20.0f),i+1);
                }
                peg[0]=numOfDisk;
                peg[1]=peg[2]=0;
               thread.launch();
                init =1;
            }
                while(window.pollEvent(TOH::event))
                {
                    if (TOH::event.type == sf::Event::Closed)
                    {
                        TOH::state=TOH::ProgramState::Close;
                    }
                    if (TOH::event.type == sf::Event::TextEntered )
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        TOH::pause=(TOH::pause+1)%2; 
                    }
                }

                if(mouseIntersect(toh.right,window,toh._right.getSize()))
                {
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                {
                    if(disc::speed < /* numOfDisk*10.0f/3.0f*/250.0f )
                    {
                        if(disc::speed>10) disc::speed+=0.005f*disc::speed/2;
                        else disc::speed+=0.005f;
                        toh.speedAdjust(disc::speed);}
                    }
                }
                if(mouseIntersect(toh.left,window,toh._left.getSize()))
                {
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) )
                {
                    if(disc::speed>0.505f)
                    {
                        if(disc::speed>10) disc::speed-=0.005f*disc::speed/2;
                        else disc::speed-=0.005f;
                    toh.speedAdjust(disc::speed);}
                }
                }
                if(mouseIntersect(toh.but1,window,toh._button.getSize())){
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) || mouseFlag[2]==1)
                {
                    mouseFlag[2]=1;
                 if(TOH::event.type==sf::Event::MouseButtonReleased)
                {
                    toh.but1.setTexture(toh._button);
                    threadTerminate=1;
                }
                }}else{mouseFlag[2]=0;toh.but1.setTexture(toh._button);}
                
                if(mouseIntersect(toh.paused,window,sf::Vector2u(40,40))){
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) || mouseFlag[3]==1)
                {
                    mouseFlag[3]=1;
                 if(TOH::event.type==sf::Event::MouseButtonReleased)
                {
                    mouseFlag[3]=0;
                    TOH::pause=(TOH::pause+1)%2;
                }
                }}else{mouseFlag[3]=0;}

                window.clear(sf::Color::Black);
                window.draw(toh.bg);
                window.draw(toh.speed);
                window.draw(toh.s);
                toh.drawPole(window);
                for(int i=numOfDisk-1;i>=0;i--)
                {
                  disk[i].draw(window);
                }
                
                window.draw(toh.left);
                window.draw(toh.right);
                window.draw(toh.but1);
                toh.drawString(2,window);
                toh.stepsDraw(window);
                window.display();
                if(*finish1==1)
                {  
                     TOH::state=TOH::ProgramState::Finish;
                     if(threadTerminate==1) {TOH::state=TOH::ProgramState::Menu;numOfDisk=0;}
                    threadTerminate=0;
                    init =0;
                    *finish1=0;
                }
                break;
            }
            case TOH::Finish:
            {
                while(window.pollEvent(TOH::event))
                {
                    if (TOH::event.type == sf::Event::Closed)
                    {
                        TOH::state=TOH::ProgramState::Close;
                    }
                }
                if(mouseIntersect(toh.but1,window,toh._button.getSize())){
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) || mouseFlag[2]==1)
                {
                    mouseFlag[2]=1;
                 if(TOH::event.type==sf::Event::MouseButtonReleased)
                {
                    toh.but1.setTexture(toh._button);
                    { TOH::state=TOH::ProgramState::Menu; numOfDisk=0;}
                }
                }}else{mouseFlag[2]=0;toh.but1.setTexture(toh._button);}
                window.clear(sf::Color::Black);
                window.draw(toh.bg);
                toh.drawPole(window);
                for(int i=numOfDisk-1;i>=0;i--)
                {
                  disk[i].draw(window);
                }
                window.draw(toh.but1);
                toh.drawString(2,window);
                toh.stepsDraw(window);
                window.display();

                break;
            }

            case TOH::ScaleInput:
            { 
            if(init == 0)
            {
                toh.but1.setTexture(toh._button);
                toh.but2.setTexture(toh._button);
                thread2.launch();
                init =1;
            }
                window.clear(sf::Color::Black);
                window.draw(toh.bg);
                toh.drawPole(window);
                for(int i=numOfDisk-1;i>=0;i--)
                {
                  disk[i].draw(window);
                }
                window.draw(toh.but1);
                window.draw(toh.but2);
                toh.drawString(1,window);
                window.display();
                if(*finish==1)
                {
                    TOH::state=TOH::ProgramState::Menu;
                    init =0;
                    *finish=0;
                }
                 break;
            }
            case TOH::DiscInp:
            {
                if(init == 0)
            {
                disc::scale=1.0f;
                disc::speed=2.0f;
                init =1;
            }
            if(di.Update(window)==1) 
            {
                if(di.setNumber(numOfDisk)==1)
                {
                    if(20.0f*numOfDisk+20.0f>WIDTH/4.5f)
                    {
                        disc::scale =(WIDTH/4.5f)/(20.0f*numOfDisk+20.0f);
                    }
                    di.Clear();
                    heightOfPole=HEIGHT-TOH::offset-(numOfDisk-1)*disc::scale*20.0f-200.0f;
                    toh.adjustPole(heightOfPole,disc::scale);
                    TOH::state=TOH::ProgramState::ScaleInput;
                    init=0;
                }
            }
            window.clear(sf::Color::Black);
            window.draw(toh.bg);
            toh.drawPole(window);
            for(int i=numOfDisk-1;i>=0;i--) disk[i].draw(window);
            window.draw(toh.number);
            di.Draw(window);
            window.draw(toh.but1);window.draw(toh.but2);
            toh.drawString(1,window);
            window.display();
            break;
            }
            case TOH::Menu:
            {
                 if(init == 0)
            {
                 TOH::pause=0;
                TOH::steps=0;
                toh.but1.setTexture(toh._button);
                toh.but2.setTexture(toh._button);
                init =1;
            }
                while(window.pollEvent(TOH::event))
                {
                    if (TOH::event.type == sf::Event::Closed)
                    {
                        TOH::state=TOH::ProgramState::Close;
                    }
                }
                if(mouseIntersect(toh.but1,window,toh._button.getSize()))
                {
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) || mouseFlag[0]==1)
                {
                    toh.but1.setTexture(toh._button2);
                    mouseFlag[0]=1;
                 if(TOH::event.type==sf::Event::MouseButtonReleased)
                {
                    toh.but1.setTexture(toh._button);
                    TOH::state = TOH::ProgramState::DiscInp;
                }
                }}else{mouseFlag[0]=0;toh.but1.setTexture(toh._button);}

                if(mouseIntersect(toh.but2,window,toh._button.getSize())){
                if( sf::Mouse::isButtonPressed(sf::Mouse::Left) || mouseFlag[1]==1)
                {
                    toh.but2.setTexture(toh._button2);
                    mouseFlag[1]=1;
                 if(TOH::event.type==sf::Event::MouseButtonReleased)
                {
                    toh.but2.setTexture(toh._button);
                    if(numOfDisk>0)
                    TOH::state = TOH::ProgramState::Solve;
                }
                }
                }else{mouseFlag[1]=0;toh.but2.setTexture(toh._button);}
            if(TOH::state!=TOH::ProgramState::Menu){init=0;}
            window.clear(sf::Color::Black);
            window.draw(toh.bg);
            toh.drawPole(window);
            for(int i=numOfDisk-1;i>=0;i--) disk[i].draw(window); 
            window.draw(toh.but1);window.draw(toh.but2);
            toh.drawString(1,window);
            window.display();
            break;
            }
            case TOH::Close:
            {
                thread.terminate();
                thread2.terminate();
                window.close();
                break;
            }
        }
        window.pollEvent(TOH::event);
        {
            if (TOH::event.type == sf::Event::Closed)
            {
                thread.terminate();
                thread2.terminate();
                window.close();
            }
        }
        
    }

    return 0;
}








void DiscUpdate(disc* d,int discNum,int srcPeg,int destPeg,float height,int *peg)//peg numbers are 1,2,3
{
    if(threadTerminate==1) return;
    float t=0.0f,dt;
    sf::Clock fullclock;
    float speedX,speedY;
    int transition=0;
    float x=0.0f;
    int flag=1;
    int flag2=0;
    int flag3=0;
    float dist=abs(d[discNum].position.x-(WIDTH/4.0f)*destPeg);
    while(flag )
    {
        if(transition==0) 
        {   
            dt=fullclock.getElapsedTime().asMilliseconds()-t;
            t=fullclock.getElapsedTime().asMilliseconds();
           if( TOH::pause==0) d[discNum].move(sf::Vector2f(0,-disc::speed*dt));
            if(d[discNum].position.y<height) 
            {
                d[discNum].position.y=height;
                d[discNum].setPos();
                transition =1;
            }
           

        }
        else if(transition==1)
        {
            if(flag2==0)
            {
                if(WIDTH*destPeg/4.0f>d[discNum].position.x)    speedX=disc::speed;
                else speedX=-disc::speed;
                flag2=1;
                speedY=-3*disc::speed;
            }
            dt=fullclock.getElapsedTime().asMilliseconds()-t;
            t=fullclock.getElapsedTime().asMilliseconds();
            if(x>dist*0.5f && flag3==0){ flag3=1; speedY*=-1;}
           if(flag3==0) {x+=speedX>0 ? speedX*dt : -speedX*dt;}
           else{ x-=speedX>0 ? speedX*dt : -speedX*dt;}
          if( TOH::pause==0)  d[discNum].move(sf::Vector2f(speedX*dt,speedY*dt/sqrt(0.1f+fabs(x))));
             if(speedX>0)
             {  if(d[discNum].position.x>(WIDTH/4.0f)*destPeg)
                 {
                     d[discNum].position.y=height;
                     d[discNum].position.x=(WIDTH/4.0f)*destPeg;
                     d[discNum].setPos();
                     transition=2;
                     flag3=0;
                     flag2=0;
                     x=0.0f;
                 }
             }
             else
             {
                 if(d[discNum].position.x<(WIDTH/4.0f)*destPeg)
                 {
                     d[discNum].position.y=height;
                     d[discNum].position.x=(WIDTH/4.0f)*destPeg;
                     d[discNum].setPos();
                     transition=2;
                     flag2=0;
                 }
             }
             
        }
        else if(transition==2)
        {
            dt=fullclock.getElapsedTime().asMilliseconds()-t;
            t=fullclock.getElapsedTime().asMilliseconds();
           if( TOH::pause==0) d[discNum].move(sf::Vector2f(0,disc::speed*dt));
            if(d[discNum].position.y>HEIGHT-TOH::offset-peg[destPeg-1]*d[discNum].size.y) 
            {
                d[discNum].position.y=HEIGHT-TOH::offset-peg[destPeg-1]*d[discNum].size.y;
                d[discNum].setPos();
                peg[srcPeg-1]--;
                peg[destPeg-1]++;
                flag=0;
            }
        }
        if(threadTerminate==1) return;
    }
    TOH::steps++;
}

void solveTOH( disc* d,float height,int *peg,int n,int src,int dest,int aux)
{
    if(threadTerminate==1) return;
    if(n==1) DiscUpdate(d,0,src,dest,height,peg);
    else
    {
    solveTOH(d,height,peg,n-1,src,aux,dest);
    DiscUpdate(d,n-1,src,dest,height,peg);
    solveTOH(d,height,peg,n-1,aux,dest,src);
    }
}

void threadToh(pThread& x)
{
    solveTOH( x.d,x.height,x.peg,x.n,x.src,x.dest,x.aux);
    x.finish[0]=1;
}
void initialDisplayThread(dThread& a)
{
    for(int i=a.num-1;i>=0;i--)
    {
        a.d[i].Create(sf::Vector2f(WIDTH*1.0f/4.0f,-200*(a.num-i)-(a.num-1-i)*disc::scale*20.0f),sf::Vector2f(40.0f+20*i,20.0f),i+1);
    }
    int j=a.num;
    sf::Clock clock;
    while(1)
    {
        float dt=clock.getElapsedTime().asMicroseconds();
        clock.restart();
        for(int i=0;i<j;i++)
        {
            a.d[i].move(sf::Vector2f(0,dt*disc::speed/500));
        }

        if(a.d[j-1].position.y>HEIGHT-TOH::offset-(a.num-j)*a.d[0].size.y)
        {
            a.d[j-1].position.y=HEIGHT-TOH::offset-(a.num-j)*a.d[0].size.y;
            a.d[j-1].setPos();
            j--;
        }
        if(j==0) break;
    }
    a.finish[0]=1;
}

bool mouseIntersect(sf::Sprite& sp,sf::RenderWindow& window,sf::Vector2u size)
{
   
   sf::Vector2i b = sf::Vector2i(int(sf::Mouse::getPosition(window).x*float(WIDTH)/window.getSize().x), int(sf::Mouse::getPosition(window).y*float(HEIGHT) / window.getSize().y));
    sf::Vector2f a=sp.getPosition();
    if(b.x<a.x) return false;
    if(b.y<a.y) return false;
    if(b.y>a.y+size.y) return false;
    if(b.x>a.x+size.x) return false;
    return true;
}