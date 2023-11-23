#include <iostream>
#include <vector>
#include <unordered_set>
#include <functional>
#include "DirectedAcyclicGraph.h"

int main() {
    DirectedAcyclicGraph graph;
    //a to b,callback is executed when a moves to b
    //graph.AddEdge("a", "b", [] { std::cout << "callback 2 -> 0\n"; });
    graph.AddEdge("processA", "processB", [] { std::cout << "processA to processB\n"; });
    graph.AddEdge("processB", "processC", [] { std::cout << "processB to processC\n"; });
    graph.AddEdge("processD", "processC", [] { std::cout << "processD to processC\n"; });
    graph.AddEdge("root", "processA", [] { std::cout << "root to processA\n"; });
    graph.AddEdge("root", "processB", [] { std::cout << "root to processB\n"; });
    graph.AddEdge("processF", "processD", [] { std::cout << "processF to processD\n"; });
    graph.AddEdge("processG", "processB", [] { std::cout << "processG to processB\n"; });
    graph.AddEdge("processH", "processD", [] { std::cout << "processH to processD\n"; });
    graph.AddEdge("processI", "ProcessJ", [] { std::cout << "processI to ProcessJ\n"; });
    graph.AddEdge("ProcessJ", "processB", [] { std::cout << "ProcessJ to processB\n"; });
    graph.AddEdge("ProcessK", "ProcessJ", [] { std::cout << "ProcessK to ProcessJ\n"; });
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
    graph2.AddEdge("processE", "root", [] { std::cout << "processE to root\n"; });
    graph2.AddEdge("processC", "processE", [] { std::cout << "processC to processE\n"; });
    graph2.AddEdge("root", "processC", [] { std::cout << "root to processC\n"; });
    graph2.PrintGraphAll();
    std::cout << "----------------------------------" << std::endl;
    if (graph2.IsCyclic()) {
        std::cout << "graph contains a cycle" << std::endl;
    }

    return 0;
}
