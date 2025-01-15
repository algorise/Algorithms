

#include <iostream>
#include <vector>
#include <string>
#include "graph_api.h"

Graph::Graph(int V)
{
    this->V_ = V;
    this->E_ = 0;
    this->adj_ = std::vector<std::vector<int>>(V);
}

Graph::Graph(std::istream& in)
{
    in >> V_;
    adj_ = std::vector<std::vector<int>>(V_);
    int E;
    in >> E;
    for (int i = 0; i < E; i++)
    {
        int v, w;
        in >> v >> w;
        addEdge(v, w);
    }
}

auto Graph::adj(int v)
{
    return adj_[v];
}

int Graph::E()
{
    return E_;
}

int Graph::V()
{
    return V_;
}

void Graph::addEdge(int v, int w)
{
    adj_[v].push_back(w);
    adj_[w].push_back(v);
    E_++;
}

std::string Graph::toString()
{
    std::string s = std::to_string(V_) + " vertices, " + std::to_string(E_) + " edges\n";
    for (int v = 0; v < V_; v++)
    {
        s += std::to_string(v) + ": ";
        for (int w : adj_[v])
        {
            s += std::to_string(w) + " ";
        }
        s += "\n";
    }
    return s;
}

static int degree(Graph& G, int v)
{
    int degree = 0;
    for (int w : G.adj(v))
    {
        degree++;
    }
    return degree;
}

static int maxDegree(Graph& G)
{
    int max = 0;
    for (int v = 0; v < G.V(); v++)
    {
        if (degree(G, v) > max)
        {
            max = degree(G, v);
        }
    }
    return max;
}

static double averageDegree(Graph& G)
{
    return 2.0 * G.E() / G.V();
}

static int numberOfSelfLoops(Graph& G)
{
    int count = 0;
    for (int v = 0; v < G.V(); v++)
    {
        for (int w : G.adj(v))
        {
            if (v == w)
            {
                count++;
            }
        }
    }
    return count / 2;
}


/**/
Paths::Paths(Graph& G, int s)
{
    marked_ = std::vector<bool>(G.V());
    edgeTo_ = std::vector<int>(G.V());
    s_ = s;
    dfs(G, s);
}

bool Paths::hasPathTo(int v)
{
    return marked_[v];
}

std::vector<int> Paths::pathTo(int v)
{
    if (!hasPathTo(v))
    {
        return std::vector<int>();
    }
    std::vector<int> path;
    for (int x = v; x != s_; x = edgeTo_[x])
    {
        path.push_back(x);
    }
    path.push_back(s_);
    return path;
}

void Paths::dfs(Graph& G, int v)
{
    marked_[v] = true;
    for (int w : G.adj(v))
    {
        if (!marked_[w])
        {
            edgeTo_[w] = v;
            dfs(G, w);
        }
    }
}

void Paths::bfs(Graph& G, int v)
{
    std::vector<bool> marked(G.V());
    std::vector<int> edgeTo(G.V());
    std::vector<int> queue;
    queue.push_back(v);
    marked[v] = true;
    while (!queue.empty())
    {
        int x = queue.front();
        queue.erase(queue.begin());
        for (int w : G.adj(x))
        {
            if (!marked[w])
            {
                edgeTo[w] = x;
                marked[w] = true;
                queue.push_back(w);
            }
        }
    }
}

/* Connected Queueries */
CC::CC(Graph& G)
{
    marked_ = std::vector<bool>(G.V());
    id_ = std::vector<int>(G.V());
    count_ = 0;
    for (int v = 0; v < G.V(); v++)
    {
        if (!marked_[v])
        {
            dfs(G, v);
            count_++;
        }
    }
}

bool CC::connected(int v, int w)
{
    return id_[v] == id_[w];
}

int CC::count()
{
    return count_;
}

int CC::id(int v)
{
    return id_[v];
}

