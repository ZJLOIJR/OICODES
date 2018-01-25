#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 10007, M = 20007;

int n, k, m, l, r, mid, ans;
struct edge { int from, to, len1, len2; } E[M];
int fa[N];

inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
inline void fainit() { for (int i = 1; i <= n; i++) fa[i] = i; }

int check(int val)
{
	fainit(); int cnt = 0, i;
	sort(E + 1, E + m + 1, [](edge x, edge y){ return x.len1 < y.len1; });
	for (i = 1; i <= m; i++)
	{
		int u = getfa(E[i].from), v = getfa(E[i].to);
		if (u != v && E[i].len1 <= val)
			fa[v] = u, cnt++;
		if (cnt == k) break;
	}
	if (cnt == n - 1) return 1;
	if (cnt < k) return 0;
	sort(E + i + 1, E + m + 1, [](edge x, edge y){ return x.len2 < x.len2; });
	for (i = i + 1; i <= m; i++)
	{
		int u = getfa(E[i].from), v = getfa(E[i].to);
		if (u != v && E[i].len2 <= val)
			fa[v] = u, cnt++;
		if (cnt == n - 1) break;
	}
	return cnt == n - 1;
}

void init()
{
	scanf("%d%d%d", &n, &k, &m);
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d%d", &E[i].from, &E[i].to, &E[i].len1, &E[i].len2);
}

void solve()
{
	l = 0, r = 3e4;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}