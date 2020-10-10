#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <string>
using namespace std;

unordered_map<string, string> id;
unordered_map<string, double> weights;

pair<string, double>  Find(string p) {
  if (id.find(p) == id.end()) return {"", -1.0};
  double weight = 1.0;
  while (p != id[p]) {
    weight *= weights[p];
    p = id[p];
  }

  return {p, weight};
}

void Union(string p, string q, double value) {
  pair<string, double> p_root = Find(p);
  pair<string, double> q_root = Find(q);
  if ("" == p_root.first || "" == q_root.first) return;
  if (p_root.first == q_root.first) return;
  id[p_root.first] = q_root.first;
  weights[p_root.first] = 1 / p_root.second * value * q_root.second;
}


vector<double> CalcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
  vector<double> ans;
  for (int i = 0; i < equations.size(); i++) {
    string a = equations[i][0];
    string b = equations[i][1];
    if (id.find(a) == id.end()) {
      id[a] = a;
      weights[a] = 1.0;
    }
    if (id.find(b) == id.end()) {
      id[b] = b;
      weights[b] = 1.0;
    }
    Union(a, b, values[i]);
  }

  for (vector<string>& query : queries) {
    string p = query[0];
    string q = query[1];
    pair<string, double> p_root = Find(p);
    pair<string, double> q_root = Find(q);
    if (p_root.first != q_root.first || "" == p_root.first || "" == q_root.first) {
      ans.push_back(-1.0);
    } else {
      ans.push_back(p_root.second / q_root.second);
    }
  }

  return ans;
}

int main() {
//  vector<vector<string>> equations1 = {{"a", "b"}, {"b", "c"}};
//  vector<double> values1 = {2.0, 3.0};
//  vector<vector<string>> queries1 = {{"a", "c"}, {"b", "a"}, {"a", "e"}, {"a", "a"}, {"x", "x"}};
//  vector<double> ans1 = CalcEquation(equations1, values1, queries1);
//  for (double& d : ans1) {
//    cout << d << " ";
//  }
//  cout << endl;

  vector<vector<string>> equations2 = {{"a", "b"}, {"b", "c"}, {"bc", "cd"}};
  vector<double> values2 = {1.5, 2.5, 5.0};
  vector<vector<string>> queries2 = {{"a", "c"}, {"c", "b"}, {"bc", "cd"}, {"cd", "bc"}};
  vector<double> ans2 = CalcEquation(equations2, values2, queries2);
  for (double& d : ans2) {
    cout << d << " ";
  }
  cout << endl;   
//
//  vector<vector<string>> equations3 = {{"a", "b"}};
//  vector<double> values3 = {0.5};
//  vector<vector<string>> queries3 = {{"a", "b"}, {"b", "a"}, {"a", "c"}, {"x", "y"}};
//  vector<double> ans3 = CalcEquation(equations3, values3, queries3);
//  for (double& d : ans3) {
//    cout << d << " ";
//  }
//  cout << endl;
}
