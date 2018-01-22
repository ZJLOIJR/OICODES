#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 300007;

int n, m, u, v, w, tot = 0;
int st[N], nx[N << 1], to[N << 1], len[N << 1], tmp[N << 1], from[N], get[N], fa[N][2], dep[N];
int l, r, mid, ans;

void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline void swap(int& a, int& b) { int t = a; a = b, b = t; }

void dfs(int x)
{
	for (int i = st[x]; i; i = nx[i])
	{
		int v = to[i];
		if (v != fa[x][0])
			fa[v][0] = x, fa[v][1] = i, dep[v] = dep[x] + 1, dfs(v);
	}
}

int check(int val)
{
	memcpy(tmp, len, sizeof(len));
	int cnt = 0;
	for (int i = 1; i <= m; i++)
	{
		int u = from[i], v = get[i], ret = 0;
		if (dep[u] < dep[v]) swap(u, v);
		while (dep[u] > dep[v])
		{
			if (ret + tmp[fa[u][1]] > val)
			{ cnt++, tmp[fa[u][1]] = 0; if (cnt > 1) return 0; }
			ret += tmp[fa[u][1]];
			u = fa[u][0];
		}
		if (u == v) continue;
		while (u != v)
		{
			if (ret + tmp[fa[u][1]] > val)
			{ cnt++, tmp[fa[u][1]] = 0; if (cnt > 1) return 0; }
			ret += tmp[fa[u][1]];
			if (ret + tmp[fa[v][1]] > val)
			{ cnt++, tmp[fa[v][1]] = 0; if (cnt > 1) return 0; }
			ret += tmp[fa[v][1]];
			u = fa[u][0], v = fa[v][0];
		}
	}
	return 1;
}

int main()
{
	freopen("transport.in", "r", stdin);
	freopen("transport.out", "w", stdout);

	n = read(), m = read();
	for (int i = 1; i <= n - 1; i++) u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w);
	dep[1] = 1, fa[1][0] = fa[1][1] = 0, dfs(1);
	for (int i = 1; i <= m; i++) *(from + i) = read(), *(get + i) = read();
	l = 0, r = 3e6;
	while (l <= r)
	{
		mid = l + r >> 1;
		if (check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}