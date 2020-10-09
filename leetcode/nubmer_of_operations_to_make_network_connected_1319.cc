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


int MakeConnected(int n, vector<vector<int>>& connections) {
  //initialize the two arrays
  if (0 >= n || n - 1 > connections.size()) return -1;
  id.resize(n);
  sz.resize(n);
  for (int i = 0; i < n; i++) {
    id[i] = i;
    sz[i] = 1;
  }
  components_count = n;
  for (vector<int>& connection : connections) {
    Union(connection[0], connection[1]);
  }

  return components_count - 1;
}

int main() {
  int n1 = 4, n2 = 6, n3 = 6, n4 = 5;
  vector<vector<int>> example_1 = {{0, 1}, {0, 2}, {1, 2}};
  vector<vector<int>> example_2 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}, {1, 3}};
  vector<vector<int>> example_3 = {{0, 1}, {0, 2}, {0, 3}, {1, 2}};
  vector<vector<int>> example_4 = {{0, 1}, {0, 2}, {3, 4}, {2, 3}};
  cout << MakeConnected(n1, example_1) << endl;
  cout << MakeConnected(n2, example_2) << endl;
  cout << MakeConnected(n3, example_3) << endl;
  cout << MakeConnected(n4, example_4) << endl;
}
