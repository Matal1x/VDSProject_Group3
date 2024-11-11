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
    //new_var.top_var = last_id;
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



}