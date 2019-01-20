#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<bits/stdc++.h>
//#include"Collision.h"

using namespace sf;
using namespace std;

class EasyGame
{
public:
    EasyGame();
    void menu();
    void run();

    RenderWindow app;

    Texture spship;
    Sprite spaceship;

    Texture bul;
    Sprite bullet;
    vector <Sprite> amo;

    Texture en;
    Sprite enemy[6];

    Texture bg;
    Sprite background;

    Texture exp;
    Sprite explosion;

    SoundBuffer gs;
    Sound gunshot;

    SoundBuffer blst;
    Sound blast;

    Clock clk;

    bool IsMovingUp=false,IsMovingDown=false,IsMovingLeft=false,IsMovingRight=false,Fire=false;
    int ex[6],ey[6],i,j,count=0,score=0,enemyspeed=-5;

    void processevents();
    void handlePlayerInput(Keyboard::Key key,bool isPressed);
    void update();
    void render();
};

EasyGame::EasyGame()
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
        ex[i]=960+rand()%300;
        ey[i]=rand()%40+i*75;
        enemy[i].setTexture(en);
        enemy[i].setScale(0.2,0.2);
        enemy[i].setOrigin(33.5,30.6);
        enemy[i].setPosition(ex[i],ey[i]);
    }
    //bullet sound
    gs.loadFromFile("gunshot.wav");
    gunshot.setBuffer(gs);
    //blast after enemy death
    blst.loadFromFile("blast.wav");
    blast.setBuffer(blst);

}

void EasyGame::run()
{
    //gameloop
    while(app.isOpen())
    {
        processevents();
        update();
        render();
    }
}

void EasyGame::processevents()
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
void EasyGame::handlePlayerInput(Keyboard::Key key,bool isPressed)
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

void EasyGame::update()
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
                amo[i].setPosition(345,900);
            }
        }

    }

    spaceship.move(movement);
    //enemy movement
    for(i=0; i<6; i++)
    {
        enemy[i].move(enemyspeed,0);
        if(enemy[i].getPosition().x<0)
            enemy[i].setPosition(960+rand()%300,ey[i]);
    }
    if(clk.getElapsedTime().asSeconds()>10)
    {
        enemyspeed--;
        clk.restart();
    }

}

void EasyGame::render()
{
    app.clear();
    app.draw(background);
    app.draw(spaceship);
    for(i=0; i<6; i++)
        app.draw(enemy[i]);
    for(i=0; i<count; i++)
        app.draw(amo[i]);
    app.display();
}
