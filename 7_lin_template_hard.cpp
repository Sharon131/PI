#include <stdio.h>
// http://www.cplusplus.com/reference/list/list/#functions
#include <list>

using namespace std;

int n;
list<int> *graph;
int curr_line;
list<int> *lines;
bool is_euler;


void euler(int u)
{
    while (!graph[u].empty())
    {
        int v = *graph[u].begin();

        // iterate over neighbours of v
        for (list<int>::iterator it = graph[v].begin();it!=graph[v].end();it++)
        {
            // if you find u remove it from list
            if (*it==u)
            {
                graph[v].erase(it);
                break;
				// use erase method
            }
        }
		graph[u].pop_front();
        euler(v);
    }

    // if we're visiting our dummy city, start a new line
    if (!is_euler && u==n+1) {	
        curr_line++;
    } else {
        // if not, just add city to current line
        lines[curr_line].push_front(u);
    }

}

int main() {
    int Z;

    scanf("%d", &Z);

    while (Z--) {
        int m, u, v;
        scanf("%d %d", &n, &m);

        graph = new list<int>[n+2];
        lines = new list<int>[n+2];

        for(int i=0; i<m; i++) {
            scanf("%d %d", &u, &v);
            graph[u].push_back(v);
            graph[v].push_back(u);
        }
        
        is_euler = true;
        for (int i = 1; i <= n; i++)
        {
            // add dummy city to each city that has odd number of neighbours
            if (graph[i].size()%2==1){
                graph[i].push_back(n+1);
            	graph[n+1].push_back(i);
        		is_euler = false;
            }
        }

        curr_line = 0;

        if (is_euler) {
            // start euler from any city            
            euler(1);
        } else {
            // start euler from dummy city
            euler(n+1);
        }

        // ignore empty lines
        int lines_number = 0;
        for (int i = 0; i <= curr_line; i++)
        {
            if (lines[i].size()>1)
                lines_number++;
        }

        printf("%d\n", lines_number);

        for (int i = lines_number; i>=0; i--)
        {
            if (lines[i].size() > 1)
            {
                printf("%lu ", lines[i].size());
                for (list<int>::iterator it = lines[i].begin(); it != lines[i].end(); it++)
                {
                    printf("%d ", *it);
                }
                printf("\n");
            }
        }

        delete[] graph;
        delete[] lines;
    }
}
