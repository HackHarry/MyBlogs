#include <cstdio>
#include <cstring>
#include <iostream>
#include <set>
#include <queue>
#include <vector>
#include <stack>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <time.h>
#define ll long long
#define maxn 205
#define exp 0.0001
using namespace std;

char x[maxn];
char y[maxn];
int dp[maxn][maxn];
int lenx, leny;

int main() {
	while(scanf("%s %s", x+1, y+1) == 2) {
		memset(dp, 0, sizeof(dp));
		lenx = strlen(x+1);
		leny = strlen(y+1);
		for(int i = 1; i <= lenx; i++) {
			for(int j = 1; j <= leny; j++) {
				if(x[i] == y[j]) dp[i][j] = dp[i-1][j-1] + 1;
				else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
			}
		}
		printf("%d\n", dp[lenx][leny]);
	}
	return 0;
}