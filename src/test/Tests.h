//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

namespace ClassProject {

class ManagerTest : public ::testing::Test  {
    protected:
        Manager manager;
};

TEST_F(ManagerTest, createVar) {
    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");
    BDD_ID var_c = manager.createVar("c");
    BDD_ID var_d = manager.createVar("d");

    EXPECT_EQ(var_a, 2);
    EXPECT_EQ(var_b, 3);
    EXPECT_EQ(var_c, 4);
    EXPECT_EQ(var_d, 5);
}

TEST_F(ManagerTest, True) {
    BDD_ID var_true = manager.True();
    EXPECT_EQ(var_true, 1);
}

TEST_F(ManagerTest, False) {
    BDD_ID var_false = manager.False();
    EXPECT_EQ(var_false, 0);
}

TEST_F(ManagerTest, isConstant) {

    BDD_ID var_true = manager.True();
    BDD_ID var_false = manager.False();
    BDD_ID var_a = manager.createVar("a");

    EXPECT_TRUE(manager.isConstant(var_true));
    EXPECT_TRUE(manager.isConstant(var_false));
    EXPECT_FALSE(manager.isConstant(var_a));

}

TEST_F(ManagerTest, isVariable) {

    BDD_ID var_true = manager.True();
    BDD_ID var_false = manager.False();
    BDD_ID var_a = manager.createVar("a");

    EXPECT_FALSE(manager.isVariable(var_true));
    EXPECT_FALSE(manager.isVariable(var_false));
    EXPECT_TRUE(manager.isVariable(var_a));

}
TEST_F(ManagerTest, uniqueTableSize){
    EXPECT_EQ(manager.uniqueTableSize(), 2);

    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");
    BDD_ID var_c = manager.createVar("c");
    BDD_ID var_d = manager.createVar("d");

    EXPECT_EQ(manager.uniqueTableSize(), 6);
}
TEST_F(ManagerTest, topVar) {
    //case of itself
    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");

    EXPECT_EQ(manager.topVar(var_a), 2);
    EXPECT_EQ(manager.topVar(var_b), 3);

    //other cases()
    // BDD_ID var_e = manager.and2(var_a, var_b);

    // EXPECT_EQ(var_e, 4);
    // EXPECT_EQ(manager.topVar(var_e), 2);
}

TEST_F(ManagerTest, ite) {
    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");
    BDD_ID var_c = manager.createVar("c");
    BDD_ID var_d = manager.createVar("d");

    BDD_ID ite_a = manager.ite(var_a, var_b, var_c);
    BDD_ID ite_b = manager.ite(var_b, var_a, var_c);
    BDD_ID ite_c = manager.ite(var_c, var_b, var_a);

    EXPECT_EQ(ite_a, 6);
    EXPECT_EQ(ite_b, 7);
    EXPECT_EQ(ite_c, 8);
}
}
#endif
