// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <boost/functional/hash.hpp>

namespace ClassProject {
	typedef struct
	{
		BDD_ID id;
		std::string label;
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
        std::size_t seed = 0;
        boost::hash_combine(seed, std::hash<BDD_ID>{}(t.F));
		boost::hash_combine(seed, std::hash<BDD_ID>{}(t.G));
		boost::hash_combine(seed, std::hash<BDD_ID>{}(t.H));
        return seed;
    }
	};


	struct NodeKey {
    BDD_ID high;
    BDD_ID low;
    BDD_ID top_var;

    bool operator==(const NodeKey &other) const {
        return high == other.high && low == other.low && top_var == other.top_var;
    }
	};

	struct HashNodeKey {
    std::size_t operator()(const NodeKey &key) const {
        std::size_t h1 = std::hash<BDD_ID>()(key.high);
        std::size_t h2 = std::hash<BDD_ID>()(key.low);
        std::size_t h3 = std::hash<BDD_ID>()(key.top_var);
        return h1 ^ (h2 << 1) ^ (h3 << 2);
    }
	};


	class Manager : public ManagerInterface {

		
		std::vector<BDD_Var> BDD_Var_Table;
		using computed_table_type = std::unordered_map<Triplet, BDD_ID, HashTriplet>;
		computed_table_type computed_table;

		std::unordered_map<NodeKey, BDD_ID, HashNodeKey> optimizedTable;
		std::unordered_map<std::string, BDD_ID> label_to_id_map;
		public:
		Manager(){
			BDD_Var_Table.push_back({0, "False", 0, 0, 0});
			BDD_Var_Table.push_back({1, "True", 1, 1, 1});
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
