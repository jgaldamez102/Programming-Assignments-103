#ifndef NETWORK_H
#define NETWORK_H

#include "user.h"
#include <string>
#include <vector>



class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(std::string username, int yr, int zipcode);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  void printFriends(int id);
  void printNetwork();
    
  
  User getUser(int id);
  int getSize();
    void reset_depth();
  std::string get_name(int id);
  std:: vector<int> bfs(int id);
  std:: vector<int> shortest_path(int from, int to);
  std :: vector<std::vector<int> >  groups();
  std :: vector<int>  suggest_friends(int who, int& score);
  
    


 private:
    std:: vector<User> userlists;
    int total;
  
};


#endif

