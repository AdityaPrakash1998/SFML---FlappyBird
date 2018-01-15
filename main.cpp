#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<iostream>
#include<string>
#include<sstream>


using namespace std;
using namespace sf;

int main()
{
    //Window
    srand(time(NULL));
    RenderWindow window(sf::VideoMode(512,512),"FLY OR JUMP");

    //Ground
    RectangleShape ground(Vector2f(window.getSize().x,20.0f));
    ground.setOrigin(window.getSize().x/2,20.0f);
    ground.setPosition(window.getSize().x/2,window.getSize().y);
    ground.setFillColor(Color::Green);

    RectangleShape grass(Vector2f(window.getSize().x,60.0f));
    grass.setPosition(0.0f,window.getSize().y-60.0);

    //sky
    RectangleShape sky(Vector2f(window.getSize().x,window.getSize().y));

    //fire
    RectangleShape fence(Vector2f(window.getSize().x,30.0f));
    fence.setOrigin(0.0f,0.0f);
    fence.setFillColor(Color::Black);

    //Player
    RectangleShape player(Vector2f(80.0f,80.0f));
    player.setPosition(176.0f,176.0f);
    player.setOrigin(80.0f,80.0f);

    //Obstacle
    float height=(rand()%200)+180;
    float obsSpeed=-0.3;
    RectangleShape obs(Vector2f(10.0f,height));
    obs.setFillColor(Color::Black);
    obs.setOrigin(5.0f,0.0f);
    obs.setPosition(window.getSize().x,window.getSize().y-height);

    //Texture
    Texture playerTexture;
    playerTexture.loadFromFile("cat.png");
    player.setTexture(&playerTexture);
    player.setOrigin(50.0f,100.0f);

    Texture grassTexture;
    grassTexture.loadFromFile("grass.png");
    grass.setTexture(&grassTexture);

    Texture skyTexture;
    skyTexture.loadFromFile("sky.jpg");
    sky.setTexture(&skyTexture);

    //Forces
    float gravity=0.6;
    float force=-1.0;

    //Score
    int score=0;
    int oldscore=4;
    int finals=0;

    //Text

    Font font;
    font.loadFromFile("sansation.ttf");
    string s="Score :";
    stringstream a;
    a<<score;
    s+=a.str();

    Text text;
    text.setColor(Color::Cyan);
    text.setPosition(350.0f,35.0f);
    text.setFont(font);
    text.setCharacterSize(30);
    text.setString(s);
    text.setStyle(Text::Style::Underlined);
    text.setOutlineColor(Color::Yellow);
    text.setOutlineThickness(2);

    //game loop
    while(window.isOpen())
    {
        Event e;
        while(window.pollEvent(e))
        {
            if(e.type==e.Closed)
            {
                window.close();
            }
            if(e.type==e.KeyReleased)
            {
                if(e.key.code==Keyboard::Space)
                    player.move(0.0f,gravity);
            }
        }

        //player jump or fly logic
     player.move(0.0f,gravity);
     if(Keyboard::isKeyPressed(Keyboard::Space))
        player.move(0.0f,force);

     if(player.getPosition().y<120)
     {
         text.setString("Game Over !");
         text.setCharacterSize(50);
         text.setPosition(156.0f,186.0f);
         obs.setFillColor(Color::Red);
         fence.setFillColor(Color::Red);
         gravity=0.0;
         force=0.0;
         obsSpeed=0.0;
     }
     else force=-1.0;

     if(player.getPosition().y-10>window.getSize().y)
        gravity=0.0;
     else gravity=0.5;

     //obstacle logic
     obs.move(obsSpeed,0.0f);
     if(obs.getPosition().x<0)
     {
        height=(rand()%200)+180;
        obs.setPosition(window.getSize().x,window.getSize().y-height);
        obs.setSize(Vector2f(10.0f,height));
    }

    //Collision Logic
    if(player.getPosition().y-10>window.getSize().y-height && obs.getPosition().x<176 && obs.getPosition().x>156 )
    {
        //cout<<"Collision\n";
        obs.setFillColor(Color::Red);
        fence.setFillColor(Color::Red);
        text.setString("Game Over !");
         text.setCharacterSize(50);
         text.setPosition(156.0f,186.0f);
        gravity=0.0;
        force=0.0;
        obsSpeed=0;
    }
    else if(player.getPosition().y<window.getSize().y-height && obs.getPosition().x<186 && obs.getPosition().x>184)
    {
        score++;
        if(score>oldscore)
        {
            oldscore-=3;
            finals+=oldscore;
            a.str("");
            a<<finals;
            s="Score :"+a.str();
            text.setString(s);
            //window.draw(text);
            oldscore=4;
            score=0;
        }
    }
    else obs.setFillColor(Color::Black);

    //Difficulty Increase
    if(finals>10)
        obsSpeed=-0.4;
    else if(finals>20)
        obsSpeed=-1.0;

    window.clear();

    window.draw(sky);
    window.draw(fence);
    window.draw(obs);
    window.draw(grass);
    window.draw(player);
    window.draw(text);
    window.display();
    }


}
