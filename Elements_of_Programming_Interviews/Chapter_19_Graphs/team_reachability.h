#ifndef ALGORITHM_ANALYSIS_TEAM_REACHABILITY_H
#define ALGORITHM_ANALYSIS_TEAM_REACHABILITY_H
// additional source for graphs boot camp

#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <vector>

using std::queue;
using std::make_unique;
using std::unique_ptr;
using std::string;
using std::unordered_map;
using std::unordered_set;
using std::vector;

using graph_type = unordered_map<string, unordered_set<string>>;

struct MatchResult;
graph_type BuildGraph( const vector<MatchResult>&);

bool IsReachableDFS(const graph_type & graph,
                    const string& curr, const string& dest,
                    unordered_set<const string*>* visited_ptr);

bool IsReachableBFS(const graph_type & graph,
                    const string& curr, const string& dest,
                    unordered_set<const string*>* visited_ptr);

// @include
struct MatchResult {
    string winning_team;
    string losing_team;
};

bool CanTeamABeatTeamB_DFS(const vector<MatchResult>& matches,
                       const string& team_a, const string& team_b) {
    //unordered_set<const string*>* visited_ptr(new unordered_set<const string*>);
    //unique_ptr<unordered_set<const string*>> visited_ptr(new unordered_set<const string*>);


    // make_unique<unordered_set<const string*>>().get())
    // above is equivalent as following
    //
    // unordered_set<const string*> visited;
    // unordered_set<const string*>* visited_ptr = &visited;
    // return IsReachableDFS(BuildGraph(matches), team_a, team_b,
    //                     visited_ptr);
    /
    // As I tested in graphs_boot_camp
    // pointer that created by make_unique<unordered_set<const string*>>().get())
    // cannot prevent to copy. That is, this is not a unique pointer.
    return IsReachableDFS(BuildGraph(matches), team_a, team_b,
                          make_unique<unordered_set<const string*>>().get());
}

bool CanTeamABeatTeamB_BFS(const vector<MatchResult>& matches,
                       const string& team_a, const string& team_b) {
    return IsReachableBFS(BuildGraph(matches), team_a, team_b,
                          make_unique<unordered_set<const string*>>().get());
}

graph_type BuildGraph(const vector<MatchResult>& matches) {
    graph_type graph;

    for (const MatchResult& match : matches) {
        graph[match.winning_team].emplace(match.losing_team);
    }

    return graph;
}

bool IsReachableDFS(const graph_type & graph,
                    const string& curr, const string& dest,
                    unordered_set<const string*>* visited_ptr) {
    unordered_set<const string*>& visited = *visited_ptr;

    if (curr == dest) {
        return true;
    } else if (visited.find(&curr) != visited.end() ||
               graph.find(curr) == graph.end()) { // if curr is visited before or curr is not included in graph.
        return false;
    }

    visited.emplace(&curr);

    for (const string& team : graph.at(curr)) { // for every adjacent nodes.
        if (IsReachableDFS(graph, team, dest, visited_ptr)) {
            return true;
        }
    }

    return false;
}
// @exclude

bool IsReachableBFS(const graph_type & graph,
                    const string& curr, const string& dest,
                    unordered_set<const string*>* visited_ptr) {
    unordered_set<const string*>& visited = *visited_ptr;

    queue<const string*> frontier;
    visited.emplace(&curr);
    frontier.emplace(&curr);

    while (!frontier.empty()) {
        const string* just_reached = frontier.front();

        if (*just_reached == dest) {
            return true;
        } else if (graph.find(*just_reached) != graph.end()) {
            for (const string& team : graph.at(*just_reached)) {
                if (visited.find(&team) == visited.end()) {
                    visited.emplace(&team);
                    frontier.emplace(&team);
                }
            }
        }

        frontier.pop();
    }

    return false;
}

#endif //ALGORITHM_ANALYSIS_TEAM_REACHABILITY_H
