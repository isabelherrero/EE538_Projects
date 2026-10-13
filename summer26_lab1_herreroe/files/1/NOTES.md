# Question 1 Notes: Spec & Generate

Use this file as your worksheet and prompt log.

## Visualize Before You Implement

- Which operations did you step through in your visualizer?
- Which behavior was clearest once you saw it animated?

## Step 0: Read The API

- What is an STL container?
    - An STL container is a C++ built-in data structure template from the standard template library.
- What is a bucket?
    - A bucket is one slot in the hash map's outer array. It holds every key/value pair whose key hashes to that slot's index.
- What is a collision?
     - A collision is when two different keys hash to the same bucket index, so both entries end up living in the same bucket's vector.
- What does `size_` count?
    - Counts the number of key/value pairs currently stored across all buckets.
- Which files may Codex edit?
    - Codex may edit files/1/q.cc and files/1/student_test.cc only to add or improve tests.
- Which files should Codex not edit?
    - Codex should not edit files/1/q.h.
- Which STL containers are allowed?
    - Allowed containers: std::vector, std::pair, std::string, std::hash<std::string>.
- Which STL containers are forbidden?
    - Forbidden containers: std::map, std::unordered_map, std::list.

## Step 1: Bad Prompt Results

Prompt used:

```text
Create a standalone hash map implementation in C++ in files/1/bad_prompt_attempt.cc.
```

- Did Codex follow `q.h`?
    - It will not follow q.h, since it was never shown that file or told VectorHashMap exists.
- Did Codex use forbidden STL containers?
    - Yes, it used std::unordered_map.
- Could the generated code replace `q.cc` without further changes?
    - The generated code could not replace q.cc without significant rewriting: wrong class name, wrong method signatures, no BucketsForDebug, no LoadFactor matching the exact formula.
- What important details were missing?
    - Missing details: the exact API surface (Insert/Contains/Get/Erase/Size/Empty/LoadFactor/Rehash/BucketsForDebug), the allowed/forbidden container list, the vectors storage requirement, the exact return value semantics for Insert/Erase, the out_of_range requirement, the zero-bucket edge cases, and the test file to satisfy.

## Step 2: Professional Prompt Results

- Did Codex keep the API unchanged?
    - Yes
- Did Codex use only allowed STL containers?
    - Yes
- Did Codex add automatic rehashing?
    - No
- Which parts of the code do you not understand yet?
    - Why Rehash must recompute std::hash<std::string>{}(key) % new_bucket_count per entry rather than just copying old bucket vectors into new slots at the same index.

## Step 3: Test Results

Command:

```bash
bazel test --cxxopt="-std=c++17" //files/1:student_test
```

- Result: All passed
- If a test failed, how did you refine your prompt?
