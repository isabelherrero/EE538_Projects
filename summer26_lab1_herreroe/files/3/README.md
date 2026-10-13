# Question 3: Review & Refactor

Code that passes its tests is not automatically good code. This question gives
you a `VectorHashMap` that is **correct and passes every visible test, but is
written poorly** — repeated logic, awkward names, and an unused helper.

Your job is to review it like a professional, then refactor it to high quality
**without changing its behavior**, using the tests as your safety net. Finally,
you add one test of your own to lock the behavior down.

Write your answers and observations in `NOTES.md`.

## Files

- `README.md`: this step-by-step lab guide
- `NOTES.md`: your review and refactor log
- `q.h`: the public API and exact behavior contract (unchanged)
- `q.cc`: a correct but messy implementation
- `student_test.cc`: visible tests (all passing)

Do not change public function names or signatures in `q.h`.

## Step 1: Establish A Green Baseline

Before changing anything, confirm the code passes:

```bash
bazel test --cxxopt="-std=c++17" //files/3:student_test
```

These passing tests are your safety net. After every refactor you will rerun
them to prove you did not change behavior.

## Step 2: Review The Code With Lanes

Use the local review skill. Copy this exact prompt into Codex:

```text
Use the instructions in .codex/skills/cpp-review-lanes/SKILL.md to review
files/3/q.cc and files/3/student_test.cc.

Check correctness first. Then check API contract, readability, complexity,
tests, safety, and maintainability.

Do not rewrite the code yet.
Do not suggest public API changes.
Do not suggest containers in the Forbidden list in files/3/q.h.
Do not suggest automatic rehashing unless you clearly mark it as an extension
outside this lab's scope.
```

In `NOTES.md`, record:

- the most important readability or maintainability issue
- the duplicated logic you noticed across the functions
- the unused helper declared in `q.h`
- one suggestion you accepted and one you rejected

## Step 3: Ask For A Senior C++ Refactor

Copy this exact prompt into Codex:

```text
Use the instructions in .codex/skills/senior-cpp-developer/SKILL.md to refactor
files/3/q.cc.

Preserve the public API in files/3/q.h.
Preserve behavior.
Do not add automatic rehashing.
Honor the Allowed/Forbidden container lists in files/3/q.h.

Prioritize correctness, clear invariants, readable helper functions,
const-correctness, and simple control flow. Use the BucketIndex helper instead
of recomputing the hash in every function. Keep comments short and only where
they clarify a non-obvious choice.
```

Inspect the result before accepting it.

## Step 4: Prove Behavior Is Unchanged

Rerun the tests:

```bash
bazel test --cxxopt="-std=c++17" //files/3:student_test
```

In `NOTES.md`, answer:

- Was the refactored version easier to understand?
- What changed?
- Did any behavior change? (The tests should still pass.)

## Step 5: Lock It Down With A Test (TDD)

A refactor is only safe if tests catch regressions. Add one edge-case test that
the current suite is missing, so future changes cannot silently break it.

Copy this exact prompt into Codex:

```text
Use the instructions in .codex/skills/tdd-cpp-gtest/SKILL.md.

Look at files/3/student_test.cc and add one missing edge-case test for
VectorHashMap. Prefer a test involving collisions, erase from the middle of a
collision bucket, or rehash down to one bucket.

Add the test first and run it. If your refactored code is correct it should
pass. If it does not, make the smallest fix. Keep the public API unchanged.
```

Run the tests again:

```bash
bazel test --cxxopt="-std=c++17" //files/3:student_test
```

Record the new test and result in `NOTES.md`.

## Step 6: Continue To Question 4

When the tests pass and the code reads cleanly, continue to
[../4/README.md](../4/README.md), where you build a visualization of the hash
map in C++.
