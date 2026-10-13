# Question 4: Visualize The Hash Map

**This question is only about visualization.** You are not building a new hash
map data structure from scratch. Instead, you implement one function,
`BuildHashMapFrames` in `q.cc`, that replays a list of operations and records a
**snapshot ("frame") of the bucket contents after each one**. The provided
`viz.cc` reads those frames and plays them back in the terminal, like a flip
book, so you can watch inserts, overwrites, erases, and rehashes change the
buckets step by step.

So the work here is:

- run each command on a simple vector-bucket hash map (same idea as Question 1),
- after each command, copy the current bucket state into a `HashMapFrame`,
- label each frame with the exact text the contract requires.

What matters here is not a clever hash map. It is producing the correct sequence
of labeled frames.

This is the same "see it to learn it" habit from the warm-up and Question 1,
turned around: instead of asking AI to visualize a concept for you, you now build
the visualization yourself, in C++.

Write your answers and observations in `NOTES.md`.

## Files

- `README.md`: this step-by-step lab guide
- `NOTES.md`: your visualization notes and final reflection
- `q.h`: structs and exact frame-building contract
- `q.cc`: the implementation you will complete
- `student_test.cc`: visible tests
- `viz.cc`: provided terminal visualization frontend

Do not change public structs or function signatures in `q.h`.

## Step 0: Read The Frame API

Open `q.h`. It is the single source of truth for this question's structs,
function signature, and exact label strings. For the underlying hash-map
concepts (buckets, collisions, rehash), see **How A Hash Map Works** in the
top-level [README.md](../../README.md).

Do not ask Codex to code yet.

Make sure you understand:

- what `HashMapEntry` represents
- what `HashMapFrame` represents
- what `HashCommand` represents
- which command strings are supported
- what label strings must look like
- why `rehash(0)` is invalid in this visualization question

Write your Step 0 answers in `NOTES.md`.

## Step 1: Understand The Output

`BuildHashMapFrames(...)` returns snapshots of a hash map over time.

The first frame is always:

```text
label: "start"
size: 0
buckets: initial empty bucket array
```

Each later frame shows the bucket state after an operation.

Example:

```text
Frame 0: start
bucket 0: []
bucket 1: []
bucket 2: []
bucket 3: []

Frame 1: insert("alpha", 1)
bucket 0: []
bucket 1: [("alpha", 1)]
bucket 2: []
bucket 3: []
```

The exact bucket index depends on `std::hash<std::string>`, so your output may
place keys in different buckets from this diagram.

## Step 2: Prompt Codex

Copy this exact prompt into Codex:

```text
Implement files/4/q.cc using the contract in files/4/q.h.

Rules:
- Use C++17.
- Keep the public structs and function signature in files/4/q.h unchanged.
- Do not edit files/4/q.h.
- Do not edit files/4/viz.cc.
- Use vector buckets.
- Return a "start" frame first.
- Treat initial_bucket_count == 0 as one bucket.
- Emit one frame after each insert, erase, valid rehash, and invalid rehash(0).
- Match label strings exactly.
- Treat rehash(0) as invalid and leave buckets unchanged.
- Ignore unknown command strings without emitting frames.

Required labels:
- start
- insert("<key>", <value>)
- insert("<key>", <value>) [overwrite]
- erase("<key>")
- erase("<key>") [missing]
- rehash(<bucket_count>)
- rehash(0) [invalid]

After making changes, summarize what you changed and tell me what test command
to run.
```

Before accepting the result, inspect it.

In `NOTES.md`, answer:

- Did Codex keep `q.h` unchanged?
- Did it match the label strings exactly?
- Did it handle invalid `rehash(0)`?
- Did it ignore unknown commands without emitting frames?

## Step 3: Run The Visible Tests

Run this command from the repo root:

```bash
bazel test --cxxopt="-std=c++17" //files/4:student_test
```

If tests fail, use the debugging prompt from Question 2 with the failing test
and the relevant code from `files/4/q.cc`.

## Step 4: Run The Visualization

After tests pass, run:

```bash
bazel run --cxxopt="-std=c++17" //files/4:viz
```

The visualizer has something to step through only after `BuildHashMapFrames`
returns the required frames. If `q.cc` still has the starter `return {};`, the
visualizer can open, but left and right arrows will have no frames to move
through.

The demo operations are defined in `viz.cc` in the `DemoScript()` function. The
provided script is:

```text
insert("alpha", 1)
insert("beta", 2)
insert("gamma", 3)
insert("alpha", 9)    [overwrite]
erase("beta")
erase("missing")      [missing]
rehash(8)
insert("delta", 4)
rehash(0)             [invalid]
```

Each frame shows both the current operation that produced the displayed state
and the next operation that will run if you press the right arrow.

Use left and right arrow keys to move through the frames. Press `q` to quit.

In `NOTES.md`, answer:

- Can you step through inserts?
- Can you step through overwrites?
- Can you step through erases?
- Can you step through rehashes?
- Which operation was easiest to visualize?
- Which operation was easiest to get wrong?

## Step 5: Final Reflection

Answer the final reflection questions in `NOTES.md`.
