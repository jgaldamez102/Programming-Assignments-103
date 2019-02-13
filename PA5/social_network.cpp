#include "network.h"
#include "user.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    int error=0, option =0;
    Network net;
    error = net.read_friends(argv[1]);
    if (error == -1){
        return -1;
    }
    
    cout << "This is the Social Network" <<endl <<
        "Please choose a menu option: ";
    
    
    while (option !=6 ){
        cout << endl << "Select a menu option: ";
        cout << "1) Add a User" << endl
            << "2) Add Friend Connection" << endl
            << "3) Remove Friend Connection" << endl
            << "4) Print Users " << endl
            << "5) List Friends" <<endl
            << "6) Make a new file with all your" << 
            "information" << endl;
        int temp =0;
        cin>> temp;
        option = temp;
    
        string first1,first2,last1,last2, newName;
        string name1,name2, file;
        int id, year, zip;
        
        switch(option){
            case 1:

                cout << "Information Format: " << endl 
                    << "'Name' 'Birth Year' 'Zipcode'" << endl;
                cin  >> first1 >> last1 >> year >> zip;
                newName = first1 + " " + last1;
                net.add_user(newName, year, zip);
                break;
                
            case 2:
                cout << "The format is: " <<endl << 
                    "'Friend One' ' Friend Two'" << endl;
                cin >> first1 >> last1;
                cin >> first2 >> last2;
                name1 = first1 + " " + last1;
                name2 = first2 + " " + last2;
                error = net.add_connection(name1, name2);
                if (error == -1){
                    cout << "At least one of these users dont exist" << endl;
                    continue;
                }
                break;
            case 3: 
                cout << "The format is: " <<endl << 
                    "'Friend One' ' Friend Two'" << endl;
                cin >> first1 >> last1 >> first2 >> last2;
                name1 = first1 + " " + last1;
                name2 = first2 + " " + last2;
                error = net.remove_connection(name1, name2);
                if (error == -1){
                    cout << "At least one of these users dont exist" << endl;
                    continue;
                }                
                break;
            case 4:
                net.printNetwork();
                break;
            case 5:
                cout << "The format is: " <<endl << "'User Name'" <<
                    endl;
                cin >> first1 >> last1;
                newName = first1 + " " + last1;
                
                id = net.get_id(newName);
                if(id == -1){
                    cout << "This user does not exist" << endl;
                    continue;
                }
                net.printFriends(id);
                break;
            case 6:
                cout << "The format is: " <<endl << "'New text file name'" 
                    <<endl;
                cin >> file;
                net.write_friends(file.c_str());
                break;
            default:
                cout << "Invalid option, goodbye!" << endl;
                return 0;
                
                
        }
    }

  return 0;
}
