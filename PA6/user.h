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
    
    void set_depth(int d);
    
    bool visit;
    std :: vector<int> friends; 
    int get_depth();
    int get_predecessor();
    void set_predecessor(int p);
    

 private:
    int _id;
    std :: string _name; //using getline function
    int _year;
    int _zip;
      int depth;
    
      int predecessor;


       

};


#endif

