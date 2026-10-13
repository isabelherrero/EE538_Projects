[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/IsYjjfDl)
# EE538 Agentic C++ Lab 1

## University of Southern California

## Instructor: Arash Saifhashemi

This is a lab for learning how to use Codex like a professional C++ programmer.

You will work on a small **hash map** across four short questions, but the real
subject is the *workflow*: how to write a clear spec, prompt an AI coding tool
well, and then debug, review, and refactor what it produces into code you would
be willing to sign your name to. Each question isolates one part of that
workflow:

1. **Spec & Generate** — turn a contract into a precise prompt and generate the
   code.
2. **Debug From Failing Tests** — find and fix a planted bug methodically.
3. **Review & Refactor** — improve correct-but-messy code without changing
   behavior, then lock it down with a test.
4. **Visualize** — build a terminal visualization of the hash map in C++.

## How A Hash Map Works

A hash map stores key/value pairs and looks them up in roughly constant time on
average. In this lab the keys are strings and the values are integers.

The core ideas, which every question assumes you understand:

- **Bucket.** The map keeps an array of slots called buckets. Each bucket can
  hold zero or more entries.
- **Hash function.** To decide where a key goes, the map computes
  `hash(key) % number_of_buckets`. That index is the key's bucket.
- **Collision.** Two different keys can hash to the same bucket index. That is a
  collision, and it is normal.
- **Separate chaining.** When keys collide, the bucket holds all of them. In
  this lab each bucket is a `std::vector` of `(key, value)` pairs, so a lookup
  scans that one short vector. (Many textbooks use a linked list here; this lab
  deliberately uses a vector instead.)
- **Load factor.** This is `size / number_of_buckets`: the average number of
  entries per bucket. A higher load factor means longer scans per lookup.
- **Rehash.** Growing or shrinking the bucket array and redistributing every
  entry into its new bucket. In this lab rehashing happens *only* when you call
  `Rehash(...)` explicitly — never automatically.

A tiny picture of 4 buckets holding `("alpha", 1)` and `("beta", 2)`, where both
keys happened to hash to bucket 1:

```text
bucket 0: []
bucket 1: [("alpha", 1), ("beta", 2)]   <- a collision, chained in one vector
bucket 2: []
bucket 3: []
```

## Warm-Up: Build A Hash Map Visualizer With AI

Before you write any C++, use an AI coding tool (Codex, Claude, or Gemini) to
build an interactive visualization that *teaches* how a hash map works. This is
your first AI-assisted coding exercise, and it forces you to put the concepts
above into a precise spec. The mental model you build here is the same one you
will rely on throughout the four questions.

**Make this your default habit, in this lab and beyond: when you meet a new data
structure or algorithm, ask an AI tool to visualize it first, learn from the
visualization, and only then implement it.** Seeing an operation before you code
it makes the contract concrete and the resulting code far easier to review.

1. Paste this prompt into your AI tool:

   ```text
   Create a single self-contained HTML file (inline CSS and JavaScript, no
   build step) that visually teaches how a hash map with separate chaining
   works.

   Requirements:
   - Show an array of buckets. Each bucket is a vector of (key, value) entries.
   - Support insert, lookup, update, delete, and rehash (grow and shrink).
   - For every operation, show the hash computation: hash(key) % numBuckets =
     bucketIndex.
   - Animate the bucket scan so collisions are obvious, and label buckets that
     hold more than one entry as collisions.
   - Display live stats: size, bucket count, and load factor (size / buckets).
   - Include a guided walkthrough of buttons that, clicked in order,
     demonstrate an insert, a collision, an update, a lookup, a rehash, and a
     delete.
   - Keep keys as strings and values as integers.

   Explain your design briefly, then give me the full HTML file.
   ```

2. Save the result as an `.html` file and open it in a browser. Click through
   the operations and watch the buckets, collisions, and load factor change.

3. Iterate. If something is unclear or wrong, refine your prompt or ask for a
   specific fix. Notice how a more precise request produces a better tool.

4. Compare your version with the reference at
   [files/hash-map-visualization.html](files/hash-map-visualization.html). Open
   it in a browser and step through the guided walkthrough. What does it make
   clearer than yours? What does yours do better?
   - Theirs uses a more realistic hash functionand a merged insert/update operation that mirrors how hash maps are actually used in practice, plus a speed slider and a walkthrough that shrinks the table all the way down to 3 buckets to force serious collisions. Mine uses a simpler sum of characters hash specifically so you can watch the actual computation build up character by character before the modulo. Also keeps insert and update as separate operations.

The goal is to understand both the data structure and what a good AI prompt
feels like before you start the C++ work.

## Where The Rules Are Defined

Each question's `q.h` is the **single source of truth** for that question. It
defines the public API, the exact required behavior, and — for the hash map
questions (1–3) — the **Allowed** and **Forbidden** container lists. When a step
or a prompt mentions
"the contract" or "forbidden containers," it means the comments at the top of
`q.h`. Read that file before you prompt, and treat it as the spec the generated
code must satisfy.

## Start Here

Do this in order:

1. Do the **Warm-Up** above: build a hash map visualizer with an AI tool and
   compare it to the reference.
2. Work through the four questions in order, following each `README.md` step by
   step and writing your answers in that question's `NOTES.md`:
   - [files/1/README.md](files/1/README.md) — Spec & Generate
   - [files/2/README.md](files/2/README.md) — Debug From Failing Tests
   - [files/3/README.md](files/3/README.md) — Review & Refactor
   - [files/4/README.md](files/4/README.md) — Visualize

The question READMEs tell you exactly when to run Bazel commands and exactly
which prompts to paste into Codex.

## Submission And Grading

This lab has **no autograder**.

Submit once after you finish the lab through GitHub Classroom. A single final
submission is enough for full credit; you do not need to submit separately after
each question, and course staff will not manually grade the code.

## What This Lab Teaches

- how to write a useful spec before asking AI to code
- how to compare vague prompts with precise prompts
- how to read and own generated code
- how to review generated code
- how to refactor without changing behavior
- how to debug from failing tests
- how to ask AI to visualize a concept so you understand it before implementing
- how to visualize a data structure

## Repository Map

- `files/1` … `files/4`: the four lab questions
- `files/hash-map-visualization.html`: reference visualizer for the warm-up
- `third_party/cpptui`: terminal UI helper library for Question 4
