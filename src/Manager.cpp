#include "Manager.h"
namespace ClassProject {

BDD_ID Manager::createVar(const std::string &label){
    BDD_Var new_var;
    last_id++;
    new_var.id = last_id;

    //values of the high and low are not defined yet and depends on the label definition

    //new_var.label = label;
    //new_var.high = 1;
    //new_var.low = 0;
    //new_var.top_var = last_id; //  **************** a problem here 
    //BDD_Var_Table.push_back(new_var);
    return new_var.id;
}

const BDD_ID &Manager::True(){
    return static_cast<BDD_ID>(1);
}
const BDD_ID &Manager::False(){
    return static_cast<BDD_ID>(0);
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
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if (x==-1){
        x=Manager::topVar(f);
    }
    if ((f==x) || (f==1)){
        return static_cast<BDD_ID>(1);
    }
    else if (f==0){
        return static_cast<BDD_ID>(0);
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
        return static_cast<BDD_ID>(0);
    }
    else if (f==1){
        return static_cast<BDD_ID>(1);
    }
    else {
        return f;
    }
}


size_t Manager::uniqueTableSize() {
    return Manager::BDD_Var_Table.size();
}
}