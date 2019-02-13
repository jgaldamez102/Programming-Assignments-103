
#include "user.h"
#include "network.h"

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <sstream>
#include <iomanip>




Network :: Network (){
    total =0;
}
Network :: ~Network(){
    
}

int Network :: getSize(){
    return userlists.size();
}

//Initializes the network's information from filename
int Network :: read_friends(const char *filename){
    std :: ifstream file;
    file.open(filename);
    
    if (file.fail()){
        std :: cout << "File does not load" << std :: endl;
        return -1;
    }
    file >> total;
    
    for (int i=0; i<total;i++){
        User temp;
        
        
        int x, t;
        file >> t /*temp._id*/;
        temp.setID(t);
        std:: string ntemp;
        getline(file, ntemp);
        getline(file, ntemp);
        std:: stringstream ss1(ntemp);
        std:: string first, last;
        
        ss1 >> first;
        ss1 >> last;
        
        std :: string jointname;
        jointname = first + " " + last;
        temp.setName(jointname);
        
        file >> t;
        temp.setYear(t);
        file >> t;
        temp.setZip(t);
        std :: string friendsList;
        getline(file, friendsList);
        getline(file, friendsList);
        
        std :: stringstream ss2(friendsList);
        
        while (ss2 >> x){
            temp.add_friend(x);
        }
        userlists.push_back(temp);
    }
    //Close
    file.close();
    
    return 0;
}

//Writes network information onto filename
int  Network :: write_friends(const char *filename){
    int totalusers = (int)userlists.size();
    std :: ofstream file;
    file.open(filename);
    if (file.fail()){
        std :: cout << "Please enter a valid file "  <<
        "name" << std :: endl;
        return -1;
    }
    file << userlists.size() << "\n";
    for (int i=0; i<totalusers; i++){
        file << userlists[i].getID() << std::endl;
        file << '\t' << userlists[i].getName() << std::endl;
        file << '\t' <<userlists[i].getYear() << std ::endl;
        file << '\t' << userlists[i].getZip() <<std::endl;
        
        int x = (int)userlists[i].getFriend()->size();
        file << '\t';
        
        for (int j=0; j<x; j++){
            file << userlists[i].getFriend()[0][j] << " ";
        }
        file <<std :: endl;
        
        
    }
    file.close();
    return 0;
}

//Adds a user to the network
void Network :: add_user(std::string username, int year, int zipcode){
    User temp;
    temp.setName(username);
    temp.setYear(year);
    temp.setZip(zipcode);
    
    temp.setID(total);
    
    userlists.push_back(temp);
    total = (int)userlists.size(); // or total++
}

//Adds two users as friends, if they both already exist
int  Network :: add_connection(std::string name1, std::string name2){
    int n1 = -1, n2=-1, names =0;
    for (int i=0; i<total; i++){
        if (userlists[i].getName() == name2){
            n1 = userlists[i].getID();
            names +=1;
        }
        if (userlists[i].getName() == name1){
            n2 = userlists[i].getID();
            names +=1;
        }
    }
    
    if (names == 2){
        userlists[n1].add_friend(n2);
        userlists[n2].add_friend(n1);
        return 0;
    }
    else{
        return -1;
    }
    
    
    
    
}

//Deletes the connection between two users, if they both exist.
int  Network :: remove_connection(std::string name1, std::string name2){
    int n1 = -1, n2=-1, names =0;
    for (int i =0; i<total;i ++){
        if (userlists[i].getName() == name1){
            n1 = userlists[i].getID();
            names++;
        }
        if (userlists[i].getName() == name2){
            n2 = userlists[i].getID();
            names++;
        }
    }
    if (names ==2){
        userlists[n1].delete_friend(n2);
        userlists[n2].delete_friend(n1);
        return 0;
    }
    
    else
        return -1;
}

//Returns the ID of the User username
int Network :: get_id(std::string username){
    int nameID = -1, names = -1;
    for (int i=0;i <total; i++){
        if (userlists[i].getName() == username){
            nameID = userlists[i].getID();
            names ++ ;
        }
    }
    if (names == -1){
        return -1;
    }
    
    return nameID;
    
}


User Network::getUser(int id) {
    return userlists[id];
}





// a shortest path starting at user “from” and ending
// at user “to”. If no path exists, returns empty vector
std:: vector<int> Network::shortest_path(int from, int to){
    std :: vector<int> shortestpath;
    bfs(from);
    if (userlists[to].get_depth() == -1){
        return shortestpath;
    }
    if (from == -1 || to == -1){
        return shortestpath;
    }
    if (from == to){
        shortestpath.push_back(to);
        return shortestpath;
    }
    else{
        int temp = to;
        if (userlists[to].get_predecessor() == to){
            shortestpath.push_back(to);
            return shortestpath;
        }
        else{
            shortestpath.push_back(temp);
            while (userlists[temp].get_predecessor() != from){
                int pred = userlists[temp].get_predecessor();
                
                shortestpath.insert(shortestpath.begin(),(pred));
                temp=pred;
                
            }
            shortestpath.insert(shortestpath.begin(),from);
            
            
            return shortestpath;
        }
        
    }
}


// a list of the components of the network
std ::vector<std ::vector<int> > Network::groups(){
    std :: vector<std :: vector<int> > group;
    
    for (int i=0; i <userlists.size(); i ++){
        if (userlists[i].get_depth() == -1){
            group.push_back(bfs(i));
        }
    }
    return group;
    
}

// suggested friends with highest score for this user.
// fills in “score” variable (passed by C++ reference).
// If no suggestions exist, give empty vector and
// set score to be -1

std::vector<int> Network::suggest_friends(int who, int& score) {
    bfs(who);
    std:: vector <int> suggestList;
    std :: vector <int> tempList;
    std :: vector <int> scoreList;

    int max;
    for (int i=0; i<userlists.size();i ++){
        if (userlists[i].get_depth() == 2){
            tempList.push_back(i);
        }
    }
    for (int j=0; j <tempList.size();j++){
        int count = 0;
        for (int k=0;k<userlists[who].getFriend()->size();k++){
            std :: vector<int> temp2 = *(userlists[tempList[j]].getFriend());
            std :: vector<int> temp3 = *(userlists[who].getFriend());
            
            for (int l=0; l<userlists[tempList[j]].getFriend()->size();l++){
                if(temp3[k] == temp2[l]){
                    count ++;
                }
                if (count >max){
                    max =count;
                }
                
            }
        }
        scoreList.push_back(count);
    }
    
    
    for (int i=0;i<scoreList.size();i++){
        if (scoreList[i] == max){
            suggestList.push_back(tempList[i]);
        }
    }
    score=max;
    if (score == 0){
        score =-1;
    }
    return suggestList;
}

//BFS Algorithm, returns the visited vector
std :: vector<int> Network :: bfs(int id){
    std :: vector<int> qu;
    std :: vector<int> visited;
    qu.push_back(id);
    visited.push_back(id);
    
    userlists[id].set_depth(0);
    
    while(!qu.empty()){
        int x=qu.front();
        qu.erase(qu.begin());
        
        std:: vector <int>* tempa= userlists[x].getFriend();
        
        for (int i=0;i<tempa->size() ; i++){
            int idfriend = (*tempa)[i];
            if(userlists[idfriend].get_depth() == -1){
                qu.push_back(idfriend);
                
                visited.push_back(idfriend);
                userlists[idfriend].set_predecessor(x);
                userlists[idfriend].set_depth( userlists[x].get_depth() +1);
                
            }
        }
        
        
    }
    return visited;
}
//resets all depth back to -1 
void Network :: reset_depth(){
    for (int i=0; i <userlists.size();i++){
        userlists[i].set_depth(-1);
    }
}

//Prints the table of all friends
void Network :: printFriends(int id){
    int totalusers = (int)userlists[id].getFriend()->size();
    std :: cout << "ID " << std:: setw(15) <<"User Name " <<
    std :: setw(8) << "Year" << std :: setw(8) <<
    "Zip" << std::endl <<
    "===========================================" << std::endl;
    for (int i=0;i < totalusers;i++){
        int tempid = userlists[id].getFriend()[0][i];
        int namelength = (int)userlists[tempid].getName().size();
        std:: cout << tempid << "." << std::setw(4+ namelength) <<
        userlists[tempid].getName() << std ::setw(19-namelength) <<
        userlists[tempid].getYear() << std :: setw(10) <<
        userlists[tempid].getZip() << std::endl;
    }
}
//Prints the network containing all friends
void Network :: printNetwork(){
    int totalusers = (int)userlists.size();
    std :: cout << "ID " << std:: setw(15) <<"User Name " <<
    std :: setw(8) << "Year " << std :: setw(8) <<
    "Zip " << std::endl <<
    "===========================================" << std::endl;
    for (int i=0; i<totalusers ; i++){
        int namelength = (int)userlists[i].getName().size();
        std :: cout << userlists[i].getID() << "." <<
        std::setw(4+namelength) << userlists[i].getName() <<
        std::setw(19-namelength) << userlists[i].getYear() <<
        std::setw(10) << userlists[i].getZip() << std::endl;
    }
}