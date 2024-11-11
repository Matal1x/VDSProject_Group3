#include "Manager.h"
namespace ClassProject {

BDD_ID ManagerInterface::createVar(const std::string &label){
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
}