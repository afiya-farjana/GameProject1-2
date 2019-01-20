#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <SFML/Window.hpp>

#include"easy.h"
#include"medium.h"
#include"hard.h"

using namespace std;
using namespace sf;

void play();
//void option();
void highscore();
void help();

bool Level_1=false,Level_2=false,Level_3=false,home=true;
int cursor=0;

RenderWindow app;
Event event;

int main()
{

    //RenderWindow app;
    app.create(VideoMode(960,540),"Space-Shooter");
    Texture menubg;
    Sprite menubackground;
    menubg.loadFromFile("images/background.png");
    menubg.setSmooth(true);
    menubackground.setTexture(menubg);
    menubackground.setScale(0.5,0.5);

    Font font;
    font.loadFromFile("Pacifico.ttf");

    Text gamename,menu_text[4];

    gamename.setFont(font);
    gamename.setString("Space Shooting");
    gamename.setCharacterSize(75);
    gamename.setScale(1.0f,1.0f);
    gamename.setOutlineThickness(1.0f);
    gamename.setFillColor(sf::Color::Blue);
    gamename.setLetterSpacing(1.0f);
    gamename.setPosition(200,2);

    for(int i=0; i<3; i++)
    {
        menu_text[i].setFont(font);
        menu_text[i].setCharacterSize(60);
        menu_text[i].setScale(1.0f,1.0f);
        menu_text[i].setPosition(200,230+(i*70));
        menu_text[i].setFillColor(Color::White);
    }
    menu_text[0].setString("Play");
    //menu_text[1].setString("Options");
    //menu_text[2].setString("Highscore");
    menu_text[1].setString("Help");
    menu_text[2].setString("Exit");
    menu_text[cursor].setFillColor(Color::Cyan);

    while (app.isOpen())
    {
        //Event event;
        while (app.pollEvent(event))
        {
            if (event.type == Event::Closed||Keyboard::isKeyPressed(Keyboard::Escape))
                app.close();
            if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                menu_text[cursor].setFillColor(Color::White);
                cursor=(cursor+1)%3;
                menu_text[cursor].setFillColor(Color::Cyan);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up))
            {
                menu_text[cursor].setFillColor(Color::White);
                cursor=(cursor+2)%3;
                menu_text[cursor].setFillColor(Color::Cyan);
            }
            if(Keyboard::isKeyPressed(Keyboard::Enter))
            {
                if(cursor==0)
                {
                    app.close();

                    app.create(VideoMode(960,540),"Space-Shooter");

                    int option=0;
                    Font font;
                    Text opt[3];
                    font.loadFromFile("Pacifico.ttf");

                    for(int i=0; i<3; i++)
                    {
                        opt[i].setFont(font);
                        opt[i].setCharacterSize(60);
                        opt[i].setScale(1.0f,1.0f);
                        opt[i].setPosition(400,130+(i*100));
                        opt[i].setFillColor(Color::White);

                    }

                    opt[0].setString("Easy");
                    opt[1].setString("Medium");
                    opt[2].setString("Hard");
                    opt[option].setFillColor(Color::Cyan);
                    while(app.isOpen())
                    {
                        while(app.pollEvent(event))
                        {
                            if (event.type == Event::Closed||Keyboard::isKeyPressed(Keyboard::Escape))
                                app.close();
                            if (Keyboard::isKeyPressed(Keyboard::Down))
                            {
                                opt[option].setFillColor(Color::White);
                                option=(option+1)%3;
                                opt[option].setFillColor(Color::Cyan);
                            }
                            if (Keyboard::isKeyPressed(Keyboard::Up))
                            {
                                opt[option].setFillColor(Color::White);
                                option=(option+2)%3;
                                opt[option].setFillColor(Color::Cyan);
                            }
                            if(Keyboard::isKeyPressed(Keyboard::Enter))
                            {
                                if(option==0)
                                {
                                    app.close();
                                    EasyGame game2;
                                    game2.run();
                                }
                                if(option==1)
                                {
                                    app.close();
                                    MediumGame game2;
                                    game2.run();
                                }
                                if(option==2)
                                {
                                    app.close();
                                    HardGame game2;
                                    game2.run();
                                }
                            }

                            for(int i=0; i<3; i++)
                                app.draw(opt[i]);

                            app.display();
                        }
                    }

                }
                else if(cursor==1)
                    help();
                else if(cursor==2)
                    app.close();

            }

        }



        if(home)
        {
            app.clear();
            app.draw(menubackground);
            app.draw(gamename);
            for(int i=0; i<5; i++)
            {
                app.draw(menu_text[i]);
            }
            app.display();
        }
    }
}

void help()
{
    app.clear();
    home=false;
    Font font;
    Text control_head,control_text[2],level_description,level_des[3];
    font.loadFromFile("Pacifico.ttf");

    control_head.setFont(font);
    control_head.setString("Controls:\n");
    control_head.setCharacterSize(50);
    control_head.setFillColor(Color::White);
    control_head.setPosition(10,10);

    for(int i=0; i<2; i++)
    {
        control_text[i].setFont(font);
        control_text[i].setCharacterSize(30);
        control_text[i].setFillColor(Color::White);
        control_text[i].setPosition(10,85+i*50);
    }

    control_text[0].setString("*Press arrow keys to move your spaceship.");
    control_text[1].setString("*Press space to shoot.");

    level_description.setFont(font);
    level_description.setString("Level Description:\n");
    level_description.setCharacterSize(50);
    level_description.setFillColor(Color::White);
    level_description.setPosition(10,195);

    for(int i=0; i<3; i++)
    {
        level_des[i].setFont(font);
        level_des[i].setCharacterSize(30);
        level_des[i].setFillColor(Color::White);
        level_des[i].setPosition(10,285+i*50);
    }

    level_des[0].setString("*Easy : Enemies move horizontally.");
    level_des[1].setString("*Medium : Enemies move vertically as well.");
    level_des[2].setString("*Hard : Enemies move and shoot bullets.");


    app.draw(control_head);
    for(int i=0; i<2; i++)
        app.draw(control_text[i]);
    app.draw(level_description);
    for(int i=0; i<3; i++)
        app.draw(level_des[i]);
    app.display();

    if (event.type == Event::Closed||Keyboard::isKeyPressed(Keyboard::Escape))
        return;
}
