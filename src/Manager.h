// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

// #define INCLUDE_LABELS
// #define INCLUDE_STRING_LABEL

#include "ManagerInterface.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/random_access_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <functional>
#include <iostream>
#include <string>


namespace ClassProject {
	struct BDD_Var
	{
		BDD_ID id;
		#ifdef INCLUDE_LABELS
			#ifdef INCLUDE_STRING_LABEL
				std::string label;
			#else
				char label[24];
			#endif
		#endif
    	BDD_ID high;
   		BDD_ID low;
    	BDD_ID top_var;
	};
    // Function to generate the Triplet key for hashing
    struct Triplet {
        BDD_ID F, G, H;
        bool operator==(const Triplet &other) const {
            return (F == other.F && G == other.G && H == other.H);
        }
    };

    struct HashTripletKey {
        std::size_t operator()(const Triplet &t) const {
            std::size_t h1 = std::hash<BDD_ID>()(t.F);
            std::size_t h2 = std::hash<BDD_ID>()(t.G);
            std::size_t h3 = std::hash<BDD_ID>()(t.H);
            return h1 ^ (h2 << 1) ^ (h3 << 2);
        }
    };



#include <boost/multi_index/member.hpp>

using namespace boost::multi_index;

typedef multi_index_container<
    BDD_Var,
    indexed_by<
        // Vector-like sequential index
        random_access<>,
        // Hash-based index using TripletKey
        hashed_unique<
            composite_key<
                BDD_Var,    
                member<BDD_Var, BDD_ID, &BDD_Var::high>,  // Use `high` as part of the key
                member<BDD_Var, BDD_ID, &BDD_Var::low>,    // Use `low` as part of the key
                member<BDD_Var, BDD_ID, &BDD_Var::top_var> // Use `top_var` as part of the key
            >
        >
    >
> MultiIndexBDD;


	class Manager : public ManagerInterface {

		
		// std::vector<BDD_Var> BDD_Var_Table;
		std::unordered_map<Triplet, BDD_ID, HashTripletKey> computed_table;
		// std::unordered_map<Triplet, BDD_ID, HashTriplet> optimizedTable;


		MultiIndexBDD bdd_table;

		public:
		Manager(){

			#ifdef INCLUDE_LABELS
				bdd_table.push_back({0, "False", 0, 0, 0});
				bdd_table.push_back({1, "True", 1, 1, 1});
			#else
				bdd_table.push_back({0, 0, 0, 0});
				bdd_table.push_back({1, 1, 1, 1});
			#endif		
		}

        BDD_ID createVar(const std::string &label);
		BDD_ID false_var = 0;
		BDD_ID true_var = 1;

        const BDD_ID &True();
        const BDD_ID &False();

		bool isConstant(BDD_ID f);
        bool isVariable(BDD_ID f);
		
		BDD_ID topVar(BDD_ID f);
		BDD_ID ite(BDD_ID i, BDD_ID t, BDD_ID e);

		BDD_ID coFactorTrue(BDD_ID f, BDD_ID x);
		BDD_ID coFactorFalse(BDD_ID f, BDD_ID x);
		BDD_ID coFactorTrue(BDD_ID f);
		BDD_ID coFactorFalse(BDD_ID f);

		size_t uniqueTableSize();

	
		BDD_ID and2(BDD_ID a, BDD_ID b);
		BDD_ID or2(BDD_ID a, BDD_ID b);
		BDD_ID xor2(BDD_ID a, BDD_ID b);
		BDD_ID neg(BDD_ID a);
		BDD_ID nand2(BDD_ID a, BDD_ID b);
		BDD_ID nor2(BDD_ID a, BDD_ID b);
		BDD_ID xnor2(BDD_ID a, BDD_ID b);
		std::string getTopVarName(const BDD_ID &root);
		void findNodes(const BDD_ID &root, std::set<BDD_ID> &nodes_of_root);
		void findVars(const BDD_ID &root, std::set<BDD_ID> &vars_of_root);
		void visualizeBDD(std::string filepath, BDD_ID &root);
		

    };
}

#endif
