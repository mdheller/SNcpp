//  main.cpp
//  Roshan The SocialNetwork
//
//  Created by Roshan Lamichhane
//  Copyright (c) 2019 Roshan Lamichhane. All rights reserved.

#include <iostream>
#include <cstdio>
#include "person.h"
#include "inputoutput.cpp"
#include "BinarySearchTree.h"
using namespace std;

int main(int argc, const char * argv[]) {
    
    inputoutput menu;
    menu.readFile("names.txt");
    int input = 0;
    while(input != 2) {
        cout << "\n-------------------Welcome to Roshan The Social Network---------------------\n\n\n";
        string name;
        string password;
        cout << "Username: ";
        cin.ignore(1,'\n');
        getline(cin, name);
        cout << "Password: ";
        cin>>password;
        if(name != "admin")
            menu.userMenu(name, password);
        else
            menu.adminMenu(menu, password);
    
    }
    
}
