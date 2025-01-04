#include "Manager.h"
namespace ClassProject {

/*
    Used to create entries in the BDD_Var_Table 
    for variables that don't need computation.
*/
BDD_ID Manager::createVar(const std::string &label){
    
    #ifdef INCLUDE_LABELS
        for (const auto &node : BDD_Var_Table){
            if (node.label == label){
                return node.id;
            }
        }
    #endif

    BDD_Var new_var;
    new_var.id = static_cast<BDD_ID>(Manager::uniqueTableSize());
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            new_var.label = label;
        #else
            strncpy(new_var.label , label.c_str(), sizeof(new_var.label)-1);
        #endif
    #endif
    new_var.high = this->True(); 
    new_var.low = this->False();
    new_var.top_var = static_cast<BDD_ID>(Manager::uniqueTableSize()); 
     
    BDD_Var_Table.push_back(new_var);

    // Adding to the fast hash table
    Triplet key = {new_var.high, new_var.low, new_var.top_var};
    optimizedTable[key] = new_var.id;

    return new_var.id;
}

/*
    Returns the refeerence to the 'True' Terminal node.
*/
const BDD_ID &Manager::True(){
    return true_var;
}

/*
    Returns the refeerence to the 'False' Terminal node.
*/
const BDD_ID &Manager::False(){
    return false_var;
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
BDD_ID Manager::ite(BDD_ID F, BDD_ID G, BDD_ID H){
    if (F==1){
        return G;
    }
    else if (F==0){
        return H;
    }
    else if ((G==1) && (H==0)){
        return F;
    }
    else if (G==H){
        return G; 
    } 
    
    Triplet tri;
    tri.F=F; tri.G=G; tri.H=H;

    auto checking = computed_table.find(tri);
    if ( checking != computed_table.end()){
        //std::cout << "         FOUND ONE IN CT (emplace)" << std::endl;
        return checking->second;
    }

    BDD_ID T,E;
  
    BDD_ID x = Manager::False();
    if (!isConstant(F)){
        x = topVar(F);
    }
    if (!isConstant(G)){
        x = std::min(topVar(G), x);
    }
    if (!isConstant(H)){
        x = std::min(topVar(H), x);
    }

    BDD_ID ct_f=Manager::coFactorTrue(F, x), ct_g=Manager::coFactorTrue(G, x), ct_h=Manager::coFactorTrue(H, x);
    T = ite(ct_f, ct_g, ct_h);
    computed_table[{ct_f, ct_g, ct_h}] = T;

    BDD_ID cf_f=Manager::coFactorFalse(F, x), cf_g=Manager::coFactorFalse(G, x), cf_h=Manager::coFactorFalse(H, x);
    E = ite(cf_f, cf_g, cf_h);
     
     
    if (T == E){
        return T;
    }
    // Putting it here just in case T=E
    computed_table[{cf_f, cf_g, cf_h}] = E;

    // for (const auto &node : BDD_Var_Table){
         
    //     if ( (node.high == T) && (node.low == E) && (node.top_var == x) ){
    //       //std::cout << "Found" << std::endl;
    //         return node.id;
    //     }
    // }

    Triplet key = {T,E,x};
    auto it = optimizedTable.find(key);
    if (it != optimizedTable.end()) {
        //std::cout << "found one in ot" << std::endl;
        return it->second; // Return existing ID
    }

    //std::cout << "         CREATED VAR" << std::endl;
    BDD_Var R;
    R.id = static_cast<BDD_ID>(Manager::uniqueTableSize());
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            R.label = "id"+std::to_string(R.id);
        #else    
            strncpy(R.label, ("id" + std::to_string(R.id)).c_str(), sizeof(R.label) - 1);
        #endif
    #endif
    R.high = T;
    R.low = E;
    R.top_var = x;
    BDD_Var_Table.push_back(R);
    computed_table[tri] = R.id;
    optimizedTable[key] = R.id;
    return R.id;
    
}

BDD_ID Manager::coFactorTrue(BDD_ID f, BDD_ID x){
    if (isConstant(f) || isConstant(x) || topVar(f) > x ){
        return f;
    }
    else {
        if (topVar(f) == x){
            return BDD_Var_Table[f].high;
        }
        return ite(topVar(f), coFactorTrue(BDD_Var_Table[f].high, x), coFactorTrue(BDD_Var_Table[f].low, x));
    }
}

BDD_ID Manager::coFactorFalse(BDD_ID f, BDD_ID x){
    if (isConstant(f) || isConstant(x) || topVar(f) > x ){
        return f;
    }
    else {
        if (topVar(f) == x){
            return BDD_Var_Table[f].low;
        }
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
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aANDb].label = "(" + BDD_Var_Table[a].label + " * " + BDD_Var_Table[b].label + ")";
        #else    
            strncpy(BDD_Var_Table[aANDb].label, ("(" + std::string(BDD_Var_Table[a].label) + " * " + std::string(BDD_Var_Table[b].label) + ")").c_str(), sizeof(BDD_Var_Table[aANDb].label));
        #endif
    #endif
    return aANDb;

}

/*
    Basic logic OR function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::or2(BDD_ID a, BDD_ID b){
    BDD_ID aORb = ite(a, Manager::True(), b);
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aORb].label = "(" + BDD_Var_Table[a].label + " + " + BDD_Var_Table[b].label + ")";
        #else
            strncpy(BDD_Var_Table[aORb].label, ("(" + std::string(BDD_Var_Table[a].label) + " + " + std::string(BDD_Var_Table[b].label) + ")").c_str(), sizeof(BDD_Var_Table[aORb].label));
        #endif
    #endif
    return aORb;
}

/*
    Basic logic XOR function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::xor2(BDD_ID a, BDD_ID b){
    BDD_ID aXORb = ite(a, neg(b), b);
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aXORb].label = "(" + BDD_Var_Table[a].label + " ^ " + BDD_Var_Table[b].label + ")";
        #else
            strncpy(BDD_Var_Table[aXORb].label , ("(" + std::string(BDD_Var_Table[a].label) + " ^ " + std::string(BDD_Var_Table[b].label) + ")").c_str(), sizeof(BDD_Var_Table[aXORb].label));
        #endif
    #endif
    return aXORb;
}

/*
    Basic logic NOT function implementation using ite.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::neg(BDD_ID a){
    
    BDD_ID aNEG = ite(a, Manager::False(), Manager::True());
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aNEG].label = "!" + BDD_Var_Table[a].label;
        #else
            strncpy(BDD_Var_Table[aNEG].label , ("!" + std::string(BDD_Var_Table[a].label)).c_str(), sizeof(BDD_Var_Table[aNEG].label));
        #endif
    #endif
    return aNEG;
}

/*
    Basic logic NAND function implementation using neg and and2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::nand2(BDD_ID a, BDD_ID b){

    BDD_ID aNANDb = neg(and2(a, b));
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aNANDb].label = "(" + BDD_Var_Table[a].label + " * " + BDD_Var_Table[b].label + ")'";
        #else
            strncpy(BDD_Var_Table[aNANDb].label, ("(" + std::string(BDD_Var_Table[a].label) + " * " + std::string(BDD_Var_Table[b].label) + ")'").c_str(), sizeof(BDD_Var_Table[aNANDb].label));
        #endif
    #endif
    return aNANDb;

}

/*
    Basic logic NOR function implementation using neg and or2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::nor2(BDD_ID a, BDD_ID b){
    BDD_ID aNORb = neg(or2(a, b));
    #ifdef INCLUDE_LABELS   
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aNORb].label = "(" + BDD_Var_Table[a].label + " + " + BDD_Var_Table[b].label + ")'";
        #else    
            strncpy(BDD_Var_Table[aNORb].label , ("(" + std::string(BDD_Var_Table[a].label) + " + " + std::string(BDD_Var_Table[b].label) + ")'").c_str(), sizeof(BDD_Var_Table[aNORb].label));
        #endif    
    #endif
    return aNORb;
}


/*
    Basic logic XNOR function implementation using neg and xor2 functions.
    Either creates a new entry in the table if it doesn't already exist
    or returns the id of the existing entry.
*/
BDD_ID Manager::xnor2(BDD_ID a, BDD_ID b){
 
    BDD_ID aXNORb = neg(xor2(a, b));
    #ifdef INCLUDE_LABELS
        #ifdef INCLUDE_STRING_LABEL
            BDD_Var_Table[aXNORb].label = "(" + BDD_Var_Table[a].label + " ^ " + BDD_Var_Table[b].label + ")'";
        #else
            strncpy(BDD_Var_Table[aXNORb].label , ("(" + std::string(BDD_Var_Table[a].label) + " ^ " + std::string(BDD_Var_Table[b].label) + ")'").c_str(), sizeof(BDD_Var_Table[aXNORb].label));
        #endif
    #endif
    return aXNORb;
}


/*
    Returns the label of the top variable of the given node.
*/
std::string Manager::getTopVarName(const BDD_ID &root) {
    #ifdef INCLUDE_LABELS
        return BDD_Var_Table[topVar(root)].label;
    #else
        return "";
    #endif
}

/*
    Takes a root id and writes to nodes_of_root the nodes that are part of the BDD that has id as root.
    treated like  recursive function where if the id is 0 or 1, it returns.
    else it adds itself id to the set and calls itself with the high and low successors.
    0 and 1 are not added to the set
*/
void Manager::findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root){

    if(nodes_of_root.find(root) != nodes_of_root.end()){
        return;
    }
    
    nodes_of_root.insert(BDD_Var_Table[root].id);
    std::cout << BDD_Var_Table[root].id << std::endl;
    findNodes(BDD_Var_Table[root].high, nodes_of_root);
    findNodes(BDD_Var_Table[root].low, nodes_of_root);
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
            #ifdef INCLUDE_LABELS
                file << "    " << node << " [label=\"" << BDD_Var_Table[BDD_Var_Table[node].top_var].label << "\"];" << std::endl;
            #endif
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