#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e5 + 3;

inline int max(int a, int b) { return a > b ? a : b; }

int tot, root = 0, n, q;
char opt;
struct SplayTree
{
	int inc[N], mx[N], key[N], son[N][2], fa[N], siz[N];
	void upd(int x) { mx[x] = max(mx[son[x][0]], mx[son[x][1]]) + inc[x], inc[x] = 0, siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }
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
			rotate((son[z][0] == y) == (son[y][0] == x) ? y : x);
		}
		if (!anc) root = x, upd(x);
	}
	void find(int x)
	{
		if (!root) return;
		int now = root;
		while (son[now][x > key[now]] && key[now] != x) now = son[now][x > key[now]];
		splay(now, 0);
	}
	void insert(int x)
	{
		int y = 0, now = root;
		while (now) { y = now, now = son[now][x > key[now]]; }
		if (!now)
		{
			now = ++tot;
			mx[now] = x, key[now] = tot, fa[now] = y, siz[now] = 1;
			if (y) son[y][x > key[y]] = now;
		}
		splay(now, 0);
	}
	int getkth(int k)
	{
		if (k > siz[root]) return;
		int now = root, tmp;
		while (1)
		{
			tmp = son[now][0];
			if (siz[tmp] + 1 < k)
			{
				k -= siz[tmp] + 1;
				now = son[now][1];
			}
			else if (siz[tmp] >= k) now = tmp;
			else return now;
		}
	}
	void change(int l, int r, int k)
	{
		int lx = getkth(l), rx = getkth(r + 2);
		splay(lx, 0), splay(rx, lx);
		inc[son[rx][0]] += k;
	}
	void del(int l, int r)
	{
		int lx = getkth(l), rx = getkth(r + 2);
		splay(lx, 0), splay(rx, lx);
		son[rx][0] = 0, upd(rx);
	}
	int getmax(int l, int r)
	{
		int lx = getkth(l), rx = getkth(r + 2);
		splay(lx, 0), splay(rx, lx);
		upd(son[rx][0]);
		return mx[son[rx][0]];
	}
} tree;

int main()
{
	return 0;
}
