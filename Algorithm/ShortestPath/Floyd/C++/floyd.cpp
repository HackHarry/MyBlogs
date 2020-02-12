#include <bits/stdc++.h>
#define INF 99999999
#define N 505 
using namespace std;  

int dist[N][N], tax[N], path[N][N];  
int n;  
  
void init()  
{  
    int i, j;  
    for(i = 1; i <= n; i++)  
        for(j = 1; j <= n; j++)  
            if(i == j) dist[i][j] = 0;  
            else dist[i][j] = INF;  
}  
  
void input()  
{  
    int i, j, k;  
    for(i = 1; i <= n; i++)  
        for(j = 1; j <= n; j++)  
        {  
            scanf("%d", &k);  
            if(k != -1) dist[i][j] = k;  
            path[i][j] = j;  
        }  
    for(i = 1; i <= n; i++)  
        scanf("%d", &tax[i]);  
}  
  
void floyd()  
{  
    int i, j, k, len;  
    for(k = 1; k <= n; k++)  
    {  
        for(i = 1; i <= n; i++)  
        {  
            for(j = 1; j <= n; j++)  
            {  
                len = dist[i][k] + dist[k][j] + tax[k];  
                if(dist[i][j] > len)  
                {  
                    dist[i][j] = len;  
                    path[i][j] = path[i][k]; 
                }  
                else if(len == dist[i][j])  
                {  
                    if(path[i][j] > path[i][k]) 
                        path[i][j] = path[i][k];  
                }  
            }  
        }  
    }  
}  
  
void output()  
{  
    int i, j, k;  
    while(scanf("%d %d", &i, &j))  
    {  
        if(i == -1 && j == -1) break;  
        printf("From %d to %d :\n", i, j);  
        printf("Path: %d", i);  
        k = i;  
        while(k != j)  
        {  
            printf("-->%d", path[k][j]);  
            k = path[k][j];  
        }  
        printf("\n");  
        printf("Total cost : %d\n\n", dist[i][j]);  
    }  
}  
  
int main()  
{  
    while(scanf("%d", &n), n)  
    {  
        init();  
        input();  
        floyd();  
        output();  
    }  
    return 0;  
}  
