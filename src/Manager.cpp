#include "Manager.h"
namespace ClassProject {

/*
    Used to create entries in the BDD_Var_Table 
    for variables that don't need computation.
*/
BDD_ID Manager::createVar(const std::string &label){
    BDD_Var new_var;
    new_var.id = static_cast<BDD_ID>(Manager::uniqueTableSize());
    new_var.label = label;
    
    new_var.high = this->True(); 
    new_var.low = this->False();
    new_var.top_var = static_cast<BDD_ID>(Manager::uniqueTableSize()); 
     
    BDD_Var_Table.push_back(new_var);
   
    return new_var.id;
}

const BDD_ID &Manager::True(){
    return BDD_Var_Table[1].id;
}
const BDD_ID &Manager::False(){
    return BDD_Var_Table[0].id;
}


bool Manager::isConstant(BDD_ID f){
    return ( (f==Manager::False()) || (f==Manager::True()));
}
bool Manager::isVariable(BDD_ID f){
    return ( (f!=Manager::False()) && (f!=Manager::True()));
}

// Concept needs to be verified
BDD_ID Manager::topVar(BDD_ID f){
    return BDD_Var_Table[f].top_var; // ******* Wrong, it should be set diffirently 
}
// Incomplete
BDD_ID Manager::ite(BDD_ID i, BDD_ID t, BDD_ID e){
    if (i==1){
        return t;
    }
    else if (i==0){
        return e;
    }
    else if ((t==1) && (e==0)){
        return i;
    }
    else if (t==e){
        return t; // Or e
    }
    // missing last terminal case ite(f,0,1)=!f 
    // and non terminal cases.

    // topvar of ite, high/low successor, 
    else {
        BDD_ID highSuccessor,lowSuccessor;

        highSuccessor = ite(Manager::coFactorTrue(i), Manager::coFactorTrue(t), Manager::coFactorTrue(e));
        lowSuccessor = ite(Manager::coFactorFalse(i), Manager::coFactorFalse(t), Manager::coFactorFalse(e));
        
        if (highSuccessor == lowSuccessor){
            return highSuccessor;
        }

        for (int i=0; i<Manager::uniqueTableSize(); i++){
            if ( (BDD_Var_Table[i].high == highSuccessor) && (BDD_Var_Table[i].low == lowSuccessor) && (BDD_Var_Table[i].top_var == Manager::topVar(i)) ){
                return BDD_Var_Table[i].id;
            }
        }
        BDD_Var new_var;
        new_var.id = static_cast<BDD_ID>(Manager::uniqueTableSize());
        new_var.label = "x"+std::to_string(new_var.id);
        new_var.high = highSuccessor;
        new_var.low = lowSuccessor;
        new_var.top_var = Manager::topVar(i);

        BDD_Var_Table.push_back(new_var);

        return new_var.id;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if (x==-1){
        x=Manager::topVar(f);
    }
    if ((f==x) || (f==1)){
        return Manager::True();
    }
    else if (f==0){
        return Manager::False();
    }
    else {
        return f;
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    if (x==-1){
        x=Manager::topVar(f);
    }
    if ((f==x) || (f==0)){
        return Manager::False();
    }
    else if (f==1){
        return Manager::True();
    }
    else {
        return f;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
    return 0;
}
BDD_ID Manager::coFactorFalse(BDD_ID f){
    return 0;
}

size_t Manager::uniqueTableSize() {
    return Manager::BDD_Var_Table.size();
}


BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    if (b < a){
        return ite(b, a, Manager::False());
    }
    return ite(a, b, Manager::False());

}
BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    if (b < a){
        return ite(b, Manager::True(), a);
    }
    return ite(a, Manager::True(), b);
}
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    if (b < a){ 
        return ite(b, neg(a), a);
    }
    return ite(a, neg(b), b);
}
BDD_ID Manager::neg(BDD_ID a){
    return ite(a, Manager::False(), Manager::True());
}
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){

    return neg(and2(a, b));
}
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    return neg(or2(a, b));
}
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
 return neg(xor2(a, b));
}

std::string Manager::getTopVarName(const BDD_ID &root){
    return "0";
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    return;
}
void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    return;
}
void Manager::visualizeBDD(std::string filepath, BDD_ID &root){
    return;
}

}