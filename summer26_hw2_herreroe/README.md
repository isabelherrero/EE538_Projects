[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/rbKvTfFZ)

# HW2 EE538

## University of Southern California

## Instructor: Arash Saifhashemi

Please clone this repository, edit README.md to answer the questions, and fill up functions to finish the homework.

Important: Please use bazel with c++17:

```bash
bazel test --cxxopt="-std=c++17"  {test_target}
```

- Please find each question in a separate folder under [files](/files).
- Question 7 is optional and is not required for full credit.
- For non-coding questions, fill out the answers in the README file.
- For coding questions, edit the files and check them in.
- For coding questions unless specified, you should add unit tests to the student_test.cc. We will clone and test your repo using your tests and some other tests (that are not provided). Your code should pass all of them.
- For submission, please push your answers to Github before the deadline.
- Rubrics:
  
| Question | Points |
| -------- | ------ |
| 1        | 10     |
| 2        | 18     |
| 3        | 10     |
| 4        | 20     |
| 5        | 25     |
| 6        | 30     |

- 100 points is considered full credit.

See [cpp-template](https://github.com/ourarash/cpp-template) for help on installing bazel and debugging.

# Question

- Please refer to [files](/files).
- For each question, implement and test it in the [files](/files).
- Write the runtime complexity of each question in this README file.

# Write non-coding answers below

[TODO: Should be filled out with runtime complexity of each question with justification.]

Problem 1: The runtime is O(n log k), where n is the length of the string and k is the number of distinct characters. The loop processes each character once, and each "counts[c]++" operation on a "std::map" takes O(log k) time because "std::map" is implemented as a balanced binary search tree. Since the key type is "char", there are at most 256 possible distinct characters, so k is bounded by a constant. Therefore, O(n log k) simplifies to O(n).

Problem 2:
- Question 1: elements[i] is used before the vector has any elements. "elements" starts empty, so this line is invalid: "elements[i] = 0;". That tries to write to index 0, 1, etc in a vector that has size 0.
    - Runtime: O(n) because the loop runs n times and does one push_back each time.
- Question 2: The problem is "int* a; (a*) = 12;" because "a" does not point to a valid int, so dereferencing it causes a crash.
    - Runtime: O(1) because there is no loops, only fixed pointer operators.
- Question 3: This question didn't crash but there is a memory leak. This prints "3" correctly, but the memory allocated with "new" is never freed. There should always be a "delete" accompanying the "new".
    - Runtime: O(1) because of the fixed number of operations regardless of what the input is.
- Question 4: This code allocates memory for one int in "int* a = new int; int* b = new int;", but after "a++; b++;" the pointers no longer point to the allocated intergers. They point one int past the allocated memory. Then "(*a) = 1; (*b) = 2;" writes to memory that does not belong to it. Also not using "delete" after using "new" is not good practice.
    - Runtime: O(1) because the array's size is fixed at 2 and no loops.
- Question 5: The loop repeats forever. The decrement inside the loop cancels out the increment in the "for" statement, so "i" never makes progress toward 10. This creates an infinite loop.
    - Runtime: O(n) because it loops n times (n = 10) and each iteration is O(1), so total O(n).
- Question 6: The loop is inserting new elements into the same "std::set" that it is iterating over. New inserted elements are also visited by the iterator, causing the set to grow indefinitely and preventing the loop from finishing.
    - Runtime: O(n log n) because of the loop with "set::insert". This is iterating over "original", so n interations. Each "set::insert" is O(log n) because "std::set" is a balanced binary search tree, giving O(n log n) total.

Problem 3: The runtime complexity is O(1) for both functions because both are 3 fixed operations. The number of operations never changes regardless of the input.

Problem 4:
- UniqueVectorNotBySet: The runtime is O(n^2) because it uses a nested loop to compare every pair. Since no "std::set" is allowed, it manually checks for duplicates and erases them.
- UniqueVectorBySet: The runtime is O(n log n) because it uses a "std::set" to track seen values in O(log n) per lookup, building a result vector and assigning it back.
- IntersectVectors: The runtime is O(n log n) because it loads "input2" into a "std::set" for fast O(log n) lookup, then walks "input1" once adding elements found in both. A second "std::set" called "added" prevents duplicates in the result.
- DiffVectors: The runtime is O(n^2) because it calls "IntersectVectors" to find common elements, then walks "input1" and keeps only values not in that intersection.

Problem 5:
- push_back: The runtime is O(n) because it must copy all n existing elements into the new array every time.
- pop_back: The runtime is O(n) because it must copy all n-1 elements into the new array, even thought it's removing the last one. This is the cost of using a dynamic array with no extra capacity.
- insert: The runtime is O(n) because even if insert at index 0, all n elements must be shifted right.
- erase: The runtime is O(n) because even erase at index 0, all n-1 elements will be shifted left.
- find: The runtime is O(n) because even if the element is at the end or not present, it will scan all n elements.

Problem 6: 
- setDifference: The runtime is O(n log m) because the function loops through every element in "set1", which takes O(n) time. For each element, it searches "set2", and searching a "std::set" takes O(log m). Therefore, the overall runtime is O(n log m).
- areDisjoint: The runtime is O(log m) in the best case because the function checks each element of "set1" to see if it exists in "set2". Each lookup takes O(log m). In the worst case, no common elements are found, so all n elements must be checked, giving O(n log m). In the best case, the first element checked is found in "set2", so the function returns immediately in O(log m) time.

Problem 7:
- BuildFrames: The runtime is O(n*m) because n is the number of commands and m is the average size of the array during execution. The outer loop runs n times. Each iteration copies the full array into a Frame snapshot, which costs O(m) and dominates all other operation costs. Even push_back and pop_back, which are normally O(1), become O(m) because of the snapshot copy. In the worst case where only push_back is called, m grows from 0 to n, making the total cost O(n^2).

