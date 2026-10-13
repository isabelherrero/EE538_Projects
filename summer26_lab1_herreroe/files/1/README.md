# Question 1: Spec & Generate

In this question, you implement `VectorHashMap` in `q.cc` by writing a clear
spec and prompting an AI tool to generate the code.

The point is not just working code. The point is the first half of a
professional AI-assisted workflow:

1. read the API contract
2. visualize the behavior before coding
3. see why a vague prompt is risky
4. write a precise prompt from the contract
5. run the visible tests until they pass

Later questions take the generated code further: debugging it (Question 2),
reviewing and refactoring it (Question 3), and visualizing it (Question 4).

Write your answers and observations in `NOTES.md`.

## Files

- `README.md`: this step-by-step lab guide
- `NOTES.md`: your worksheet and prompt log
- `q.h`: the public API and exact behavior contract
- `q.cc`: the implementation you will complete
- `student_test.cc`: visible tests you can run and improve

Do not change public function names or signatures in `q.h`.

## Visualize Before You Implement

Keep up the habit from the warm-up: see the behavior before you build it. You
already created a hash map visualizer with an AI tool. Before you ask AI to
write any C++ here, step through that visualizer for the exact behaviors this
question requires:

- inserting a new key
- overwriting an existing key (size must not change)
- inserting two keys that land in the same bucket (a collision)
- erasing a key from the middle of a collision bucket
- rehashing, and rehashing down to one bucket

If your visualizer does not cover one of these, ask your AI tool to add it.
Watching each operation first makes the contract in `q.h` concrete and makes the
generated code much easier to review later.

## Step 0: Read The API First

Open `q.h`.

Do not ask Codex to code yet.

If the hash-map terms below are unfamiliar (bucket, collision, separate
chaining, load factor, rehash), read the **How A Hash Map Works** section in the
top-level [README.md](../../README.md) first.

`q.h` is the contract. Make sure you understand:

- what `Insert` returns for a new key
- what `Insert` returns when overwriting an existing key
- what `Get` does when a key is missing
- what `Erase` does when a key is missing
- what `VectorHashMap(0)` does
- what `Rehash(0)` does
- the **Allowed** and **Forbidden** container lists in the header comment

The Allowed/Forbidden lists in `q.h` are the only place those rules are defined.
"Container" here means a C++ Standard Library data structure such as
`std::vector`, `std::list`, `std::map`, or `std::unordered_map`.

Write your Step 0 answers in `NOTES.md`.

Done when:

- you can explain what a bucket is and what a collision is
- you can explain what `size_` should count
- you can name the allowed and forbidden containers from `q.h`
- you know which files Codex may edit

## Step 1: Try A Bad Prompt

Copy this exact prompt into Codex:

```text
Create a standalone hash map implementation in C++ in files/1/bad_prompt_attempt.cc.
```

Do not use the result yet.

In `NOTES.md`, answer:

- Did Codex follow the API in `q.h`?
- Did Codex use forbidden STL containers?
- Did Codex explain collision handling?
- Did Codex create code that could replace `q.cc` without further changes?
- What important details were missing from the prompt?

The point of this step is to see why vague prompts are risky. The scratch file
makes the result observable as a diff without giving Codex the real target
implementation file. The prompt is still bad because it does not mention
`VectorHashMap`, `q.h`, the API contract, allowed containers, exact behavior, or
tests.

After recording your observations, delete `files/1/bad_prompt_attempt.cc`.

## Step 2: Use A Professional Prompt

Copy this exact prompt into Codex:

```text
Implement files/1/q.cc for the VectorHashMap API in files/1/q.h.

Follow the contract in files/1/q.h exactly.

Rules:
- Use C++17.
- Keep the public API unchanged.
- You may edit files/1/q.cc.
- You may edit files/1/student_test.cc only to add or improve tests.
- Do not edit files/1/q.h.
- Store entries using vector buckets:
  std::vector<std::vector<std::pair<std::string, int>>>
- Use only the containers in the Allowed list in files/1/q.h. Do not use any
  container in the Forbidden list.
- Do not add automatic rehashing.

Required behavior:
- VectorHashMap(0) creates one bucket.
- Insert returns true when inserting a new key.
- Insert returns false when overwriting an existing key.
- Overwriting a key updates the value but does not change Size().
- Contains returns whether the key exists.
- Get returns the value for an existing key.
- Get throws std::out_of_range for a missing key.
- Erase returns true when it removes an existing key.
- Erase returns false for a missing key.
- Size returns the number of stored key/value pairs.
- Empty returns whether Size() is 0.
- LoadFactor returns Size() divided by the number of buckets.
- Rehash(new_bucket_count) preserves all key/value pairs.
- Rehash(0) rebuilds the map with one bucket.
- BucketsForDebug returns a copy of the current bucket structure.

Also add or improve GoogleTest tests in files/1/student_test.cc for:
- empty map
- insert and get
- overwrite existing key
- missing Get throws
- erase existing key
- erase missing key
- rehash preserves entries
- VectorHashMap(0) or Rehash(0)

After making changes, summarize what you changed and tell me what test command
to run.
```

Before accepting the result, inspect it.

In `NOTES.md`, answer:

- Did Codex keep the API unchanged?
- Did Codex use only allowed STL containers?
- Did Codex add automatic rehashing?
- Which parts of the code do you not understand yet?

## Step 3: Run The Visible Tests

Run this command from the repo root:

```bash
bazel test --cxxopt="-std=c++17" //files/1:student_test
```

If the tests pass, you are done with this question.

If the tests fail, do not jump straight to fixing code. Refine your prompt:
state the exact behavior the failing test expects and ask Codex to regenerate.
The disciplined way to debug a failing test from existing code is the whole
subject of Question 2.

## Step 4: Continue To Question 2

When the visible tests pass and you can explain the code Codex produced,
continue to [../2/README.md](../2/README.md), where you will debug a planted
bug in a similar hash map.
