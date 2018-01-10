#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1007, M = 100007;

int n, m, u, v, cnt = 0;
int fa[N];
struct way { int from, to, len; } E[M];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", &E[i].from, &E[i].to, &E[i].len);
	sort(E + 1, E + m + 1, [](way x, way y){ return x.len < y.len; } );
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
	{
		int u = getfa(E[i].from), v = getfa(E[i].to);
		if (u != v)
			fa[v] = u, cnt++;
		if (cnt == n - 1)
		{
			printf("%d\n", E[i].len);
			return 0;
		}
	}
	printf("-1\n");
	return 0;
}
