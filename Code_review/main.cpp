//
//  main.cpp
//  Code_review
//
//  Created by Yuliana Vintyuk on 11.05.22.
//

#include <iostream>
#include "my_vector.h"

int main(int argc, const char * argv[]) {
    MyVector<int> vector;
    
    vector.push_back(1, "abc");
    vector.push_back(2, "def");
    
    MyVector<int> v2 = vector;
    vector.push_back(3, "jhi");
    v2.push_back(48, "AAAAAAAAAAAA");
    
    v2["def"] = 123;
    
    std::cout<<vector[1].first<< "::" << vector[1].second<<std::endl;
    std::cout<<v2[1].first<< "::" << v2[1].second<<std::endl;
    std::cout<<vector[2].first<< "::" << vector[2].second<<std::endl;
    std::cout<<v2[2].first<< "::" << v2[2].second<<std::endl;
    
    std::cout << "Hello, World!\n";
    return 0;
}
