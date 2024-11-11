// A minimalistic BDD library, following Wolfgang Kunz lecture slides
//
// Created by Markus Wedler 2014

#ifndef VDSPROJECT_MANAGER_H
#define VDSPROJECT_MANAGER_H

#include "ManagerInterface.h"
#include <vector>

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

		BDD_ID last_id = 1;
		std::vector<BDD_Var> BDD_Var_Table;
		Manager(){
			BDD_Var_Table.push_back({0, "False", 0, 0, 0});
			BDD_Var_Table.push_back({1, "True", 1, 1, 1});
		}

        BDD_ID createVar(const std::string &label);

        const BDD_ID &True();
        const BDD_ID &False();

		bool isConstant(BDD_ID f);
        bool isVariable(BDD_ID f);
		
    };
}

#endif
