#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include "DirectedAcyclicGraph.h"

int main() {
    DirectedAcyclicGraph graph;
    //a dependent b,callback is executed when a moves to b
    //graph.AddEdge("a", "b", [] { std::cout << "callback 2 -> 0\n"; });
    graph.AddEdge("processA", "processB", [] { std::cout << "processA dependent processB\n"; });
    graph.AddEdge("processB", "processC", [] { std::cout << "processB dependent processC\n"; });
    graph.AddEdge("processD", "processC", [] { std::cout << "processD dependent processC\n"; });
    graph.AddEdge("processE", "root", [] { std::cout << "processE depedent root\n"; });
    graph.AddEdge("processC", "root", [] { std::cout << "processC depedent root\n"; });
    graph.AddEdge("processF", "processD", [] { std::cout << "processF dependent processD\n"; });
    graph.AddEdge("processG", "processB", [] { std::cout << "processG dependent processB\n"; });
    graph.AddEdge("processH", "processD", [] { std::cout << "processH dependent processD\n"; });
    graph.AddEdge("processI", "ProcessJ", [] { std::cout << "processI dependent ProcessJ\n"; });
    graph.AddEdge("ProcessJ", "processB", [] { std::cout << "ProcessJ dependent processB\n"; });
    graph.AddEdge("ProcessK", "ProcessJ", [] { std::cout << "ProcessK dependent ProcessJ\n"; });
    graph.PrintGraphFromRoot();
    std::cout << "----------------------------------" << std::endl;
    if (graph.IsCyclic()) {
        std::cout << "graph contains a cycle" << std::endl;
    }
    else {
        std::cout << "graph is acyclic" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        std::cout << "execute callback:" << std::endl;
        std::cout << "----------------------------------" << std::endl;
        graph.Start();
    }
    std::cout << "----------------------------------" << std::endl;
    std::cout << "new graph" << std::endl;
    std::cout << "----------------------------------" << std::endl;
    DirectedAcyclicGraph graph2;
    graph2.AddEdge("processE", "root", [] { std::cout << "processE depedent root\n"; });
    graph2.AddEdge("processC", "processE", [] { std::cout << "processC depedent processE\n"; });
    graph2.AddEdge("root", "processC", [] { std::cout << "root depedent processC\n"; });
    graph2.PrintGraphAll();
    std::cout << "----------------------------------" << std::endl;
    if (graph2.IsCyclic()) {
        std::cout << "graph contains a cycle" << std::endl;
    }

    return 0;
}
