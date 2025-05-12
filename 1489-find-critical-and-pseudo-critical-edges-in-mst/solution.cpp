#include <bits/stdc++.h>

using namespace std;

class UnionFind {
public:
    vector<int> parent, tree_size;

    UnionFind(int n) {
        parent.resize(n);
        tree_size.resize(n);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
            tree_size[i] = 1;
        }
    }

    int find(int n) {
        if (parent[n] != n)
            parent[n] = find(parent[n]);
        return parent[n];
    }

    bool union_sets(int n, int m) {
        int root_n = find(n);
        int root_m = find(m);

        if (root_n == root_m) return false; // faz ciclo se unir

        if (tree_size[root_n] < tree_size[root_m]) {
            parent[root_n] = root_m;
        } else if (tree_size[root_n] > tree_size[root_m]) {
            parent[root_m] = root_n;
        } else {
            parent[root_n] = root_m;
            tree_size[root_n]++;
        }

        return true;
    }
};

class Solution {
public:
    int total_weight(const vector<vector<int>>& mst) {
        int total = 0;
        for (const auto& edge : mst)
            total += edge[2];
        return total;
    }

    vector<vector<int>> kruskal(vector<vector<int>> edges, int vert_n, vector<int> forced_edge = {}) {
        UnionFind uf(vert_n);
        vector<vector<int>> mst;

        if (!forced_edge.empty()) {
            uf.union_sets(forced_edge[0], forced_edge[1]);
            mst.emplace_back(forced_edge);
        }

        sort(edges.begin(), edges.end(), [](const vector<int>& e1, const vector<int>& e2) {
            return e1[2] < e2[2];
        });
        

        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];

            if (uf.union_sets(u, v)) {
                mst.emplace_back(edge);
            }
        }

        return mst;
    }

    vector<vector<int>> findCriticalAndPseudoCriticalEdges(int n, vector<vector<int>>& edges) {
        vector<vector<int>> indexed_edges;
        for (int i = 0; i < edges.size(); ++i) {
            vector<int> e = edges[i];
            e.push_back(i);
            indexed_edges.push_back(e);
        }

        vector<vector<int>> original_mst = kruskal(indexed_edges, n);
        int mst_total_weight = total_weight(original_mst);
        
        vector<vector<int>> solution(2);

        for (int i = 0; i < edges.size(); ++i) {
            vector<vector<int>> new_edges;
            for (int j = 0; j < indexed_edges.size(); ++j) {
                if (i != j) new_edges.push_back(indexed_edges[j]);
            }

            vector<vector<int>> new_mst = kruskal(new_edges, n);

            if (new_mst.size() < n - 1 || total_weight(new_mst) > mst_total_weight) {
                solution[0].emplace_back(indexed_edges[i][3]);
            } else {
                vector<vector<int>> forced_mst = kruskal(indexed_edges, n, indexed_edges[i]);

                if (forced_mst.size() == n - 1 && total_weight(forced_mst) == mst_total_weight)
                    solution[1].emplace_back(indexed_edges[i][3]);
            }
        }
        
        return solution;
    }
};

int main() {
    vector<vector<int>> edges1 = {
        {0,1,1},
        {1,2,1},
        {2,3,2},
        {0,3,2},
        {0,4,3},
        {3,4,3},
        {1,4,6}
    };

    vector<vector<int>> edges2 = {
        {0,1,1},
        {1,2,1},
        {2,3,1},
        {0,3,1}
    };

    Solution s;

    vector<vector<int>> critical = s.findCriticalAndPseudoCriticalEdges(5, edges1);
    cout << "Critical Edges: ";
    for (int i = 0; i < critical[0].size(); ++i) {
        cout << critical[0][i] << " ";
    }
    cout << "\n\nPseudo-Critical Edges: ";
    for (int j = 0; j < critical[1].size(); ++j) {
        cout << critical[1][j] << " ";
    }
    cout << "\n";
    return 0;
}
