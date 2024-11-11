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

	std::vector<BDD_Var> BDD_Var_Table;
	
	
	class Manager : public ManagerInterface {
	
	};
}

#endif
