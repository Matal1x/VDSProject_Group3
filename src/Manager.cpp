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

/*
    Returns the refeerence to the 'True' Terminal node.
*/
const BDD_ID &Manager::True(){
    return BDD_Var_Table[1].id;
}

/*
    Returns the refeerence to the 'False' Terminal node.
*/
const BDD_ID &Manager::False(){
    return BDD_Var_Table[0].id;
}

/*
    Checks if a given node is Terminal (Constant) or not and returns 
    the corresponding boolean value.
*/
bool Manager::isConstant(BDD_ID f){
    return ( (f==Manager::False()) || (f==Manager::True()));
}

/*
    Checks if a given node is Non-Terminal (Variable) or not and returns 
    the corresponding boolean value.
*/
bool Manager::isVariable(BDD_ID f){
    return ( (!isConstant(f)) && (topVar(f)==f) );
}

/*
    Returns the top variable of a given node.
*/
BDD_ID Manager::topVar(BDD_ID f){
    return BDD_Var_Table[f].top_var;  
}




/*
    The if-then-else function.
    It takes 3 BDD_IDs and returns the result of the ite function.
    First, it checks for terminal cases and returns the corresponding value.
    Then, if it is not a terminal case, it takes the minimum of the top variables of the 3 BDD_IDs.
    Then it calculates the high and low successors using CoFactorTrue and CofactorFalse respectively within
    the ite function recursively and checks if they are equal.
    if they are, it returns the high successor (or low as it doesn't matter).
    if they are not equal, it checks if the result is already in the BDD_Var_Table and returns it.
    if it is not, it creates a new entry in the BDD_Var_Table and returns the id of the new entry.     
*/
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
        return t; 
    } 
    else {
        BDD_ID highSuccessor,lowSuccessor;

       

        BDD_ID x = Manager::False();
        if (!isConstant(i)){
            x = topVar(i);
        }
        if (!isConstant(t)){
            x = std::min(topVar(t), x);
        }
        if (!isConstant(e)){
            x = std::min(topVar(e), x);
        }


        highSuccessor = ite(Manager::coFactorTrue(i, x), Manager::coFactorTrue(t, x), Manager::coFactorTrue(e, x));
        lowSuccessor = ite(Manager::coFactorFalse(i, x), Manager::coFactorFalse(t, x), Manager::coFactorFalse(e, x));
        
        if (highSuccessor == lowSuccessor){
            return highSuccessor;
        }

        for (BDD_ID k=0; k<Manager::uniqueTableSize(); k++){
            

            if ( (BDD_Var_Table[k].high == highSuccessor) && (BDD_Var_Table[k].low == lowSuccessor) && (BDD_Var_Table[k].top_var == Manager::topVar(k)) ){
                std::cout << "found" << std::endl;
                return BDD_Var_Table[k].id;
            }
        }

        std::cout << "         CREATED VAR" << std::endl;
        BDD_Var new_var;
        new_var.id = static_cast<BDD_ID>(Manager::uniqueTableSize());
        new_var.label = "id"+std::to_string(new_var.id);
        new_var.high = highSuccessor;
        new_var.low = lowSuccessor;
        new_var.top_var = x;
        BDD_Var_Table.push_back(new_var);

        return new_var.id;
    }
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if (isConstant(f) || isConstant(x) || topVar(f) > x ){
        return f;
    }
    else {
        if (topVar(f) == x){
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

/*
    One Parameter Version of CoFactorTrue.
    returns the high successor of the given node.
*/
BDD_ID Manager::coFactorTrue(BDD_ID f){
    return BDD_Var_Table[f].high;
}

/*
    One Parameter Version of CoFactorFalse.
    returns the low successor of the given node.
*/
BDD_ID Manager::coFactorFalse(BDD_ID f){
    return BDD_Var_Table[f].low;
}

/*
    Returns the size of the BDD_Var_Table.
    ie. the number of unique nodes in the BDD.
*/
size_t Manager::uniqueTableSize() {
    return Manager::BDD_Var_Table.size();
}

/*
    Basic logic AND function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::and2(BDD_ID a, BDD_ID b){
    BDD_ID aANDb = ite(a, b, Manager::False());
    BDD_Var_Table[aANDb].label = "(" + BDD_Var_Table[a].label + " * " + BDD_Var_Table[b].label + ")";
    return aANDb;

}

/*
    Basic logic OR function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    BDD_ID aORb = ite(a, Manager::True(), b);
    BDD_Var_Table[aORb].label = "(" + BDD_Var_Table[a].label + " + " + BDD_Var_Table[b].label + ")";
    return aORb;
}

/*
    Basic logic XOR function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    BDD_ID aXORb = ite(a, neg(b), b);
    BDD_Var_Table[aXORb].label = "(" + BDD_Var_Table[a].label + " ^ " + BDD_Var_Table[b].label + ")";
    return aXORb;
}

/*
    Basic logic NOT function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::neg(BDD_ID a){
    
    BDD_ID aNEG = ite(a, Manager::False(), Manager::True());
    BDD_Var_Table[aNEG].label = "!" + BDD_Var_Table[a].label;
    return aNEG;
}

/*
    Basic logic NAND function implementation using neg and and2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){

    BDD_ID aNANDb = neg(and2(a, b));
    BDD_Var_Table[aNANDb].label = "(" + BDD_Var_Table[a].label + " * " + BDD_Var_Table[b].label + ")'";
    return aNANDb;

}

/*
    Basic logic NOR function implementation using neg and or2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    BDD_ID aNORb = neg(or2(a, b));
    BDD_Var_Table[aNORb].label = "(" + BDD_Var_Table[a].label + " + " + BDD_Var_Table[b].label + ")'";
    return aNORb;
}


/*
    Basic logic XNOR function implementation using neg and xor2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
 
    BDD_ID aXNORb = neg(xor2(a, b));
    BDD_Var_Table[aXNORb].label = "(" + BDD_Var_Table[a].label + " ^ " + BDD_Var_Table[b].label + ")'";
    return aXNORb;
}


/*
    Returns the label of the top variable of the given node.
*/
std::string Manager::getTopVarName(const BDD_ID &root) {
    return BDD_Var_Table[topVar(root)].label;
}

/*
    Takes a root id and writes to nodes_of_root the nodes that are part of the BDD that has id as root.
    treated like  recursive function where if the id is 0 or 1, it returns.
    else it adds itself id to the set and calls itself with the high and low successors.
    0 and 1 are not added to the set
*/
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){
    
    nodes_of_root.insert(BDD_Var_Table[root].id);
    
    if(BDD_Var_Table[root].id==0 || BDD_Var_Table[root].id==1){
        return;
    }
    else {
        nodes_of_root.insert(BDD_Var_Table[root].high);
        nodes_of_root.insert(BDD_Var_Table[root].low);
        findNodes(BDD_Var_Table[root].high, nodes_of_root);
        findNodes(BDD_Var_Table[root].low, nodes_of_root);
    }
}

/*  
    takes a root id and writes to vars_of_root the variables that are part of the BDD that has id as root.
    calls findNodes to get the nodes of the BDD and then adds the topVar of each node to the set since we need only the vars.
*/

void Manager::findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root){
    std::set<BDD_ID> nodes_of_root;
    findNodes(root, nodes_of_root);
    for (const auto &node : nodes_of_root){
       if(node!=0 && node!=1)
        vars_of_root.insert(topVar(node));
    
    }
}

/*
    writes the BDD to a file in the dot format.
    after the header is written, the nodes are found using findNodes.
    then the nodes are written with their top variable as label.
    dotted lines are used for low successors and solid lines for high successors.
    in the end the 0 and 1 nodes are written.
*/
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
           if(node!=0 && node!=1){
            file << "    " << node << " [label=\"" << BDD_Var_Table[BDD_Var_Table[node].top_var].label << "\"];" << std::endl;
        
            file << "    " << node << " -> " << high << " [style=solid];" << std::endl;
            file << "    " << node << " -> " << low << " [style=dotted];" << std::endl;
        }
        
    }

    file << "    0 [shape=box, label=\"0\"];" << std::endl;
    file << "    1 [shape=box, label=\"1\"];" << std::endl;

    file << "}" << std::endl;
    file.close();
}

}