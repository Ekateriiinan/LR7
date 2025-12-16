#include "npc.h"
#include <cmath>
#include <random>
#include <algorithm>
#include "game_config.h"
#include "visitor.h"

std::mt19937 NPC::rng(std::random_device{}());

NPC::NPC(double x, double y, std::string name, int moveDist, int killDist)
    : x(x), y(y), name(name), alive(true), moveDistance(moveDist), killDistance(killDist) {}

void NPC::initializeRNG() {
    rng.seed(std::random_device{}());
}

void NPC::moveRandom() {
    if (!alive) return;
    
    std::uniform_int_distribution<int> dirDist(-1, 1);
    std::uniform_int_distribution<int> moveDist(0, moveDistance);
    
    int dx = dirDist(rng) * moveDist(rng);
    int dy = dirDist(rng) * moveDist(rng);
    
    double newX = x + dx;
    double newY = y + dy;
    
    if (newX >= 0 && newX < GameConfig::MAP_WIDTH && 
        newY >= 0 && newY < GameConfig::MAP_HEIGHT) {
        x = newX;
        y = newY;
    }
}

bool NPC::isInKillRange(const NPC& other) const {
    if (!alive || !other.alive) return false;
    return distanceTo(other) <= killDistance;
}

double NPC::distanceTo(const NPC& other) const {
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

double NPC::getX() const { return x; }
double NPC::getY() const { return y; }
std::string NPC::getName() const { return name; }
bool NPC::isAlive() const { return alive; }
void NPC::die() { alive = false; }
int NPC::getMoveDistance() const { return moveDistance; }
int NPC::getKillDistance() const { return killDistance; }

Bear::Bear(double x, double y, std::string name) 
    : NPC(x, y, name, GameConfig::BEAR_MOVE_DISTANCE, GameConfig::BEAR_KILL_DISTANCE) {}

std::string Bear::getType() const { return "Bear"; }

void Bear::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitBearBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitBearVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitBearVihyhol(*this, *vihyhol);
    }
}

Vip::Vip(double x, double y, std::string name)
    : NPC(x, y, name, GameConfig::VIP_MOVE_DISTANCE, GameConfig::VIP_KILL_DISTANCE) {}

std::string Vip::getType() const { return "Vip"; }

void Vip::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitVipBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitVipVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitVipVihyhol(*this, *vihyhol);
    }
}

Vihyhol::Vihyhol(double x, double y, std::string name)
    : NPC(x, y, name, GameConfig::VIHYHOL_MOVE_DISTANCE, GameConfig::VIHYHOL_KILL_DISTANCE) {}

std::string Vihyhol::getType() const { return "Vihyhol"; }

void Vihyhol::accept(BattleVisitor& visitor, NPC& other) {
    if (auto bear = dynamic_cast<Bear*>(&other)) {
        visitor.visitVihyholBear(*this, *bear);
    } else if (auto vip = dynamic_cast<Vip*>(&other)) {
        visitor.visitVihyholVip(*this, *vip);
    } else if (auto vihyhol = dynamic_cast<Vihyhol*>(&other)) {
        visitor.visitVihyholVihyhol(*this, *vihyhol);
    }
}