#ifndef ALGORITHM_ANALYSIS_ROAD_NETWORK_H
#define ALGORITHM_ANALYSIS_ROAD_NETWORK_H

#include <limits>
#include <vector>

using std::numeric_limits;
using std::vector;

void FloydWarshall(vector<vector<double>>* G);

// @include
struct HighwaySection {
    int x, y;
    double distance;
};

HighwaySection FindBestProposals(const vector<HighwaySection>& Highways,
                                 const vector<HighwaySection>& Proposals, int n) {
    // G stores the shortest path distances between all pairs of vertices.
    vector<vector<double>> G(n,
                             vector<double>(n, numeric_limits<double>::max()));
    for (int i = 0; i < n; ++i) {
        G[i][i] = 0;
    }

    // Builds an undirected graph G based on existing highway sections H.
    for (const HighwaySection& h : Highways) {
        G[h.x][h.y] = G[h.y][h.x] = h.distance;
    }

    // Performs Floyd Warshall to build the shortest path between vertices.
    FloydWarshall(&G);

    // Examines each proposal for shorter distance for all pairs.
    double best_distance_saving = numeric_limits<double>::min();
    HighwaySection best_proposal = {-1, -1, 0.0};  // Default.

    for (const HighwaySection& p : Proposals) {
        double proposal_saving = 0.0;
        for (int a = 0; a < n; ++a) {
            for (int b = 0; b < n; ++b) {
                double saving = G[a][b] - (G[a][p.x] + p.distance + G[p.y][b]);
                proposal_saving += saving > 0.0 ? saving : 0.0;
            }
        }

        if (proposal_saving > best_distance_saving) {
            best_distance_saving = proposal_saving;
            best_proposal = p;
        }
    }
    return best_proposal;
}

void FloydWarshall(vector<vector<double>>* G) {
    // i --> k --> j
    for (int k = 0; k < G->size(); ++k) {
        for (int i = 0; i < G->size(); ++i) {
            for (int j = 0; j < G->size(); ++j) {
                if ((*G)[i][k] != numeric_limits<double>::max() &&
                    (*G)[k][j] != numeric_limits<double>::max() &&
                    (*G)[i][j] > (*G)[i][k] + (*G)[k][j]) {
                    (*G)[i][j] = (*G)[i][k] + (*G)[k][j];
                }
            }
        }
    }
}
// @exclude

#endif //ALGORITHM_ANALYSIS_ROAD_NETWORK_H
