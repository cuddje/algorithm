#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <sstream>
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

  inline bool operator==(Position& b)
  {
    return x == b.x && y == b.y;
  }
}Position;

typedef struct Node{
  Node(){}
  Node(const Position& pos)
  {
    this->pos = pos;
    this->id = pos.y * width + pos.x;
    H = 0;
    G = 0;
    F = 0;
    closed = false;
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
  bool closed;
  Position pos;
  Node* parent;

  // inline bool operator<(const Node& b)
  // {
  //   return F < b.F;
  // }
}Node, *pNode;


Node* crete_new_node(const Position& pos, map<int, pNode>& list, const Position& end){
  auto node = new Node(pos);
  node->setH(end);
  list[node->id] = node;
  return node;
}

int main(int argc, char* argv[])
{
  auto comp = [=](pNode a, pNode b) { return a->F > b->F; };
  priority_queue<pNode, vector<pNode>, decltype(comp) > open_list(comp);//开放列表
  map<int, pNode> open_list_map;
  map<int, pNode> close_list;                                           //关闭列表
  map<int, pNode> node_list;                                            //全部节点列表

  pNode find = nullptr;
  Position start(0,2);
  Position end(9, 2);
  pNode s = crete_new_node(start, node_list, end);
  open_list.push(s);//起点加入开放列表
  open_list_map[s->id] = s;

  while(!open_list.empty())
  {
    auto current = open_list.top();
    close_list[current->id] = current;//加入关闭列表
    open_list.pop();
    open_list_map.erase(current->id);


    auto f = current->F;
    for (auto v:open_list_map) 
    {
      if (f > v.second->F)
      {
        int test = 0;
      }
    }


    if (current->pos == end){
      find = current;
      break;
    }

    int dir[][2] = { {0,1}, {0,-1}, {1,0}, {-1,0}};
    for (int i=0; i < 4; i++)
    {
      auto v = dir[i];
      int x = current->pos.x + v[0];
      int y = current->pos.y + v[1];
      int id = y * width + x;
      if (x < 0 || x >= width || y < 0 || y >= height || cfg[x][y] != 0) continue;
      if (close_list.find(id) != close_list.end()) continue;

      pNode next_node = nullptr;
      if (open_list_map.find(id) != open_list_map.end())
      {
        next_node = open_list_map.at(id);
        if (current->G + 10 < next_node->G)
        {
          next_node->setG(current->G + 10);
          next_node->parent = current;
        }
      }
      else
      {
        next_node = crete_new_node(Position(x, y), node_list, end);
        next_node->parent = current;
        next_node->setG(current->G + 10);
        open_list.push(next_node);
        open_list_map[next_node->id] = next_node;
      }
    }
  }

  vector<pNode> path;
  while(find != nullptr)
  {
    path.push_back(find);
    find = find->parent;
  }

  for (auto node : path)
  {
    cfg[node->pos.x][node->pos.y] = 2;
  }
  for (int y = 0; y < height; y++)
  {
    stringstream fmt;
    fmt << "lien:" << y << " ";
    for (int x = 0; x < width; x++)
    {
      fmt << cfg[x][y] << " ";
    }

    cout << fmt.str() << endl;
  }

  //清理
  for (auto v : node_list)
  {
    delete v.second;
  }

  return 0;
}