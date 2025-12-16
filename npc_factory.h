#pragma once

#include <memory>
#include <string>
#include <vector>
#include "npc.h"

class NPCFactory {
public:
    static std::unique_ptr<NPC> createNPC(const std::string& type, double x, double y, const std::string& name);
    static std::unique_ptr<NPC> createRandomNPC();
    static std::vector<std::unique_ptr<NPC>> createRandomNPCs(int count);
};
