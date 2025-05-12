#include <bits/stdc++.h>

using namespace std;

class Solution {
public:
    int swimInWater(vector<vector<int>>& grid) {
        pair<int,int> start = {0,0};
        pair<int,int> finish = {grid.size() - 1, grid.size() - 1};

        int result = dijkstra(grid, start, finish);

        return result;
    }

private:
    struct hash_function {
        size_t operator()(const pair<int,int> &x) const {
            return x.first ^ x.second;
        }
    };

    const array<array<int, 2>, 4> directions = {{{0,1}, {1,0}, {0,-1}, {-1,0}}};

    int dijkstra(vector<vector<int>>& grid, pair<int,int> start, pair<int,int> finish) {
        priority_queue<tuple<int, int, int>, vector<tuple<int, int, int>>, greater<>> minHeap;
        unordered_set<pair<int,int>, hash_function> explored;
        int n = grid.size();

        int start_x = start.first, start_y = start.second;
        int finish_x = finish.first, finish_y = finish.second;

        minHeap.emplace(grid[start_x][start_y], start_x, start_y);

        while (!minHeap.empty()) {
            auto [cur_max, x, y] = minHeap.top();
            minHeap.pop();

            if (explored.count({x, y})) continue;
            explored.insert({x, y});

            if (x == finish_x && y == finish_y) return cur_max;

            for (auto [dx, dy] : directions) {
                int next_x = x + dx, next_y = y + dy;
                if (next_x >= 0 && next_x < n && next_y >= 0 && next_y < n && explored.count({next_x, next_y}) == 0) {
                    int new_max = max(cur_max, grid[next_x][next_y]);
                    minHeap.emplace(new_max, next_x, next_y);
                }
            }
        }

        return -1;
    }
};

int main() {
    Solution s;
    vector<vector<int>> grid = {
        {0,1,2,3,4},
        {24,23,22,21,5},
        {12,13,14,15,16},
        {11,17,18,19,20},
        {10,9,8,7,6}
    };

    cout << s.swimInWater(grid) << "\n";

    return 0;
}
