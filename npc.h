#pragma once

#include <string>
#include <memory>
#include <random>

class BattleVisitor;

class NPC {
protected:
    double x;
    double y;
    std::string name;
    bool alive;
    int moveDistance;
    int killDistance;
    
    static std::mt19937 rng;
    
public:
    NPC(double x, double y, std::string name, int moveDist, int killDist);
    virtual ~NPC() = default;

    virtual std::string getType() const = 0;
    virtual void accept(BattleVisitor& visitor, NPC& other) = 0;
    
    void moveRandom();
    bool isInKillRange(const NPC& other) const;
    double distanceTo(const NPC& other) const;
    
    double getX() const;
    double getY() const;
    std::string getName() const;
    bool isAlive() const;
    void die();
    int getMoveDistance() const;
    int getKillDistance() const;
    
    static void initializeRNG();
};

class Bear : public NPC {
public:
    Bear(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
};

class Vip : public NPC {
public:
    Vip(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
};

class Vihyhol : public NPC {
public:
    Vihyhol(double x, double y, std::string name);
    std::string getType() const override;
    void accept(BattleVisitor& visitor, NPC& other) override;
};