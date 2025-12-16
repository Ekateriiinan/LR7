#pragma once

#include <vector>
#include <memory>
#include <mutex>
#include <shared_mutex>
#include "npc.h"
#include "game_config.h"

class Game {
private:
    std::vector<std::unique_ptr<NPC>> npcs;
    mutable std::shared_mutex npcsMutex;
    std::mutex coutMutex;
    bool gameRunning;
    
    void movementThread();
    void battleDetectionThread();
    void battleThread(NPC& npc1, NPC& npc2);
    void printMapThread();
    
    void moveNPCs();
    void detectBattles();
    void printMap() const;
    
public:
    Game();
    ~Game();
    
    void initialize();
    void run();
    void stop();
    
    std::vector<std::unique_ptr<NPC>> getSurvivors() const;
    void printSurvivors() const;
};