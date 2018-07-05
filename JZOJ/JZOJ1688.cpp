#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int min(int a, int b) { return a < b ? a : b; }

const int N = 2e5 + 7;

int n, q, a;

int tot, root, son[N][2], fa[N], mi[N], val[N], siz[N];
void init()
{
	mi[0] = val[0] = 0x3f3f3f3f, tot = 2, root = 1, son[1][1] = 2, fa[2] = 1, val[1] = val[2] = 0x3f3f3f3f, siz[1] = 2, siz[2] = 1;
}
void upd(int x)
{
	siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
	mi[x] = min(val[x], min(mi[son[x][0]], mi[son[x][1]]));
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = (son[y][1] == x);
	son[y][k] = son[x][!k]; if (son[x][!k]) fa[son[x][!k]] = y;
	son[x][!k] = y, fa[y] = x;
	fa[x] = z; if (z) son[z][son[z][1] == y] = x;
	upd(y), upd(x);
}
void splay(int x, int anc)
{
	for (int y, z; (y = fa[x]) != anc; rotate(x))
	{
		z = fa[y];
		if (z == anc) continue;
		rotate((son[z][1] == y) == (son[y][1] == x) ? y : x);
	}
	if (!anc) root = x, upd(x);
}
int findkth(int k)
{
	int now = root;
	while (1)
	{
		if (k > siz[son[now][0]] + 1) k -= siz[son[now][0]] + 1, now = son[now][1];
		else if (k <= siz[son[now][0]]) now = son[now][0];
		else return now;
	}
}
void insert(int po, int v)
{
	int x = findkth(po + 1), y = findkth(po + 2);
	splay(x, 0), splay(y, x);
	son[y][0] = ++tot, fa[tot] = y, siz[tot] = 1, mi[tot] = val[tot] = v;
	int now = y;
	while (now) upd(now), now = fa[now];
	splay(tot, 0);
}
int qrymin(int l, int r)
{
	int x = findkth(l), y = findkth(r + 2);
	splay(x, 0), splay(y, x);
	return mi[son[y][0]];
}

int main()
{
	n = read();
	init();
	for (int i = 1; i <= n; i++) a = read(), insert(i - 1, a);
	q = read();
	while (q--)
	{
		char ch;
		int a, b;
		scanf(" %c", &ch), a = read(), b = read();
		if (ch == 'Q') printf("%d\n", qrymin(a, b));
		else insert(a, b);
	}	
	return 0;
}
