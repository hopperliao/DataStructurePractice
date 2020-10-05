#include <vector>

class UnionFind {
 public:
  UnionFind(int n);
  ~UnionFind();
  int Count();
  bool Connected(int p, int q);
  virtual int Find(int p) = 0;
  virtual void Union(int p, int q) = 0;

 protected:
  int count;  //The number of connected components
  std::vector<int> id;  //The index of connected components
};

class QuickFind : public UnionFind {
 public:
  QuickFind(int n);
  int Find(int p);
  void Union(int p, int q);
};

class QuickUnion : public UnionFind {
 public:
  QuickUnion(int n);
  int Find(int p);
  void Union(int p, int q);
};

class WeightedQuickUnion : public QuickUnion {
 public:
  WeightedQuickUnion(int n);
  void Union(int p, int q);

 protected:
  std::vector<int> sz;  //The size of connected components
};


