#include <iostream>
#include <fstream>
#include <vector>

int vertices_count = 5;
int edges_count = 4;
std::vector<std::pair<int, int>> paths = { {0,1}, {0,4}, {1,2}, {1,3} };
int start_vertex = 4;

void bfs(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& distances) {
    std::vector<std::pair<int, int>> stack;
    stack.push_back({ start, 0 });
    distances[start] = 0;

    while (!stack.empty()) {
        std::pair<int, int> current = stack.back();
        stack.pop_back();
        int v = current.first;
        int dist = current.second;

        for (int i = 0; i < graph[v].size(); i++) {
            int neighbor = graph[v][i];
            if (distances[neighbor] == -1) { 
                distances[neighbor] = dist + 1;
                stack.push_back({ neighbor, distances[neighbor] });
            }
        }
    }
}

int main() {
    std::ifstream input("graph.txt");
    input >> vertices_count >> edges_count;

    paths.resize(edges_count);

    for (int i = 0; i < edges_count; i++){
        int a, b;
        input >> a >> b;
        paths[i].first = a;
        paths[i].second = b;
    }
    input >> start_vertex;

    std::vector<std::vector<int>> graph(vertices_count);
    for (int i = 0; i < paths.size(); i++) {
        std::pair<int, int>& edge = paths[i];
        graph[edge.first].push_back(edge.second);
        graph[edge.second].push_back(edge.first);
    }

    std::vector<int> distances(vertices_count, -1);
    bfs(graph, start_vertex, distances);

    for (int i = 0; i < distances.size(); ++i) {
        int dist = distances[i];
        std::cout << dist << std::endl;
    }
}
