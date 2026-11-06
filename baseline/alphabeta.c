// sequential alphabeta (negamax) on a fake game tree
// every node has B kids, leaf score is just a hash of the node id so same args = same tree
// usage: ./alphabeta depth branching seed
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define INF 1000000
static int B;           // branching factor, set once in main from argv, never changes
static long long nodes; // nodes visited, for the benchmark output

// splitmix64, gives us random looking but deterministic ids/scores
static uint64_t mix(uint64_t x) {
    x += 0x9E3779B97F4A7C15ULL;
    x = (x ^ (x >> 30)) * 0xBF58476D1CE4E5B9ULL;
    x = (x ^ (x >> 27)) * 0x94D049BB133111EBULL;
    return x ^ (x >> 31);
}

// tree isnt stored, nodes get generated during the search
// node = 64 bit id, child i = mix(id + i + 1), leaf score = mix(id) mapped to -1000..1000
static int negamax(uint64_t id, int depth, int alpha, int beta) {
    nodes++;
    if (depth == 0) return (int)(mix(id) % 2001) - 1000;
    for (int i = 0; i < B; i++) {
        int s = -negamax(mix(id + i + 1), depth - 1, -beta, -alpha);
        if (s >= beta) return beta;
        if (s > alpha) alpha = s;
    }
    return alpha;
}

int main(int argc, char **argv) {
    if (argc != 4) { fprintf(stderr, "usage: %s depth branching seed\n", argv[0]); return 1; }
    int depth = atoi(argv[1]);
    B = atoi(argv[2]);
    uint64_t seed = strtoull(argv[3], NULL, 10);

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    int score = negamax(mix(seed), depth, -INF, INF); // hash seed so seeds 1,2,3 dont share subtrees
    clock_gettime(CLOCK_MONOTONIC, &t1);

    double secs = (t1.tv_sec - t0.tv_sec) + (t1.tv_nsec - t0.tv_nsec) / 1e9;
    printf("depth=%d branching=%d seed=%llu score=%d nodes=%lld time=%.3fs\n",
           depth, B, (unsigned long long)seed, score, nodes, secs);
    return 0;
}
