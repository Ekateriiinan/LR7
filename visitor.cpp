#include "visitor.h"
#include <random>
#include <iostream>

BattleLogicVisitor::BattleLogicVisitor() {}

bool BattleLogicVisitor::rollDiceAttack() {
    static std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dice(1, 6);
    int attack = dice(rng);
    int defense = dice(rng);
    return attack > defense;
}

void BattleLogicVisitor::visitBearBear(Bear& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitBearVip(Bear& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitBearVihyhol(Bear& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVipBear(Vip& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVipVip(Vip& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVipVihyhol(Vip& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVihyholBear(Vihyhol& attacker, Bear& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVihyholVip(Vihyhol& attacker, Vip& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}

void BattleLogicVisitor::visitVihyholVihyhol(Vihyhol& attacker, Vihyhol& target) {
    if (attacker.distanceTo(target) <= attacker.getKillDistance()) {
        if (rollDiceAttack()) {
            target.die();
        }
    }
}