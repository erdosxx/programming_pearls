#ifndef ALGORITHM_ANALYSIS_TEAM_PHOTO_1_H
#define ALGORITHM_ANALYSIS_TEAM_PHOTO_1_H
// 14.8 Team photo day - 1

#include <algorithm>
#include <vector>

using std::vector;

// @include
struct Player {
    bool operator<(const Player& that) const { return height < that.height; }

    int height;
};

class Team {
public:
    explicit Team(const vector<int>& height) {
        for (int h : height) {
            players_.emplace_back(Player{h});
        }
    }

    // Checks if A can be placed in front of B.
    static bool valid_placement_exists(const Team& A, const Team& B) {
        vector<Player> A_sorted(A.SortPlayersByHeight());
        vector<Player> B_sorted(B.SortPlayersByHeight());

        for (int i = 0; i < A_sorted.size() && i < B_sorted.size(); ++i) {
            if (B_sorted[i] < A_sorted[i]) {
                return false;
            }
        }
        return true;
    }

private:
    vector<Player> SortPlayersByHeight() const {
        vector<Player> sorted_players(players_);
        sort(sorted_players.begin(), sorted_players.end());
        return sorted_players;
    }

    vector<Player> players_;
};
// @exclude

#endif //ALGORITHM_ANALYSIS_TEAM_PHOTO_1_H
