/*
dijstra�㷨���Ż�ģ��
��Ŵ�1��n����Դ�޸�Ȩ���·�� 
*/
#include <bits/stdc++.h>
#define INF 99999999
#define maxn 101
using namespace std;  

int dist[maxn][maxn];
int length[maxn], f[maxn], pre[maxn];
int n, m;

void init()
{
	memset(pre, 0, sizeof(pre));
    memset(f, 0, sizeof(f));
    for(int i = 0; i < maxn; i++)
        for(int j = 0; j < maxn; j++)
            dist[i][j] = INF;
}//��ʼ�� 

void dijkstra(int v)
{
    for(int i = 1; i <= n; i++)
    	length[i] = dist[v][i];
    f[v] = 1;
    while(1)
    {
        int min = INF, k = -1;
        for(int j = 1; j <= n; j++)
            if(!f[j] && length[j] < min) 
			{
				min = length[j]; k = j;
			}
        if(k == -1) break;
		f[k] = 1;
		if(pre[k] == 0) pre[k] = 1;//���ܴ���bug 
        for(int j = 1; j <= n; j++)
            if(!f[j] && dist[k][j] < length[j] - min) 
			{
				length[j] = dist[k][j] + min;
				pre[j] = k;
			}
    }
}

void print_path(int v)
{
	if(v == 0) return;
	print_path(pre[v]);
	if(v == n) printf("%d\n", v);
	else printf("%d->", v); 
}//�ݹ����·�� 

int main()
{  
    while(~scanf("%d%d", &n, &m))
    {
        if(n + m == 0) break;//n��mΪ0ʱ�˳� 
        init();
        for(int i = 0; i < m; i++)
        {
            int x, y, d;
            scanf("%d %d %d", &x, &y, &d); 
            if(dist[x][y] > d) dist[x][y] = dist[y][x] = d;
        }
        dijkstra(1);
        if(length[n] < INF)
        {
        	printf("%d\n", length[n]);
        	print_path(n);
		}
        else printf("-1\n");
    }
    return 0;  
}
