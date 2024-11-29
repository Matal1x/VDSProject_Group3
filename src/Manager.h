// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>
#include <iostream>
#include <fstream>

namespace ClassProject {
	typedef struct
	{
		BDD_ID id;
		std::string label;
		BDD_ID high;
		BDD_ID low;
		BDD_ID top_var;
	} BDD_Var;
	
	class Manager : public ManagerInterface {

		
		std::vector<BDD_Var> BDD_Var_Table;
		
		public:
		Manager(){
			BDD_Var_Table.push_back({0, "False", 0, 0, 0});
			BDD_Var_Table.push_back({1, "True", 1, 1, 1});
		}

        BDD_ID createVar(const std::string &label);

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
