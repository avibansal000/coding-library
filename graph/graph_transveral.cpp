#include <bits/stdc++.h>
using namespace std;

//-------------------------------depth first search algorithm----------------------------------------

vector<vector<int>> adj(2e5 + 5); // graph represented as an adjacency list
// int n;                   // number of vertices
vector<int> color(2e5 + 5); // color is 0 if vertex not entered ,else 1 if entered but not exited ,else 2

void dfs(int v)
{
    color[v] = 1;
    for (int u : adj[v])
    {
        if (color[u] == 0)
        {
            dfs(u);
        }
    }
    color[v] = 2;
}
//a vertex is ancestor of another vertex b if and only if time_in[a]<time_in[b] || time_out[a]>time_out[b]
// we can find lowest common ancestor
//topological sorting =for every edge from u to v u should placed early than b ,,,  Run a series of depth first searches so as to visit each vertex exactly once in O(n+m) time. The required topological ordering will be the vertices sorted in descending order of exit time.
//we can check that if there is cycles in the graph using backedges,if there is a path from a vertex to its ancestor then there is cycle

//------------------------------Breadth-first search algorithm-----------------------------------------
vector<vector<int>> adj; // adjacency list representation
int n;                   // number of nodes
int s;                   // source vertex

queue<int> q;
vector<bool> used(n); // check whether current vertex is used or not
vector<int> d(n);     // keeps distance
vector<int> p(n);     // keeps parent;
void bfs(int s)
{
    q.push(s);
    used[s] = true;
    p[s] = -1;
    while (!q.empty())
    {
        int v = q.front();
        q.pop();
        for (int u : adj[v])
        {
            if (!used[u])
            {
                used[u] = true;
                q.push(u);
                d[u] = d[v] + 1;
                p[u] = v;
            }
        }
    }
}

/*
Find the shortest path from a source to other vertices in an unweighted graph.

Find all connected components in an undirected graph in O(n+m) time: To do this, we just run BFS starting from each vertex, except for vertices which have already been visited from previous runs. Thus, we perform normal BFS from each of the vertices, but do not reset the array used[] each and every time we get a new connected component, and the total running time will still be O(n+m) (performing multiple BFS on the graph without zeroing the array used[] is called a series of breadth first searches).

Finding a solution to a problem or a game with the least number of moves, if each state of the game can be represented by a vertex of the graph, and the transitions from one state to the other are the edges of the graph.

Finding the shortest path in a graph with weights 0 or 1: This requires just a little modification to normal breadth-first search: Instead of maintaining array used[], we will now check if the distance to vertex is shorter than current found distance, then if the current edge is of zero weight, we add it to the front of the queue else we add it to the back of the queue.This modification is explained in more detail in the article 0-1 BFS.

Finding the shortest cycle in a directed unweighted graph: Start a breadth-first search from each vertex. As soon as we try to go from the current vertex back to the source vertex, we have found the shortest cycle containing the source vertex. At this point we can stop the BFS, and start a new BFS from the next vertex. From all such cycles (at most one from each BFS) choose the shortest.

Find all the edges that lie on any shortest path between a given pair of vertices (a,b). To do this, run two breadth first searches: one from a and one from b. Let da[] be the array containing shortest distances obtained from the first BFS (from a) and db[] be the array containing shortest distances obtained from the second BFS from b. Now for every edge (u,v) it is easy to check whether that edge lies on any shortest path between a and b: the criterion is the condition da[u]+1+db[v]=da[b].

Find all the vertices on any shortest path between a given pair of vertices (a,b). To accomplish that, run two breadth first searches: one from a and one from b. Let da[] be the array containing shortest distances obtained from the first BFS (from a) and db[] be the array containing shortest distances obtained from the second BFS (from b). Now for each vertex it is easy to check whether it lies on any shortest path between a and b: the criterion is the condition da[v]+db[v]=da[b].


*/
void solve()
{
}

int main()
{
    int t = 1;
    while (t--)
    {
        solve();
    }
    return 0;
}