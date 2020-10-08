#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> id;
vector<int> sz;

int Find(int p) {
  while (p != id[p]) {
    id[p] = id[id[p]];
    p = id[p];
  }

  return p;
}

void Union(int p, int q) {
  int p_root = Find(p);
  int q_root = Find(q);

  if (p_root == q_root) return;
  if (sz[p_root] > sz[q_root]) {
    id[q_root] = p_root;
    sz[p_root] += sz[q_root];
  } else {
    id[p_root] = q_root;
    sz[q_root] += sz[p_root];
  }
}


vector<int> FindRedundantConnection(vector<vector<int>>& edges) {
  if (0 == edges.size() || 0 == edges[0].size()) return {};
 
  int n = edges.size();
  int e0 = 0, e1 = 0; 

  id.resize(n);
  sz.resize(n);
  for (int i = 0; i < n; i++) {
    id[i] = i;
    sz[i] = 1;
  }

  for (vector<int>& edge : edges)
  {
    if (Find(edge[0] - 1) == Find(edge[1] - 1))
    {
      e0 = edge[0];
      e1 = edge[1];
    } else {
      Union(edge[0] - 1, edge[1] - 1);
    }
  }

  int u = e0 > e1 ? e1 : e0;
  int v = e0 > e1 ? e0 : e1;
  return {u, v};
}

int main() {
  vector<vector<int>> example_1 = {{1, 2}, {1, 3}, {2, 3}};
  vector<vector<int>> example_2 = {{1, 2}, {2, 3}, {3, 4}, {1, 4}, {1, 5}};
  vector<int> ans1 = FindRedundantConnection(example_1);
  vector<int> ans2 = FindRedundantConnection(example_2);
  cout << ans1[0] << ", "<< ans1[1] << endl;
  cout << ans2[0] << ", "<< ans2[1] << endl;
}
