#include <gtest/gtest.h>
#include "npc.h"
#include "visitor.h"
#include "game_config.h"

TEST(NPCTest, BearCreation) {
    Bear bear(10, 20, "TestBear");
    EXPECT_EQ(bear.getType(), "Bear");
    EXPECT_EQ(bear.getX(), 10);
    EXPECT_EQ(bear.getY(), 20);
    EXPECT_EQ(bear.getName(), "TestBear");
    EXPECT_TRUE(bear.isAlive());
    EXPECT_EQ(bear.getMoveDistance(), GameConfig::BEAR_MOVE_DISTANCE);
    EXPECT_EQ(bear.getKillDistance(), GameConfig::BEAR_KILL_DISTANCE);
}

TEST(NPCTest, VipCreation) {
    Vip vip(30, 40, "TestVip");
    EXPECT_EQ(vip.getType(), "Vip");
    EXPECT_EQ(vip.getMoveDistance(), GameConfig::VIP_MOVE_DISTANCE);
    EXPECT_EQ(vip.getKillDistance(), GameConfig::VIP_KILL_DISTANCE);
}

TEST(NPCTest, VihyholCreation) {
    Vihyhol vihyhol(50, 60, "TestVihyhol");
    EXPECT_EQ(vihyhol.getType(), "Vihyhol");
    EXPECT_EQ(vihyhol.getMoveDistance(), GameConfig::VIHYHOL_MOVE_DISTANCE);
    EXPECT_EQ(vihyhol.getKillDistance(), GameConfig::VIHYHOL_KILL_DISTANCE);
}

TEST(NPCTest, DistanceCalculation) {
    Bear bear1(0, 0, "Bear1");
    Bear bear2(3, 4, "Bear2");
    
    EXPECT_DOUBLE_EQ(bear1.distanceTo(bear2), 5.0);
}

TEST(NPCTest, Death) {
    Bear bear(0, 0, "TestBear");
    EXPECT_TRUE(bear.isAlive());
    bear.die();
    EXPECT_FALSE(bear.isAlive());
}

TEST(NPCTest, KillRange) {
    Bear bear1(0, 0, "Bear1");
    Bear bear2(8, 0, "Bear2"); 
    
    EXPECT_TRUE(bear1.isInKillRange(bear2));
    
    Bear bear3(12, 0, "Bear3"); 
    EXPECT_FALSE(bear1.isInKillRange(bear3));
}

TEST(VisitorTest, BattleVisitorCreation) {
    BattleLogicVisitor visitor;

    EXPECT_TRUE(true);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
