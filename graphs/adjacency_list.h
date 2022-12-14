#ifndef __GRAPH_ADJACENCY_LIST__
#define __GRAPH_ADJACENCY_LIST__

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>

namespace gal {

class EdgeNode {
   public:
    EdgeNode(int target, EdgeNode* curr_edges)
        : y(target), weight(0), next(curr_edges) {}
    int y;
    int weight;
    EdgeNode* next;
};

class Graph {
   public:
    Graph(bool d)
        : nedges_(0),
          nvertices_(0),
          directed_(d),
          degree_(max, 0),
          edges_(max, nullptr) {}

    void addEdge(int source, int target) {
        auto* edge_node =
            new EdgeNode(target, edges_[source]); /* insert at head of list */
        edges_[source] = edge_node;
        degree_[source]++;
        nedges_++;
    }

    std::vector<int> bfs(int source, void (*callback)(int value)) {
        if (source < 0 || source >= max) {
            std::cout << "Out of boundary!" << std::endl;
        }
        std::unordered_map<int, bool> map;
        std::queue<int> queue;
        std::vector<int> parent(max, -1);
        map.insert({source, true}), queue.push(source);
        while (!queue.empty()) {
            callback(queue.front());
            if (edges_[queue.front()]) {
                auto v = edges_[queue.front()];
                while (v) {
                    if (map.find(v->y) == map.end()) {
                        queue.push(v->y);
                        map.insert({v->y, true});
                        parent[v->y] = queue.front();
                    }
                    v = v->next;
                }
            }
            queue.pop();
        }
        return parent;
    }

    std::vector<int> dfs(int source) {
        std::vector<bool> visited(max, false);
        std::vector<int> res;
        return dfs_(source, visited, res);
    }

    void shortest_path(int start, int end, std::vector<int> parent) {
        if (start == end || end == -1) {
            std::cout << start << ' ';
        } else {
            shortest_path(start, parent[end], parent);
            std::cout << end << ' ';
        }
    }

    void print() {
        for (int i = 0; i < edges_.size(); i++) {
            if (edges_[i]) {
                std::cout << "Source: " << i << std::endl;
                auto temp_head = edges_[i];
                while (temp_head) {
                    std::cout << temp_head->y << std::endl;
                    temp_head = temp_head->next;
                }
            }
        }
    }

   private:
    const int max = 10;
    int nedges_;
    int nvertices_;
    bool directed_;
    std::vector<int> degree_;  // outdegree of each vertex
    std::vector<EdgeNode*> edges_;

    std::vector<int> dfs_(int source, std::vector<bool>& visited,
                          std::vector<int>& res) {
        visited[source] = true;
        res.push_back(source);
        auto v = edges_[source];
        while (v) {
            if (!visited[v->y]) {
                dfs_(v->y, visited, res);
            }
            v = v->next;
        }
        return res;
    }
};

}  // namespace gal
#endif
