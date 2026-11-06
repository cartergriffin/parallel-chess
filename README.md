# Parallel Chess

This project is intended to implement a *chess engine* utilizing several different parallel optimizations on its evaluation algorithm and evaluate their effectiveness.

## Background

A chess engine is a program that analyzes a game state and chooses a move.

One common algorithm for move selection is *Alpha-Beta* pruning, an optimization of the *Minimax* algorithm for selecting the best move in a competetive environment.

This algorithm has some inherent challenges in its parallelization due to a partially sequential limitation enforced on it due to *shared alpha-beta states* across the search tree.

Despite this limitation, there are many different types of algorithms built to parallelize *alpha-beta* pruning.

## Recurring Challenges

Different algorithms will face different challenges. There are several overarching challenges for parallelizing *alpha-beta pruning*, inherent to a tree-search algorithm:

 - **Idle processors:** naively splitting work between several processors may result in a great deal of *idle time* while processors wait for dependencies to be resolved
 - **Workload imbalance:** skewed trees may result in imbalanced workloads between tasks and create a poor parallel optimization
 - **Synchronization overhead:** since parallel executions are very dependent on the tree's *shared alpha-beta states*, there must be a sophisticated synchronization technique as to not incur excessive overhead
 - **Shared structure contention:** data structures used to synchronize state can create bottlenecks when multiple workers attempt to interact with them
 - **Redundancy:** some optimizations result in several workers performing some of the same job, resuling in greater parallelism but also greater redundancy

## Parallel Algorithms

### Dynamic Tree Splitting

### ABDADA


## Proposal

The project proposal is in `proposal/`, built from the course IEEE template. Build with `make` (or `pdflatex paper && bibtex paper && pdflatex paper && pdflatex paper`) inside that folder; output is `proposal/paper.pdf`.

## Sequential Baseline

`baseline/alphabeta.c` is a single-threaded negamax alpha-beta search over a synthetic game tree: every node has the same number of children, and leaf scores are a hash of the node id, so a given (depth, branching, seed) always produces the same tree. It is the preliminary benchmark for the proposal.

```
gcc -O2 -o alphabeta baseline/alphabeta.c
./alphabeta 6 35 1    # depth 6, 35 children per node, seed 1
```
