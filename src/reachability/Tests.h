#ifndef VDSPROJECT_REACHABILITY_TESTS_H
#define VDSPROJECT_REACHABILITY_TESTS_H

#include <gtest/gtest.h>
#include "Reachability.h"

using namespace ClassProject;

struct ReachabilityTest : testing::Test {

    std::unique_ptr<ClassProject::ReachabilityInterface> fsm1 = std::make_unique<ClassProject::Reachability>(2);
    std::unique_ptr<ClassProject::ReachabilityInterface> fsm2 = std::make_unique<ClassProject::Reachability>(2, 2);

    std::vector<BDD_ID> stateVars1 = fsm1->getStates();
    std::vector<BDD_ID> inputVars1 = fsm1->getInputs();
    std::vector<BDD_ID> transitionFunctions1;


    std::vector<BDD_ID> stateVars2 = fsm2->getStates();
    std::vector<BDD_ID> inputVars2 = fsm2->getInputs();
    std::vector<BDD_ID> transitionFunctions2;

};

TEST_F(ReachabilityTest, HowTo_Example) { /* NOLINT */

    BDD_ID s0 = stateVars1.at(0);
    BDD_ID s1 = stateVars1.at(1);

    transitionFunctions1.push_back(fsm1->neg(s0)); // s0' = not(s0)
    transitionFunctions1.push_back(fsm1->neg(s1)); // s1' = not(s1)

    fsm1->setTransitionFunctions(transitionFunctions1);

    fsm1->setInitState({false,false});
    ASSERT_EQ(fsm1->stateDistance({false, false}), 0);

    ASSERT_TRUE(fsm1->isReachable({false, false}));
    ASSERT_FALSE(fsm1->isReachable({false, true}));
    ASSERT_FALSE(fsm1->isReachable({true, false}));
    ASSERT_TRUE(fsm1->isReachable({true, true}));
}

TEST_F(ReachabilityTest, Lecture_Example){
    BDD_ID s1 = stateVars2.at(0);
    BDD_ID s2 = stateVars2.at(1);

    BDD_ID x1 = inputVars2.at(0);
    BDD_ID x2 = inputVars2.at(1);
    
    // NOT(x1). (S1+S2)
    transitionFunctions2.push_back(fsm2->and2(fsm2->neg(x1), fsm2->or2(s1, s2)));
    // x2 (x1+S1+S@)
    transitionFunctions2.push_back(fsm2->and2(x2, fsm2->or2(fsm2->or2(x1, s1), s2)));

    fsm2->setTransitionFunctions(transitionFunctions2);

    ASSERT_EQ(fsm2->stateDistance({true, true}),  2);
    ASSERT_EQ(fsm2->stateDistance({false, false}), 0);

    ASSERT_TRUE(fsm2->isReachable({true, true}));
    ASSERT_TRUE(fsm2->isReachable({true, false}));
    
    ASSERT_TRUE(fsm2->isReachable({false, true}));
    ASSERT_TRUE(fsm2->isReachable({false, false}));
    
}

#endif
