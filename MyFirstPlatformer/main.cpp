#include "SFML/Audio.hpp"
#include "Goblin.h"

#include <iostream>

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1300, 600), "MFP");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    Player player;
    Goblin goblin;
    RectangleShape rectangle(Vector2f(32, 32));
    Clock clock;
    Clock playerAttackClock;
    Clock goblinAttackClock;

    while (window.isOpen())  {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 800;

        player.Update(time);
        goblin.Update(time);

        Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == Keyboard::Escape)
                event.type = Event::Closed;
            if (event.type == Event::Closed)
                window.close();

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::Z) {
                    playerAttackClock.restart();
                    player.isAttacking = true;
                }
            }

            if (event.type == Event::KeyReleased) {
                if (event.key.code == Keyboard::X) {
                    goblinAttackClock.restart();
                    goblin.isAttacking = true;
                }
            }
        }

        window.clear(Color::Black);

        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') {
                    rectangle.setFillColor(Color::Red);
                    rectangle.setPosition(j * 32, i * 32);
                    window.draw(rectangle);

                    if (player.rect.intersects(rectangle.getGlobalBounds()))
                        std::cout << "dd";
                }
            }



        window.draw(player.sprite);
        window.draw(goblin.sprite);

        window.display();
    }

    return 0;
}