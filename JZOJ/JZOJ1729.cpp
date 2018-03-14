#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 53;

struct Edge
{ int from, to, len; } edges[N];

int cnt = 0, ans = 0, enemy[N];
int n, fa[N], fa1[N];

inline int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= n - 1; i++)
		scanf("%d%d%d", &edges[i].from, &edges[i].to, &edges[i].len);
	sort(edges + 1, edges + n + 1, [](Edge x, Edge y){ return x.len > y.len; });
	while (~scanf("%d", &enemy[++cnt])); cnt--;
	for (int i = 1; i <= n - 1; i++)
	{
		memcpy(fa1, fa, sizeof(fa));
		fa[getfa(edges[i].to)] = getfa(edges[i].from);
		int flag = 1;
		for (int i = 1; i <= cnt - 1; i++)
		{
			for (int j = i + 1; j <= cnt; j++)
				if (getfa(enemy[i]) == getfa(enemy[j])) { flag = 0; break; }
			if (!flag) break;
		}
		if (!flag)
		{
			ans += edges[i].len;
			memcpy(fa, fa1, sizeof(fa1));
		}
	}
	printf("%d\n", ans);
	return 0;
}
