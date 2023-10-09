#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>

using namespace std;

void Graph::addVertex(string name){
    //TODO

    bool found = false;
    for(long unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == name)
        {
            found = true;
        }
    }

    if(found == false)
    {
        vertex* v = new vertex;
        v->name = name;
        vertices.push_back(v);
    }
}

void Graph::addEdge(string v1, string v2)
{
    for(long unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == v1)
        {
            for(long unsigned int j = 0; j < vertices.size(); j++)
            {
                if(vertices[j]->name == v2 && i != j)
                {
                    adjVertex av;
                    av.v = vertices[j];
                    vertices[i]->adj.push_back(av);
                    adjVertex av2;
                    av2.v = vertices[i];
                    vertices[j]->adj.push_back(av2);

                }
            }
        }
    }
}

void Graph::displayEdges(){
    //TODO
    for (long unsigned int i = 0; i < vertices.size(); i++)
    {
        cout << vertices[i]->name << " -->";
        if (vertices[i]->adj.size() != 0)
        {
                for (long unsigned int k = 0; k < vertices[i]->adj.size(); k++)
            {
                vertex* m = vertices[i]->adj[k].v;
                cout << " " << m->name;
            }
        }
        cout << " \n";
    }
}

void Graph::breadthFirstTraverse(string sourceVertex){
    //TODO
    vertex *vStart;
    for(long unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == sourceVertex)
        {
            vStart = vertices[i];
        }
    }
    vStart->visited = true;
    queue<vertex*> q;
    q.push(vStart);
    vStart->distance = 0;
    vertex *n;
    cout<< "Starting vertex (root): " << vStart->name << "-> ";

    while(!q.empty()){

        n = q.front();
        // go to all the adjacent vertices of n
        for(long unsigned int x = 0; x < n->adj.size(); x++ )
        {
            // If a adjacent has not been visited, then mark it visited and enqueue it
            // Update the distance of the adjacent vertices along the way
            // Stop when you reach the destination vertex and return the needful
            if (n->adj[x].v->visited == false)
            {
                n->adj[x].v->distance = n->distance +1;
                q.push(n->adj[x].v);
                n->adj[x].v->visited = true;
                cout << n->adj[x].v->name <<"("<< n->adj[x].v->distance <<")"<< " ";
            }
        }
        q.pop();
    }
    cout << "\n\n";
}

/*
string::source : source vertex (starting city)
int::k : distance that you can travel from source city with remaining fuel
*/
vector<string> Graph::findReachableCitiesWithinDistanceK(string source, int k){
    //TODO
    vertex *vStart;
    vector<string> list;
    for(long unsigned int i = 0; i < vertices.size(); i++)
    {
        if(vertices[i]->name == source)
        {
            vStart = vertices[i];
        }
    }

    vStart->visited = true;

    // Use the queue to keep track of visited vertices
    queue<vertex*> q;

    // Enqueue the source vertex
    q.push(vStart);
    vStart->distance = 0;

    vertex *n;

    // standard BFS
    while(!q.empty()){

        n = q.front();
        // go to all the adjacent vertices of n
        for(long unsigned int x = 0; x < n->adj.size(); x++ )
        {
            // If a adjacent has not been visited, then mark it visited and enqueue it
            // Update the distance of the adjacent vertices along the way
            // Stop when you reach the destination vertex and return the needful
            vertex* a = n->adj[x].v;

            if (a->visited == false)
            {
                a->distance = n->distance + 1;
                q.push(a);
                a->visited = true;
                if (a->distance == k)
                {
                    list.insert(list.begin(), a->name);
                }
            }
        }
        q.pop();
    }
    return list;
}
