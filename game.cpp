#include "game.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <future>
#include <vector>
#include <algorithm>
#include "npc_factory.h"
#include "visitor.h"

Game::Game() : gameRunning(false) {
    NPC::initializeRNG();
}

Game::~Game() {
    stop();
}

void Game::initialize() {
    std::unique_lock lock(npcsMutex);
    npcs = NPCFactory::createRandomNPCs(GameConfig::TOTAL_NPCS);
}

void Game::run() {
    gameRunning = true;
    
    std::thread movement(&Game::movementThread, this);
    std::thread battleDetection(&Game::battleDetectionThread, this);
    std::thread mapPrinting(&Game::printMapThread, this);
    
    std::this_thread::sleep_for(std::chrono::seconds(GameConfig::GAME_DURATION_SECONDS));
    
    stop();
    
    movement.join();
    battleDetection.join();
    mapPrinting.join();
    
    printSurvivors();
}

void Game::stop() {
    gameRunning = false;
}

void Game::movementThread() {
    while (gameRunning) {
        moveNPCs();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Game::battleDetectionThread() {
    while (gameRunning) {
        detectBattles();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void Game::battleThread(NPC& npc1, NPC& npc2) {
    if (!npc1.isAlive() || !npc2.isAlive()) return;
    
    BattleLogicVisitor visitor;
    npc1.accept(visitor, npc2);
    
    {
        std::lock_guard<std::mutex> coutLock(coutMutex);
        if (!npc1.isAlive()) {
            std::cout << npc2.getType() << " " << npc2.getName() 
                      << " killed " << npc1.getType() << " " << npc1.getName() << std::endl;
        }
        if (!npc2.isAlive()) {
            std::cout << npc1.getType() << " " << npc1.getName() 
                      << " killed " << npc2.getType() << " " << npc2.getName() << std::endl;
        }
    }
}

void Game::printMapThread() {
    while (gameRunning) {
        printMap();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void Game::moveNPCs() {
    std::shared_lock lock(npcsMutex);
    for (auto& npc : npcs) {
        if (npc->isAlive()) {
            npc->moveRandom();
        }
    }
}

void Game::detectBattles() {
    std::vector<std::future<void>> battles;
    
    {
        std::shared_lock lock(npcsMutex);
        for (size_t i = 0; i < npcs.size(); ++i) {
            for (size_t j = i + 1; j < npcs.size(); ++j) {
                if (npcs[i]->isAlive() && npcs[j]->isAlive() && 
                    npcs[i]->isInKillRange(*npcs[j])) {
                    battles.push_back(std::async(std::launch::async, 
                        &Game::battleThread, this, 
                        std::ref(*npcs[i]), 
                        std::ref(*npcs[j])));
                }
            }
        }
    }
    
    for (auto& battle : battles) {
        battle.wait();
    }
}

void Game::printMap() const {
    const int width = GameConfig::MAP_WIDTH;
    const int height = GameConfig::MAP_HEIGHT;
    
    std::vector<std::vector<char>> map(height, std::vector<char>(width, '.'));
    
    {
        std::shared_lock lock(npcsMutex);
        for (const auto& npc : npcs) {
            if (npc->isAlive()) {
                int x = static_cast<int>(npc->getX());
                int y = static_cast<int>(npc->getY());
                
                if (x >= 0 && x < width && y >= 0 && y < height) {
                    char symbol = '.';
                    if (npc->getType() == "Bear") symbol = 'B';
                    else if (npc->getType() == "Vip") symbol = 'V';
                    else if (npc->getType() == "Vihyhol") symbol = 'H';
                    
                    map[y][x] = symbol;
                }
            }
        }
    }
    
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "\nКарта игры:\n";
    for (int y = 0; y < height; y += 2) {
        for (int x = 0; x < width; x += 2) {
            std::cout << map[y][x];
        }
        std::cout << std::endl;
    }
    std::cout << "B-Медведь, V-Выпь, H-Выхухоль" << std::endl;
}

std::vector<std::unique_ptr<NPC>> Game::getSurvivors() const {
    std::shared_lock lock(npcsMutex);
    std::vector<std::unique_ptr<NPC>> survivors;
    
    for (const auto& npc : npcs) {
        if (npc->isAlive()) {
            survivors.push_back(std::make_unique<NPC>(*npc));
        }
    }
    
    return survivors;
}

void Game::printSurvivors() const {
    auto survivors = getSurvivors();
    
    std::lock_guard<std::mutex> coutLock(coutMutex);
    std::cout << "\n=== Survivor NPC ===" << std::endl;
    std::cout << "Всего выжило: " << survivors.size() << std::endl;
    
    for (const auto& npc : survivors) {
        std::cout << npc->getType() << " " << npc->getName() 
                  << " (" << npc->getX() << ", " << npc->getY() << ")" << std::endl;
    }
}