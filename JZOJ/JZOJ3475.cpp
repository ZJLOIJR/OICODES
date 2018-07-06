#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 7;

int c;

int root, tot, son[N][2], fa[N], siz[N], rev[N], val[N];
void swap(int &a, int &b) { int t = a; a = b, b = t; }
void init()
{
	root = 1, tot = 2
}
void upd(int x)
{
	siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
	if (!rev[x] || !x) return;
	swap(son[x][0], son[x][1]), rev[son[x][0]] ^= 1, rev[son[x][1]] ^= 1, rev[x] = 0;
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = (son[y][1] == x);
	son[y][k] = son[x][!k]; if (son[x][!k]) fa[son[x][!k]] = y;
	son[x][!k] = y, fa[y] = x, fa[x] = z;
	if (z) son[z][son[z][1] == y] = x;
}
void splay(int x, int anc)
{
	for (int y, z; (y = fa[x]) != anc; rotate(x))
	{
		z = fa[y];
		if (z == anc) continue;
		rotate((son[z][1] == y) == (son[y][1] == x) ? y : x);
	}
	if (!anc) root = x;
}

int main()
{
	return 0;
}
