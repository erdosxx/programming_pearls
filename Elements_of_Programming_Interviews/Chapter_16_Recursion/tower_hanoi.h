#ifndef ALGORITHM_ANALYSIS_TOWER_HANOI_H
#define ALGORITHM_ANALYSIS_TOWER_HANOI_H
// 16.1 The Towers of Hanoi problem

#include <array>
#include <stack>

using std::array;
using std::stack;

enum {kNumPegs = 3};

void ComputeTowerHanoiSteps(const int& num_rings_to_move,
                            array<stack<int>, kNumPegs>* pegs_ptr, int* num_steps_ptr, const int& from_peg,
                            const int& to_peg, const int& use_peg) {
    array<stack<int>, kNumPegs>& pegs = *pegs_ptr;
    int& num_steps = *num_steps_ptr;

    if (num_rings_to_move > 0) {
        ComputeTowerHanoiSteps(num_rings_to_move - 1, pegs_ptr, num_steps_ptr, from_peg, use_peg,
                               to_peg);
        //     |       |       |
        //     |       |       |
        //    ---     ---     ---
        //  from_peg to_peg  use_peg
        pegs[to_peg].push(pegs[from_peg].top());
        pegs[from_peg].pop();
        // cout << "Move from peg " << from_peg << " to peg " << to_peg << endl;
        num_steps++;
        ComputeTowerHanoiSteps(num_rings_to_move - 1, pegs_ptr, num_steps_ptr, use_peg, to_peg,
                               from_peg);
    }
}

int ComputeTowerHanoi(int num_rings) {
    int num_steps = 0;

    array<stack<int>, kNumPegs> pegs;
    // Initialize pegs.
    for (int i = num_rings; i >= 1; --i) {
        pegs[0].push(i);
    }

    ComputeTowerHanoiSteps(num_rings, &pegs, &num_steps, 0, 1, 2);
    return num_steps;
}

#endif //ALGORITHM_ANALYSIS_TOWER_HANOI_H
