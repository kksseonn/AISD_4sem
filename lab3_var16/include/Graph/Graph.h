#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <set>
#include <stack>
#include <vector>
#include <limits>
#include <algorithm>


template<typename Vertex, typename Distance = double>
class Graph {
public:
    struct Edge {
        Vertex from, to;
        Distance distance;

        bool operator==(const Edge& other) const {
            return from == other.from && to == other.to && distance == other.distance;
        }
    };

private:
    std::unordered_set<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;

public:
    bool has_vertex(const Vertex& v) const {
        return _vertices.find(v) != _vertices.end();
    }

    void add_vertex(const Vertex& v) {
        if (has_vertex(v)) {
            throw std::invalid_argument("Vertex already exists in the graph");
        }
        _vertices.insert(v);
        _edges[v] = std::vector<Edge>();
    }

    bool remove_vertex(const Vertex& v) {
        if (!has_vertex(v)) return false;

        _vertices.erase(v);
        _edges.erase(v);
        for (auto& pair : _edges) {
            auto& edges = pair.second;
            edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) {
                return e.to == v;
                }), edges.end());
        }
        return true;
    }

    std::unordered_set<Vertex> vertices() const {
        return _vertices;
    }

    void add_edge(const Vertex& from, const Vertex& to, const Distance& d) {
        if (!has_vertex(from) || !has_vertex(to)) {
            throw std::invalid_argument("Vertex does not exist in the graph");
        }
        if (has_edge(from, to)) {
            throw std::invalid_argument("Edge already exists in the graph");
        }
        _edges[from].push_back({ from, to, d });
    }

    bool remove_edge(const Vertex& from, const Vertex& to) {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }
        auto& edges = _edges[from];
        auto it = std::remove_if(edges.begin(), edges.end(), [&](const Edge& e) {
            return e.to == to;
            });
        if (it == edges.end()) {
            return false;
        }
        edges.erase(it, edges.end());
        return true;
    }

    bool remove_edge(const Edge& e) {
        if (!has_vertex(e.from) || !has_vertex(e.to)) return false;

        auto& edges = _edges[e.from];
        auto it = std::find(edges.begin(), edges.end(), e);
        if (it != edges.end()) {
            edges.erase(it);
            return true;
        }
        return false;
    }

    bool has_edge(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) {
            return false;
        }
        const auto& edges = _edges.at(from);
        return std::find_if(edges.begin(), edges.end(), [&](const Edge& e) {
            return e.to == to;
            }) != edges.end();
    }

    bool has_edge(const Edge& e) const {
        if (!has_vertex(e.from) || !has_vertex(e.to)) {
            return false;
        }
        auto it = _edges.find(e.from);
        if (it == _edges.end()) {
            return false;
        }
        const auto& edges = it->second;
        return std::find(edges.begin(), edges.end(), e) != edges.end();
    }

    std::vector<Edge> edges(const Vertex& vertex) const {
        auto it = _edges.find(vertex);
        if (it != _edges.end()) {
            return it->second;
        }
        return {};
    }

    size_t order() const {
        return _vertices.size();
    }

    size_t degree(const Vertex& v) const {
        if (!has_vertex(v)) {
            throw std::invalid_argument("Vertex does not exist in the graph");
        }
        size_t degree = 0;
        for (const auto& pair : _edges) {
            for (const auto& edge : pair.second) {
                if (edge.from == v || edge.to == v) {
                    ++degree;
                }
            }
        }
        return degree;
    }

    std::vector<Edge> shortest_path(const Vertex& from, const Vertex& to) const {
        if (!has_vertex(from) || !has_vertex(to)) {
            throw std::invalid_argument("Vertex does not exist in the graph");
        }

        std::unordered_map<Vertex, Distance> distance;
        std::unordered_map<Vertex, Vertex> predecessor;
        std::set<std::pair<Distance, Vertex>> pq;

        for (const Vertex& v : _vertices) {
            distance[v] = std::numeric_limits<Distance>::infinity();
        }

        distance[from] = Distance(); // initial distance is 0
        pq.insert({ Distance(), from });

        while (!pq.empty()) {
            Vertex u = pq.begin()->second;
            pq.erase(pq.begin());

            for (const Edge& e : _edges.at(u)) {
                Vertex v = e.to;
                Distance weight = e.distance;

                if (weight < 0) {
                    throw std::runtime_error("Graph contains an edge with negative weight");
                }

                if (distance[u] + weight < distance[v]) {
                    pq.erase({ distance[v], v });
                    distance[v] = distance[u] + weight;
                    predecessor[v] = u;
                    pq.insert({ distance[v], v });
                }
            }
        }

        std::vector<Edge> path;
        if (distance[to] == std::numeric_limits<Distance>::infinity()) {
            return path; // No path to the vertex `to`
        }

        for (Vertex at = to; at != from; at = predecessor[at]) {
            Vertex pred = predecessor[at];
            auto it = std::find_if(_edges.at(pred).begin(), _edges.at(pred).end(), [&at](const Edge& e) {
                return e.to == at;
                });
            if (it != _edges.at(pred).end()) {
                path.push_back(*it);
            }
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

    std::vector<Vertex> walk(const Vertex& start_vertex) const {
        if (!has_vertex(start_vertex)) {
            throw std::invalid_argument("Start vertex does not exist in the graph");
        }

        std::unordered_set<Vertex> visited;
        std::stack<Vertex> stack;
        std::vector<Vertex> result;

        stack.push(start_vertex);

        while (!stack.empty()) {
            Vertex current = stack.top();
            stack.pop();

            if (visited.find(current) == visited.end()) {
                visited.insert(current);
                result.push_back(current);

                for (const auto& edge : _edges.at(current)) {
                    if (visited.find(edge.to) == visited.end()) {
                        stack.push(edge.to);
                    }
                }
            }
        }
        return result;
    }

    Vertex find_farthest_traumacentre() const {
        std::unordered_map<Vertex, Distance> total_distance;
        std::unordered_map<Vertex, size_t> neighbor_count;

        for (const auto& vertex : vertices()) {
            if (total_distance.find(vertex) != total_distance.end()) {
                continue;
            }

            std::vector<Vertex> component = walk(vertex);

            for (const Vertex& v : component) {
                total_distance[v] = Distance();
                neighbor_count[v] = 0;

                for (const auto& edge : edges(v)) {
                    total_distance[v] += edge.distance;
                    ++neighbor_count[v];
                }
            }
        }

        Vertex farthest_traumacentre;
        Distance max_avg_distance = -std::numeric_limits<Distance>::infinity();

        for (const auto& pair : total_distance) {

            const Vertex& vertex = pair.first;
            Distance total_dist = pair.second;

            if (neighbor_count[vertex] > 0) {
                Distance avg_distance = total_dist / neighbor_count[vertex];

                if (avg_distance > max_avg_distance) {
                    max_avg_distance = avg_distance;
                    farthest_traumacentre = vertex;
                }
            }
        }
        return farthest_traumacentre;
    }
};