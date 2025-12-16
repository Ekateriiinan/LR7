#include "npc_factory.h"
#include <random>
#include "game_config.h"

std::unique_ptr<NPC> NPCFactory::createNPC(const std::string& type, double x, double y, const std::string& name) {
    if (type == "Bear") {
        return std::make_unique<Bear>(x, y, name);
    } else if (type == "Vip") {
        return std::make_unique<Vip>(x, y, name);
    } else if (type == "Vihyhol") {
        return std::make_unique<Vihyhol>(x, y, name);
    }
    return nullptr;
}

std::unique_ptr<NPC> NPCFactory::createRandomNPC() {
    static std::mt19937 rng(std::random_device{}());
    static std::uniform_real_distribution<double> posDist(0, 99);
    static std::uniform_int_distribution<int> typeDist(0, 2);
    static int npcCounter = 0;
    
    double x = posDist(rng);
    double y = posDist(rng);
    std::string name = "NPC_" + std::to_string(++npcCounter);
    
    int type = typeDist(rng);
    switch (type) {
        case 0: return std::make_unique<Bear>(x, y, name);
        case 1: return std::make_unique<Vip>(x, y, name);
        case 2: return std::make_unique<Vihyhol>(x, y, name);
        default: return std::make_unique<Bear>(x, y, name);
    }
}

std::vector<std::unique_ptr<NPC>> NPCFactory::createRandomNPCs(int count) {
    std::vector<std::unique_ptr<NPC>> npcs;
    npcs.reserve(count);
    
    for (int i = 0; i < count; ++i) {
        npcs.push_back(createRandomNPC());
    }
    
    return npcs;
}