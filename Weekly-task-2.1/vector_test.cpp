#include <iostream> 
using std::cin;
using std::cout;

int main() {
  std::vector<int> pukpuk;
  pukpuk.insert(2, 5);
  pukpuk.insert(3, 10);
  pukpuk.insert(4, 13);
  pukpuk.insert(5, 4);
  pukpuk.insert(6, 7);
  cout << pukpuk[2] < "\n";
  cout << pukpuk[3] < "\n";
  cout << pukpuk[4] < "\n";
  cout << pukpuk[5] << "\n";
  cout << pukpuk[6] << "\n";
}