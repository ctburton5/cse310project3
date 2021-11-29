// libraries
#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

#define NULL -999

// stack class definitions
class stack {
    int* stackArr;
    int start;
    int size;

    public:
        stack(int);
        ~stack();

        void push(int);
        int pop();

        int size();
};

stack::stack(int size) {
    stackArr = new int[size];
    size = size;
}

stack::~stack() {
    delete stackArr;
}

void stack::push(int value) {
    stackArr[start] = value;
}

int stack::pop() {
    return stackArr[start];
}

int stack::size() {
    return start + 1;
}


// adjacency list structures
struct node {
    int vertex;
    struct node* next;
};

struct vertex {
    int vertex;
    int weight = 1;
    int degree = 0;
    int* aLists;
};


int main(int argc, char* argv[]) {

    vertex* vertexArr;
    int n, m, u, v;    
    
    // get the first 2 integers from input showing the n and m values
    // n = number of vertices
    // m = number of edges
    cin >> n >> m;

    int i = 0;
    vertexArr = new vertex[n];

    for (int j = 0; j < n; j++) {
        vertexArr[j].aLists = new int[m];
    }

    loop:
    // u = first vertex of the edge
    // v = second vertex in the edge
    while (cin >> u >> v) {
        
        if (i == 0) {
            vertexArr[i].vertex = u;
            vertexArr[i].degree++;
            vertexArr[i].aLists[vertexArr[i].degree - 1] = v;
        } else {
            if (vertexArr[i - 1].vertex == u) {
                vertexArr[i].degree++;
                vertexArr[i].aLists[vertexArr[i].degree - 1] = v;
                goto loop;
            } else {
                vertexArr[i].vertex = u;
                vertexArr[i].degree++;
                vertexArr[i].aLists[vertexArr[i].degree - 1] = v;
            }
        }




        i++;
    }

    //getting all the odd degree vertices
    int* oddArr;
    oddArr = new int[n];
    for (int i = 0; i < n; i++) {
        if (vertexArr[i].degree % 2 != 0) {
            oddArr[i] = vertexArr[i].vertex;
        }
    }

    //Floyd-Warshall on the graph
    int** G;
    G = new int*[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
           for (int k = 0; k < n; k++) {
                G[n] = new int[m];
                G[i][j] = min(G[i][j], G[i][k], G[j][k]);
           }
        }
    }

    // minimum weight perfect matching
    int** newG;
    newG = new int*[n];
    for (int i = 0; i < n; i++) {
        newG[n] = new int[m];
        for (int j = 0; j < n; j++) {
            if (G[i][j] == G[i][j]) {
                newG[i][j] = G[i][j];
            }
        }
    }

    // inserting virtual edges into G
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            G[i][j] = newG[i][j];
        }
    }

    return 0;
}