#include "user.h"
#include <vector>
#include <string>
#include <cstdlib>

User :: User(){
    _id = -1;
    _year = 0;
    _zip = 0;
    depth=-1;
    predecessor =-1;
    
}
User :: ~User(){
    
}

int User :: getID(){
    return _id;
}

void User :: setID(int id){
    this->_id = id;
}

std :: string User :: getName(){
    return _name;
}
void User :: setName (std ::string name){
    _name = name;
}

int User :: getYear(){
    return _year;
}
void User :: setYear(int year){
    _year = year;
}

int User :: getZip(){
    return _zip;
}
void User :: setZip(int zip){
    _zip = zip;
}


 std:: vector <int>* User :: getFriend(){
    return &friends;
}

void User::add_friend(int id){
    friends.push_back(id);
}

void User::delete_friend(int id){
    int i = 0;
    while(id != friends[i]){
        i++;
    }
    friends.erase(friends.begin()+i);
}
void User :: set_depth(int d){
       depth = d;
}
int User :: get_depth(){
    return depth;
    
}

void User :: set_predecessor(int p){
    predecessor = p;
}
int User :: get_predecessor(){
    return predecessor;
}