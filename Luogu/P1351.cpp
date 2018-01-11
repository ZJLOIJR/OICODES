#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 200007, P = 10007;

int n, u, v, tot = 0, anssum = 0, ansmax = 0;
int st[N], to[N << 1], nx[N << 1];
int w[N];

inline void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

void init()
{
	n = read();
	for (int i = 1; i <= n - 1; i++)
		u = read(), v = read(), add(u, v), add(v, u);
	for (int i = 1; i <= n; i++)
		*(w + i) = read();
}

void solve()
{
	for (int t = 1; t <= n; t++)
	{
		for (int i = st[t]; i; i = nx[i])
		{
			int u = to[i];
			for (int j = nx[i]; j; j = nx[j])
			{
				int v = to[j];
				if (w[u] * w[v] > ansmax)
					ansmax = w[u] * w[v];
				anssum = (anssum + w[u] * w[v]) % P;
			}
		}
	}
	printf("%d %d\n", ansmax, anssum * 2 % P);
}

int main()
{
	init();
	solve();
	return 0;
}
