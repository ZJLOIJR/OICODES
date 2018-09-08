#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 5e3 + 7, M = 6e3 + 7, K = 10, INF = 0x3f3f3f3f;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

int n, m, k, tot = 0, st[N], to[M], nx[M], val[M], keys[N];
int ans, full, f[1 << K][N];

int main()
{
	freopen("room.in", "r", stdin);
	freopen("room.out", "w", stdout);

	n = read(), m = read(), k = read();
	for (int i = 1, a; i <= n; i++) for (int j = 1; j <= k; j++) a = read(), keys[i] |= (a << (j - 1));
	for (int i = 1, u, v, a; i <= m; i++)
	{
		u = read(), v = read();
		to[++tot] = v, nx[tot] = st[u], st[u] = tot;
		for (int j = 1; j <= k; j++) a = read(), val[tot] |= (a << (j - 1));
	}
	memset(f, 0x3f, sizeof(f));
	if (!k)
	{
		f[0][1] = 0;
		for (int s = 0; s <= 233; s++)
			for (int i = 1; i <= n; i++)
				for (int j = st[i]; j; j = nx[j])
					f[0][to[j]] = min(f[0][to[j]], f[0][i] + 1);
		if (f[0][n] == INF) printf("No Solution\n");
		else printf("%d\n", f[0][n]);
	}
	else
	{
		full = (1 << k) - 1;
		f[keys[1]][1] = 0;
		for (int s = 0; s <= full; s++)
			for (int i = 1; i <= n; i++)
				if (((s & keys[i]) == keys[i]) && f[s][i] != INF)
					for (int j = st[i]; j; j = nx[j])
						if ((s & val[j]) == val[j])
							f[s | keys[to[j]]][to[j]] = min(f[s | keys[to[j]]][to[j]], f[s][i] + 1);
		ans = INF;
		for (int s = 0; s <= full; s++) ans = min(ans, f[s][n]);
		if (ans == INF) printf("No Solution\n");
		else printf("%d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
