#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>

const int WIDTH = 800;
const int HEIGHT = 600;

enum GameState {
    MENU,
    PLAY,
    RECORDS,
    LEVEL,
    GAME_OVER,
    EXIT
};

class Game {
public:
    Game() 
        : window(sf::VideoMode(WIDTH, HEIGHT), "Catch the Falling Object"),
          state(MENU), score(0), gameOver(false), highScore(0), fallingSpeed(0.05f) {
        font.loadFromFile("arial.ttf");
        setupMenu();
        setupLevelMenu();
        reset();
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text menuText[4];
    sf::Text levelText[3];
    sf::Text gameOverText; 
    GameState state;
    int score;
    bool gameOver;
    int highScore;
    sf::CircleShape object;
    sf::Vector2f objectPosition;
    float fallingSpeed;

    void setupMenu() {
        std::string menuItems[4] = { "Play", "Records", "Level", "Exit" };
        for (int i = 0; i < 4; ++i) {
            menuText[i].setFont(font);
            menuText[i].setCharacterSize(30);
            menuText[i].setFillColor(sf::Color::White);
            menuText[i].setString(menuItems[i]);
            menuText[i].setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 60 + i * 40);
        }
    }

    void setupLevelMenu() {
        std::string levelItems[3] = { "Easy", "Medium", "Hard" };
        for (int i = 0; i < 3; ++i) {
            levelText[i].setFont(font);
            levelText[i].setCharacterSize(30);
            levelText[i].setFillColor(sf::Color::White);
            levelText[i].setString(levelItems[i]);
            levelText[i].setPosition(WIDTH / 2 - 50, HEIGHT / 2 - 60 + i * 40);
        }
    }

    void reset() {
        score = 0;
        gameOver = false;
        object.setRadius(20);
        object.setFillColor(sf::Color::Red);
        resetObject();
    }

    void resetObject() {
        objectPosition.x = rand() % (WIDTH - static_cast<int>(object.getRadius() * 2));
        objectPosition.y = 0;
        object.setPosition(objectPosition);
    }

    void handleEvents() {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (state == MENU) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedItemIndex = (selectedItemIndex > 0) ? selectedItemIndex - 1 : 3;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        selectedItemIndex = (selectedItemIndex + 1) % 4;
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        switch (selectedItemIndex) {
                            case 0: state = PLAY; reset(); break; 
                            case 1: state = RECORDS; break; 
                            case 2: state = LEVEL; selectedItemIndex = 0; break; 
                            case 3: window.close(); break; 
                        }
                    }
                }
            } else if (state == PLAY) {
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (object.getGlobalBounds().contains(mousePosition)) {
                        score++;
                        resetObject();
                        if (score > highScore) {
                            highScore = score; 
                        }
                    }
                }
            } else if (state == LEVEL) {
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        selectedItemIndex = (selectedItemIndex > 0) ? selectedItemIndex - 1 : 2;
                    }
                    if (event.key.code == sf::Keyboard::Down) {
                        selectedItemIndex = (selectedItemIndex + 1) % 3;
                    }
                    if (event.key.code == sf::Keyboard::Enter) {
                        switch (selectedItemIndex) {
                            case 0: fallingSpeed = 0.05f; break; 
                            case 1: fallingSpeed = 0.1f; break; 
                            case 2: fallingSpeed = 0.15f; break; 
                        }
                        state = MENU; 
                    }
                }
            } else if (state == RECORDS) {
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    state = MENU; 
                }
            } else if (state == GAME_OVER) { 
                if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
                    state = MENU; 
                }
            }
        }
    }

    void update() {
        if (state == PLAY) {
            objectPosition.y += fallingSpeed; 
            object.setPosition(objectPosition);

            if (objectPosition.y > HEIGHT) {
                gameOver = true;
                state = GAME_OVER; 
            }

            scoreText.setString("Score: " + std::to_string(score));
        }
    }

    void render() {
    window.clear();
    if (state == MENU) {
        for (int i = 0; i < 4; ++i) {
            menuText[i].setFillColor(i == selectedItemIndex ? sf::Color::Yellow : sf::Color::White);
            window.draw(menuText[i]);
        }
    } else if (state == PLAY) {
        window.draw(object);
        scoreText.setFont(font);
        scoreText.setCharacterSize(24);
        scoreText.setFillColor(sf::Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);
    } else if (state == RECORDS) {
        sf::Text recordText("High Score: " + std::to_string(highScore), font, 30);
        recordText.setFillColor(sf::Color::White);
        recordText.setPosition(WIDTH / 2 - 100, HEIGHT / 2 - 15);
        window.draw(recordText);
        sf::Text backText("Press Enter to go back", font, 20);
        backText.setFillColor(sf::Color::White);
        backText.setPosition(WIDTH / 2 - 100, HEIGHT / 2 + 30);
        window.draw(backText);
    } else if (state == LEVEL) {
        for (int i = 0; i < 3; ++i) {
            levelText[i].setFillColor(i == selectedItemIndex ? sf::Color::Yellow : sf::Color::White);
            window.draw(levelText[i]);
        }
    } else if (state == GAME_OVER) {
        
        sf::Text gameOverText("Game Over! Your score: " + std::to_string(score), font, 30);
        gameOverText.setFillColor(sf::Color::White);

        sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
        gameOverText.setPosition((WIDTH - gameOverBounds.width) / 2, HEIGHT / 2 - 15);
        window.draw(gameOverText);

        sf::Text playAgainText("Press Enter to return to menu", font, 20);
        playAgainText.setFillColor(sf::Color::White);

        sf::FloatRect playAgainBounds = playAgainText.getLocalBounds();
        playAgainText.setPosition((WIDTH - playAgainBounds.width) / 2, HEIGHT / 2 + 30);
        window.draw(playAgainText);
    }
    window.display();
}


    int selectedItemIndex = 0;
};

int main() {
    srand(static_cast<unsigned int>(time(0)));
    Game game;
    game.run();
    return 0;
}
