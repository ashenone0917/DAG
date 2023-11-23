#pragma once
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include <string>
#include <deque>
#include <iostream>
class DirectedAcyclicGraph {
public:
    DirectedAcyclicGraph() = default;

    void AddEdge(const std::string& from, const std::string& to,
        std::function<void()> callback = nullptr) {
        if (from == to)
            return;

        auto& to_node = nodes_[to];
        auto& from_node = nodes_[from];
        auto [key,insert_succ] = from_node.edges_.insert({ to, callback });
        if(insert_succ)
            ++to_node.in_degree_;
    }

    bool IsCyclic() {
        std::unordered_set<std::string> visited;
        std::unordered_set<std::string> recursion_stack;

        for (const auto& [name,node] : nodes_) {
            if (!visited.count(name) &&
                IsCyclicUtil(name, node.edges_, visited, recursion_stack)) {
                return true;
            }
        }
        return false;
    }

    void Start() {
        std::deque<std::string> execute_nodes;
        for (const auto& [name, node] : nodes_) {
            if (node.in_degree_ == 0) {
                execute_nodes.emplace_back(name);
            }
        }

        while (!execute_nodes.empty()) {
            const auto& current = execute_nodes.front();
            for (const auto& edge : nodes_[current].edges_) {
                if (edge.callback_) {
                    edge.callback_();
                }

                auto& neighbor = nodes_[edge.to_];
                if (--neighbor.in_degree_ == 0) {
                    execute_nodes.emplace_back(edge.to_);
                }
            }
            execute_nodes.pop_front();
        }
    }

    void PrintGraphFromRoot() {
        std::unordered_set<std::string> recursion_stack;
        for (const auto& [name, node] : nodes_) {
            if (node.in_degree_ == 0) {
                recursion_stack.insert(name);
                std::cout << name << " -> " << std::endl;
                PrintEdges(node.edges_, recursion_stack, "\t");
                std::cout << "end." << std::endl;
                recursion_stack.erase(name);
           }    
        }
    }

    void PrintGraphAll() {
        std::unordered_set<std::string> recursion_stack;
        for (const auto& [name, node] : nodes_) {
            recursion_stack.insert(name);
            std::cout << name << " -> " << std::endl;
            PrintEdges(node.edges_, recursion_stack, "\t");
            std::cout << "end." << std::endl;
            recursion_stack.erase(name);
        }
    }

private:
    struct Edge {
        std::string to_;
        std::function<void()> callback_;

        struct Hash {
            std::size_t operator()(const Edge& edge) const {
                std::size_t hash = std::hash<std::string>{}(edge.to_);
                return hash;
            }
        };

        struct Equal {
            bool operator()(const Edge& lhs, const Edge& rhs) const {
                return lhs.to_ == rhs.to_;
            }
        };
    };

    struct Node {
        std::unordered_set<Edge, Edge::Hash, Edge::Equal> edges_;
        int in_degree_ = 0;
    };

    std::unordered_map<std::string,Node> nodes_;

private:
    bool IsCyclicUtil(const std::string& node, const std::unordered_set<Edge, Edge::Hash, Edge::Equal>& edges,
        std::unordered_set<std::string>& visited,
        std::unordered_set<std::string>& recursion_stack) {
        visited.insert(node);
        recursion_stack.insert(node);
        for (const auto& edge : edges) {
            const auto& neighbor = edge.to_;
            if (!visited.count(neighbor)) {
                if (IsCyclicUtil(neighbor, nodes_[neighbor].edges_,
                    visited, recursion_stack)) {
                    return true;
                }
            }
            else if (recursion_stack.count(neighbor)) {
                return true;
            }
        }

        recursion_stack.erase(node);
        return false;
    }

    void PrintEdges(const std::unordered_set<Edge, Edge::Hash, Edge::Equal>& edges, std::unordered_set<std::string>& recursion_stack,
        const std::string& prefix) {
        for (const auto& edge : edges) {
            std::cout << prefix <<"-> ";
            std::cout << edge.to_ << std::endl;
            try {
                if (!recursion_stack.count(edge.to_)) {
                    recursion_stack.insert(edge.to_);
                    PrintEdges(nodes_.at(edge.to_).edges_, recursion_stack, prefix + "\t");
                    recursion_stack.erase(edge.to_);
                }        
            }
            catch (std::out_of_range ex) {
                continue;
            }    
        }
    }
};