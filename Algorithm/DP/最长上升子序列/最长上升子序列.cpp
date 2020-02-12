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
#define maxn 1005
#define exp 0.0001
using namespace std;

int main() {
	int n; scanf("%d", &n);
	int a[maxn];
	int dp[maxn]; memset(dp, 0 , sizeof(dp));
	int maxnum = 0;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
		for(int j = 0; j < i; j++) {
			if(a[j] < a[i]) dp[i] = max(dp[i], dp[j]+1); 
		}
		maxnum = max(maxnum, dp[i]);
	} 
	printf("%d\n", maxnum+1);
	return 0;
}