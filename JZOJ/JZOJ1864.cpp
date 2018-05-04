#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 2e4 + 3, M = 1e5 + 3;

int n, m;
int fa[N << 1];
struct edge { int u, v, w; } edg[M];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n * 2; i++) fa[i] = i;
	for (int i = 1; i <= m; i++) scanf("%d%d%d", &edg[i].u, &edg[i].v, &edg[i].w);
	sort(edg + 1, edg + m + 1, [](edge x, edge y){ return x.w > y.w; });
	for (int i = 1; i <= m; i++)
	{
		int u = getfa(edg[i].u), v = getfa(edg[i].v);
		if (u == v) { printf("%d\n", edg[i].w); return 0; }
		fa[u] = getfa(edg[i].v + n), fa[v] = getfa(edg[i].u + n);
	}
	printf("0\n");
	return 0;
}
