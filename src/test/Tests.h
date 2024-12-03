//
// Created by tobias on 21.11.16.
//

#ifndef VDSPROJECT_TESTS_H
#define VDSPROJECT_TESTS_H

#include <gtest/gtest.h>
#include "../Manager.h"

namespace ClassProject {

// class ManagerTest : public ::testing::Test  {
//     protected:
//         Manager manager;
// };

// // WORKS

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

// // WORKS

// TEST_F(ManagerTest, True) {
//     BDD_ID var_true = manager.True();
//     EXPECT_EQ(var_true, 1);
// }

// // WORKS

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
//     // BDD_ID ite_cANDd = manager.ite(var_c, var_d, 0);
//     // BDD_ID ite_f = manager.ite(ite_aORb, ite_cANDd, 0);

//     EXPECT_EQ(ite_aORb, 6);
//     // EXPECT_EQ(ite_cANDd, 7);
//     // EXPECT_EQ(ite_f, 9);
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



// TEST_F(ManagerTest, coFactorTrueNonTerminal) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID aORb = manager.and2(var_a, var_b);


//     EXPECT_EQ(manager.coFactorTrue(aORb, var_b), var_a);

// }


// TEST_F(ManagerTest, coFactorFalse) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     BDD_ID aORb = manager.or2(var_a, var_b);
//     BDD_ID cANDd = manager.and2(var_c, var_d);
//     BDD_ID f = manager.and2(aORb, cANDd);

//     EXPECT_EQ(manager.coFactorFalse(var_a, var_a), 0);
//     EXPECT_EQ(manager.coFactorFalse(var_a, 0), var_a);
//     EXPECT_EQ(manager.coFactorFalse(0, var_a), 0);
//     EXPECT_EQ(manager.coFactorFalse(var_b, var_a), var_b);
//     EXPECT_EQ(manager.coFactorFalse(var_d, var_c), var_d);
//     EXPECT_EQ(manager.coFactorFalse(aORb, var_a), var_b);
//     EXPECT_EQ(manager.coFactorFalse(cANDd, var_a), cANDd);
//     EXPECT_EQ(manager.coFactorFalse(cANDd, var_c), 0);

//     // Non-terminal
//     // both subgraphs rely on c.
//     // so if c=0, then f=0.
//     EXPECT_EQ(manager.coFactorFalse(f, var_c), 0);

// }

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
// TEST_F(ManagerTest, getoptVarName) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");
//     BDD_ID var_c = manager.createVar("c");
//     BDD_ID var_d = manager.createVar("d");

//     BDD_ID aANDb = manager.and2(var_a, var_b);
//     std::string label = manager.getTopVarName(aANDb);
//     EXPECT_EQ(label, "a");

// }

// TEST_F (ManagerTest, findNodes) {

//     BDD_ID a = manager.createVar("a");
//     BDD_ID b = manager.createVar("b");
//     BDD_ID c = manager.createVar("c");
//     BDD_ID d = manager.createVar("d");
//     BDD_ID aORb = manager.or2(a,b);
//     BDD_ID cANDd = manager.and2(c,d);
//     BDD_ID f = manager.and2(aORb,cANDd);
//     std::set<BDD_ID> nodes_of_root, predefined_nodes_of_root;
//     predefined_nodes_of_root = {0, 1, 5, 7, 8, 9};
//     manager.findNodes(f, nodes_of_root);

//     EXPECT_EQ(predefined_nodes_of_root, nodes_of_root);
// }

// TEST_F (ManagerTest, findVars) {

//     BDD_ID a = manager.createVar("a");
//     BDD_ID b = manager.createVar("b");
//     BDD_ID c = manager.createVar("c");
//     BDD_ID d = manager.createVar("d");
//     BDD_ID aORb = manager.or2(a,b);
//     BDD_ID cANDd = manager.and2(c,d);
//     BDD_ID f = manager.and2(aORb,cANDd);
//     std::set<BDD_ID> vars_of_root, predefined_vars_of_root;
//     predefined_vars_of_root = {2,3 , 4, 5};
//     manager.findVars(f, vars_of_root);

//     EXPECT_EQ(predefined_vars_of_root, vars_of_root);
// }

// TEST_F (ManagerTest, visualizeBDD) {
//     BDD_ID a = manager.createVar("a");
//     BDD_ID b = manager.createVar("b");
//     BDD_ID c = manager.createVar("c");
//     BDD_ID d = manager.createVar("d");
//     BDD_ID aORb = manager.or2(a,b);
//     BDD_ID cANDd = manager.and2(c,d);
//     BDD_ID f = manager.and2(aORb,cANDd);
//     std::string filepath = "bdd.dot";
//     manager.visualizeBDD(filepath, f);
// }

// ////////////////////////////////////////////////////////////////////////////////

// TEST_F(ManagerTest, IsVariableTest) /* NOLINT */
// {   
    

//     ClassProject::BDD_ID false_id = manager.False();
//     ClassProject::BDD_ID true_id = manager.True();

//     ClassProject::BDD_ID a_id = manager.createVar("a");
//     ClassProject::BDD_ID b_id = manager.createVar("b");
//     ClassProject::BDD_ID c_id = manager.createVar("c");
//     ClassProject::BDD_ID d_id = manager.createVar("d");


//     ClassProject::BDD_ID a_and_b_id = manager.and2(a_id, b_id);
//     EXPECT_FALSE(manager.isVariable(a_and_b_id));
// }


// TEST_F(ManagerTest, iteOFFICIAL) {
//     BDD_ID var_a = manager.createVar("a");
//     BDD_ID var_b = manager.createVar("b");

//     BDD_ID ite_aANDb = manager.ite(var_a, var_b, 0);
//     BDD_ID ite_bANDa = manager.ite(var_b, var_a, 0);

//     EXPECT_EQ(ite_aANDb, 4);
//     EXPECT_EQ(ite_bANDa, ite_aANDb);
// }

    
// TEST_F(ManagerTest, FindNodesTest) /* NOLINT */
// {

//     std::set<ClassProject::BDD_ID> true_nodes, a_and_b_nodes;
//     ClassProject::BDD_ID false_id = manager.False();
//     ClassProject::BDD_ID true_id = manager.True();
//     ClassProject::BDD_ID a_id = manager.createVar("a");
//     ClassProject::BDD_ID b_id = manager.createVar("b");
//     ClassProject::BDD_ID c_id = manager.createVar("c");
//     ClassProject::BDD_ID d_id = manager.createVar("d");


//     ClassProject::BDD_ID a_and_b_id = manager.and2(a_id, b_id);
//     manager.findNodes(a_and_b_id, a_and_b_nodes);

//     manager.findNodes(true_id, true_nodes);

//     EXPECT_EQ(true_nodes.size(), 1);
//     EXPECT_TRUE(a_and_b_nodes.find(true_id) != true_nodes.end());
// }

// TEST_F(ManagerTest, FindVarsTest) /* NOLINT */
//  {
//     std::set<ClassProject::BDD_ID> true_nodes, a_and_b_nodes;
//     ClassProject::BDD_ID false_id = manager.False();
//     ClassProject::BDD_ID true_id = manager.True();
//     ClassProject::BDD_ID a_id = manager.createVar("a");
//     ClassProject::BDD_ID b_id = manager.createVar("b");
//     ClassProject::BDD_ID c_id = manager.createVar("c");
//     ClassProject::BDD_ID d_id = manager.createVar("d");

//     ClassProject::BDD_ID a_and_b_id = manager.and2(a_id, b_id);

     

//      manager.findVars(a_and_b_id, a_and_b_nodes);

//      EXPECT_EQ(a_and_b_nodes.size(), 2);
//      EXPECT_TRUE(a_and_b_nodes.find(a_id) != a_and_b_nodes.end());
//      EXPECT_TRUE(a_and_b_nodes.find(b_id) != a_and_b_nodes.end());
//  }

// TEST_F(ManagerTest, LAST_test) {
//     ClassProject::BDD_ID false_id = manager.False();
//     ClassProject::BDD_ID true_id = manager.True();

//     ClassProject::BDD_ID a_id = manager.createVar("a");
//     ClassProject::BDD_ID b_id = manager.createVar("b");
//     ClassProject::BDD_ID c_id = manager.createVar("c");
//     ClassProject::BDD_ID d_id = manager.createVar("d");


//     ClassProject::BDD_ID a_and_b_id = manager.and2(a_id, b_id);
//     BDD_ID t1 = manager.ite(b_id, a_id, true_id);
//     BDD_ID t2 = manager.or2(a_and_b_id, manager.neg(b_id));
//     std::cout << "t1: " << t1 << std::endl;
//     std::cout << "t2: " << t2 << std::endl;
//     EXPECT_EQ(t1, t2);
// }


struct ManagerTest : testing::Test {
    std::unique_ptr<ClassProject::Manager> manager = std::make_unique<ClassProject::Manager>();

    ClassProject::BDD_ID false_id = manager->False();
    ClassProject::BDD_ID true_id = manager->True();

    ClassProject::BDD_ID a_id = manager->createVar("a");
    ClassProject::BDD_ID b_id = manager->createVar("b");
    ClassProject::BDD_ID c_id = manager->createVar("c");
    ClassProject::BDD_ID d_id = manager->createVar("d");


    ClassProject::BDD_ID a_and_b_id = manager->and2(a_id, b_id);
};


TEST_F(ManagerTest, IsVariableTest) /* NOLINT */
{
    EXPECT_FALSE(manager->isVariable(a_and_b_id));
}

TEST_F(ManagerTest, FindNodesTest) /* NOLINT */
{

    std::set<ClassProject::BDD_ID> true_nodes, a_and_b_nodes;

    manager->findNodes(true_id, true_nodes);

    EXPECT_EQ(true_nodes.size(), 1);
    EXPECT_TRUE(a_and_b_nodes.find(true_id) != true_nodes.end());

}

TEST_F(ManagerTest, FindVarsTest) /* NOLINT */
{
    std::set<ClassProject::BDD_ID> a_and_b_nodes;

    manager->findVars(a_and_b_id, a_and_b_nodes);

    EXPECT_EQ(a_and_b_nodes.size(), 2);
    EXPECT_TRUE(a_and_b_nodes.find(a_id) != a_and_b_nodes.end());
    EXPECT_TRUE(a_and_b_nodes.find(b_id) != a_and_b_nodes.end());
}

TEST_F(ManagerTest, IteTest) /* NOLINT */
{
    EXPECT_EQ(manager->ite(b_id, a_id, false_id), a_and_b_id);
    EXPECT_EQ(manager->ite(b_id, a_id, true_id), manager->or2(a_and_b_id, manager->neg(b_id)));

}

}

#endif
