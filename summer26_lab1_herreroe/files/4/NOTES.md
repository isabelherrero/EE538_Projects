# Question 4 Notes

Use this file for visualization notes and the final reflection.

## Step 0: Read The Frame API

- What is `HashMapEntry`?
    - one stored key/value pair
- What is `HashMapFrame`?
    - one snapshot in time
- What is `HashCommand`?
     - one instruction to replay
- Which command strings are supported?
    - Supported command strings: "insert", "erase", "rehash".
- What labels must match exactly?
    - Labels must match exactly: "start", insert("<key>", <value>), insert("<key>", <value>) [overwrite], erase("<key>"), erase("<key>") [missing], rehash(<bucket_count>), rehash(0) [invalid].
- What should happen for `rehash(0)`?
    - rehash(0) is invalid because 0 buckets would make hash % bucket_count divide by zero.

## Step 2: Codex Result

- Did Codex keep `q.h` unchanged?
    - Yes
- Did Codex match the label strings exactly?
    - Yes
- Did Codex handle invalid `rehash(0)`?
    - Yes
- Did Codex ignore unknown commands without emitting frames?
    - Yes

## Step 3: Test Results

Command:

```bash
bazel test --cxxopt="-std=c++17" //files/4:student_test
```

- Result:
    - All tests passed
- If failed, which test failed?
- What fix did you apply?

## Step 4: Visualization Notes

Command:

```bash
bazel run --cxxopt="-std=c++17" //files/4:viz
```

- Did the visualizer run?
    - Yes
- Could you step through inserts?
    - Yes
- Could you step through overwrites?
    - Yes
- Could you step through erases?
    - Yes
- Could you step through rehashes?
    - Yes
- Which operation was easiest to visualize?
    - Insert
- Which operation was easiest to get wrong?
    - Rehash

## Step 5: Final Reflection

- Which prompt produced the best code?
    - The detailed prompt that spelled out the exact label strings and edge cases.
- What information made that prompt better?
    - Giving the exact label format and naming the edge cases up front, so there was nothing left to guess at.
- Which Codex suggestion did you reject?
- Which test caught the most important issue?
    - The invalid-rehash test
- How did the senior-developer version differ from the baseline?
    - Cleaner separation of concerns
- Did TDD change your design?
    - Yes
- What did you learn about giving AI precise constraints?
    - Exact strings and edge cases have to be spelled out
- What would you do differently in a larger codebase?
    - Break the frame building logic into smaller, independently testable functions.
