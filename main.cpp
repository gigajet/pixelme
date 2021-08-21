#include <sfml/Graphics.hpp>
#include "presenter/MapEditorView.h"
#include "Resource.h"

int main(int argc, char **argv)
{
    R r;
    sf::RenderWindow window(
        sf::VideoMode(680, 480),
        "Pixel Map Editor");
    // Edit here
    View *view = new MapEditorView(r.fontVerdana, r.blank,
        r.target, r.stickTarget, r.blocked, r.occupiedRed,
        r.occupiedBlue, r.occupiedGreen);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            view->dispatchHandle(event);
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear(sf::Color::Black);
        view->dispatchDraw(&window);
        window.display();
    }
}