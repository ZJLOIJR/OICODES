#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7, M = N << 1;

int n, m;
int tot = 0, st[N], to[M], nx[M], len[M], out[N], rd[N];
int arr[N], sta[N], top;
double f[N];

inline void add(int u, int v, int w) { out[u]++, rd[v]++, to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, u, v, w; i <= m; i++) scanf("%d%d%d", &u, &v, &w), add(u, v, w);
	for (int i = 1; i <= n; i++) if (!rd[i]) sta[++top] = i;
	while (top)
	{
		int u = sta[top--];
		arr[++arr[0]] = u;
		for (int i = st[u]; i; i = nx[i])
		{
			rd[to[i]]--;
			if (!rd[to[i]]) sta[++top] = to[i];
		}
	}
	for (int i = arr[0]; i; i--)
	{
		int u = arr[i];
		for (int i = st[u]; i; i = nx[i]) f[u] += (1.0 / out[u]) * (f[to[i]] + len[i]);
	}
	printf("%.2lf\n", f[1]);
	return 0;
}
