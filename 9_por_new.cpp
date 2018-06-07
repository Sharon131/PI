#include <cstdio>
#include <queue>
#include<climits>
// #define DEBUG 1

using namespace std;

const int INF=INT_MAX;

struct square
{
    int x, y;
    int d;
};

bool operator==(square a,square b){
	if(a.x==b.x && a.y==b.y){
		return true;
	}
	return false;
}

bool operator< (square a, square b)
{
    if (a.d < b.d)
        return true;
    else
        return false;
}

void print_map(int **map, int n) {
    #ifdef DEBUG
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", map[i][j]);
        }
        printf("\n");
    }    
    printf("\n");
    #endif
}

square find (square point, square** parent)
{
    if(!(parent[point.x][point.y]==point)){
		parent[point.x][point.y]=find(parent[point.x][point.y], parent);
		return parent[point.x][point.y];
	}
	return point;
}

void Union (square x, square y, square** parent, int** rank)
{
    x=find(x,parent);
    y=find(y,parent);

	if(x==y) return;
	
	if(rank[x.x][x.y]>rank[y.x][y.y]){
		parent[y.x][y.y].x=x.x;	
		parent[y.x][y.y].y=x.y;
	}
	else{
		parent[x.x][x.y].x=y.x;	
		parent[x.x][x.y].y=y.y;
		if(rank[x.x][x.y]==rank[y.x][y.y]){
			rank[y.x][y.y]++;
		}	
	}
	
}

int draught_calculator(int **map, int n, int k) {
    
	square** parent=new square*[n];
	for(int i=0;i<n;i++){				
		parent[i]=new square[n];		
		for(int j=0;j<n;j++){
			parent[i][j].x=i;
			parent[i][j].y=j;
			parent[i][j].d=map[i][j];
		}
	}
	
	priority_queue<square> Q;
    bool **vis;
    vis=new bool*[n];
    for(int i=0;i<n;i++){
    	vis[i]=new bool[n];
    	for(int j=0;j<n;j++){
    		vis[i][j]=false;	
		}
	}
    vis[0][0]=true;
    
	Q.push(parent[0][0]);
    int depth=INT_MAX;
    while(Q.top().x!=n-1 || Q.top().y!=n-1){
		square current=Q.top();
    	Q.pop();
    	int x=current.x;
    	int y=current.y;
    	
		if(depth > current.d)	depth=current.d;
		
    	if(x < n-1 && !vis[x+1][y]){
    		vis[x+1][y]=true;
    		Q.push(parent[x+1][y]);
		}
		if(x > 0 && !vis[x-1][y]){
    		vis[x-1][y]=true;
    		Q.push(parent[x-1][y]);
		}
		if(y < n-1 && !vis[x][y+1]){
    		vis[x][y+1]=true;
    		Q.push(parent[x][y+1]);
		}
		if(y > 0 && !vis[x][y-1]){
    		vis[x][y-1]=true;
    		Q.push(parent[x][y-1]);
		}
	}
	if(depth > parent[n-1][n-1].d) depth=parent[n-1][n-1].d;
	
	for(int i=0;i<n;i++) delete[] vis[i];
	delete[] vis;
	
	if(k-depth >0){
		return k-depth;
	}
	return 0;
}

int main ()
{
    int Z;
    scanf("%d", &Z);
    while(Z--)
    {
        int n, k;
        scanf ("%d %d", &n, &k);
        int **map = new int*[n];
        for (int i = 0; i < n; i++)
            map[i] = new int[n];

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                scanf("%d", &map[i][j]);
            }
        }

        print_map(map, n);
        
        int result = draught_calculator(map, n, k);

        printf ("%d\n", result);

        for (int i = 0; i < n; i++)
            delete[] map[i];
        delete[] map;

    }
}
