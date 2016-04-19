#ifndef PROGRAMMING_PEARLS_GRAPH_H
#define PROGRAMMING_PEARLS_GRAPH_H

#include <stdlib.h>

// Ref: Algorithm Design Manual 2nd Edition, Steven Skiena

class graph_skeina {
private:
    enum {MAXV=1000, TRUE=1, FALSE=0};

    struct edgenode {
        int dst_node;
        int weight;
        edgenode* next;
    };

    edgenode** edges;
    int* degree;
    int _num_vertices;
    int _num_edges;
    bool _directed;

    void insert_edge(int src, int dst, int weight) {
        //edgenode *p = (edgenode*) malloc(sizeof(edgenode));
        //edgenode* p = new edgenode;
        edgenode *p = new edgenode;

        p->weight = weight;
        p->dst_node = dst;
        p->next = edges[src];
        edges[src] = p;
        degree[src]++;
        _num_edges++;
    }

public:
    graph_skeina(int num_vertices, bool directed):
            _num_vertices(num_vertices), _num_edges(0), _directed(directed) {

        edges = new edgenode*[num_vertices+1];
        degree = new int[num_vertices+1];

        for(int i=1; i <= num_vertices; i++) {
            edges[i] = NULL;
            degree[i] = 0;
        }
    }

    void insert_edges(int src, int dst, int weight=0) {
        insert_edge(src, dst, weight);

        if (_directed == FALSE)
            insert_edge(dst, src, weight);
    }

    void print_graph() {
        edgenode* eg_ptr;

        printf("\n");
        for(int i =1; i <= _num_vertices; i++) {
            printf("%d: ", i);
            eg_ptr = edges[i];

            while (eg_ptr != NULL) {
                printf("%d-", eg_ptr->dst_node);
                eg_ptr = eg_ptr->next;
            }
            printf("\n");
        }
    }

    void initialize_search() {
        bool processed[_num_vertices +1];
        bool discovered[_num_vertices+1];
        int parent[_num_vertices+1];

        for (int i; i <= _num_vertices; i++){
            processed[i]= discovered[i]= FALSE;
            parent[i]= -1;
        }
    }

//    void BFS(int start){
//        queue q;     /* queue of vertices to visit */
//        int v;       /* current vertex */
//        int y;       /* successor vertex */
//        edgenode* p; /* temporary pointer*/
/*
        init_queue(&q);
        enqueue(&q, start);
        discovered[start] = TRUE;

        while (empty_queue(&q) == FALSE) {
            v = dequeue(&q);
            process_vertex_early(v);
            processed[v] = TRUE;
            p = edges[v];
            while (p != NULL) {
                y = p->dst_node;
                if ((processed[y] == FALSE) || _directed)
                    process_edge(v,y);
                if (discovered[y] == FALSE) {
                    enquene(&q, y);
                    discovered[y] = TRUE;
                    parent[y] = v;
                }
                p = p->next;
            }
            process_vertex_late(v);
        }
    }
*/
/*
    void DFS(int v) {
        edgenode *p;
        int y;

        if (finished) return;

        discovered[v] = TRUE;
        time = time +1;
        entry_time[v] = time;

        process_vertex_early(v);

        p = edges[v];

        while (p != NULL) {
            y= p->dst_node;
            if (discovered[y] == FALSE) {
                parent[y] = v;
                process_edge(v,y);
                DFS(y);
            } else if ( processed[y] == FALSE || _directed == TRUE) {
                process_edge(v,y);
            }

            if (finished) return;
            p = p->next;
        }

        process_vertex_late(v);
        time = time +1;
        exit_time[v] = time;
        processed[v]= TRUE;
    }
*/

};
#endif //PROGRAMMING_PEARLS_GRAPH_H
