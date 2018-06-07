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
    
	int** rank=new int*[n];
	square** parent=new square*[n];
	for(int i=0;i<n;i++){				//inicjowanie tablicy parentów jako wspó³ na niego.
		parent[i]=new square[n];		//Oraz tablicy rz¹dów dla odpowiednich wêz³ów
		rank[i]=new int[n];
		for(int j=0;j<n;j++){
			rank[i][j]=0;
			parent[i][j].x=i;
			parent[i][j].y=j;
			parent[i][j].d=map[i][j];
		}
	}
	
	priority_queue<square> Q;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			square aux;
			aux.x=i;
			aux.y=j;
			aux.d=map[i][j];
			Q.push(aux);
		}
	}
	
	square start=parent[0][0];
	square end=parent[n-1][n-1];
	square u=Q.top();
	Q.pop();
	bool decr=false;
	int count=0;
	while(!Q.empty() && !(find(start,parent)==find(end, parent))){
		square v=Q.top();
		Q.pop();
		
		if(v.d<k){
			count+=k-v.d;
			k=v.d;
		}
		Union(u,v, parent, rank);
	}
	return count;
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
