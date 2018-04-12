#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e5 + 3;

int root, tot = 0, q, opt, x;
struct SplayTree
{
	int key[N], son[N][2], fa[N], siz[N], cnt[N];
	void upd(int x) { siz[x] = siz[son[x][0]] + siz[son[x][1]] + cnt[x]; }
	int get(int x) { return son[fa[x]][1] == x; }
	void rotate(int x)
	{
		int y = fa[x], z = fa[y], k = get(x);
		son[y][k] = son[x][!k]; if (son[x][!k]) fa[son[x][!k]] = y;
		son[x][!k] = y, fa[y] = x;
		fa[x] = z; if (z) son[z][son[z][1] == y] = x;
		upd(y);
	}
	void splay(int x, int anc)
	{
		for (int y, z; (y = fa[x]) != anc; rotate(x))
		{
			z = fa[y];
			if (z == anc) continue;
			rotate(get(x) == get(y) ? y : x);
		}
		if (!anc) root = x, upd(x);
	}
	void insert(int x)
	{
		int y = 0, now = root;
		while (now && key[now] != x) { y = now; now = son[now][x > key[now]]; }
		if (now) cnt[now]++;
		else
		{
			now = ++tot;
			siz[now] = cnt[now] = 1, key[now] = x, fa[now] = y;
			if (y) son[y][x > key[y]] = now;
		}
		splay(now, 0);
	}
	void find(int x)
	{
		if (!root) return;
		int now = root;
		while (son[now][x > key[now]] && key[now] != x) now = son[now][x > key[now]];
		splay(now, 0);
	}
	int getrank(int x)
	{
		find(x);
		return siz[son[root][0]];
	}
	int getkth(int k)
	{
		if (k > siz[root]) return 0;
		int now = root, tmp;
		while (1)
		{
			tmp = son[now][0];
			if (siz[tmp] + cnt[now] < k)
			{
				k -= siz[tmp] + cnt[now];
				now = son[now][1];
			}
			else if (siz[tmp] >= k) now = tmp;
			else return key[now];
		}
	}
	int getnex(int x, int k)
	{
		find(x);
		if (((key[root] > x) && k) || ((key[root] < x) && !k)) return root;
		int now = son[root][k];
		while (son[now][!k]) now = son[now][!k];
		return now;
	}
	void del(int x)
	{
		int pre = getnex(x, 0), nex = getnex(x, 1);
		splay(pre, 0), splay(nex, pre);
		int tmp = son[nex][0];
		if (cnt[tmp] > 1) cnt[tmp]--, splay(tmp, 0);
		else son[nex][0] = 0;
	}
} tree;

int main()
{
	scanf("%d", &q);
	tree.insert(-0x7f7f7f7f), tree.insert(0x7f7f7f7f);
	while (q--)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 1) tree.insert(x);
		else if (opt == 2) tree.del(x);
		else if (opt == 3) printf("%d\n", tree.getrank(x));
		else if (opt == 4) printf("%d\n", tree.getkth(x + 1));
		else if (opt == 5) printf("%d\n", tree.key[tree.getnex(x, 0)]);
		else if (opt == 6) printf("%d\n", tree.key[tree.getnex(x, 1)]);
	}
	return 0;
}

//5632 3922
//https://blog.csdn.net/gengmingrui/article/details/49978543
