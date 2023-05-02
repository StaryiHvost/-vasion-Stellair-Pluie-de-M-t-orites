#include "worklib.h"
 
int main()
{
    srand(time(NULL));
    //proprietes de la fenetre windows
    RenderWindow win(VideoMode(1280, 720), L"Évasion Stellairе: Pluie de Météorites");
    Image icon;
    if (!icon.loadFromFile("Image/icon.png"))
    {
        return 1; //icone de lappli manquante
    }
    win.setIcon(32, 32, icon.getPixelsPtr());


    //Panel
    Texture TextureInfoPanel;
    TextureInfoPanel.loadFromFile("Image/panel.png");
    RectangleShape GameInfoPanel(Vector2f(1280,113));
    GameInfoPanel.setTexture(&TextureInfoPanel);
    GameInfoPanel.setPosition(Vector2f(0, 0));

    //radar
    CircleShape Rcircle(5.f);
    Rcircle.setFillColor(Color(255, 0, 0));
    Rcircle.setOutlineThickness(2.f);
    Rcircle.setOutlineColor(Color(255, 155, 0));
    Rcircle.setPosition(495, 33);

    //Earth
    Texture textEarth;
    if (!textEarth.loadFromFile("Image/earth.png")) return 33; 
    RectangleShape Earth(Vector2f(500, 500));
    Earth.setTexture(&textEarth);
    Earth.setPosition(Vector2f(1100, 150));

    //Fuel

    int pusk = 0;                   //temps de text de fuel(bonus)
    double tmpfull = 0;             //quantite de fuel
    int fuel = 200;                 //fuel dans navire
    Text text_full, plusfull, text_pause, end_game;
    Font GameFont;
    if (!GameFont.loadFromFile("Font/BankGothic Md BT Medium.otf")) return 11;
    //Fuel de navire
    text_full.setFont(GameFont);
    text_full.setFillColor(Color::Green);
    text_full.setCharacterSize(30);
    text_full.setPosition(1070, 20);
    //Fuel de jerrican
    plusfull.setFont(GameFont);
    plusfull.setFillColor(Color::Green);
    plusfull.setCharacterSize(25);
    //End Game
    end_game.setFont(GameFont);
    end_game.setFillColor(Color::Red);
    end_game.setCharacterSize(100);
    end_game.setString(L"Tu y se arrivé");
    end_game.setPosition(300, 333);

    //Pause
    text_pause.setFont(GameFont);
    text_pause.setFillColor(Color::Magenta);
    text_pause.setCharacterSize(50);
    text_pause.setString(L"P A U S E");
    text_pause.setPosition(500, 333);
    //Cosmos

    Texture TextureSpace;
    TextureSpace.loadFromFile("Image/cosmos.jpg");
    RectangleShape gamingBackGround(Vector2f(1280, 720));
    gamingBackGround.setTexture(&TextureSpace);

    RectangleShape gamingBackGround2(Vector2f(1280, 720));
    gamingBackGround2.setTexture(&TextureSpace);
    gamingBackGround2.setPosition(Vector2f(1280, 0));


    //VALEURS
    bool GameOver = false, GamePause = false;
    Vector2f pos;               //coordinat
    Clock clock, clockAnimPlay, clockAnimMeteor, clockAnimText;     //montre
    float time, timePlayer, timeGamingBackground, timeMeteor;

    //navire spatial
    Vector2f moveRec;
    int traffic = 0;
    FrameAnim FramePlAnim;
    FramePlAnim.Frame = 700;
    Texture textPlayer;
    textPlayer.loadFromFile("Image/playeranim.png");
    Sprite player;
    player.setTexture(textPlayer);
    player.setTextureRect(IntRect(0, FramePlAnim.Frame, 90, 90));
    player.scale(0.7, 0.7);
    //EXPLOSIONS
    FrameAnim DestructAnim;
    DestructAnim.Frame = 5;
    DestructAnim.Frame1 = 15;
    Texture texdest;
    texdest.loadFromFile("Image/explox.png");
    Sprite destruction;
    destruction.setTexture(texdest);
    destruction.setTextureRect(IntRect(5, 15, 95, 80));
    destruction.scale(0.7, 0.7);


    //METEORS
    Meteors meteors[15];
    const int Nmeteor = 15;

    //Fuels

    Fuul jerrican("Image/FUELS.png", 1000, 1000);

    //animation jet stream
    //int arrAnim[3]{ 9,59,103 };
    //int Frame = 3, step = -1;

    //
    //Texture jetfire;
    //jetfire.loadFromFile("Image/jetfire.png");
    //Sprite jetSprite;
    //jetSprite.setTexture(jetfire);
    //jetSprite.setTextureRect(IntRect(0, 103, 85, 43));


    //gaming cycle
    while (win.isOpen())
    {
        Event event;
        //relier le gameplay au temps
        time = clock.getElapsedTime().asMicroseconds();
        timeGamingBackground = time / 6000;
        timeMeteor = time / 3000;
        timePlayer = time / 2000;
        clock.restart();
        //---------------------------------------------

        while (win.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                win.close();
            //controle de navire
            switch (event.type)
            {
            case Event::KeyPressed:
                if (event.key.code == Keyboard::Pause) GamePause = !GamePause;
                if (event.key.code == Keyboard::Escape) win.close();
                if ((event.key.code == Keyboard::Numpad5) || (event.key.code == Keyboard::S))
                    if (fuel != 0) { moveRec.y = 0.3 * timePlayer; traffic = 2; fuel--; }
                if ((event.key.code == Keyboard::Numpad8) || (event.key.code == Keyboard::Z))
                    if (fuel != 0) { moveRec.y = -0.3 * timePlayer; traffic = 1; fuel--; }
                if ((event.key.code == Keyboard::Numpad4) || (event.key.code == Keyboard::Q))
                    if (fuel != 0) { moveRec.x = -0.3 * timePlayer; fuel--; }
                if ((event.key.code == Keyboard::Numpad6) || (event.key.code == Keyboard::D))
                    if (fuel != 0) { moveRec.x = 0.3 * timePlayer; fuel--; }
                break;
            case Event::KeyReleased:
                if ((event.key.code == Keyboard::Numpad5) || (event.key.code == Keyboard::S)) { moveRec.y = 0; traffic = 0; }
                if ((event.key.code == Keyboard::Numpad8) || (event.key.code == Keyboard::Z)) { moveRec.y = 0; traffic = 0; }
                if ((event.key.code == Keyboard::Numpad4) || (event.key.code == Keyboard::Q)) moveRec.x = 0;
                if ((event.key.code == Keyboard::Numpad6) || (event.key.code == Keyboard::D)) moveRec.x = 0;
                break;
            default:
                break;
            }

        }
        if (!GamePause) {
            //Radar
            if (Rcircle.getPosition().x <= 850) {
            if (GameOver)
            {
                //Animation d'explosion
                if (clockAnimMeteor.getElapsedTime() > milliseconds(80))
                {
                    clockAnimMeteor.restart();
                    DestructAnim.Frame += DestructAnim.Step;
                    if (DestructAnim.Frame > 405)
                    {
                        DestructAnim.Frame1 += DestructAnim.Step1; DestructAnim.Frame = 5;
                    }
                    if (DestructAnim.Frame1 > 415) {
                        GameOver = false;
                        player.setPosition(Vector2f(80, 380));
                        for (int i = 0; i < Nmeteor; i++) meteors[i].restart();
                        jerrican.restart();
                        Rcircle.setPosition(495, 33);
                        DestructAnim.Frame = 5; DestructAnim.Frame1 = 15;
                        fuel = 100;
                    }
                    else
                    {
                        destruction.setTextureRect(IntRect(DestructAnim.Frame, DestructAnim.Frame1, 95, 80));
                    }
                }
            }
            else {
                //animation player
                if (clockAnimPlay.getElapsedTime() > milliseconds(100))
                {
                    clockAnimPlay.restart();
                    playeranim(player, FramePlAnim, traffic);
                }
                if (clockAnimMeteor.getElapsedTime() > milliseconds(80))
                {
                    clockAnimMeteor.restart();
                    for (int i = 0; i < Nmeteor, i++;) meteors[i].animation();
                    Rcircle.move(1, 0);     //mouv de radar

                }
                if (clockAnimText.getElapsedTime() > milliseconds(50))
                {
                    clockAnimText.restart();
                    if (pusk > 0)
                    {
                        pusk--;
                        plusfull.move(0, -1);
                    }
                }
                //Cosmos
                gamingBackGround.move(-0.2 * timeGamingBackground, 0);
                pos = gamingBackGround.getPosition();
                if (pos.x < -1280) gamingBackGround.setPosition(1280, pos.y);
                gamingBackGround2.move(-0.2 * timeGamingBackground, 0);
                pos = gamingBackGround2.getPosition();
                if (pos.x < -1280) gamingBackGround2.setPosition(1280, pos.y);

                playermove(player, moveRec);//mouvement de navire

                for (int i = 0; i < Nmeteor; i++) {
                    if (meteors[i].newborn) Correct(jerrican, i, meteors, Nmeteor);
                    meteors[i].move(timeMeteor);            //mouvement de meteorite
                    if (meteors[i].collision(player.getGlobalBounds()))     //etat de collision
                    {
                        GameOver = true; destruction.setPosition(player.getPosition().x, player.getPosition().y); break;
                    }
                }
                //Fuel
                if (jerrican.newborn) CorrectFuul(jerrican, meteors, Nmeteor);
                jerrican.move(timeMeteor);          //mouvement des jerricans
                //
                if (jerrican.collision(player.getGlobalBounds()))
                {
                    tmpfull = 10 + rand() % 90;
                    fuel += tmpfull;
                    plusfull.setString(IntToStr(tmpfull));
                    plusfull.setPosition(jerrican.getPosBonus().x, jerrican.getPosBonus().y);
                    pusk = 40;
                    jerrican.restart();
                }
                //tab fuel
                if (fuel >= 100) text_full.setFillColor(Color::Green);
                if (fuel < 100 && fuel >= 50) text_full.setFillColor(Color::Yellow);
                if (fuel < 50) text_full.setFillColor(Color::Red);
                text_full.setString(IntToStr(fuel) + L"tonnes");

            }

            win.clear();
            //dessin de lespace
            win.draw(gamingBackGround);
            win.draw(gamingBackGround2);
            //dessin de panneau
            win.draw(GameInfoPanel);
            win.draw(Rcircle);
            //dessin de navire
            if (GameOver) win.draw(destruction); else  win.draw(player);
            for (int i = 0; i < Nmeteor; i++) meteors[i].draw(win);     //meteors
            //dessin de jetstream
            //.draw(jetSprite);
            jerrican.draw(win);
            win.draw(text_full);
            if (pusk > 0) win.draw(plusfull);
            win.display();

        }
        else
        {
            win.clear();
            win.draw(gamingBackGround);
            win.draw(gamingBackGround2);

            win.draw(GameInfoPanel);
            win.draw(Rcircle);
            win.draw(text_full);
            win.draw(Earth);
            win.draw(end_game);
            win.display();
            if (clockAnimText.getElapsedTime() > seconds(20)) win.close();
        }
    }
    else
{
        win.draw(text_pause);
        win.display();
}



    
}

    return 0;
}