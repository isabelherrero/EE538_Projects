# Question 2 Notes: Debug From Failing Tests

Use this file as your debugging log.

## Step 1: Reproduce The Failure

Command:

```bash
bazel test --cxxopt="-std=c++17" --test_output=all //files/2:student_test
```

- Which test(s) failed?
    - VectorHashMapStudentTest.ErasesExistingAndMissingKeys
- Expected value: 
     - map.Size() == 1 after map.Erase("a") succeeds (one entry, "a", removed from a two-entry map).
- Actual value:
    - map.Size() == 2.

## Step 2: Localize

- Which function is most likely responsible?
    - VectorHashMap::Erase
- What does `q.h` say that function should do?
    - If key is present: remove the key/value pair, decrease Size() by 1, return true.
- What does the code actually do instead?
    - It correctly finds the entry and removes it from the bucket's vector, but never decrements size_, so the entry disappears from Contains/Get/BucketsForDebug while Size() and LoadFactor() silently drift out.
- What map state did you expect before the suspicious operation?
    - two entries, {"a": 1, "b": 2}, Size() == 2.
- What map state did you expect after the suspicious operation?
    - Erase("a"): one entry, {"b": 2}, Size() == 1, Contains("a") == false.

## Step 3: The Fix

Prompt used:

```text
I am debugging a C++17 GoogleTest failure.

Failing test: VectorHashMapStudentTest.ErasesExistingAndMissingKeys

Expected behavior: After erasing an existing key, Size() should decrease by 1,
per the contract in q.h ("decrease Size() by 1").

Actual behavior: Erase() correctly removes the entry from its bucket vector
and Contains() correctly returns false afterward, but Size() stays unchanged,
so EXPECT_EQ(map.Size(), 1) fails and still reports 2.

Relevant code from files/2/q.cc:

bool VectorHashMap::Erase(const std::string& key) {
  auto& bucket = buckets_[BucketIndex(key)];
  for (auto it = bucket.begin(); it != bucket.end(); ++it) {
    if (it->first == key) {
      bucket.erase(it);
      return true;
    }
  }
  return false;
}

Please find the smallest correctness fix.
Do not refactor unrelated code.
Do not change the public API.
Honor the Allowed/Forbidden container lists in files/2/q.h.
Do not add automatic rehashing.
```

- What fix did Codex suggest?
    - add --size_; immediately after bucket.erase(it);, before return true;.
- How small was the change?
    - one line added, zero lines removed elsewhere

## Step 4: Verify

- Root cause in one sentence:
    - Erase removed the entry from its bucket but forgot to decrement size_, so Size()/LoadFactor() never reflected the removal even though Contains/Get did.
- Exact change you made:
     - added --size_; in VectorHasMap::Erase
- Why the failing test now passes:
    - after Erase("a"), bucket.erase(it) removes the pair as before, and --size_ brings size_ from 2 down to 1, so EXPECT_EQ(map.Size(), 1) matches, and the subsequent EXPECT_FALSE(map.Erase("a")) / EXPECT_EQ(map.Get("b"), 2) checks were already passing and remain unaffected.
