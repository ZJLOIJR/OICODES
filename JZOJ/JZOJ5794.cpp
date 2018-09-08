#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e3 + 7, M = 3e3 + 7;

int n, m, maxlen, minl;
struct edge { int from, to, l, r; } E[M];

int fa[N];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

int check(int l, int len)
{
	for (int i = 1; i <= n; i++) fa[i] = i;
	for (int i = 1; i <= m; i++)
		if (E[i].l <= l && E[i].r >= l + len - 1)
			fa[getfa(E[i].from)] = getfa(E[i].to);
	if (getfa(1) == getfa(n)) return 1;
	return 0;
}

void work(int val)
{
	int l = 0, r = 1e6, mid, ans = -1;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(val, mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	if (ans == -1) return;
	if (ans == maxlen) minl = min(minl, val);
	if (ans > maxlen) maxlen = ans, minl = val;
}

int main()
{
	freopen("travel.in", "r", stdin);
	freopen("travel.out", "w", stdout);
	
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) scanf("%d%d%d%d", &E[i].from, &E[i].to, &E[i].l, &E[i].r);
	for (int i = 1; i <= m; i++) work(E[i].l);
	printf("%d\n", maxlen);
	for (int i = minl; i <= minl + maxlen - 1; i++) printf("%d ", i);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
