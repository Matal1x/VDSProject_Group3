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

        bool isVariable_i = isVariable(i);
        bool isVariable_t = isVariable(t);
        bool isVariable_e = isVariable(e);

        BDD_ID x = Manager::False();
        if (isVariable_i){
            x = topVar(i);
        }
        else if (isVariable_t){
            x = std::min(topVar(t), x);
        }
        else if (isVariable_e){
            x = std::min(topVar(e), x);
        }

        highSuccessor = ite(Manager::coFactorTrue(i, x), Manager::coFactorTrue(t, x), Manager::coFactorTrue(e, x));
        lowSuccessor = ite(Manager::coFactorFalse(i, x), Manager::coFactorFalse(t, x), Manager::coFactorFalse(e, x));
        
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
        new_var.top_var = x;

        BDD_Var_Table.push_back(new_var);

        return new_var.id;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if (isConstant(f) || isConstant(x) || topVar(f) > x ){
        // if f==1, return 1, 
        // if f==0, return 0,
        // if x==1 or x==0, it doesn't affect the result, so return f
        // if topVar(f) > x, it means that x is not part of f, so return f
        return f;
    }
    else {
        if (topVar(f) == x){
            // just like CoFactorTrue(f)
            return BDD_Var_Table[f].high;
        }
        // if topVar(f) < x


        // the case of CoFactorTrue(a*b, b)= a
        // we need to call the function ite in a way that it returns a.
        // we also need to keep in mind the cases the function given in the PDF
        // and that they are still working.
        //return ite(topVar(f), BDD_Var_Table[x].high, BDD_Var_Table[x].low);
        // this works for this case but since the False variation which is
        // built on this model doesn't yield correct values than it is not correct.
        // in case we want ite to return a;
        // we have:
        // ite(something=1, something=a, whatever)
        // ite(something=0, whatever, something=a}
        // ite(something, something=a, something=a)
        // ite(something=a, something=1, something=1)
        // since we are using topvar(f) then 
        // the first two cases are impossible. (explanation in False variant)

        /*
            Let's take the case of f=(a+b)*c*d
            cofactorTrue(f, c) = a+b*d
            if we take into consideration that we are using topVar(f)
            then we have to implement it and the ite function
            
            if we look at the function f, we can have two sub graphs: a*c*d and b*c*d
            if we cofactorTrue the first one, we get a*d
            if we cofactorTrue the second one, we get b*d
            at the end we get a*d+b*d which is a+b*d
            in this example both subgraphs contain c.
            so if a is true, then we would only need to look at the right sub graph.
            but if it is false, then we would need to look at the left sub graph which is b*c*d.
            the point is, both could contain c.
            if we write this in 'ite language', we get:
            if a is true then look at the right subgraph which is c*d and cofactor it wrt c,
            else look at the left subgraph which is b*c*d and cofactor it wrt to c.
            thus we get:
        */
            return ite(topVar(f), coFactorTrue(BDD_Var_Table[f].high, x), coFactorTrue(BDD_Var_Table[f].low, x));
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    if (isConstant(f) || isConstant(x) || topVar(f) > x ){
        // if f==1, return 1, 
        // if f==0, return 0,
        // if x==1 or x==0, it doesn't affect the result, so return f
        // if topVar(f) > x, it means that x is not part of f, so return f
        return f;
    }
    else {
        if (topVar(f) == x){
            // just like CoFactorFalse(f)
            return BDD_Var_Table[f].low;
        }
        // if topVar(f) < x


        // in case CoFactorFalse(a*b, b)= 0, 
        // ite(topVar(f), BDD_Var_Table[x].low, BDD_Var_Table[x].high)
        // is false as it will return !a instead of 0.
        // thus returning 0 with ite would result in something like:
        // ite(something, something=0,something=0)
        // ite(something=1. something=0, whatever)
        // ite(something=0, whatever, something=0).
        // if we take into consideration that we are using topVar(f)
        // then it can only be the ite of the first case.
        // becasue topVar(f) with f=a*b can never be 0 or 1.
        // which means the other 2 parameters need to be 0 in this case.
        // and most likely diffirent than each other. as in, their calculation is diffirent.
       // return ite(topVar(f), BDD_Var_Table[x].low, BDD_Var_Table[x].high);

       /*
        Basically the same concept as in the cofactorTrue function.
        explanation is there.
       */
        return ite(topVar(f), coFactorFalse(BDD_Var_Table[f].high, x), coFactorFalse(BDD_Var_Table[f].low, x));
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f){
    return BDD_Var_Table[f].high;
}
BDD_ID Manager::coFactorFalse(BDD_ID f){
    return BDD_Var_Table[f].low;
}

size_t Manager::uniqueTableSize() {
    return Manager::BDD_Var_Table.size();
}


BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    return ite(a, b, Manager::False());

}
BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    return ite(a, Manager::True(), b);
}
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
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

std::string Manager::getTopVarName(const BDD_ID &root) {
    return BDD_Var_Table[topVar(root)].label;
}

void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    
    if(BDD_Var_Table[root].id==0 || BDD_Var_Table[root].id==1){
        return;
    }
    else {
       
        nodes_of_root.insert(BDD_Var_Table[root].id);
        findNodes(BDD_Var_Table[root].high, nodes_of_root);
        findNodes(BDD_Var_Table[root].low, nodes_of_root);
    }
}

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    std::set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);
    for (const auto &node : nodes_of_root){
       
            vars_of_root.insert(topVar(node));
    
    }
}

void Manager::visualizeBDD(std::string filepath, BDD_ID &root) {
    
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    file << "digraph BDD {" << std::endl;
    file << "    node [shape=circle];" << std::endl;

    std::set<BDD_ID> nodes;
    BDD_ID high,low;
    findNodes(root, nodes);

    for (const auto &node : nodes) {
        
            high = BDD_Var_Table[node].high;
            low = BDD_Var_Table[node].low;
            file << "    " << node << " [label=\"" << BDD_Var_Table[node].label << "\"];" << std::endl;
            file << "    " << node << " -> " << high << " [label=\"" <<BDD_Var_Table[high].label<< "\"];" << std::endl;
            file << "    " << node << " -> " << low << " [label=\"" <<BDD_Var_Table[high].label<< "\"];" << std::endl;
        
    }

    file << "    0 [shape=box, label=\"0\"];" << std::endl;
    file << "    1 [shape=box, label=\"1\"];" << std::endl;

    file << "}" << std::endl;
    file.close();
}

}