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

// WORKS

// TEST_F(ManagerTest, createVar) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     EXPECT_EQ(var_a, 2);
//     EXPECT_EQ(var_b, 3);
//     EXPECT_EQ(var_c, 4);
//     EXPECT_EQ(var_d, 5);
// }

// WORKS

// TEST_F(ManagerTest, True) {
//     BDD_ID var_true = manager.True();
//     EXPECT_EQ(var_true, 1);
// }

// WORKS

// TEST_F(ManagerTest, False) {
//     BDD_ID var_false = manager.False();
//     EXPECT_EQ(var_false, 0);
// }

// TEST_F(ManagerTest, isConstant) {

//     BDD_ID var_true = manager.True();
//     BDD_ID var_false = manager.False();
//     BDD_ID var_a = manager.createVar("a");

//     EXPECT_TRUE(manager.isConstant(var_true));
//     EXPECT_TRUE(manager.isConstant(var_false));
//     EXPECT_FALSE(manager.isConstant(var_a));

// }

// TEST_F(ManagerTest, isVariable) {

//     BDD_ID var_true = manager.True();
//     BDD_ID var_false = manager.False();
//     BDD_ID var_a = manager.createVar("a");

//     EXPECT_FALSE(manager.isVariable(var_true));
//     EXPECT_FALSE(manager.isVariable(var_false));
//     EXPECT_TRUE(manager.isVariable(var_a));

// }
// TEST_F(ManagerTest, uniqueTableSize){
//     EXPECT_EQ(manager.uniqueTableSize(), 2);

//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     EXPECT_EQ(manager.uniqueTableSize(), 6);
// }
// TEST_F(ManagerTest, topVar) {
//     //case of itself
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     EXPECT_EQ(manager.topVar(var_a), 2);
//     EXPECT_EQ(manager.topVar(var_b), 3);

//     //other cases()
//     BDD_ID aOR2 = manager.or2(var_a, var_b);
//     EXPECT_EQ(aOR2, 6);
//     EXPECT_EQ(manager.topVar(aOR2), 2);

//     BDD_ID cANDd = manager.and2(var_c, var_d);
//     EXPECT_EQ(cANDd, 7);
//     EXPECT_EQ(manager.topVar(cANDd), 4);

//     BDD_ID f = manager.and2(aOR2, cANDd);
//     EXPECT_EQ(f, 9);
//     EXPECT_EQ(manager.topVar(f), 2);
// }

// TEST_F(ManagerTest, ite) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     BDD_ID ite_aORb = manager.ite(var_a, 1, var_b);
//     BDD_ID ite_cANDd = manager.ite(var_c, var_d, 0);
//     BDD_ID ite_f = manager.ite(ite_aORb, ite_cANDd, 0);

//     EXPECT_EQ(ite_aORb, 6);
//     EXPECT_EQ(ite_cANDd, 7);
//     EXPECT_EQ(ite_f, 9);
// }


// TEST_F(ManagerTest, coFactorTrue) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     BDD_ID aORb = manager.or2(var_a, var_b);
//     BDD_ID cANDd = manager.and2(var_c, var_d);
//     BDD_ID f = manager.and2(aORb, cANDd);

//     EXPECT_EQ(manager.coFactorTrue(var_a, var_a), 1);
//     EXPECT_EQ(manager.coFactorTrue(var_a, 1), var_a);
//     EXPECT_EQ(manager.coFactorTrue(1, var_a), 1);
//     EXPECT_EQ(manager.coFactorTrue(var_b, var_a), var_b);
//     EXPECT_EQ(manager.coFactorTrue(var_d, var_c), var_d);
//     EXPECT_EQ(manager.coFactorTrue(aORb, var_a), 1);
//     EXPECT_EQ(manager.coFactorTrue(cANDd, var_a), cANDd);
// }



TEST_F(ManagerTest, coFactorTrueNonTerminal) {
    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");
    BDD_ID aORb = manager.and2(var_a, var_b);


    EXPECT_EQ(manager.coFactorTrue(aORb, var_b), var_a);

}


TEST_F(ManagerTest, coFactorFalse) {
    BDD_ID var_a = manager.createVar("a");
    BDD_ID var_b = manager.createVar("b");
    BDD_ID var_c = manager.createVar("c");
    BDD_ID var_d = manager.createVar("d");

    BDD_ID aORb = manager.or2(var_a, var_b);
    BDD_ID cANDd = manager.and2(var_c, var_d);
    BDD_ID f = manager.and2(aORb, cANDd);

    EXPECT_EQ(manager.coFactorFalse(var_a, var_a), 0);
    EXPECT_EQ(manager.coFactorFalse(var_a, 0), var_a);
    EXPECT_EQ(manager.coFactorFalse(0, var_a), 0);
    EXPECT_EQ(manager.coFactorFalse(var_b, var_a), var_b);
    EXPECT_EQ(manager.coFactorFalse(var_d, var_c), var_d);
    EXPECT_EQ(manager.coFactorFalse(aORb, var_a), var_b);
    EXPECT_EQ(manager.coFactorFalse(cANDd, var_a), cANDd);
    EXPECT_EQ(manager.coFactorFalse(cANDd, var_c), 0);
}

// TEST_F(ManagerTest, neg) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

    
//     BDD_ID NotA = manager.neg(var_a);
//     EXPECT_EQ(NotA, 6);
//     EXPECT_EQ(manager.topVar(NotA), 2);
//     // EXPECT_EQ(manager.BDD_Var_Table[NotA].low, 1);
//     // EXPECT_EQ(manager.BDD_Var_Table[NotA].high, 0);


// }
}

#endif
