#include "union_find.h"
#include <iostream>
UnionFind::UnionFind(int n) {
  id.resize(n);
  for (int i = 0; i < n; i++) {
    id[i] = i;
  }
  count = n;
}

UnionFind::~UnionFind(){}

int UnionFind::Count() {
  return count;
}

bool UnionFind::Connected(int p, int q) {
  return Find(p) == Find(q);
}

QuickFind::QuickFind(int n):UnionFind(n) {}

int QuickFind::Find(int p) {
  return id[p];
}

void QuickFind::Union(int p, int q) {
  int p_id = Find(p);
  int q_id = Find(q);

  if (p_id == q_id) return;
  
  for (int i = 0; i < id.size(); i++) {
    if (p_id == id[i]) {
      id[i] = q_id;
    }
  }
  
  count--;
}

QuickUnion::QuickUnion(int n):UnionFind(n){}

int QuickUnion::Find(int p) {
  //get the root node of the tree which contains p
  while (p != id[p]) {
    p = id[p];
  }
  return p;
}

void QuickUnion::Union(int p, int q) {
  int p_root = Find(p);
  int q_root = Find(q);
  
  if (p_root == q_root) return;
  
  id[p_root] = q_root;
  count--;
}

WeightedQuickUnion::WeightedQuickUnion(int n):QuickUnion(n) {
  sz.resize(n);
  for (int i = 0; i < n; i++) {
    sz[i] = 1;
  }
}

void WeightedQuickUnion::Union(int p, int q) {
  int p_root = Find(p);
  int q_root = Find(q);

  if (p_root == q_root) return;

  //add the small tree to the big tree to prevent the tree from becoming too deep
  if (sz[p_root] < sz[q_root]) {
    id[p_root] = q_root;
    sz[q_root] += sz[p_root];
  } else {
    id[q_root] = p_root;
    sz[p_root] += sz[q_root];
  }
  count--;
}

int main() {
  int n = 10;
  std::vector<std::vector<int>> p_q_pair = {{4, 3}, {3, 8}, {6, 5}, {9, 4}, {2, 1}, {8, 9}, {5, 0}, {7, 2}, {6, 1}, {1, 0}, {6, 7}};
  QuickFind quick_find_case(n);
  std::cout << "*********quick find case*********" << std::endl; 
  for (int i = 0; i < p_q_pair.size(); i++) {
    if (quick_find_case.Connected(p_q_pair[i][0], p_q_pair[i][1])) continue;
   
    quick_find_case.Union(p_q_pair[i][0], p_q_pair[i][1]);
    std::cout << p_q_pair[i][0] << " " << p_q_pair[i][1] << std::endl;
  }
  
  std::cout << "Components: " << quick_find_case.Count() << std::endl;

  QuickUnion quick_union_case(n);
  std::cout << "*********quick union case*********" << std::endl; 
  for (int i = 0; i < p_q_pair.size(); i++) {
    if (quick_union_case.Connected(p_q_pair[i][0], p_q_pair[i][1])) continue;
   
    quick_union_case.Union(p_q_pair[i][0], p_q_pair[i][1]);
    std::cout << p_q_pair[i][0] << " " << p_q_pair[i][1] << std::endl;
  }
  
  std::cout << "Components: " << quick_union_case.Count() << std::endl;

  WeightedQuickUnion weighted_quick_union_case(n);
  std::cout << "*********weighted quick union case*********" << std::endl; 
  for (int i = 0; i < p_q_pair.size(); i++) {
    if (weighted_quick_union_case.Connected(p_q_pair[i][0], p_q_pair[i][1])) continue;
   
    weighted_quick_union_case.Union(p_q_pair[i][0], p_q_pair[i][1]);
    std::cout << p_q_pair[i][0] << " " << p_q_pair[i][1] << std::endl;
  }
  
  std::cout << "Components: " << weighted_quick_union_case.Count() << std::endl;


}
