#ifndef USER_H
#define USER_H

#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>


class User {
 public:
    User();
    ~User();
    
    void add_friend(int id);
    void delete_friend(int id);
    
    int getID();
    void setID(int id);
    
    std :: string getName();
    void setName(std:: string name);
    
    int getYear();
    void setYear(int year);
    
    int getZip();
    void setZip(int zip);
    
    std :: vector<int>* getFriend();
    
    
    

 private:
    int _id;
    std :: string _name; //using getline function
    int _year;
    int _zip;
    std :: vector<int> friends;
    
       

};


#endif
