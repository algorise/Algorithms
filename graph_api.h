#pragma once


/*
    representation   |  space | add edge | edge between v and w? | iterate over vertices adjacent to v?
    -----------------|--------|----------|------------------------|---------------------------------------
    list of edges    |   E    |   1      |         E              |          E
    adjacency matrix |  V^2   |   1 *    |         1              |          V
    adjacency list   |  E+V   |   1      |         degree(v)      |          degree(v)
 */




class Graph
{
private:
    int V_;
    int E_;
    std::vector<std::vector<int>> adj_;

public:
    Graph(int V);
    Graph(std::istream& input_stream);
    void addEdge(int v, int w);
    int V();
    int E();
    std::string toString();
    auto adj(int v);
};

class Paths
{
private:
    std::vector<bool> marked_;
    std::vector<int> edgeTo_;
    int s_;
public:
    Paths(Graph& G, int s);
    
    hasPathTo(int v);
    
    pathTo(int v);
    
    void dfs(Graph& G, int v);

    void bfs(Graph& G, int v);
};

class CC
{
private:
    std::vector<bool> marked_;
    std::vector<int> id_;
    int count_;
public:    
    CC(Graph& G);
    bool connected(int v, int w);
    int count();
    int id(int v);
};