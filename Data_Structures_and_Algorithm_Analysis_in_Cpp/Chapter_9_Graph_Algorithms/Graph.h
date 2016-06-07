#ifndef ALGORITHM_ANALYSIS_GRAPH_H
#define ALGORITHM_ANALYSIS_GRAPH_H

#include <limits.h>
//#include <vector>
#include "Vector.h"
#include <string>
#include <map>
#include <functional>
#include "Queue.h"
#include "dsexceptions.h"
#include <iostream>
#include <queue>
#include "PairingHeap.h"

using namespace std;

class Graph {
public:
    Graph() { }
    ~Graph();

    void addVertex( const string & nodeName) {
        Vertex * v = getVertex( nodeName );
    }

    void addEdge( const string & sourceName, const string & destName, double cost = 0.0);

    //TODO: add removeVertex, removeEdge

    int get_num_vertices() const {
        return vertexMap.size();
    }

    //size_t get_num_edges() const;

    int get_indegree(const string & nodeName) {
        Vertex * v = getVertex( nodeName );
        return v->indegree;
    }

    int get_outdegree(const string & nodeName) {
        Vertex *v = getVertex(nodeName);
        return v->outdegree;
    }

    int get_topological_order(const string & nodeName) {
        Vertex * v = getVertex( nodeName );
        return v->topNum;
    }

    double get_distance(const string & nodeName) {
        Vertex * v = getVertex( nodeName );
        return v->dist;
    }

    string get_prev_node(const string & nodeName) {
        Vertex * v = getVertex( nodeName );
        return v->prev->name;
    }

    void topsort();

    void unweighted(const string & sourceNode);

    void dijkstra(const string & startName);

    void dijkstra_with_pairing_heap(const string & startName);

    void negative( const string & startName );

    void acyclic( const string & startName );

private:
    static const int INFINITY = INT_MAX;

    struct Vertex;

    struct Edge {
        // First vertex in edge is implicit
        Vertex *dest;   // Second vertex in edge
        double cost;

        Edge(Vertex *d = nullptr, double c = 0.0)
                : dest{d}, cost{c} { }

    };

    struct Path {
        Vertex *dest;
        double  cost;

        Path( Vertex *d = nullptr, double c = 0.0 )
                : dest( d ), cost( c ) { }

        bool operator> ( const Path & rhs ) const {
            return cost > rhs.cost;
        }

        bool operator< ( const Path & rhs ) const {
            return cost < rhs.cost;
        }
    };

    struct Vertex {
        string        name;
        Vector<Edge>  adj;
        double        dist;
        Vertex       *prev;    // Previous vertex on shortest path
        int indegree;
        int outdegree;
        int topNum;
        bool known;
        int scratch;

        PairingHeap<Path>::Position pos;

        Vertex( const string & nm = "NULL" ) : name{nm}, dist{INFINITY}, prev{nullptr},
                                      scratch{0}, indegree{0}, outdegree{0}, topNum{0}, known{false} { }

        void reset() {
            dist = INFINITY;
            prev = nullptr;
            pos = nullptr;
            known = false;
            scratch = 0;
        }
    };

    Vertex * getVertex( const string & vertexName );

    //typedef map<string,Vertex *,less<string> > vmap;
    using vmap = map<string, Vertex *, less<string> >;
    using vmap_itr = vmap::iterator;
    using vmap_const_itr = vmap::const_iterator;

    // Copy semantics are disabled; these make no sense.
    Graph( const Graph & rhs ) { }

    void recover_indegree();

    const Graph & operator= ( const Graph & rhs ) {
        return *this;
    }

    void reset_path_value();

    vmap vertexMap;
};

void Graph::reset_path_value() {
    for( vmap_itr itr = vertexMap.begin(); itr != vertexMap.end(); ++itr )
        (*itr).second->reset();
}

void Graph::dijkstra(const string &startName) {
    // TODO: can we change vector<Path> --> Vector<Path>
    priority_queue<Path, vector<Path>, greater<Path> > pq;
    Path vrec;     // Stores the result of a deleteMin

    vmap_itr itr = vertexMap.find( startName );

    reset_path_value();

    if( itr == vertexMap.end() )
        throw GraphException( startName + " is not a vertex in this graph" );

    Vertex *start = (*itr).second;
    pq.push( Path( start, 0 ) );
    start->dist = 0;

    for( int nodesSeen = 0; nodesSeen < vertexMap.size( ); nodesSeen++ ) {
        do { // Find an unvisited vertex
            if( pq.empty() )
                return;
            vrec = pq.top();
            pq.pop();
        } while( vrec.dest->known != false );

        Vertex *v = vrec.dest;
        v->known = true;

        for( int i = 0; i < v->adj.size(); i++ ) {
            Edge e = v->adj[i];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( cvw < 0 )
                throw GraphException( "Graph has negative edges" );

            if( w->dist > v->dist + cvw ) {
                w->dist = v->dist + cvw;
                w->prev = v;
                pq.push( Path( w, w->dist ) );
            }
        }
    }
}

void Graph::dijkstra_with_pairing_heap(const string &startName) {
    PairingHeap<Path> pq;
    Path vrec;     // Stores the result of a deleteMin

    vmap_itr itr = vertexMap.find( startName );

    if( itr == vertexMap.end() )
        throw GraphException( startName + " is not a vertex in this graph" );

    reset_path_value();

    Vertex *start = (*itr).second;
    start->dist = 0;
    start->pos = pq.insert( Path( start, 0 ) );

    while( !pq.isEmpty() ) {
        pq.deleteMin( vrec );

        Vertex *v = vrec.dest;

        for( int i = 0; i < v->adj.size(); i++ ) {
            Edge e = v->adj[i];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( cvw < 0 )
                throw GraphException( "Graph has negative edges" );

            if( w->dist > v->dist + cvw ) {
                w->dist = v->dist + cvw;
                w->prev = v;
                Path newVal( w, w->dist );

                if( w->pos == nullptr )
                    w->pos = pq.insert( newVal );
                else
                    pq.decreaseKey( w->pos, newVal );
            }
        }
    }
}

void Graph::negative( const string & startName ) {
    vmap::iterator itr = vertexMap.find( startName );

    if( itr == vertexMap.end() )
        throw GraphException( startName + " is not a vertex in this graph" );

    reset_path_value();

    Vertex *start = (*itr).second;
    Queue<Vertex *> q;

    q.enqueue(start);

    start->dist = 0;
    start->scratch++;

    // scratch increase when enqueue and check size with vertex number.
    while( !q.isEmpty() ) {
        Vertex *v = q.dequeue();

        if( v->scratch++ > 2 * vertexMap.size() )
            throw GraphException( "Negative cycle detected" );

        for( int i = 0; i < v->adj.size(); i++ ) {
            Edge e = v->adj[i];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( w->dist > v->dist + cvw ) {
                w->dist = v->dist + cvw;
                w->prev = v;
                // Enqueue only if not already on the queue
                if( w->scratch++ % 2 == 0 )
                    q.enqueue( w );
                else // already exist in queue
                    w->scratch--;   // undo enqueue count
            }
        }
    }
}

// Single-source weighted shortest-path algorithm for acyclic graphs.
void Graph::acyclic( const string & startName ) {
    vmap_itr itr = vertexMap.find( startName );

    if( itr == vertexMap.end() )
        throw GraphException( startName + " is not a vertex in this graph" );

    reset_path_value();

    Vertex *start = (*itr).second;
    Queue<Vertex *> q;
    start->dist = 0;

    // Compute the indegrees
    recover_indegree();

    // Enqueue vertices of indegree zero
    for( itr = vertexMap.begin(); itr != vertexMap.end(); ++itr ) {
        Vertex *v = (*itr).second;
        if( v->indegree == 0 )
            q.enqueue(v);
    }

    int iterations;
    for( iterations = 0; !q.isEmpty(); iterations++ ) {
        Vertex *v = q.dequeue();

        for( int i = 0; i < v->adj.size(); i++ ) {
            Edge e = v->adj[i];
            Vertex *w = e.dest;
            double cvw = e.cost;

            if( --w->indegree == 0 )
                q.enqueue(w);

            if( v->dist == INFINITY )
                continue;

            if( w->dist > v->dist + cvw ) {
                w->dist = v->dist + cvw;
                w->prev = v;
            }
        }
    }

    if( iterations != vertexMap.size() )
        throw GraphException( "Graph has a cycle!" );

    recover_indegree();
}

void Graph::unweighted(const string &sourceNode) {
    Queue<Vertex *> q;

    vmap_const_itr citr;

    for (citr= vertexMap.begin(); citr != vertexMap.end(); citr++)
        (*citr).second->dist = INFINITY;

    Vertex * vs = getVertex( sourceNode );
    vs->dist = 0;
    q.enqueue(vs);

    Vector<Edge>::iterator v_itr;

    while ( !q.isEmpty() ) {
        Vertex * v = q.dequeue();

        for(v_itr = v->adj.begin(); v_itr != v->adj.end(); v_itr++)
            if ( v_itr->dest->dist == INFINITY ) {
                v_itr->dest->dist = v->dist + 1;
                v_itr->dest->prev = v;
                q.enqueue(v_itr->dest);
            }
    }
}

void Graph::recover_indegree() {
    vmap_itr itr;
    Vector<Edge>::iterator e_itr;

    for (itr = vertexMap.begin(); itr != vertexMap.end(); itr++) {
        itr->second->indegree =0;
    }

    for (itr = vertexMap.begin(); itr != vertexMap.end(); itr++) {
        for( e_itr = (*itr).second->adj.begin(); e_itr != (*itr).second->adj.end(); e_itr++){
            (*e_itr).dest->indegree++;
        }
    }
}

void Graph::topsort() {
    Queue<Vertex *> q;

    //q.makeEmpty();
    vmap_const_itr citr;

    for (citr= vertexMap.begin(); citr != vertexMap.end(); citr++)
        if ( (*citr).second->indegree == 0 )
            q.enqueue((*citr).second);

    int counter = 0;
    Vector<Edge>::iterator v_itr;

    while ( !q.isEmpty() ) {
        Vertex * v = q.dequeue();
        v->topNum = ++counter;

        for(v_itr = v->adj.begin(); v_itr != v->adj.end(); v_itr++)
            if (--v_itr->dest->indegree == 0)
                q.enqueue(v_itr->dest);
    }

    recover_indegree();

    if (counter != get_num_vertices())
        throw CycleFoundException{};
}

Graph::Vertex * Graph::getVertex( const string & vertexName ) {
    vmap_itr itr = vertexMap.find( vertexName );

    if( itr == vertexMap.end() ) {
        Vertex *newv = new Vertex( vertexName );
        vertexMap[ vertexName ] = newv;
        return newv;
    }
    return (*itr).second;
}

void Graph::addEdge( const string & sourceName, const string & destName, double cost ) {
    Vertex * v = getVertex( sourceName );
    Vertex * w = getVertex( destName );
    v->adj.push_back( Edge( w, cost ) );
    v->outdegree++;
    w->indegree++;
}

Graph::~Graph() {
    for( vmap_itr itr = vertexMap.begin(); itr != vertexMap.end(); ++itr )
        delete (*itr).second;
}
#endif //ALGORITHM_ANALYSIS_GRAPH_H
