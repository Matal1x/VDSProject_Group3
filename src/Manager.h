// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#define INCLUDE_LABELS
//#define INCLUDE_STRING_LABEL

#include "ManagerInterface.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <cstring>

namespace ClassProject {
	typedef struct
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
	} BDD_Var;

	struct Triplet {
    BDD_ID F, G, H;
    bool operator==(const Triplet &other) const {
        return (F == other.F && G == other.G && H == other.H);
    }
	};

	struct HashTriplet {
    std::size_t operator()(const Triplet &t) const {
        std::size_t h1 = std::hash<BDD_ID>()(t.F);
        std::size_t h2 = std::hash<BDD_ID>()(t.G);
        std::size_t h3 = std::hash<BDD_ID>()(t.H);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
	};




	class Manager : public ManagerInterface {

		
		std::vector<BDD_Var> BDD_Var_Table;
		std::unordered_map<Triplet, BDD_ID, HashTriplet> computed_table;
		std::unordered_map<Triplet, BDD_ID, HashTriplet> optimizedTable;
		
		public:
		Manager(){

			#ifdef INCLUDE_LABELS
				BDD_Var_Table.push_back({0, "False", 0, 0, 0});
				BDD_Var_Table.push_back({1, "True", 1, 1, 1});
			#else
				BDD_Var_Table.push_back({0, 0, 0, 0});
				BDD_Var_Table.push_back({1, 1, 1, 1});
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
