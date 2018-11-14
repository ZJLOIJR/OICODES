#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 50007;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, a[N], b[N], c[N];

int tot, st[N], to[N << 1], nx[N << 1], len[N << 1];
void add(int u, int v, int w) { to[++tot] = v, nx[tot] = st[u], len[tot] = w, st[u] = tot; }

int main()
{
	//freopen("track.in", "r", stdin);
	//freopen("track.out", "w", stdout);
	freopen("input", "r", stdin);

	n = read(), m = read();
	for (int i = 1; i < n; i++) a[i] = read(), b[i] = read(), c[i] = read(), add(a[i], b[i], c[i]), add(b[i], a[i], c[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
