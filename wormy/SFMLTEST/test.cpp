
////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <stdio.h>
#include <iostream>
using namespace std;

#include <SFML/Graphics.hpp>


////////////////////////////////////////////////////////////
/// Entry point of application
///
/// \return Application exit code
///
////////////////////////////////////////////////////////////
int main( int argc, char **argv )
{
    char path[1024];
    getcwd( path, 1024 );
    sf::String strpath;
    strpath.SetFont( sf::Font::GetDefaultFont());
    strpath.SetSize( 12 );
    strpath.SetText( path );

    // Create the main rendering window
    sf::RenderWindow App(sf::VideoMode(800, 600, 32), "SFML Graphics");

    // Start game loop
    while (App.IsOpened())
    {
        // Process events
        sf::Event Event;
        while (App.GetEvent(Event))
        {
            // Close window : exit
            if (Event.Type == sf::Event::Closed)
                App.Close();

            // A key has been pressed
            if (Event.Type == sf::Event::KeyPressed)
            {
                // Escape key : exit
                if (Event.Key.Code == sf::Key::Escape)
                    App.Close();

                // F1 key : capture a screenshot
                if (Event.Key.Code == sf::Key::F1)
                {
                    sf::Image Screen = App.Capture();
                    Screen.SaveToFile("screenshot.jpg");
                }
            }
        }

        // Clear the screen with red color
        App.Clear(sf::Color(200, 0, 0));
        App.Draw( strpath );
        // Display window contents on screen
        App.Display();
    }

    return EXIT_SUCCESS;
}

