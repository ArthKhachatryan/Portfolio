#include "Game.h"
#include <iostream>
#include <vector>

void setupGame(Game& game) {
    // Rooms
    Room room1("A dark and damp cave.");
    Room room2("A sunlit forest clearing.");
    Room room3("A mysterious ancient temple.");

    // Add enemies to rooms
    Enemy* goblin = new Enemy("Goblin", 50, 5, 2, 0);
    Enemy* troll = new Enemy("Troll", 100, 15, 5, 2);
    Enemy* dragon = new Enemy("Dragon", 200, 25, 10, 5, true);
    room1.addEnemy(goblin);
    room2.addEnemy(troll);
    room3.addEnemy(dragon);

    // Add items to rooms
    room1.addItem(Item("Healing Potion", "Restores 30 health.", 30));
    room2.addItem(Item("Mana Potion", "Restores 20 magic.", 20));
    room3.addItem(Item("Golden Key", "Unlocks the temple room."));

    room3.lockRoom("Golden Key");

    // Add rooms to the game
    game.rooms.push_back(room1);
    game.rooms.push_back(room2);
    game.rooms.push_back(room3);

    Quest findKey("Find the Golden Key to unlock the ancient temple.", "Golden Key");
    game.quests.push_back(findKey);
}

int main() {
    std::string playerName;
    std::string playerClass;

    std::cout << "Enter your player name: ";
    std::cin >> playerName;

    std::cout << "Choose your class (Warrior, Mage, Healer): ";
    std::cin >> playerClass;

    if (playerClass != "Warrior" && playerClass != "Mage" && playerClass != "Healer") {
        std::cout << "Invalid class. Defaulting to Warrior." << std::endl;
        playerClass = "Warrior";
    }

    Game game(playerName, playerClass);

    setupGame(game);

    // Start the game
    game.start();

    return 0;
}
