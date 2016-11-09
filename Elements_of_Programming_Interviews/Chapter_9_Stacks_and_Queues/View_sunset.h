#ifndef ALGORITHM_ANALYSIS_VIEW_SUNSET_H
#define ALGORITHM_ANALYSIS_VIEW_SUNSET_H
// 9.6 Compute buildings with a sunset view

#include <sstream>
#include <stack>
#include <utility>
#include <vector>

using std::istringstream;
using std::stack;
using std::stringstream;
using std::uniform_int_distribution;
using std::vector;

// @include
vector<int> ExamineBuildingsWithSunset(istringstream* sin) {
  int building_idx = 0;
  int building_height;

  struct BuildingWithHeight {
    int id, height;
  };

  stack<BuildingWithHeight> candidates;

  // convert string to int by using istringstream. See: http://www.cplusplus.com/articles/D9j2Nwbp/
  while (*sin >> building_height) {
    while (!candidates.empty() &&
           building_height >= candidates.top().height) {
      candidates.pop();
    }
    candidates.emplace(BuildingWithHeight{building_idx++, building_height});
  }

  vector<int> buildings_with_sunset;
  while (!candidates.empty()) {
    buildings_with_sunset.emplace_back(candidates.top().id);
    candidates.pop();
  }
  return buildings_with_sunset;
}
// @exclude

#endif //ALGORITHM_ANALYSIS_VIEW_SUNSET_H
