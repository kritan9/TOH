
#include "TOH.hpp"
#include "disc.hpp"
using namespace std;
#define WIDTH 1366
#define HEIGHT 768
#define offset 100.0f

struct pThread //parameters for the thread function to solve TOH
{
 disc* d;float height;int *peg;int n;int src;int dest;int aux;
pThread ( disc* di,float heigh,int *pe,int nu,int sr,int des,int au):
d(di),height(heigh),peg(pe),n(nu),src(sr),dest(des),aux(au)
{}
};
void threadToh(pThread& x);//thread Function to solve TOH
void DiscUpdate(disc* d,int discNum,int srcPeg,int destPeg,float height,int *peg);//peg numbers are 1,2,3
void solveTOH(disc* d,float height,int *peg,int n,int src,int dest,int aux);


int main()
{

    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tower Of Hanoi");
    int numOfDisk=3;
    disc *disk=new disc[numOfDisk];
    for(int i=numOfDisk-1;i>=0;i--)
    {
        disk[i].Create(sf::Vector2f(WIDTH*1.0f/4.0f,HEIGHT-offset-(numOfDisk-1-i)*20.0f),sf::Vector2f(40.0f+20*i,20.0f));
    }
    int peg[3]={numOfDisk,0,0};
    pThread _temp(disk,400.0f,peg,numOfDisk,1,3,2);
    sf::Thread thread(&threadToh,_temp);
    thread.launch();
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                thread.terminate();
                window.close();
            }
        }
        window.clear(sf::Color::Black);

        for(int i=numOfDisk-1;i>=0;i--)
        {
            disk[i].draw(window);
        }
       window.display();
        
    }
    delete[] disk;
    return 0;
}








void DiscUpdate(disc* d,int discNum,int srcPeg,int destPeg,float height,int *peg)//peg numbers are 1,2,3
{
    float t=0.0f,dt;
    sf::Clock fullclock;
    float speedX,speedY;
    int transition=0;
    float x=0.0f;
    int flag=1;
    int flag2=0;
    int flag3=0;
    float dist=abs(d[discNum].position.x-(WIDTH/4.0f)*destPeg);
    while(flag)
    {
        if(transition==0) 
        {   
            dt=fullclock.getElapsedTime().asMilliseconds()-t;
            t=fullclock.getElapsedTime().asMilliseconds();
            d[discNum].move(sf::Vector2f(0,-disc::speed*dt));
            if(d[discNum].position.y<height) 
            {
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
            d[discNum].move(sf::Vector2f(speedX*dt,speedY*dt/sqrt(0.1f+fabs(x))));
             if(speedX>0)
             {  if(d[discNum].position.x>(WIDTH/4.0f)*destPeg)
                 {
                     d[discNum].position.y=height;
                     d[discNum].position.x=(WIDTH/4.0f)*destPeg;
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
                     transition=2;
                     flag2=0;
                 }
             }
             
        }
        else if(transition==2)
        {
            dt=fullclock.getElapsedTime().asMilliseconds()-t;
            t=fullclock.getElapsedTime().asMilliseconds();
            d[discNum].move(sf::Vector2f(0,disc::speed*dt));
            if(d[discNum].position.y>HEIGHT-offset-peg[destPeg-1]*d[discNum].size.y) 
            {
                d[discNum].position.y=HEIGHT-offset-peg[destPeg-1]*d[discNum].size.y;
                peg[srcPeg-1]--;
                peg[destPeg-1]++;
                flag=0;
            }
        }
        
    }
}

void solveTOH( disc* d,float height,int *peg,int n,int src,int dest,int aux)
{
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
}