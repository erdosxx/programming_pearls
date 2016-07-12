#ifndef ALGORITHM_ANALYSIS_TOWER_HANOI_H
#define ALGORITHM_ANALYSIS_TOWER_HANOI_H

#include <array>
#include <stack>

using std::array;
using std::stack;

void ComputeTowerHanoiSteps(int, array<stack<int>, 3>&, int&, int, int, int);


enum {kNumPegs = 3};
// @include

int ComputeTowerHanoi(int num_rings) {
    int num_steps = 0;

    array<stack<int>, kNumPegs> pegs;
    // Initialize pegs.
    for (int i = num_rings; i >= 1; --i) {
        pegs[0].push(i);
    }

    ComputeTowerHanoiSteps(num_rings, pegs, num_steps, 0, 1, 2);
    return num_steps;
}

void ComputeTowerHanoiSteps(int num_rings_to_move,
                            array<stack<int>, kNumPegs>& pegs, int& num_steps, int from_peg,
                            int to_peg, int use_peg) {
    if (num_rings_to_move > 0) {
        ComputeTowerHanoiSteps(num_rings_to_move - 1, pegs, num_steps, from_peg, use_peg,
                               to_peg);
        pegs[to_peg].push(pegs[from_peg].top());
        pegs[from_peg].pop();
        // cout << "Move from peg " << from_peg << " to peg " << to_peg << endl;
        // @exclude
        num_steps++;
        // @include
        ComputeTowerHanoiSteps(num_rings_to_move - 1, pegs, num_steps, use_peg, to_peg,
                               from_peg);
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_TOWER_HANOI_H
