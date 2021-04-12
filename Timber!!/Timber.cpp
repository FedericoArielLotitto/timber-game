// Timber.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <sstream>
#include <iostream>
//Include important librearies here
#include <SFML/Graphics.hpp>

//Make the code easier to type using namespace
using namespace sf;

//This is where the game starts from
int main()
{
    //Create a VideoObject
    VideoMode vm(1366, 768, 32);

    //Creat a window for the game
    RenderWindow window(vm, "Timber!!!", Style::Fullscreen);

    //Creat a Texture to hold a graphic on the GPU
    Texture textureBackground;

    //Load a graphic into de texture
    textureBackground.loadFromFile("d:/Users/Federico/Desktop/VisualStudioCode/VSProjects/Timber/graphics/backgroundResized.png");

    //Create a sprite
    Sprite spriteBackground;

    //Ataching texture to the sprite
    spriteBackground.setTexture(textureBackground);

    //Set the spriteBackground to cover the screen
    spriteBackground.setPosition(0, 0);

    //Make a tree sprite
    Texture textureTree;
    textureTree.loadFromFile("d:/Users/Federico/Desktop/VisualStudioCode/VSProjects/Timber/graphics/tree.png");
    Sprite spriteTree;
    spriteTree.setTexture(textureTree);
    spriteTree.setPosition(533, 0);

    //Prepare the bee
    Texture textureBee;
    textureBee.loadFromFile("d:/Users/Federico/Desktop/VisualStudioCode/VSProjects/Timber/graphics/bee.png");
    Sprite spriteBee;
    spriteBee.setTexture(textureBee);
    spriteBee.setPosition(0, 384);

    //Is the bee actually moving?
    bool beeActive = false;

    //How fast can they fly?
    float beeSpeed = 0.0f;

    //make 3 cloud sprites
    Texture textureCloud;
    textureCloud.loadFromFile("d:/Users/Federico/Desktop/VisualStudioCode/VSProjects/Timber/graphics/cloud.png");

    //sprites fromo the texture

    Sprite spriteCloud1;
    Sprite spriteCloud2;
    Sprite spriteCloud3;

    spriteCloud1.setTexture(textureCloud);
    spriteCloud2.setTexture(textureCloud);
    spriteCloud3.setTexture(textureCloud);

    //Position of the clouds on the left of the screen and different highs
    spriteCloud1.setPosition(0, 0);
    spriteCloud2.setPosition(0, 250);
    spriteCloud3.setPosition(0, 500);

    //Are the clouds currently on the screen?
    bool cloud1Active = false;
    bool cloud2Active = false;
    bool cloud3Active = false;

    //How fast can the clouds move? 
    float cloud1Speed = 0.0f;
    float cloud2Speed = 0.0f;
    float cloud3Speed = 0.0f;

    //Variables to control time itself 
    Clock clock;

    //Adding time-bar
    RectangleShape timeBar;
    float timeBarStartWidth = 400;
    float timeBarHeight = 80;
    timeBar.setSize(Vector2f(timeBarStartWidth, timeBarHeight));
    timeBar.setFillColor(Color::Red);
    timeBar.setPosition((1366 / 2) - timeBarStartWidth / 2, 980);

    Time gameTimeTotal; 
    float timeRemaining = 6.0f;
    float timeBarWidthPerSecond = timeBarStartWidth / timeRemaining;


    //Setting a 'pause' button
    bool paused = true;

    //Drawing the text

    int score = 0;

    Text messageText;
    Text scoreText;

    //We need to choose a font
    Font font;
    font.loadFromFile("d:/Users/Federico/Desktop/VisualStudioCode/VSProjects/Timber/fonts/KOMIKAP_.ttf");

    //Setting font
    messageText.setFont(font);
    scoreText.setFont(font);

    //Setting the message indeed
    messageText.setString("PRESS ENTER TO START");
    scoreText.setString("SCORE = 0");

    //Defining size
    messageText.setCharacterSize(75);
    scoreText.setCharacterSize(100);

    //Choosing the color
    messageText.setFillColor(Color::White);
    scoreText.setFillColor(Color::White);

    //Position of the text
    FloatRect textRect = messageText.getLocalBounds();

    messageText.setOrigin(textRect.left + textRect.width / 2.0f,
        textRect.top + textRect.height / 2.0f);

    messageText.setPosition(1366 / 2.0f, 768 / 2.0f);
    scoreText.setPosition(20, 20);

    while (window.isOpen())
    {
        /* 
        Handle the player's input
        */
        if (Keyboard::isKeyPressed(Keyboard::Escape)) {
            window.close();
        }
        if (Keyboard::isKeyPressed(Keyboard::Return)) {
            paused = false;

            //Reseting time and score
            score = 0;
            timeRemaining = 6;
        }
        /* Update the scene */
        if (!paused) {
            //Measure time 
            Time dt = clock.restart();

            //Substract from the amount time of time remaining
            timeRemaining -= dt.asSeconds();
            //size up the time bar
            timeBar.setSize(Vector2f(timeBarWidthPerSecond * timeRemaining, timeBarHeight));

            if (timeRemaining <= 0.0f) {
                //Pause the game 
                paused = true;

                //Change the message shown to the player
                messageText.setString("OUT OF TIME!!");

                //Reposition the text based on the new size
                FloatRect textRect = messageText.getLocalBounds();
                messageText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                messageText.setPosition(1366 / 2.0f, 768 / 2.0f);


            }
            //Move the bee
            if (!beeActive) {
                //How fast is the bee
                srand((int)time(0));
                beeSpeed = (rand() % 200) + 200;

                //How high is the bee
                srand((int)time(0) * 10);
                float height = (rand() % 500) + 500;
                spriteBee.setPosition(2000, height);
                beeActive = true;
            }
            else {
                //Move the bee
                spriteBee.setPosition(spriteBee.getPosition().x - (beeSpeed * dt.asSeconds()), spriteBee.getPosition().y);

                //Has the bee reached the left-hand of the screen? 
                if (spriteBee.getPosition().x < -100) {
                    beeActive = false;
                }
            }

            //Moving clouds
            //Cloud 1 
            if (!cloud1Active) {
                //How fast is the cloud
                srand((int)time(0) * 10);
                cloud1Speed = rand() % 200;

                //How high is the cloud
                srand((int)time(0) * 10);
                float cloud1Height = rand() % 150;
                spriteCloud1.setPosition(-200, cloud1Height);
                cloud1Active = true;
            }
            else {
                spriteCloud1.setPosition(spriteCloud1.getPosition().x + (cloud1Speed * dt.asSeconds()), spriteCloud1.getPosition().y);
                //Has the cloud1 reached the right hand edge of the screen
                if (spriteCloud1.getPosition().x > 1366) {
                    cloud1Active = false;
                }
            }
            //Cloud 2 
            if (!cloud2Active) {
                //How fast is the cloud
                srand((int)time(0) * 20);
                cloud2Speed = (rand() % 200);

                //How high is the cloud
                srand((int)time(0) * 10);
                float cloud2Height = (rand() % 200) - 150;
                spriteCloud2.setPosition(-200, cloud2Height);
                cloud2Active = true;
            }
            else {
                spriteCloud2.setPosition(spriteCloud1.getPosition().x + (cloud2Speed * dt.asSeconds()), spriteCloud2.getPosition().y);
                //Has the cloud1 reached the right hand edge of the screen
                if (spriteCloud1.getPosition().x > 1366) {
                    cloud1Active = false;
                }
            }
            //Cloud 3 
            if (!cloud3Active) {
                //How fast is the cloud
                srand((int)time(0) * 30);
                cloud3Speed = rand() % 200;

                //How high is the cloud
                srand((int)time(0) * 10);
                float cloud3Height = (rand() % 450) - 150;
                spriteCloud3.setPosition(-200, cloud3Height);
                cloud3Active = true;
            }
            else {
                spriteCloud3.setPosition(spriteCloud3.getPosition().x + (cloud3Speed * dt.asSeconds()), spriteCloud3.getPosition().y);
                //Has the cloud1 reached the right hand edge of the screen
                if (spriteCloud3.getPosition().x > 1366) {
                    cloud3Active = false;
                }
            }

            //Update the score text
            std::stringstream ss;
            ss << "Score = " << score;
            scoreText.setString(ss.str());

        }
        /* Draw the scene*/
       
        //Clear everything from the last frame
        window.clear();
        //Drawing the scene
        window.draw(spriteBackground);

        //Drawing the clouds 
        window.draw(spriteCloud1);
        window.draw(spriteCloud2);
        window.draw(spriteCloud3);

        //Drawing the trees
        window.draw(spriteTree);

        //Drawing the bee
        window.draw(spriteBee);

        //Drawing the score
        window.draw(scoreText);

        //Drawing the time-bar
        window.draw(timeBar);

        //Drawing the message
        if (paused) {
            window.draw(messageText);
        }
        //Show everything just drew
        window.display();
        score++;
    }

    return 0;
}

// Ejecutar programa: Ctrl + F5 o menú Depurar > Iniciar sin depurar
// Depurar programa: F5 o menú Depurar > Iniciar depuración

// Sugerencias para primeros pasos: 1. Use la ventana del Explorador de soluciones para agregar y administrar archivos
//   2. Use la ventana de Team Explorer para conectar con el control de código fuente
//   3. Use la ventana de salida para ver la salida de compilación y otros mensajes
//   4. Use la ventana Lista de errores para ver los errores
//   5. Vaya a Proyecto > Agregar nuevo elemento para crear nuevos archivos de código, o a Proyecto > Agregar elemento existente para agregar archivos de código existentes al proyecto
//   6. En el futuro, para volver a abrir este proyecto, vaya a Archivo > Abrir > Proyecto y seleccione el archivo .sln
