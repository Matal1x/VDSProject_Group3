#include "Reachability.h"

namespace ClassProject{

Reachability::Reachability(unsigned int stateSize, unsigned int inputSize)
: ReachabilityInterface(stateSize, inputSize) {
    //error handling 
    if (stateSize == 0) {
        throw std::runtime_error("stateSize can not be zero!");
    }

    for (unsigned int i = 0; i < stateSize; i++) {
        
        //Step 1
        stateVars.push_back(createVar("s" + std::to_string(i)));
        nextStateVars.push_back(createVar("s" + std::to_string(i) + "'")); 
        //Step 2  
        transitionFunctions.push_back(nextStateVars[i]);
        initState.push_back(False());
    }

    std::cout << "step1 and 2 done " << std::endl;
    for (unsigned int i = 0; i < inputSize; i++) {
        inputVars.push_back(createVar("i" + std::to_string(i)));
    }

}

const std::vector<BDD_ID> &Reachability::getStates() const {
    return stateVars;
}

const std::vector<BDD_ID> &Reachability::getInputs() const {
    
    return inputVars;  
 
}

bool Reachability::isReachable(const std::vector<bool> &stateVector) {
    //error handling
    if (stateVector.size() != stateVars.size()) {
        throw std::runtime_error("size does not match with number of state bits");
    }

    //Step 3
    BDD_ID tao = True();
    for(unsigned int i = 0; i < stateVars.size(); i++) {
        tao = and2(tao, xnor2(nextStateVars[i], transitionFunctions[i]));
    }
    std::cout << "step 3 done " << std::endl;
    //Step 4
    BDD_ID Cs = True();
    for(unsigned int i = 0; i < stateVars.size(); i++) {
        Cs = and2(Cs, xnor2(stateVars[i], initState[i]));
    }
    std::cout << "step 4 done " << std::endl;

    //Step 5
    BDD_ID CRit = Cs;
    std::cout << "step 5 done " << std::endl;
    BDD_ID CR, nextImg, currentImg;
    do {
        
        //Step 6
        CR = CRit;
        std::cout << "step 6 done " << std::endl;
        //Step 7
        nextImg = and2(CR, tao);
        std::cout << "step7 and done " << std::endl;
        for(int i = stateVars.size() - 1; i >= 0; i--) {
            nextImg = or2(coFactorTrue(nextImg, stateVars[i]), coFactorFalse(nextImg, stateVars[i]));
        }
        std::cout << "step 7 loop done " << std::endl;
        //Step 8
        currentImg = nextImg;
        for(int i = 0 ; i < stateVars.size(); i++) {
            currentImg = and2(currentImg,xnor2(stateVars[i], nextStateVars[i]));
        }
        for(int i = nextStateVars.size() - 1 ; i >= 0 ; i--){
            currentImg = or2(coFactorTrue(currentImg,nextStateVars[i]), coFactorFalse(currentImg,nextStateVars[i]));
        }
        std::cout << "step 8 done " << std::endl;
        //Step 9
        CRit = or2(CR, currentImg);
        std::cout << "step 9 done " << std::endl;
        //Step 10
    } while (CR != CRit);
    std::cout << "step 10 done " << std::endl;
    //Step 11
    BDD_ID reachable = CR;
    
    for(unsigned int i = 0; i < stateVector.size(); i++) {
        std::cout << "reachable: " << reachable << std::endl;
        std::cout << "stateVector["<< i<< "] = "<<  stateVector[i] <<std::endl;
        if (stateVector[i] == true) {
            reachable = coFactorTrue(reachable, stateVars[i]);
        } else {
            reachable = coFactorFalse(reachable, stateVars[i]);
        }
    }
    std::cout << "step 11 done " << std::endl;
    std::cout << "reachable: " << reachable << std::endl;
   if(reachable == True()) {
       return true;
   } else {
       return false;
   }    

}

int Reachability::stateDistance(const std::vector<bool> &stateVector) {
    //error handling
    if (stateVector.size() != stateVars.size()) {
        throw std::runtime_error("size does not match with number of state bits");
    }

    // Step 3
    BDD_ID tao = True();
    for (unsigned int i = 0; i < stateVars.size(); i++) {
        tao = and2(tao, xnor2(nextStateVars[i], transitionFunctions[i]));
    }

    // Step 4
    BDD_ID Cs = True();
    for (unsigned int i = 0; i < stateVars.size(); i++) {
        Cs = and2(Cs, xnor2(stateVars[i], initState[i]));
    }

    // Step 5
    BDD_ID CRit = Cs;
    BDD_ID CR, nextImg, currentImg;
    int distance = 0;

    do {
        // Step 6
        CR = CRit;

        // Step 7
        nextImg = and2(CR, tao);
        for (int i = stateVars.size() - 1; i >= 0; i--) {
            nextImg = or2(coFactorTrue(nextImg, stateVars[i]), coFactorFalse(nextImg, stateVars[i]));
        }

        // Step 8
        currentImg = nextImg;
        for (int i = 0; i < stateVars.size(); i++) {
            currentImg = and2(currentImg, xnor2(stateVars[i], nextStateVars[i]));
        }
        for (int i = nextStateVars.size() - 1; i >= 0; i--) {
            currentImg = or2(coFactorTrue(currentImg, nextStateVars[i]), coFactorFalse(currentImg, nextStateVars[i]));
        }

        // Step 9
        CRit = or2(CR, currentImg);
        distance++;

        // Check if the stateVector is reachable at this distance
        BDD_ID reachable = CRit;
        for (unsigned int i = 0; i < stateVector.size(); i++) {
            if (stateVector[i] == true) {
                reachable = coFactorTrue(reachable, stateVars[i]);
            } else {
                reachable = coFactorFalse(reachable, stateVars[i]);
            }
        }
        if (reachable == True()) {
            return distance;
        }

    } while (CR != CRit);

    // If the state is not reachable, return -1
    return -1;
}

void Reachability::setTransitionFunctions(const std::vector<BDD_ID> &transitionFunctions) {
    //error handling
    if (transitionFunctions.size() != stateVars.size()) {
        throw std::runtime_error("size does not match with number of state bits");
    }

    for(unsigned int i = 0; i < transitionFunctions.size(); i++) {
        this->transitionFunctions[i] = transitionFunctions[i];
    }

}

void Reachability::setInitState(const std::vector<bool> &stateVector) {
    //error handling
    if (stateVector.size() != stateVars.size()) {
        throw std::runtime_error("size does not match with number of state bits");
    }
    for(unsigned int i = 0; i < stateVector.size(); i++) {
        if (stateVector[i] == true) {
            initState[i] = True();
        } else {
            initState[i] = False();
        }
    }
}



}