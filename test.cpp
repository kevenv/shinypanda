#include <SFML/Graphics.hpp>
#include <math.h>

#define PI 3.14159265

using namespace sf;


int main()
{

    int xCircle=200,yCircle=150, step=2, xTri=500, yTri=400, angle=0, ouvert=1;
    // create the window
    ContextSettings settings;
    settings.antialiasingLevel = 8;

    RenderWindow window(VideoMode(800, 600), "My window", Style::Default, settings);
    window.setVerticalSyncEnabled(true);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                window.close();
            else if (event.type == sf::Event::LostFocus)
                ouvert = 0;
            else if (event.type == sf::Event::GainedFocus)
                ouvert = 1;
        }

        if (ouvert)
        {
            if(Keyboard::isKeyPressed(Keyboard::Left))
                xCircle -= step;
            if(Keyboard::isKeyPressed(Keyboard::Right))
                xCircle += step;
            if(Keyboard::isKeyPressed(Keyboard::Up))
                yCircle -= step;
            if(Keyboard::isKeyPressed(Keyboard::Down))
                yCircle += step;
            if(Keyboard::isKeyPressed(Keyboard::W))
                yTri -= step;
            if(Keyboard::isKeyPressed(Keyboard::A))
                xTri -= step;
            if(Keyboard::isKeyPressed(Keyboard::S))
                yTri += step;
            if(Keyboard::isKeyPressed(Keyboard::D))
                xTri += step;
            if(Keyboard::isKeyPressed(Keyboard::Q))
                angle += step;
            if(Keyboard::isKeyPressed(Keyboard::E))
                angle -= step;


            // clear the window with black color
            window.clear(Color::Black);

            // draw everything here...
            // window.draw(...);
            CircleShape shape(45);
            shape.setFillColor(Color::Yellow);
            shape.setOutlineThickness(5);
            shape.setOutlineColor(Color::Red);
            shape.setPosition(xCircle,yCircle);

            ConvexShape triangle;
            triangle.setPointCount(3);
            triangle.setPoint(0,Vector2f(xTri+50*cos(angle),yTri+50*sin(angle)));
            triangle.setPoint(1,Vector2f(xTri+50*cos(angle+2*PI/3),yTri+50*sin(angle+2*PI/3)));
            triangle.setPoint(2,Vector2f(xTri+50*cos(angle+4*PI/3),yTri+50*sin(angle+4*PI/3)));
            triangle.setFillColor(Color::Green);

            window.draw(triangle);
            window.draw(shape);
            // end the current frame
            window.display();
        }


    }

    return 0;
}
