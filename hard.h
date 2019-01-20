#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
//#include"Collision.h"

using namespace sf;
using namespace std;

class HardGame
{
public:
    HardGame();
    void menu();
    void run();

    RenderWindow app;

    Texture spship;
    Sprite spaceship;

    Texture bul;
    Sprite bullet;
    vector <Sprite> amo;
    Sprite en_amo[6];

    Texture en;
    Sprite enemy[6];

    Texture bg;
    Sprite background;

    //Texture exp;
    //Sprite explosion;

    SoundBuffer gs;
    Sound gunshot;

    SoundBuffer blst;
    Sound blast;

    Clock clk;

    bool IsMovingUp=false,IsMovingDown=false,IsMovingLeft=false,IsMovingRight=false,Fire=false;
    int ex[6],ey[6],i,j,count=0,score=0,enemyspeed_x[6],enemyspeed_y[6],en_amo_speed;
    void processevents();
    void handlePlayerInput(Keyboard::Key key,bool isPressed);
    void update();
    void render();
};

HardGame::HardGame()
{
    //window
    ContextSettings settings;
    settings.antialiasingLevel = 8;
    app.create(VideoMode(960,540),"Space-Shooter");
    app.setVerticalSyncEnabled(true);
    //background
    bg.loadFromFile("images/background.png");
    bg.setSmooth(true);
    background.setTexture(bg);
    background.setScale(0.5,0.5);
    //player
    spship.loadFromFile("images/rocket.png");
    spship.setSmooth(true);
    spaceship.setTexture(spship);
    spaceship.setScale(0.25,0.25);
    spaceship.setOrigin(45,18);
    spaceship.setPosition(45,240);
    //bullet
    bul.loadFromFile("images/bullet.png");
    bul.setSmooth(true);
    bullet.setTexture(bul);
    bullet.setScale(0.05,0.05);
    bullet.setOrigin(12,12);
    //enemy
    en.loadFromFile("images/enemy.png");
    en.setSmooth(true);

    for(i=0; i<6; i++)
    {
        ex[i]=960+i*40;
        if(i<3)
            ey[i]=135;
        else
            ey[i]=405;
        enemy[i].setTexture(en);
        enemy[i].setScale(0.2,0.2);
        enemy[i].setOrigin(33.5,30.6);
        enemy[i].setPosition(ex[i],ey[i]);

        en_amo[i].setTexture(bul);
        en_amo[i].setScale(0.05,0.05);
        en_amo[i].setOrigin(12,12);

        enemyspeed_x[i]=-5;
        enemyspeed_y[i]=0;
    }
    //bullet sound
    gs.loadFromFile("gunshot.wav");
    gunshot.setBuffer(gs);
    //blast after enemy death
    blst.loadFromFile("blast.wav");
    blast.setBuffer(blst);

}

void HardGame::run()
{
    //gameloop
    while(app.isOpen())
    {
        processevents();
        update();
        render();
    }
}

void HardGame::processevents()
{
    Event event;
    //event loop
    while(app.pollEvent(event))
    {
        if(event.type == Event::Closed)
            app.close();
        if(event.type == Event::KeyReleased)
            handlePlayerInput(event.key.code,false);
    }
}
//keyboard controls
void HardGame::handlePlayerInput(Keyboard::Key key,bool isPressed)
{
    if(key == Keyboard::Up)
        IsMovingUp = true;
    if(key == Keyboard::Left)
        IsMovingLeft = true;
    if(key == Keyboard::Down)
        IsMovingDown = true;
    if(key == Keyboard::Right)
        IsMovingRight = true;
    if(key == Keyboard::Space)
    {
        Fire=true;
    }

}

void HardGame::update()
{
    Vector2f movement(0.f,0.f);

    if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        movement.y-=10;
        if(spaceship.getPosition().y<18)
            movement.y+=10;
    }
    if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        movement.x-=10;
        if(spaceship.getPosition().x<10)
            movement.x+=10;
    }
    if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        movement.y+=10;
        if(spaceship.getPosition().y>470)
            movement.y-=10;
    }
    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        movement.x+=10;
        if(spaceship.getPosition().x > 810)
            movement.x-=10;
    }
    //firing
    if(Fire)
    {
        gunshot.play();
        bullet.setPosition(spaceship.getPosition().x+120,spaceship.getPosition().y+17);
        amo.push_back(Sprite(bullet));
        count++;
        Fire=false;
    }
    //bullet movement and collision with enemy
    for(i=0; i<count; i++)
    {
        amo[i].move(10.f,0.f);
        for(j=0; j<6; j++)
        {
            if(amo[i].getGlobalBounds().intersects(enemy[j].getGlobalBounds()))
            //if(Collision::PixelPerfectTest(amo[i],enemy[j]))
            {
                blast.play();
                enemy[j].setPosition(960+rand()%300,ey[j]);
                enemyspeed_y[j]=0;
                amo[i].setPosition(345,900);
            }
        }

    }

    spaceship.move(movement);
    //enemy movement
    for(i=0; i<6; i++)
    {
        if(enemy[i].getPosition().x<0)
        {
            enemy[i].setPosition(960+i*40,ey[i]);
            enemyspeed_y[i]=0;
        }
        else if(enemy[i].getPosition().x<960)
        {
            if(clk.getElapsedTime().asSeconds()>0.2)
                //enemyspeed_y[i]=20*sin(enemy[i].getPosition().x);
            enemyspeed_y[i]-=1;
            if(enemy[i].getPosition().y<80 && i<3)
                enemyspeed_y[i]+=2;
            if(enemy[i].getPosition().y<300 && i>=3)
                enemyspeed_y[i]+=2;
        }
        int k = 900+i*20;
        if(enemy[i].getPosition().x==k)
        {
            en_amo[i].setPosition(enemy[i].getPosition().x-enemy[i].getGlobalBounds().width,enemy[i].getPosition().y);

        }
        enemy[i].move(enemyspeed_x[i],enemyspeed_y[i]);
        en_amo[i].move(enemyspeed_x[i]-3,0);
        if(en_amo[i].getPosition().x<0)
            en_amo[i].setPosition(enemy[i].getPosition().x-enemy[i].getGlobalBounds().width,enemy[i].getPosition().y);
    }
}

void HardGame::render()
{
    app.clear();
    app.draw(background);
    app.draw(spaceship);
    for(i=0; i<6; i++)
    {
        app.draw(enemy[i]);
        if(en_amo[i].getPosition().x>0)
            app.draw(en_amo[i]);
    }
    for(i=0; i<count; i++)
        app.draw(amo[i]);
    app.display();
}
