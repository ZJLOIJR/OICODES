#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int M = 5e4 + 7, L = 57;

int m, k, l, n, cnt = 0, tot = 0, ans = 0;
int st[M * L / 2], to[M * L / 2], nx[M * L / 2], id[M * L / 2], pos[M * L / 2], w1[M * L / 2], w2[M * L / 2], vis[M * L / 2];
int val[M * L / 2], son[M * L / 2][26];
char str[L];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void insert(char *s, int po)
{
	int now = 0;
	while (*s != '\0')
	{
		int num = *s - 'A';
		if (!son[now][num]) son[now][num] = ++cnt, add(cnt, now);
		now = son[now][num];
		s++;
	}
	val[now]++, id[po] = now;
}

int getw(int x)
{
	if (~w2[x]) return w2[x];
	w2[x] = val[x];
	for (int i = st[x]; i; i = nx[i]) w2[x] += getw(to[i]);
	return w2[x];
}

int dfs(int x)
{
	if (vis[x]) return 0;
	vis[x] = 1; int ret = val[x];
	for (int i = st[x]; i; i = nx[i]) ret += dfs(to[i]);
	return ret;
}

void init()
{
	scanf("%d%d%d%d", &m, &k, &l, &n);
	for (int i = 1; i <= m; i++)
	{
		scanf("%s", str);
		insert(str, i);
	}
}

void solve()
{
	memset(w2, 0xff, sizeof(w2));
	for (int i = 1; i <= m; i++) w1[i] = getw(id[i]);
	for (int i = 1; i <= m; i++) pos[i] = i;
	sort(pos + 1, pos + m + 1, [](int x, int y) { return w1[x] > w1[y]; });
	memset(w1, 0, sizeof(w1));
	for (int i = 1; i <= m; i++) w1[i] = dfs(id[pos[i]]);
	sort(w1 + 1, w1 + m + 1);
	for (int i = m; i >= m - n + 1; i--) ans += w1[i];
	printf("%d\n", ans);
}

int main()
{
	init();
	solve();
	return 0;
}
