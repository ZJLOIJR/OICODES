#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100007;

int T, n, u, v, m1, m2, a, tot, sum1, sum2;
int st[N], to[N << 1], nx[N << 1], depth[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

inline void read(int& num)
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	num = f ? -x : x;
}

void dfs(int u, int from)
{
	for (int i = st[u]; i; i = nx[i])
	{
		int v = to[i];
		if (v != from)
			depth[v] = depth[u] + 1, dfs(v, u);
	}
}

void init()
{
	memset(st, 0, sizeof(st));
	memset(nx, 0, sizeof(nx));
	memset(to, 0, sizeof(to));
	memset(depth, 0, sizeof(depth));
	tot = 0;
	read(n), read(m1), read(m2);
	for (int i = 1; i <= n - 1; i++)
	{
		read(u), read(v);
		u++, v++;
		add(u, v), add(v, u);
	}
	dfs(1, 0);
}

void solve()
{
	sum1 = 0, sum2 = 0;
	for (int i = 1; i <= m1; i++)
		read(a), sum1 += depth[a + 1];
	for (int i = 1; i <= m2; i++)
		read(a), sum2 += depth[a + 1];
	if (sum1 <= sum2)
		printf("Bob\n");
	else
		printf("Alice\n");
}

int main()
{
	read(T);
	while (T--)
	{
		init();
		solve();
	}
	return 0;
}
