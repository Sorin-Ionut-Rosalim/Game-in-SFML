#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include "Source.h"

using namespace sf;

int windowWidth = 528;
int windowHeight = 528;

void moveKeyPressed(bool& playerRight, bool& playerLeft, bool& playerUp, bool& playerDown)
{
    if (Keyboard::isKeyPressed(Keyboard::Right)) {
        playerRight = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Left)) {
        playerLeft = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Up)) {
        playerUp = true;
    }
    if (Keyboard::isKeyPressed(Keyboard::Down)) {
        playerDown = true;
    }
    if (!Keyboard::isKeyPressed(Keyboard::Right)) {
        playerRight = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::Left)) {
        playerLeft = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::Up)) {
        playerUp = false;
    }
    if (!Keyboard::isKeyPressed(Keyboard::Down)) {
        playerDown = false;
    }
}

int main() {

    std::ifstream openfile("Map1.txt");
    Texture tileTexture;
    Sprite tiles;

    std::vector<std::vector<Vector2i>> map;
    std::vector<Vector2i> tempMap;

    if (openfile.is_open()) {
        std::string tileLocation;
        openfile >> tileLocation;
        tileTexture.loadFromFile(tileLocation);
        tiles.setTexture(tileTexture);


        while (!openfile.eof()) {
            std::string str;
            openfile >> str;
            char x = str[0], y = str[2];
            if (!isdigit(x) || !isdigit(y)) {
                tempMap.push_back(Vector2i(-1, -1));
            }
            else {
                tempMap.push_back(Vector2i(x - '0', y - '0'));
            }

            if (openfile.peek() == '\n') {

                map.push_back(tempMap);
                tempMap.clear();
            }
        }
        map.push_back(tempMap);
    }

        //Main Window
        RenderWindow window(VideoMode(windowWidth, windowHeight, 24), "Spongey!");
        View view(Vector2f(0.0f, 0.0f), Vector2f(528.0f, 528.0f));


        bool playerUp = false;
        bool playerDown = false;
        bool playerLeft = false;
        bool playerRight = false;

        Player playerObject;

        Font font;
        font.loadFromFile("D:/VSProb/TEST_SFML/data/fonts/Ac437_ACM_VGA_9x14.ttf");
        Text helloText("Hello to the sponge!", font, 50);

        Texture sponge1, sponge2;
        sponge1.loadFromFile("D:/VSProb/TEST_SFML/data/img/Sponge1.png");
        sponge2.loadFromFile("D:/VSProb/TEST_SFML/data/img/Sponge2.png");

        Sprite spongeSprite;
        spongeSprite.setPosition(0, 24 * 6);
        int i = 0;
        // GAME LOOP
        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed)
                    window.close();
            }

            window.clear(Color(0,240,255));
        

 
            
            if ( true) {
                spongeSprite.setTexture(sponge1);
                i++;
            }
            else
            {
                spongeSprite.setTexture(sponge2);
                i++;
            }
            



            for (int i = 0; i < map.size(); i++) {
                for (int j = 0; j < map[i].size(); j++) {
                    if (!(map[i][j].x == -1 ||  map[i][j].y == -1)) {
                        tiles.setPosition(j * 24, i * 24);
                        tiles.setTextureRect(IntRect(map[i][j].x * 24, map[i][j].y * 24, 24, 24));
                        window.draw(tiles);
                    }
                }

            }

            moveKeyPressed(playerRight, playerLeft, playerUp, playerDown);

            playerObject.update(playerRight, playerLeft, playerUp, playerDown);

            /*if (!playerObject.lookRight) {
                spongeSprite.setRotation(180);
            }
            else
            {
                spongeSprite.setRotation(0);
            }
            */
            

            view.setCenter(playerObject.getPosition());


            window.draw(spongeSprite);
            //window.draw(helloText);

            
            spongeSprite.move(Vector2f(playerObject.xvel, playerObject.yvel));
            window.setView(view);
            window.display();

        }

    

   

    return 0;
}