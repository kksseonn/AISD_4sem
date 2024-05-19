#pragma once
#include <unordered_map>
#include <unordered_set>
#include <stdexcept>


template<typename Vertex, typename Distance = double>
class Graph {

public:
    struct Edge {
        Vertex from, to;
        Distance distance;
    };
private:
    std::unordered_set<Vertex> _vertices;
    std::unordered_map<Vertex, std::vector<Edge>> _edges;

    std::unordered_set<Vertex> vertices() const {
        return _vertices;
    }
    std::vector<Edge> edges(const Vertex& vertex) {
        return _edges[vertex];
    }
public:
    // проверка-добавление-удаление вершин
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
                return e.to == v || e.from == v;
                }), edges.end());
        }

        return true;
    }

    //проверка-добавление-удаление ребер
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
        if (!has_vertex(e.from) || !has_vertex(e.to))
            return false;
        auto& list = _edges[e.from];
        auto it = std::find(list.begin(), list.end(), e);
        if (it != list.end()) {
            list.erase(it);
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
        const auto& edges = _edges.at(e.from);
        return std::find(edges.begin(), edges.end(), e) != edges.end();
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
};
    
    ////поиск кратчайшего пути
    //std::vector<Edge> shortest_path(const Vertex& from,
    //    const Vertex& to) const;
    ////обход
    //std::vector<Vertex>  walk(const Vertex& start_vertex)const;

