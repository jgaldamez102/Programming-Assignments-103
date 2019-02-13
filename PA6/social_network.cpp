#include "network.h"
#include "user.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>


using namespace std;

int main(int argc, char *argv[])
{
    int error=0,option =0;
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
        "information" << endl
        << "7) Find the shortest path between two people " <<endl <<
        "8) Print a list of all subgroups in a network" <<endl
        << "9) Give friend suggestions" << endl;
        int temp =0;
        cin>> temp;
        option = temp;
        
        string first1,first2,last1,last2, newName;
        string name1,name2, file;
        int id, year, zip, score;
        int name1Id,  name2Id;
        vector<int>   path;
        vector<vector<int> > group;
        
        
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
            case 7:
                cin >> first1 >> last1;
                name1 = first1 + " " + last1;
                cin >> first2 >> last2;
                name2 = first2 + " " + last2;
                name1Id = net.get_id(name1);
                name2Id = net.get_id(name2);
               if (net.shortest_path(name1Id, name2Id).empty()){
                    cout << "None" <<endl;
                }
                if (name1 == name2){
                    cout << "Distance: 0" <<endl;
                    cout << name1 << endl;
                }
                else{
                    std ::vector <int> path =
                        net.shortest_path(name1Id, name2Id);
                    cout << "Distance: " << path.size() <<endl;
                    cout << name1 << " ->";
                    while (!path.empty()){
                        int back=path.back();
                        cout << " " << net.getUser(back).getName()
                            << " ";
                        if (path.size() != 1){
                            cout << "->";
                        }
                        path.pop_back();
                    }
                    //cout << endl;
                }
                for (int i=0;i<net.getSize();i++){
                    net.getUser(i).set_depth(-1);
                }
                net.reset_depth();
                    
                break;
            case 8:
                group = net.groups();
                for (int i = 0; i < group.size(); i++) {
                    cout << "Set " << i + 1 << " => ";
                    for (int j = 0; j < (group[i]).size(); j++) {
                        cout << net.getUser((group[i])[j]).getName();
                     if(j != group[i].size() - 1){
						cout << ", ";
					}
                            
                    }
                    cout << endl;
                }
               net.reset_depth();
                break;
            case 9:
                {
                cin >> first1 >> last1;
                name1 = first1 + " " + last1;
                id = net.get_id(name1);
                if(id == -1){
                    cout << "This user does not exist" << endl;
                    continue;
                }
                else{
                name1Id = net.get_id(name1);
                vector<int> forward = net.suggest_friends(name1Id, score);

                cout << "The suggested friend(s) is/are: "<< endl;
                if (score <=0 || forward.size() < 1){
                    cout << "None" << endl;
                }
                else{
                    
                    for (int i=0;i<forward.size();i++){
                        cout << left << setw(15) 
                            << net.getUser(forward[i]).getName() 
                            << "Score: " << score << endl;
                    }
                }
                }
                }
                break;
            case -1:
                return 0;
            default:
                cout << "Invalid option, goodbye!" << endl;
                return 0;
                
                
                
        }
    }
    
    return 0;
}

