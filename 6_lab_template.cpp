#include <iostream>
using namespace std;

typedef struct point {
    int x, y;
} point;

typedef struct neighbours {
    int n;
    point* elems[4];
} neighbours;

neighbours get_neighbours(int** labyrinth, int n, int m, point* p) {
    // find (if exist) all neighbours of point p
        // (consider points: one above p, one below p, one on the left site and one on the right site)
    // use defined structures
    neighbours nb;
    if(p->y==0 || labyrinth[p->x][p->y-1]==0){
    	nb.elems[0]=NULL;
	}
	else{
		nb.elems[0]=new point;
		nb.elems[0]->x=p->x;
		nb.elems[0]->y=p->y-1;
	}
	if(p->y==m-1 || labyrinth[p->x][p->y+1]==0){
    	nb.elems[1]=NULL;
	}
	else{
		nb.elems[1]=new point;
		nb.elems[1]->x=p->x;
		nb.elems[1]->y=p->y+1;
	}
	if(p->x==0 || labyrinth[p->x-1][p->y]==0){
    	nb.elems[2]=NULL;
	}
	else{
		nb.elems[2]=new point;
		nb.elems[2]->x=p->x-1;
		nb.elems[2]->y=p->y;
	}
	if(p->x==n-1 || labyrinth[p->x+1][p->y]==0){
    	nb.elems[3]=NULL;
	}
	else{
		nb.elems[3]=new point;
		nb.elems[3]->x=p->x+1;
		nb.elems[3]->x=p->y;
	}
	return nb;
}

bool dfs(int** graph, int n, int m, bool** visited, point* p, point* end) {
    // if p is already at the end - return true
    if(p->x==end->x && p->y==end->y){
    	return true;
	}
    // mark p visited
    visited[p->x][p->y]=true;
    // call recursively on every unvisited neighbour
    neighbours nb=get_neighbours(graph,n,m,p);
	
	for(int i=0;i<4;i++){
		if(nb.elems[i]!=NULL && !visited[nb.elems[i]->x][nb.elems[i]->y] && dfs(graph,n,m,visited,nb.elems[i],end)){
			return true;	
		}
	}
    // if all calls finished fruitlessly - you didn't find exit
	return false;
}


int main() {
    int n, m;
    cin >> n;
    cin >> m;
    int **labyrinth = new int*[n];
    for(int i=0; i<n; i++) labyrinth[i] = new int[m];
    bool** visited = new bool*[n];
    for(int i=0; i<n; i++){
		visited[i] = new bool[m];
    	for(int j=0;j<m;j++){
    		visited[i][j]=false;
		}
	} 
    for(int i=0; i<n; i++) {
        for(int j=0; j<m; j++) {
            cin >> labyrinth[i][j];
        }
    }
    point start, end;
    cin >> start.x;
    cin >> start.y;
    cin >> end.x;
    cin >> end.y;
    
    if(labyrinth[start.x][start.y]==0 || labyrinth[end.x][end.y]==0){
    	cout << "NIE" << endl;
	}
	else{
		cout << (dfs(labyrinth, n, m, visited, &start, &end) ? "TAK" : "NIE") << endl;		
	}
	
	for(int i=0;i<n;i++){
		delete [] labyrinth[i];
		delete [] visited[i];
	}
	delete [] labyrinth;
	delete [] visited;
}
