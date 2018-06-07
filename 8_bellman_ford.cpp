#include <iostream>
#include <climits>
#include <vector>
#include <utility>

using namespace std;

const int INF = INT_MAX;

typedef struct Node {
    Node *parent;
    vector <pair<Node *, int>> neighbours;
    int val, dist;
} Node;

Node *newNode(int val) {
    Node *n = new Node;
    n->val = val;
    n->dist = INF;
    n->parent = NULL;
}

void addEdge(Node *u, Node *v, int w) {
    pair <Node *, int> edge(v, w);
    u->neighbours.push_back(edge);
}

void relax(Node *u, Node *v, int weight) {
    // put your code here
    if(u->dist+weight < v->dist){
    	v->dist=u->dist+weight;
    	v->parent=u;
	}
    
}

bool bellmann_ford(Node **nodes, int n, Node *start) {
    // put your code here
    start->dist=0;
    
    for(int k=0;k<n-1;k++){
    	for(int i=0;i<n;i++){
    		Node* u=nodes[i];
    		vector <pair <Node*,int>> nb=u->neighbours;
    		
    		for(int j=0;j<nb.size();j++){
    			Node* v=nb[j].first;
    			int w=nb[j].second;
				relax(u,v,w);
			}
		}
	}
    
    for(int i=0;i<n;i++){
    	Node* u=nodes[i];
    	vector <pair<Node*,int>> nb=u->neighbours;
    	for(int j=0;j<nb.size();j++){
    		Node* v=nb[j].first;
    		int weight=nb[j].second;
			if(v->dist > u->dist + weight){
    			return false;
			}
		}
	}
    
    return true;
}

int main() {
    int N, k, start, end;
    cin >> N >> k;
    Node *nodes[N];
    for (int i = 0; i < N; i++) nodes[i] = newNode(i);

    for (int i = 0; i < k; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        addEdge(nodes[u], nodes[v], w);
    }

    cin >> start >> end;
    if (!bellmann_ford(nodes, N, nodes[start])) cout << "CYKL" << endl;
    else if (nodes[end]->dist < INF) cout << nodes[end]->dist << endl;
    else cout << "NIE" << endl;

    for(int i=0; i<N; i++) delete nodes[i];
}
