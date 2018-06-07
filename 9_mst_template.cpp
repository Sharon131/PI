#include <cstdio>
#include <queue>

using namespace std;

struct edge
{
    int u, v;
    int s;
};

bool operator< (edge a, edge b)
{
    if (a.s > b.s)
        return true;
    else
        return false;
}


int find (int x, int* parent)
{
    if(parent[x]!=x){
    	parent[x]=find(parent[x], parent);
		return parent[x];
	}
	return x;
}

bool Union(int x, int y, int* parent)
{
    x=find(x,parent);
    y=find(y,parent);

	if(y==x) return false;
	
	parent[y]=x;
	
	return true;
}

unsigned long long mst(priority_queue<edge> Q, int n)
{
    unsigned long long cost = 0;
    int *parent = new int[n+1];
    
    for (int i = 0; i <= n; i++) {
        parent[i] = i;
    }
	
    while(!Q.empty()){
		edge u=Q.top();
    	Q.pop();
    	int x=u.u;
    	int y=u.v;
		if(Union(x,y,parent)){
			cost+=u.s;
		}	
	}

    return cost;
}

int main ()
{
    int Z;
    scanf("%d", &Z);
    while(Z--)
    {
        int n, m;
        scanf ("%d %d", &n, &m);

        priority_queue<edge> Q;

        for (int i = 0; i < m; i++)
        {
            edge temp;
        	int u, v, s;
			scanf("%d %d %d", &u, &v, &s);
        	temp.s=s;
        	temp.u=u;
        	temp.v=v;
        	Q.push(temp);						//??????
		}

        unsigned long long cost = mst(Q, n);

        printf ("%llu\n", cost);
    }
}
