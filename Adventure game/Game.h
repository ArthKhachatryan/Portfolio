#ifndef GAME_H
#define GAME_H

#include <string>
#include <vector>
#include <functional>
#include <map>

class Item {
public:
    std::string name;
    std::string description;
    int effectValue;

    Item(std::string n, std::string d, int effect = 0) : name(n), description(d), effectValue(effect) {}
};

class Enemy {
public:
    std::string name;
    int health;
    int attackPower;
    int defense;
    int magicResistance;
    bool isBoss;
    std::function<void(class Player&)> specialAttack;

    Enemy(std::string n, int h, int a, int def, int mr, bool boss = false)
        : name(n), health(h), attackPower(a), defense(def), magicResistance(mr), isBoss(boss) {}

    void attackPlayer(class Player& p);
    void specialAction(class Player& p);
    void resetHealth() { health = 100; }
};

class Player {
public:
    std::string name;
    int health;
    int attackPower;
    int defense;
    int level;
    int experience;
    int magic;
    std::string className;
    std::vector<Item> inventory;
    bool isPoisoned;
    bool isStunned;
    bool hasLeveledUp;
    int skillPoints;
    std::vector<std::string> learnedSkills;

    Player(std::string n, std::string cl);

    void attackEnemy(Enemy& e);
    void collectItem(const Item& item);
    void useItem(const std::string& itemName);
    void equipItem(const Item& item);
    void showInventory();
    void displayStats();
    void checkLevelUp();
    void applyPoison();
    void applyStun();
    void learnNewSkill(const std::string& skillName);
    void applySkill(const std::string& skillName, Enemy& enemy);
    void heal(int amount);
};

class Room {
public:
    std::string description;
    Enemy* enemy;
    std::vector<Item> items;
    bool isLocked;
    std::string questItem;
    bool isVisited;

    Room(std::string d);
    void addEnemy(Enemy* e);
    void addItem(const Item& item);
    void lockRoom(const std::string& itemNeeded);
    void unlockRoom();
    void markAsVisited();
    bool hasQuestItem();
};

class Quest {
public:
    std::string description;
    bool isCompleted;
    std::string questItemNeeded;
    bool requiresAction;

    Quest(std::string desc, std::string itemNeeded = "", bool actionRequired = false)
        : description(desc), isCompleted(false), questItemNeeded(itemNeeded), requiresAction(actionRequired) {}

    void completeQuest();
};

class Game {
public:
    Player player;
    std::vector<Room> rooms;
    std::vector<Quest> quests;
    int currentRoomIndex;
    bool gameWon;
    bool isQuestActive;
    int totalXPRequiredForLevelUp;

    Game(std::string playerName, std::string className);
    void start();
    void displayRoom();
    void moveRoom(int direction);
    void battleEnemy();
    void handleInput();
    void applyRoomEffects();
    void completeQuest();
    void displayQuests();
    void showSkills();
    void grantQuestReward();
    void updateQuest();
    void randomRoomEvent();
};

#endif
