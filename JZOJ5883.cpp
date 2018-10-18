#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 1e5 + 7;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int n, m, q;

int fa[N], buc[N];

int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }
void link(int u, int v)
{
	u = getfa(u), v = getfa(v);
	if (buc[u]) swap(u, v);
	fa[u] = v;
}

int lenq, qu[N], qv[N], ans[N];

int main()
{
	//freopen("arrival.in", "r", stdin);
	//freopen("arrival.out", "w", stdout);

	n = read(), m = read();
	for (int i = 1, x; i <= m; i++) x = read(), buc[x]++;
	for (int i = 1, u, v; i <= n - m; i++) u = read(), v = read(), link(u, v);
	q = read();
	while (q--)
	{
		int opt = read(), u = read(), v = read();
		if (opt == 1) link(v, u);
		else qu[++lenq] = u, qv[lenq] = v;
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
