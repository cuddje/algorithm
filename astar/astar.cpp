#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;


int width = 10, height = 10;
int cfg[10][10] = {
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

typedef struct Position{
  Position(){}
  Position(int x, int y)
  {
    this->x = x;
    this->y = y;
  }

  int x;
  int y;
}Position;

typedef struct Node{
  Node(const Position& pos)
  {
    this->pos = pos;
    this->id = pos.y * width + pos.x;
    H = 0;
    G = 0;
    F = 0;
  }

  void setH(const Position& pos){
    this->H = abs(this->pos.x - pos.x) + abs(this->pos.y - pos.y);
  }

  void setG(int v){
    this->G = v;
    this->F = G + H;
  }

  int F;
  int G;  //当前的消耗
  int H;  //距离终点的预估值
  int id;
  Position pos;
  Node* parent;

  inline bool operator<(Node b)
  {
    return F < b.F;
  }
}Node, *pNode;


Node* crete_new_node(const Position& pos, vector<pNode>& vec, const Position& end){
  auto node = new Node(pos);
  node->setH(end);
  vec.push_back(node);
  return node;
}

int main(int argc, char* argv[])
{
  auto comp = [](pNode a, pNode b) { return *a < *b; };
  priority_queue<pNode, vector<pNode>, decltype(comp) > open_list;//开放列表
  map<int, bool> close_list;                                      //关闭列表
  vector<pNode> node_list;

  Position start(0,2);
  Position end(9, 2);
  open_list.push(crete_new_node(start, node_list, end));//起点加入开放列表

  while(!open_list.empty())
  {
    auto current = open_list.top();
    open_list.pop();
  }


  //清理
  for (auto node : node_list)
  {
    delete node;
  }

  return 0;
}