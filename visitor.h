#pragma once

#include <memory>
#include "npc.h"
#include "game_config.h"

class BattleVisitor {
public:
    virtual ~BattleVisitor() = default;
    
    virtual void visitBearBear(Bear& attacker, Bear& target) = 0;
    virtual void visitBearVip(Bear& attacker, Vip& target) = 0;
    virtual void visitBearVihyhol(Bear& attacker, Vihyhol& target) = 0;
    
    virtual void visitVipBear(Vip& attacker, Bear& target) = 0;
    virtual void visitVipVip(Vip& attacker, Vip& target) = 0;
    virtual void visitVipVihyhol(Vip& attacker, Vihyhol& target) = 0;
    
    virtual void visitVihyholBear(Vihyhol& attacker, Bear& target) = 0;
    virtual void visitVihyholVip(Vihyhol& attacker, Vip& target) = 0;
    virtual void visitVihyholVihyhol(Vihyhol& attacker, Vihyhol& target) = 0;
};

class BattleLogicVisitor : public BattleVisitor {
public:
    BattleLogicVisitor();
    
    void visitBearBear(Bear& attacker, Bear& target) override;
    void visitBearVip(Bear& attacker, Vip& target) override;
    void visitBearVihyhol(Bear& attacker, Vihyhol& target) override;
    
    void visitVipBear(Vip& attacker, Bear& target) override;
    void visitVipVip(Vip& attacker, Vip& target) override;
    void visitVipVihyhol(Vip& attacker, Vihyhol& target) override;
    
    void visitVihyholBear(Vihyhol& attacker, Bear& target) override;
    void visitVihyholVip(Vihyhol& attacker, Vip& target) override;
    void visitVihyholVihyhol(Vihyhol& attacker, Vihyhol& target) override;
    
private:
    bool rollDiceAttack();
};