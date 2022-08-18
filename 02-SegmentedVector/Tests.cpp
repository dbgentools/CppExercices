#include "Solution.hpp"
#include <iostream>

int main(int, char**) {
  solution::SegmentedVector<int> sv{};
  for (int i = 0; i < 200; ++i)
    sv.push_back(i);

  sv.reorganize(10, 50);

  int arr[128];
  memset(arr, 0, 128*sizeof(int));
  sv.copy(arr, 120);

  for (int i{0}; i<128; ++i)
    std::cout << arr[i] << ",";
  std::cout << "\n";

  for (int i{ 0 }; i < 128; ++i)
    std::cout << sv.at(i) << ",";
  std::cout << "\n";

  sv.remove(70);

  for (int i{ 0 }; i < 128; ++i)
    std::cout << sv.at(i) << ",";
  std::cout << "\n";

  return 0;
}