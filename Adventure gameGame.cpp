#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// Player constructor
Player::Player(std::string n, std::string cl) 
    : name(n), health(100), attackPower(10), defense(5), level(1), experience(0), magic(50), className(cl), isPoisoned(false), isStunned(false), hasLeveledUp(false), skillPoints(0) {

    if (className == "Warrior") {
        attackPower = 15;
        defense = 10;
        magic = 0;
    } else if (className == "Mage") {
        attackPower = 8;
        defense = 5;
        magic = 50;
    } else if (className == "Healer") {
        attackPower = 6;
        defense = 8;
        magic = 40;
    }
}

void Player::attackEnemy(Enemy& e) {
    int damage = attackPower - e.defense;
    if (damage < 0) damage = 0;
    e.health -= damage;
    std::cout << "You attack " << e.name << " for " << damage << " damage.\n";
}

void Player::equipItem(const Item& item) {
    if (item.name == "Sword") {
        attackPower += item.effectValue;
        std::cout << "You equipped " << item.name << ", increasing attack power by " << item.effectValue << ".\n";
    } else if (item.name == "Shield") {
        defense += item.effectValue;
        std::cout << "You equipped " << item.name << ", increasing defense by " << item.effectValue << ".\n";
    }
    // Remove the item from inventory after equipping
    inventory.erase(std::remove_if(inventory.begin(), inventory.end(), [&item](const Item& i) { return i.name == item.name; }), inventory.end());
}

void Player::useItem(const std::string& itemName) {
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->name == itemName) {
            if (itemName == "Healing Potion") {
                health += 30;
                std::cout << "You use a Healing Potion and restore 30 health.\n";
            } else if (itemName == "Mana Potion") {
                magic += 20;
                std::cout << "You use a Mana Potion and gain 20 magic.\n";
            }
            inventory.erase(it);
            return;
        }
    }
    std::cout << "You don't have that item.\n";
}

void Enemy::attackPlayer(Player& p) {
    int damage = attackPower - p.defense;
    if (damage < 0) damage = 0;
    p.health -= damage;
    std::cout << name << " attacks you for " << damage << " damage.\n";
}

void Player::collectItem(const Item& item) {
    inventory.push_back(item);
    std::cout << "You collect " << item.name << ".\n";
}

void Player::showInventory() {
    std::cout << "Your inventory:\n";
    for (const auto& item : inventory) {
        std::cout << item.name << " - " << item.description << "\n";
    }
}

void Player::displayStats() {
    std::cout << "Player: " << name << "\nHealth: " << health << "\nAttack Power: " << attackPower << "\nDefense: " << defense
              << "\nMagic: " << magic << "\nLevel: " << level << "\nExperience: " << experience << "\nClass: " << className << "\nSkill Points: " << skillPoints << "\n";
}

void Player::checkLevelUp() {
    int xpForNextLevel = level * 100;
    if (experience >= xpForNextLevel) {
        level++;
        attackPower += 5;
        defense += 2;
        magic += 10;
        skillPoints += 2;
        experience = 0;
        std::cout << "You leveled up to level " << level << "!\n";
    }
}

void Player::learnNewSkill(const std::string& skillName) {
    if (std::find(learnedSkills.begin(), learnedSkills.end(), skillName) == learnedSkills.end()) {
        learnedSkills.push_back(skillName);
        std::cout << "You learned a new skill: " << skillName << "!\n";
    } else {
        std::cout << "You already know this skill.\n";
    }
}

void Player::applySkill(const std::string& skillName, Enemy& enemy) {
    if (skillName == "Fireball" && magic >= 20) {
        int damage = 30;
        enemy.health -= damage;
        magic -= 20;
        std::cout << "You cast Fireball! " << enemy.name << " takes " << damage << " damage.\n";
    } else if (skillName == "Healing Wave" && magic >= 15) {
        heal(25);
        magic -= 15;
        std::cout << "You cast Healing Wave! You restore 25 health.\n";
    } else {
        std::cout << "You don't have enough magic or that skill is unknown.\n";
    }
}

void Player::applyPoison() {
    if (isPoisoned) {
        health -= 5;
        std::cout << "You are poisoned! You lose 5 health.\n";
    }
}

void Player::applyStun() {
    if (isStunned) {
        std::cout << "You are stunned and cannot attack this turn!\n";
    }
}

void Player::heal(int amount) {
    health += amount;
    if (health > 100) health = 100; // Max health is 100
}

Room::Room(std::string d) : description(d), enemy(nullptr), isLocked(false), questItem(""), isVisited(false) {}

void Room::addEnemy(Enemy* e) {
    enemy = e;
}

void Room::addItem(const Item& item) {
    items.push_back(item);
}

void Room::lockRoom(const std::string& itemNeeded) {
    isLocked = true;
    questItem = itemNeeded;
}

void Room::unlockRoom() {
    isLocked = false;
    questItem = "";
}

void Room::markAsVisited() {
    isVisited = true;
}

bool Room::hasQuestItem() {
    return !questItem.empty();
}

void Quest::completeQuest() {
    isCompleted = true;
}

Game::Game(std::string playerName, std::string className)
    : player(playerName, className), currentRoomIndex(0), gameWon(false), isQuestActive(false), totalXPRequiredForLevelUp(100) {}

void Game::start() {
    std::cout << "Welcome to the adventure game, " << player.name << " the " << player.className << "!\n";
    while (player.health > 0 && !gameWon) {
        displayRoom();
        handleInput();
        applyRoomEffects();
        randomRoomEvent(); // Introduce random events
        if (rooms[currentRoomIndex].enemy) {
            battleEnemy();
        }
        if (currentRoomIndex == rooms.size() - 1 && gameWon) {
            std::cout << "Congratulations! You have won the game by defeating the final boss.\n";
            break;
        }
    }
    if (!gameWon) {
        std::cout << "Game Over! You died.\n";
    }
}

void Game::displayRoom() {
    std::cout << "\nYou are in a new room. " << rooms[currentRoomIndex].description << "\n";

    if (rooms[currentRoomIndex].isLocked) {
        std::cout << "This room is locked. You need to find the " << rooms[currentRoomIndex].questItem << " to unlock it.\n";
    }

    for (auto& item : rooms[currentRoomIndex].items) {
        std::cout << "Item found: " << item.name << " - " << item.description << "\n";
    }
}

void Game::moveRoom(int direction) {
    if (direction == 0 && currentRoomIndex < rooms.size() - 1) {
        if (rooms[currentRoomIndex].isLocked) {
            std::cout << "This room is locked. You need to unlock it first.\n";
            return;
        }
        currentRoomIndex++;
    } else if (direction == 1 && currentRoomIndex > 0) {
        currentRoomIndex--;
    } else {
        std::cout << "Can't move in that direction.\n";
    }
}

void Game::battleEnemy() {
    if (rooms[currentRoomIndex].enemy) {
        Enemy& enemy = *rooms[currentRoomIndex].enemy;
        while (enemy.health > 0 && player.health > 0) {
            player.applyPoison();
            player.applyStun();
            player.attackEnemy(enemy);
            if (enemy.health > 0) {
                enemy.attackPlayer(player);
            }
        }
        if (enemy.health <= 0) {
            std::cout << "You defeated " << enemy.name << "!\n";
            player.experience += 50;
            player.checkLevelUp();
            delete rooms[currentRoomIndex].enemy;
            rooms[currentRoomIndex].enemy = nullptr;
        }
    }
}

void Game::applyRoomEffects() {
    Room& currentRoom = rooms[currentRoomIndex];
    if (!currentRoom.isVisited) {
        std::cout << "You sense something unusual in the room...\n";
        if (currentRoomIndex % 2 == 0) {
            std::cout << "A magical aura strengthens you!\n";
            player.health += 10;
            if (player.health > 100) player.health = 100;
        } else {
            std::cout << "A trap is triggered! You lose 10 health.\n";
            player.health -= 10;
        }
        currentRoom.markAsVisited();
    }
}

void Game::handleInput() {
    std::string command;
    std::cout << "What would you like to do? (move, inventory, stats, use, equip, unlock, quest, skills): ";
    std::cin >> command;

    if (command == "move") {
        int direction;
        std::cout << "Enter direction (0 for next room, 1 for previous room): ";
        std::cin >> direction;
        moveRoom(direction);
    } else if (command == "inventory") {
        player.showInventory();
    } else if (command == "stats") {
        player.displayStats();
    } else if (command == "use") {
        std::string itemName;
        std::cout << "Which item would you like to use? ";
        std::cin >> itemName;
        player.useItem(itemName);
    } else if (command == "equip") {
        std::string itemName;
        std::cout << "Which item would you like to equip? ";
        std::cin >> itemName;
        for (auto& item : player.inventory) {
            if (item.name == itemName) {
                player.equipItem(item);
                break;
            }
        }
    } else if (command == "unlock") {
        std::string itemName;
        std::cout << "Enter the item name to unlock the room: ";
        std::cin >> itemName;
        if (rooms[currentRoomIndex].questItem == itemName) {
            rooms[currentRoomIndex].unlockRoom();
            std::cout << "You unlocked the room!\n";
        } else {
            std::cout << "You don't have the required item.\n";
        }
    } else if (command == "quest") {
        std::cout << "Current Quest: Find the " << rooms[currentRoomIndex].questItem << " to unlock the next room.\n";
    } else if (command == "skills") {
        showSkills();
    } else {
        std::cout << "Unknown command.\n";
    }
}

void Game::showSkills() {
    std::cout << "Available Skills: \n";
    for (const auto& skill : player.learnedSkills) {
        std::cout << "- " << skill << "\n";
    }
    if (player.className == "Mage") {
        std::cout << "1. Fireball (Cost: 20 magic)\n";
        std::cout << "2. Healing Wave (Cost: 15 magic)\n";
    }
}

void Game::updateQuest() {
    if (isQuestActive) {
        Quest& quest = quests.back();
        if (player.inventory.empty() || player.inventory[0].name != quest.questItemNeeded) {
            std::cout << "You need to find the quest item.\n";
        } else {
            quest.completeQuest();
            std::cout << "Quest Completed!\n";
            isQuestActive = false;
            grantQuestReward();
        }
    }
}

void Game::grantQuestReward() {
    std::cout << "You gained 100 experience for completing the quest.\n";
    player.experience += 100;
    player.checkLevelUp();
}

void Game::randomRoomEvent() {
    std::srand(std::time(0));
    int eventChance = std::rand() % 100;

    if (eventChance < 20) {
        std::cout << "You found a hidden treasure chest! It contains a rare item.\n";
        Item rareItem("Rare Gem", "A mystical gem that sparkles with unknown power.", 50);
        player.collectItem(rareItem);
    } else if (eventChance < 40) {
        std::cout << "You triggered a trap! Lose 15 health.\n";
        player.health -= 15;
    } else {
        std::cout << "The room is eerily quiet. Nothing happens.\n";
    }
}
