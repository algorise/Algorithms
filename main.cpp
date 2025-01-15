

#include <iostream>
#include <vector>
#include "graph_api.h"

std::vector<std::vector<int>> adjacencyList(Graph& G)
{
    std::vector<std::vector<int>> adj(G.V());
    for (int v = 0; v < G.V(); v++)
    {
        for (int w : G.adj(v))
        {
            adj[v].push_back(w);
        }
    }
    return adj;
}

int main()
{
    Graph G(std::cin);
    std::cout << G.toString() << std::endl;
    return 0;
}

