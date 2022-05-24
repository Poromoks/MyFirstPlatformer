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

    Texture background;
    background.loadFromFile("textures/oak_woods_v1.0/background/background_layer_1.png");
    Sprite backgroundSprite;
    backgroundSprite.setTexture(background);
    backgroundSprite.setScale(4, 4);

    Texture tiles;
    tiles.loadFromFile("textures/oak_woods_v1.0/oak_woods_tileset.png");
    Sprite tile;
    tile.setTexture(tiles);


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
        window.draw(backgroundSprite);

        for (int i = 0; i < H; i++)
            for (int j = 0; j < W; j++) {
                rectangle.setTexture(&tiles);
                rectangle.setPosition(j * 32, i * 32);
                if (TileMap[i][j] == 'B')
                    rectangle.setTextureRect(IntRect(120, 216, 23, 23));
                else if (TileMap[i][j] == 'A')
                    rectangle.setTextureRect(IntRect(0, 23, 23, 23));
                else if (TileMap[i][j] == 'D')
                    rectangle.setTextureRect(IntRect(72, 23, 23, 23));
                else if (TileMap[i][j] == 'Q')
                    rectangle.setTextureRect(IntRect(0, 0, 23, 23));
                else if (TileMap[i][j] == 'E')
                    rectangle.setTextureRect(IntRect(72, 0, 23, 23));
                if (TileMap[i][j] != ' ')
                    window.draw(rectangle);
            }

        for (auto& player : players) {
            window.draw(player->sprite);
        }

        window.display();
    }

    return 0;
}