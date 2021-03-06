//
//  inputoutput.cpp
//  Roshan The Social Network
//  Created by Roshan Lamichhane 2019
//  Copyright (c) 2019 Roshan Lamichhane. All rights reserved.
//
#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "person.h"
#include "BinarySearchTree.h"
#include "BinarySearchTree.cpp"
#include "hashing.h"
#include "vector"
using namespace std;

class inputoutput {
    
public:
    BinarySearchTree<person> tree;
    person personArray[1000];
    int count;
	int personindex;
	vector<person> arrayvector;
    inputoutput() {
        count = 0;
    }
    void readFile(string textname)  //dynamically allocate memory and storing each product line into the dynamic memory array
    {
        string  name;
        string password;
        string gender;
        string age;
        string city;
        string college;
        string wasteSpace;
        
        
        ifstream infile;
        infile.open(textname);
        while(!infile.eof())
        {
            getline(infile, name);
            getline(infile, password);
            getline(infile, gender);
            getline(infile, age);
            getline(infile, city);
            getline(infile, college);
            getline(infile, wasteSpace);
            int Age = atoi(age.c_str());
            
            person tempPerson(name, password, gender, Age, city, college);
            personArray[count] = tempPerson;
			arrayvector.push_back(tempPerson);
            tree.insert(personArray[count]);
            count++;
            
            
        }
    }
 
    
    void userMenu(string name, string password) {
        
        bool options = true;
        person *temp;  person *other; person temporary; vector<person *> tempFriends;
        
        temporary.setName(name);
        temp = tree.search(temporary);
        if(temp == NULL ){
            cout << "Incorrect Username and Password";
            return;
        }
        if(temp->getPwd() != password){
            cout << "Incorrect Username and Password";
            return;
        }
        if(temp->getStatus() != false)
                {
                    int status;
                    cout << "Your account is not active" << endl;
                    cout << "Please reactivate your account in order to access it" <<endl;
                    cout << "Press [1] to Reactivate or [2] to Exit" <<endl;
                    cin >> status;
                    if (status == 1)
                        temp->deactivateAccount(false);
                    else
                        return;
                }
                while(options == true) {
                    cout << endl<< "-------------"<< temp->getName() << " Profile --------------" << endl;;
                    cout << "Choose an option from below" << endl;
                    cout << "1. Add a friend" << endl
                    << "2. Write a new Status Message" << endl
                    << "3. Send a message" << endl
                    << "4. Show your friends" << endl
                    << "5. Show newsfeed" << endl
                    << "6. Print your status messages" <<endl
                    << "7. Print your private messages" << endl
                    << "8. Account Settings" << endl
                    << "9. Logout"  << endl << "[Choose Your Option] : " ;
                    
                    int option;
                    string friendName;
                    string message;
                    string pressKey;
                    bool friendFound = false;
                    string status = " ";
                    cin >> option;
                    switch(option) {
                        case 1 : cout << "Which friend would you like to add" << endl;
                            cin.ignore();
                            getline(cin, friendName);
                            temporary.setName(friendName);
                            other = tree.search(temporary);
                            if(other == NULL)
                            { cout << "Person does not exist in the database";
                                continue;
                            } else {
                                    temp->addFriend(*other);
                                    friendFound = true;
                                }
                            break;
                            
                        case 2 : cout << "What's on your mind?" << endl;
                            cin.ignore();
                            getline(cin, status);
                            cout << " " << endl;
                            temp->setStatus(status);
                            break;
                            
                        case 3 :
                            cout << "Which friend would you like to send a message" << endl;
                            cin.ignore();
                            getline(cin, friendName);
                            cout << "What message would you like to send : " << endl;
                            getline(cin, message);
                            temporary.setName(friendName);
                            other = tree.search(temporary);
                            if(other == NULL)
                            { cout << "Person does not exist in the database";
                                break;
                            }
                            else
                                temp->sendMessage(*other, message);
                            break;
                        case 4 :
                            temp->printFriends();
                            break;
                        case 5 :
                            tempFriends = temp->getFriends();
                            for(int i = 0; i < tempFriends.size(); i++) {
                                tempFriends[i]->printStatus();
                            }
                            break;
                        case 6 :
                             temp->printStatus();
                            break;
                        case 7 :
                            temp->printMessages();
                            break;
                        case 8:
                            userAdminMenu(*temp);
                            break;
                        case 9 :
                            options = false;
                            break;
                        default:
                            cout << "select the right option";
                            
                    }
                    cout <<endl << "Press z to continue : ";
                    cin>> pressKey;
                    
                }
        
        
        if(options == false){
            cout << "You've been logged out." << endl;
            return;
        }
        
    }
    
    void userAdminMenu(person &personName) {
        person temporary;
        person *other;
        bool options = true;
        while( options == true ) {
            int option;
            string temp;
            cout << "-------------"<< personName.getName() << " Settings --------------" << endl;;
            cout << "Choose an option from below" << endl;
            cout << "1. Change Password" << endl
            << "2. Change City " << endl
            << "3. Change University" << endl
            << "4. Delete a Friend" << endl
            << "5. Change Relationship status" <<endl
            << "6. Deactivate Profile " << endl
            << "7. Back to your Profile" << endl
            <<"[Choose Your Option] : ";
            cin >> option;
            switch(option) {
                case 1 :
                    cout << "New Password : ";
                    cin>>temp;
                    personName.setPassword(temp);
                    cout << "Your Password has been changed";
                    break;
                case 2 ://IT DOENST WORK.. SEE WHATS WRONG
                    cout << "New City : ";
                    cin>>temp;
                    personName.setCity(temp);
                    cout << "Your City has been changed";
                    break;
                case 3 :
                    cout << "New University : ";
                    cin>>temp;
                    personName.setCollege(temp);
                    cout << "\nYour University has been changed";
                    break;
                case 4:
                    cout << "Enter the name of the friend you want to Delete : ";
                    cin.ignore();
                    getline(cin, temp);
                    temporary.setName(temp);
                    other = tree.search(temporary);
                    if(other == NULL)
                    { cout << "The person does not exist in the database.";
                        break;
                    }
                    personName.deleteFriend(*other);
                    break;
                case 5 :
                    cout << "Who are you in relationship with (write name or type 'none') : " << endl;
                    cin.ignore();
                    getline(cin, temp);
                    temporary.setName(temp);
                    other = tree.search(temporary);
                    
                    if(temp != "none"){
                        if(other == NULL)
                        { cout << "The person does not exist in the database.";
                            break;
                        }
                        personName.setRelationship(other);}
                    else
                        
                        personName.setRelationship(NULL);
                    break;
                case 6 :
                    cout << "Are you sure you want to deactivate your account?" <<endl
                    <<"Choose [1] for Yes \n [2] for No  : ";
                    cin >> temp;
                    if (temp == "1"){
                        personName.deactivateAccount(true);
                        cout <<"Your account has been deactivated, however you can still access your account until you logout";
                    }
                    else {
                        cout << "Your account has not been deactivated" << endl;
                    }
                    break;
                case 7:
                    options = false;
                    break;
                default:
                    cout << "please select the right option";
                    
            }
        }
        
        
    }
    
    
    void adminMenu(inputoutput &obj, string password) {
      //  cout << "count = " <<count <<endl;
		hashing hashfunc(count);
		hashing* hashptr = &hashfunc;
		
		personindex =0;
		
        for (int i = 0 ; i < count ; i++ ) {
            hashptr->addObject(arrayvector[i]);
			
			personindex = i;

        }
        person *temp; person temporary; string name;
        
        
        if (password != "vno")
        {
            cout << "incorrect username or password";
            return;
        }
        
        bool options = true;
        while(options == true) {
            cout <<  "-------------------- ADMINISTRATOR  --------------" << endl;;
            cout << "Choose an option from below" << endl;
            cout << "1. Create a new Profle" <<endl
            << "2. Delete a Person" << endl
            << "3. Search a person by Name" << endl
            << "4. Print the Hash Table" << endl
            << "5. Print the Binary Tree" << endl
            << "6. Print Indented Tree" <<endl
            << "7. Write to File" << endl
            << "8. Usage Statistics" << endl
            << "9. Logout" << endl
            << "[Choose Your Option] : " ;
            int option;
            cin >> option;
            cout <<endl<< "option = " << option <<endl;
					

            switch(option) {
                case 1:
					
					getcaseone(hashptr);
					
                    break;
					
                case 2:
                    cout << "Name of the person to be deleted : " <<endl;
                    cin.ignore();
                    getline(cin, name);
                    temporary.setName(name);
                    tree.remove(temporary);
                    hashptr->removeObject(temporary);
				

                    break;
                    
                case 3 :
                    
                    break;
                    
                case 4 :
                    hashptr->PrintTable();
                    break;
                    
                case 5 :
                    tree.print_inOrder();
                    break;
                    
                case 6:
                    tree.printIndent();
                    break;
                    
                case 7 :
                    
                    break;
                    
                case 8 :
                    
                    break;
                    
                case 9 :
                    options = false;
                    break;
                default :
                    cout << "Please enter the correct choice:" ;
            }



			if(hashptr->getLoadingfactor() > .75)
			//	cout<< "Changinghhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh " <<endl;
					{
						hashing newhashing(hashptr->getTablesize());

						
						for(int i = 0; i < personindex; i++)
						{

							 newhashing.addObject(arrayvector[i]);
						//	tempPerson = hashfunc.getHashtable[i];
						//	newhashing.addObject(tempPerson);
            
							
						}
					//	hashing* tempptr = hashptr;
					//	delete(&tempptr);
					//	delete(tempptr);
						hashptr = &newhashing;
					}


            
        }
        if(options == false) {
            cout << "You have been logged out" <<endl;
            return;
        }
    }

	void getcaseone(hashing* hashptr)
	{

					string name;
					string password;
					string gender;
					string age;
					string city;
					string college;

					cout << "Name : ";
					cin >> name;
					cout << endl << "Password : ";
					cin >> password;
					cout << endl << "Gender : ";
					cin >> gender;
					cout << endl << "age";
					cin >> age;
					cout << endl << "city";
					cin >> city;
					cout << endl << "college : ";
					cin >> college;
					int Age = atoi(age.c_str());

					person tempPersons(name, password, gender, Age, city, college);
					hashptr->addObject(tempPersons);
					arrayvector.push_back(tempPersons);
					personArray[personindex] = tempPersons;
					personindex++;
					
	
	
					
	}
};
