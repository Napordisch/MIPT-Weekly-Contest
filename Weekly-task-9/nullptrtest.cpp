#include <iostream>

int main(){
 int* ptr = new int;
  *ptr = 2;
  std::cout << ptr<< "\n";
  delete ptr;
  if (ptr == nullptr){
    std::cout << "yes";
  }
  std::cout << ptr;
  return 0;
}