#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;


class Node
{
public:
  Node(char letter,float probability);
  Node();
  float get_probability();
  char get_letter();
  string get_path();
  void set_path();

  void add_son(Node* son,int right_or_left);
  void update_value();
  Node* get_son(int right_or_left);
  string get_path(char letter);
  char search(string sample);
private:
  /*friend class boost::serialization::access;*/
  Node* right_son;
  Node* left_son;
  char letter;
  float probability;
  string path;/*
  template <class Archive> void serialize(Archive &ar, unsigned) {
          ar &letter;
          ar &probability;
          ar &right_son;
          ar &left_son;
          ar &path;
      }*/

};

#endif // NODE_H
