#include <cstdio>
#include <algorithm>

const int N = 3e2 + 7, M = N * N;

int n, w, tot = 0, ans = 0, fa[N];
struct edge { int from, to, len; } a[M];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &w), a[++tot].from = n + 1, a[tot].to = i, a[tot].len = w, fa[i] = i;
	fa[n + 1] = n + 1;
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			scanf("%d", &w);
			if (i != j) a[++tot].from = i, a[tot].to = j, a[tot].len = w;
		}
	std::sort(a + 1, a + tot + 1, [](edge x, edge y){ return x.len < y.len; });
	for (int i = 1, cnt = 0; i <= tot; i++)
	{
		int u = getfa(a[i].from), v = getfa(a[i].to);
		if (u != v) fa[v] = u, ans += a[i].len, cnt++;
		if (cnt == n) break;
	}
	printf("%d\n", ans);
	return 0;
}
