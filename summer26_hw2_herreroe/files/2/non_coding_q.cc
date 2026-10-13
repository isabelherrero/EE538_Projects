#include <iostream>
#include <set>
#include <vector>
// - Run the following code with Address Sanitizer enabled:
//   - bazel run //files/2:non_coding_q --config=asan
//   - Note: the program might crash!
// - What is wrong with each piece of code below?
// - For each case modify the code so that the issue is fixed.

void Question1() {
  std::vector<int> elements;

  // Number of values to read from the input
  const int number_of_items = 10;

  // Initializing the elements vector.
  for (int i = 0; i < number_of_items; i++) {
    elements.push_back(0);
    //int element;
    //elements[i] = 0;
  }
}

void Question2() {
  //int* a;
  //(*a) = 12;
  //(*a)++;
  int a = 12;
  int* p = &a;
  (*p)++;
  //std::cout << "(*a): " << (*a) << std::endl;
  std::cout << "(*p): " << (*p) << std::endl;
}

void Question3() {
  int* a = new int;
  int* b = new int;
  (*a) = 1;
  (*b) = 2;

  std::cout << "(*a) + (*b): " << (*a) + (*b) << std::endl;

  delete a;
  delete b;
}

void Question4() {
  int* a = new int[2];
  int* b = new int[2];
  (*a) = 1;
  (*b) = 2;
  std::cout << "(*a) + (*b): " << (*a) + (*b) << std::endl;

  a++;
  b++;
  (*a) = 1;
  (*b) = 2;
  std::cout << "(*a) + (*b): " << (*a) + (*b) << std::endl;

  delete[] (a - 1);
  delete[] (b - 1);
}

void Question5() {
  for (int i = 0; i < 10; i++) {
    std::cout << "i: " << i << std::endl;
    //i = i - 1;
    //std::cout << "i: " << i << std::endl;
  }
}

void Question6() {
  std::set<int> elements = {0, 1, 2, 3, 4, 5};

  std::set<int> original = elements;

  //for (auto it = elements.begin(); it != elements.end(); ++it) {
  //  elements.insert((*it) + 1);
  //}
  for (auto e : original) {
    elements.insert(e + 1);
  }
  
  for (auto e : elements) {
    std::cout << "e: " << e << std::endl;
  }
}

int main() {
  int user_choice;

  bool run_the_loop = true;
  while (run_the_loop) {
    std::cout << "Please enter a value between 1 to 6 to run a function. Any "
                 "other value to exit."
              << std::endl;
    std::cin >> user_choice;
    switch (user_choice) {
      case 1:
        Question1();
        break;
      case 2:
        Question2();
        break;
      case 3:
        Question3();
        break;
      case 4:
        Question4();
        break;
      case 5:
        Question5();
        break;
      case 6:
        Question6();
        break;
      default:
        std::cout << "Invalid value entered. Exit the program!" << std::endl;
        run_the_loop = false;
        break;
    }
  }
  return 0;
}