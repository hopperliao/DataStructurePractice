#include <iostream>
#include <vector>

void Exchange(int& a, int& b) {
  int temp = a;
  a = b;
  b = temp;
}

void Print(const std::vector<int>& data) {
  for (auto e : data) {
    std::cout << e << " ";
  }
  std::cout << std::endl;
}
void SelectionSort(std::vector<int> data) {
  for (int i = 0; i < data.size(); i++) {
    int min = i;
    for (int j = i + 1; j < data.size(); j++) {
      if (data[j] < data[min]) {
        Exchange(data[j], data[min]);
      }
    }  
  }
  Print(data);
}

void InsertSort(std::vector<int> data) {
  for (int i = 1; i < data.size(); i++) {
    for (int j = i; j > 0 && data[j] < data[j - 1]; j--) {
      Exchange(data[j], data[j - 1]);
    }
  }
  Print(data);
}

void ShellSort(std::vector<int> data) {
  int n = data.size();
  int h = 1;
  while (h < n / 3) h = 3 * h + 1;

  while (h >= 1) {
    for (int i = h; i < n; i++) {
      for (int j = i; j >= h && data[j] < data[j - h]; j-=h) {
        Exchange(data[j], data[j - h]);
      }
    }
    h = h/3;
  }

  Print(data);
}
int main() {
  std::vector<int> data = {3, 5, 1, 4, 2};
  SelectionSort(data);
  InsertSort(data);
  ShellSort(data);
}
