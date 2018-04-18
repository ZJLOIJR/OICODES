#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 3, INF = 0x3f3f3f3f;

void swap(int &a, int &b) { int t = a; a = b, b = t; }

int root, tot = 0, n, q, l, r;
struct SplayTree
{
	int fa[N], son[N][2], rev[N], key[N], siz[N];

	void down(int x)
	{
		if (!rev[x] || !x) return;
		swap(son[x][0], son[x][1]);
		rev[x] = 0, rev[son[x][0]] ^= 1, rev[son[x][1]] ^= 1;
	}
	void upd(int x) { siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }
	void rotate(int x)
	{
		int y = fa[x], z = fa[y], k = (son[y][1] == x);
		son[y][k] = son[x][!k];
		if (son[x][!k]) fa[son[x][!k]] = y;
		son[x][!k] = y, fa[y] = x, fa[x] = z;
		if (z) son[z][son[z][1] == y] = x;
		down(y), down(x), upd(y), upd(x);
	}
	void splay(int x, int anc)
	{
		for (int y, z; (y = fa[x]) != anc; rotate(x))
		{
			z = fa[y];
			if (z == anc) continue;
			rotate((son[y][0] == x) == (son[z][0] == y) ? y : x);
		}
		if (!anc) root = x;
	}
	void insert(int x)
	{
		int now = root, y = 0;
		while (now && key[now] != x) { y = now, now = son[now][x > key[now]]; }
		now = ++tot;
		fa[now] = y, key[now] = x, siz[now] = 1;
		if (y) son[y][x > key[y]] = now;
		splay(now, 0);
	}
	int getkth(int k)
	{
		if (k > siz[root]) return 0;
		int now = root, tmp;
		while (1)
		{
			down(now);
			tmp = son[now][0];
			if (siz[tmp] + 1 < k) k -= siz[tmp] + 1, now = son[now][1];
			else if (siz[tmp] >= k) now = tmp;
			else return now;
		}
	}
	void reverse(int l, int r)
	{
		int lx = getkth(l), rx = getkth(r + 2);
		splay(lx, 0), splay(rx, lx);
		rev[son[rx][0]] ^= 1;
	}
	void print(int x)
	{
		if (!x) return;
		down(x);
		print(son[x][0]);
		if (key[x] != INF && key[x] != -INF) printf("%d ", key[x]);
		print(son[x][1]);
	}
} tree;

int main()
{
	scanf("%d%d", &n, &q);
	tree.insert(-INF);
	for (int i = 1; i <= n; i++) tree.insert(i);
	tree.insert(INF);
	while (q--)
	{
		scanf("%d%d", &l, &r);
		tree.reverse(l, r);
	}
	tree.print(root);
	return 0;
}
