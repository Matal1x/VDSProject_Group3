//
// Created by Carolina P. Nogueira 2016
//

#include <iostream>
#include <string>
#include "Manager.h"
#include "Tests.h"


int main(int argc, char* argv[])
{
    std::cout << "Testing started" << std::endl;
    
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

    
}
