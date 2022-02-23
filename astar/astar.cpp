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
  Node(){}
  Node(const Position& pos)
  {
    this->pos = pos;
    this->id = pos.y * width + pos.x;
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
}Node, *pNode;


int main(int argc, char* argv[])
{
  priority_queue<pNode, vector<pNode>, greater<pNode> > open_list;//开放列表
  map<int, bool> close_list;                                      //关闭列表
  vector<pNode> node_list;






  //清理
  for (auto node : node_list)
  {
    delete node;
  }

  return 0;
}