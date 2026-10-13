[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/nPoEoba1)

# HW3 EE538

University of Southern California

Instructor: Arash Saifhashemi

Please clone this repository, edit README.md to answer the questions, and fill up functions to finish the homework.

## Important

- Use address sanitizer!
- Every time that you use a dereferencing operator (* or ->) make sure your pointer is valid!

Also note that:

- Please find each question in a separate folder under [files](/files).
- For non-coding questions, fill out the answers in the README file.
- For coding questions, edit the files and check them in.
- For coding questions unless specified, you should add unit tests to the student_test.cc. We will clone and test your repo using your tests and some other tests (that are not provided). Your code should pass all of them.
- For submission, please push your answers to Github before the deadline.
- Rubrics:
  
| Question | Points |
| -------- | ------ |
| 1        | 32     |
| 2        | 15     |
| 3        | 15     |
| 4        | 25     |
| 5        | 25     |

- 100 points is considered full credit.
- See [cpp-template](https://github.com/ourarash/cpp-template) for help on installing bazel and debugging.

- Problem 1:
    - Q1: Non-parameterized constructor
          o1.v_.size(): 0
          Destructor
          - o1 uses the default constructor (a_= b_= 0, ptr_ = new int), which never touches v_, so it stays empty. The destructor fires at the end of the block.
    - Q2: Non-parameterized constructor
          Parameterized constructor
          Copy constructor
          Destructor
          Destructor
          Destructor
          - o1 (default), o2 (parameterized (1,3)), o3 = o1 (copy constructor = here is copy initialization, not assignment, since o3 is being created). Destructors run in reverse declaration order: o3, o2, o1.
    - Q3: Non-parameterized constructor
          Copy constructor
          Something 1.
          Destructor
          Destructor
          - DoSomething1(MyClass o) takes its parameter by value, so calling it copy constructs a temporary parameter from o. That parameter is destroyed when the function returns, o itself is destroyed at the end of the outer block.
    - Q4: Non-parameterized constructor
          Something 2.
          Destructor
          - DoSomething2(MyClass &o) takes a reference, so no copy is made so no extra copy constructor/destructor pair compared to Q3. This is why Q3 and Q4 are different, pass-by-value versus pass-by-reference.
    - Q5: Non-parameterized constructor
          Something 3.
          Destructor
          - Same as Q4, DoSomething3 is also pass-by-reference.
    - Q6: Non-parameterized constructor
          Copy constructor
          Something 4.
          Destructor
          Destructor
          - DoSomething4 takes a reference, but inside it does MyClass o2 = o, which invokes the copy constructor. o2 is destroyed when the function returns and o is destroyed at the end of the outer block.
    - Q7: Parameterized constructor
          Copy constructor
          Destructor
          p1.first.v_.size(): 0
          p1.second: 0
          Copy constructor
          p2.first.v_.size(): 0
          p2.second: 0
          Destructor
          Destructor
          - MyClass(1, 2) creates a temporary. Building p1 from {temp, 0} copy constructs p1.first from that temporary. MyClass has no move constructor, so any move attempt falls back to the copy constructor. The temporary is destroyed at the end of that expression. Also v_.size() is 0: MyClass(1,2) matches the (int a, int b) overload, so v_ is never populated. p2 = p1 then copy constructs p2.first from p1.first. At end, p2 is destroyed before p1.
    - Q8: Parameterized constructor
          Copy constructor
          Destructor
          Something 2.
          Something 2.
          Something 2.
          Destructor
          - The for loop's statement runs once, not once per iteration. p is a single object that persists across all iterations. So the pair/temporary (ctor -> copy ctor -> destructor) happens once up front. Then the loop body runs 3 times (p.second goes 0->1->2, exits when it hits 3). DoSomething2 is pass-by-reference so no copies happen inside the loop. p is destroyed once, at the end of the block.
    - Q9: Parameterized constructor
          - No destructor is printed. o is a raw pointer allocated with new and never deleted. The object (and the int its ptr_ points to) is leaked. The memory is never reclaimed and the destructor never runs.
    - Q10: Parameterized constructor
           Destructor
           - Same setup as Q9, but delete o. Invokes the destructor and frees the memory so no leak.
    - Q11: Non-parameterized constructor
           Copy constructor
           Parameterized constructor
           Copy constructor
           Parameterized constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Copy constructor
           Destructor
           Copy constructor
           Destructor
           Copy constructor
           Destructor
           Destructor
           Destructor
           Destructor
           - Builds my_map from a list of {key, MyClass} pairs involves two layers of copying:
            - Each MyClass()/MyClass(1,2)/MyClass(3,4) temporary is constructed, then copied into the underlying std::initializer_list's pair<const int, MyClass> array (a move is requested but falls back to copy since there's no move constructor).
            - std::map's constructor then copies each element again from the initializer list into its own tree nodes, because initializer_list elements are always const and therefore can never be moved from, only copied. That is a second copy ctor per element.
            - Once the whole statement finishes, the initializer_list's temporary array is destroyed. Then the range for (auto e : my_map) copies each map entry by value into e every iteration (3 more copy ctor + destructor pairs), and finally my_map's own 3 stored MyClasses are destroyed when the block ends.
    - Q12: Non-parameterized constructor
           Copy constructor
           Parameterized constructor
           Copy constructor
           Parameterized constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           - Map construction is identical to Q11 for the same reasons: 3 base constructors + 6 copy constructors (one copy into the initializer_list's array per element, then a second copy from the initializer_list into the map's tree nodes, since initializer_list elements are always const and can only be copied, never moved). Those 6 copies are cleaned up via 6 destructors once the construction statement finishes. The loop itself, for (const auto &e : my_map), binds e as a reference, so it adds zero extra copies or destructors. But my_map still owns 3 MyClass objects that get destroyed when the block ends giving 9 destructors total (6 from construction phase temporaries + 3 from the map's), matching the 9 in the output above.
    - Q13: Parameterized constructor
           Destructor
           - It is the same code as Q10 so same explanation.
    - Q14: Parameterized constructor
           Operation took: 14429 milliseconds
           Copy constructor
           Copy constructor
           Something 1.
           Destructor
           o2.v_.size(): 100000000
           Destructor
           Copy constructor
           Copy constructor
           Something 1.
           Destructor
           o2.v_.size(): 100000000
           Destructor
           Operation took: 18377 milliseconds
           Destructor
           - MyClass o(100000000) builds a 100 million element vector one push_back at a time (no reserve), so T1 reflects the cost of that (reallocation/copying of a growing int vector). Inside the loop, MyClass o2 = o; copy constructs a fresh 100 million int vector which is high cost because of the amount of allocation and copies. Then DoSomething1(o2) copy constructs it again for the function parameter using pass-by-value. So each of the 2 iterations does two full 100 million element vector copies, meaning T2 is dominated by 4 large copies total.
    - Q15: Parameterized constructor
           Operation took: 2487 milliseconds
           Copy constructor
           Something 2.
           o2.v_.size(): 100000000
           Destructor
           Copy constructor
           Something 2.
           o2.v_.size(): 100000000
           Destructor
           Operation took: 1069 milliseconds
           Destructor
           - Same setup, but DoSomething2 takes a reference, so only one big vector copy happens per iteration (o2 = o), not two. Q14's second measurement was 18377 ms and Q15's was 1069 ms, which is bigger than twice the amount. Since Q14 only does twice as much copying as Q15 (two big-vector copies per iteration versus one), the raw copy-count alone would only predict roughly twice a gap. 
    - Q16: Parameterized constructor
           Parameterized constructor
           Parameterized constructor
           Parameterized constructor
           Parameterized constructor
           Parameterized constructor
           Parameterized constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Copy constructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Operation took: 33266 milliseconds
           Copy constructor
           e.v_.size(): 10000000
           Destructor
           Copy constructor
           e.v_.size(): 20000000
           Destructor
           Copy constructor
           e.v_.size(): 30000000
           Destructor
           Copy constructor
           e.v_.size(): 40000000
           Destructor
           Copy constructor
           e.v_.size(): 50000000
           Destructor
           Copy constructor
           e.v_.size(): 60000000
           Destructor
           Copy constructor
           e.v_.size(): 70000000
           Destructor
           Operation took: 2300 milliseconds
           e.v_.size(): 10000000
           e.v_.size(): 20000000
           e.v_.size(): 30000000
           e.v_.size(): 40000000
           e.v_.size(): 50000000
           e.v_.size(): 60000000
           e.v_.size(): 70000000
           Operation took: 2 milliseconds
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           Destructor
           - Building my_vector from an initializer list works like Q11's map case: each MyClass(size) temporary is built (its own push_back loop) then copied into the vector's storage (copy constructor, initializer_list elements are const so must be copied, not moved). Because the vector is constructed directly from an initializer_list of known length, it can size its buffer once, so there's no additional reallocation copy beyond that one copy per element. T1 reflects building plus copying roughly 280 million ints total. The first loop, for (auto e : my_vector), copies each MyClass by value. For the largest elements this means copying tens of millions of ints just to print a .size(). T2 will be large and dominated by these copies. The second loop, for (const auto &e : my_vector), binds by reference, zero copies, just pointer/reference access. T3 should be dramatically smaller than T2 which is the point of the comparison, iterating by reference avoids needless deep copies of large objects.