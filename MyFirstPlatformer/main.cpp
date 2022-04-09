#include "SFML/Audio.hpp"
#include "Goblin.h"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1300, 600), "MFP");
    window.setFramerateLimit(60);
    window.setVerticalSyncEnabled(true);
    
    std::vector <Player*> players;
    players.push_back(new Player);
    players.push_back(new Goblin);

    Clock clock;
    Clock AttackClock;

    RectangleShape rectangle(Vector2f(32, 32));

    while (window.isOpen())  {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();

        time = time / 800;

        for (auto& player : players) {
            player->Update(time);
        }

        Event event;
        while (window.pollEvent(event)) {
            if (event.key.code == Keyboard::Escape)
                event.type = Event::Closed;
            if (event.type == Event::Closed)
                window.close();

            for (const auto& player : players) {
                player->Move(event, AttackClock);
            }
        }

        window.clear(Color::Black);

        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++) {
                if (TileMap[i][j] == 'B') {
                    rectangle.setFillColor(Color::Red);
                    rectangle.setPosition(j * 32, i * 32);
                    window.draw(rectangle);
                }
            }

        for (auto& player : players) {
            window.draw(player->sprite);
        }

        window.display();
    }

    return 0;
}