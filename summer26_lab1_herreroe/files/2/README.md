# Question 2: Debug From Failing Tests

In Question 1 you generated a hash map from a precise spec. Real AI-generated
code is not always correct. This question gives you a **complete `VectorHashMap`
that looks right but has a planted bug.** At least one visible test fails.

Your job is to debug it the way a professional does: reproduce the failure, read
it carefully, localize the cause, and apply the *smallest* correct fix — without
rewriting working code.

Write your answers and observations in `NOTES.md`.

## Files

- `README.md`: this step-by-step lab guide
- `NOTES.md`: your debugging log
- `q.h`: the public API and exact behavior contract (unchanged from Question 1)
- `q.cc`: a complete implementation that contains a bug
- `student_test.cc`: visible tests, at least one of which fails

Do not change public function names or signatures in `q.h`.

## Step 1: Reproduce The Failure

Run the visible tests from the repo root:

```bash
bazel test --cxxopt="-std=c++17" --test_output=all //files/2:student_test
```

In `NOTES.md`, record:

- which test(s) failed
- the exact expected value and the actual value the test reported

Never start fixing before you can reproduce the failure and read its output.

## Step 2: Localize Before You Prompt

Do not paste the whole file at the AI and ask "fix it." First narrow the search.

Use the failing assertion to identify which operation is suspicious. For
example, if the failure happens after `Erase`, focus on what erase is supposed
to change.

Do a tiny state trace before editing code:

1. Read the few lines of `student_test.cc` around the failing expectation.
2. Write down the map state immediately before the suspicious operation:
   which keys should exist, and what should `Size()` be?
3. Write down the expected state immediately after that operation:
   which keys should exist, and what should `Size()` be?
4. Compare that expectation with the implementation in `q.cc`. `Contains`,
   `Get`, `Size`, and `BucketsForDebug()` are useful observability tools.

In `NOTES.md`, answer:

- Which single function is most likely responsible?
- What does the contract in `q.h` say that function should do?
- What does the code actually do instead?
- What map state did you expect before and after the suspicious operation?

## Step 3: Ask For The Smallest Fix

Fill in the blanks below with your actual failure, then paste into Codex:

```text
I am debugging a C++17 GoogleTest failure.

Failing test:

Expected behavior:

Actual behavior:

Relevant code from files/2/q.cc:

Please find the smallest correctness fix.
Do not refactor unrelated code.
Do not change the public API.
Honor the Allowed/Forbidden container lists in files/2/q.h.
Do not add automatic rehashing.
```

Inspect the suggested fix before accepting it. A good bug fix changes as little
as possible and you can explain exactly why it works.

## Step 4: Verify

Rerun the tests:

```bash
bazel test --cxxopt="-std=c++17" //files/2:student_test
```

In `NOTES.md`, record:

- the root cause in one sentence
- the exact change you made
- why the failing test now passes

## Step 5: Continue To Question 3

When the tests pass and you can explain the bug, continue to
[../3/README.md](../3/README.md), where you will review and refactor working
code.
