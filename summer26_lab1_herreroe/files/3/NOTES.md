# Question 3 Notes: Review & Refactor

Use this file as your review and refactor log.

## Step 1: Green Baseline

Command:

```bash
bazel test --cxxopt="-std=c++17" //files/3:student_test
```

- Result before any changes:
    - all 7 tests pass.

## Step 2: Review Lanes

- Most important readability or maintainability issue:
    - every public method (Insert, Contains, Get, Erase) manually recomputes std::hash<std::string>{}(key) % buckets_.size() inline instead of calling the existing BucketIndex(key) helper. If the hashing/indexing strategy ever changes, there are four places to update instead of one.
- Duplicated logic you noticed across functions:
    - the index-lookup-and-scan pattern (hash % size, then a manual index-based for loop comparing .first == key) is repeated in Insert, Contains, Get, and Erase.
- The unused helper declared in `q.h`:
    - BucketIndex
- One suggestion you accepted:
    - oute every method through BucketIndex(key) instead of recomputing the hash inline.
- One suggestion you rejected:
    - a suggestion to make Rehash call Insert(...) in a loop to redistribute entries (reusing existing logic instead of writing new redistribution code). I rejected it because Insert also does a "does this key already exist?" scan, which is wasted work and slightly misleading during a rehash.

## Step 3 & 4: Refactor

- Was the refactored version easier to understand?
    - Yes
- What changed?
    - Insert, Contains, Get, Erase all now call BucketIndex(key) once at the top instead of recomputing the hash inline.
    - Manual for (std::size_t i = 0; i < bucket.size(); i++) loops replaced with range-based for (const auto& entry : bucket) (or iterator-based where erasure needs the iterator).
    - Empty()'s if/else replaced with return size_ == 0;.
- Did any behavior change?
    - No
- Test result after refactor:
    - all 7 tests passed

## Step 5: TDD Lock-Down

- New test added:
    - ErasingMiddleOfCollisionBucketPreservesOthers
- Why this test matters:
    - none of the existing tests erase from a bucket that has more than two entries, so an off-by-one in an iterator/index-based erase could pass every existing test while still being broken.
- Did the refactored code pass it immediately, or did you need a fix?
    - Passed immediately
- Final test result:
    - All tests passed
