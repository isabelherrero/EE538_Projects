[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/m1l-iSid)

# HW1 EE538
## University of Southern California
## Instructor: Arash Saifhashemi

Please clone this repository, edit README.md to answer the questions, and fill up functions to finish the homework.

- Please find each question in a separate folder under [files](/files).
- For non-coding questions, fill out the answers in the README file.
- For coding questions, edit the files and check them in.
- For coding questions unless specified, you should add unit tests to the student_test.cc.
  We will clone and test your repo using your tests and some other tests (that are not provided). Your code should pass all of them.
- For submission, please push your answers to Github before the deadline.
- Deadline: June 9 by 12:00 pm (noon)
- Rubrics:
  
| Question | Points |
| -------- | ------ |
| 1        | 18     |
| 2        | 18     |
| 3        | 18     |
| 4        | 18     |
| 5        | 18     |
| 6        | 18     |
| 7        | 18     |

- Total: 126 points. 100 points is considered full credit.


See [cpp-template](https://github.com/ourarash/cpp-template) for help on installing bazel and debugging.

# Question
- Please refer to [files](/files).
- For each question, implement and test it in the [files](/files).
- Write the runtime complexity of each question in this README file.

# Answers
[TODO: Should be filled out with runtime complexity of each question with justification.]

1. Reverse: O(n) time, O(n) space.
   Justification: the function visits each element once and stores all elements in a new vector.

   PlusOne: O(n) time, O(n) space.
   Justification: in the worst case it scans the whole vector once from right to left, and the returned vector uses linear space.

2. IsPrime: O(sqrt(n)) time, O(1) space.
   Justification: it only checks divisibility up to sqrt(n), and it uses a constant amount of extra memory.

3. CountNumberOfSpaces: O(n) time, O(1) space.
   Justification: it scans the string once and counts spaces with one integer variable.

4. Flatten3DVector: O(n) time, O(n) space.
   Justification: it visits every integer exactly once, and the output vector stores all integers.
   Here, n means the total number of integers inside the 3D vector.

5. ClimbStairs: O(3^n) time, O(n) space.
   Justification: the recursive solution branches into up to 3 recursive calls at each step, and the maximum recursion depth is n.

6. Calculator: O(1) time, O(1) space.
   Justification: it performs a fixed number of arithmetic operations and uses only a few reference variables.

7. CanBecome: O(n) time, O(n) space.
   Justification: it builds a doubled string of size 2n and searches through it once; the extra space comes from the doubled string.
