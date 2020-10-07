#include <iostream>
#include <vector>
using namespace std;

vector<int> id;
vector<int> sz;
int components_count;

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
  components_count--;
}


int FindCircleNum(vector<vector<int>>& M) {
  //initialize the two arrays
  int n = M.size();  
  id.resize(n);
  sz.resize(n);
  for (int i = 0; i < n; i++) {
    id[i] = i;
    sz[i] = 1;
  }
  components_count = n;

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      if (1 == M[i][j]) {
        Union(i, j);
      }
    }
  }

  return components_count;
}

int main() {
  vector<vector<int>> example_1 = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
  vector<vector<int>> example_2 = {{1, 1, 0}, {1, 1, 1}, {0, 1, 1}};
  cout << FindCircleNum(example_1) << endl;
  cout << FindCircleNum(example_2) << endl;
}
