#include <iostream>
#include <vector>
#include <string>
using namespace std;

vector<int> id(26);
vector<int> sz(26);

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

bool EquationsPossible(vector<string>& equations) {
  for (int i = 0; i < 26; i++)
  {
    id[i] = i;
    sz[i] = 1;
  }

  for (string s : equations) {
    if (s[1] == '=') {
      Union(s[0] - 'a', s[3] - 'a');
    }
  }

  for (string s: equations) {
    if (s[1] == '!') {
      if (Find(s[0] - 'a') == Find(s[3] - 'a')) {
        return false;
      } 
    }
  }

  return true;
}

int main() {
  vector<string> example_1 = {"a==b", "b!=a"};
  vector<string> example_2 = {"b==a", "a==b"};
  cout << EquationsPossible(example_1) << endl;
  cout << EquationsPossible(example_2) << endl;
}
