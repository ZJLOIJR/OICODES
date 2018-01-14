#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 100007, INF = 2147483647;

struct SplayTree
{
	int root, tot;
	int son[N][2], fa[N], siz[N], key[N], tim[N];

	void init() { root = tot = 0; }
	int get(int x) { return x == son[fa[x]][1]; }
	void update(int x) { if (x) siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }

	void rotate(int x)
	{
		int y = fa[x], z = fa[y], kind = !get(x);
		son[y][!kind] = son[x][kind];
		if (son[x][kind]) fa[son[x][kind]] = y;
		fa[x] = z;
		if (z) son[z][get(y)] = x;
		son[x][kind] = y, fa[y] = x;
		update(y), update(x);
	}

	void splay(int x, int anc)
	{
		while (fa[x] != anc)
		{
			int y = fa[x];
			if (fa[y] == anc)
				rotate(x);
			else
				rotate(get(x) == get(y) ? y : x);
		}
		if (anc == 0)
			root = x;
	}

	void insert(int x)
	{
		if (!root)
			root = ++tot, son[root][0] = son[root][1] = 0, fa[root] = 0, siz[root] = 1, key[root] = x, tim[root] = 1;
		else
		{
			int now = root;
			while (1)
			{
				siz[now]++;
				if (x == key[now]) { tim[now]++; splay(now, 0); return; }
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, son[tot][0] = son[tot][1] = 0, fa[tot] = now, siz[tot] = 1, key[tot] = x, tim[root] = 1;
					break;
				}
				now = son[now][x > key[now]];
			}
			splay(tot, 0);
		}
	}

	int getpre(int x)
	{
		splay(x, 0);
		int now = son[x][0];
		while (son[now][1]) now = son[now][1];
		splay(now, 0);
		return now;
	}
	
	int getnext(int x)
	{
		splay(x, 0);
		int now = son[x][1];
		while (son[now][0]) now = son[now][0];
		splay(now, 0);
		return now;
	}

	int qrykth(int k)
	{
		int now = root, cnt;
		while (1)
		{
			cnt = siz[son[now][0]];
			if (cnt == k - 1) return key[now];
			else if (cnt < k - 1) now = son[now][1], k -= cnt + 1;
			else now = son[now][0];
		}
	}

	int findx(int x)
	{
		int now = root;
		while (1)
		{
			if (now == 0) return -1;
			if (key[now] == x) return now;
			now = son[now][x > key[now]];
		}
	}

	int qryrank(int x)
	{
		int now = root, ret = 0, y;
		while (1)
		{
			y = now;
			if (now == 0) return ret;
			if (x > key[now]) ret += siz[son[now][0]] + 1;
			now = son[now][x > key[now]];
		}
		splay(y, 0);
	}

	void erase(int x)
	{
		int k = findx(x);
		if (k == -1) return;
		int a = getpre(k), b = getnext(k);
		splay(a, 0);
		splay(b, a);
		tim[son[son[root][1]][0]]--;
		if (!tim[son[son[root][1]][0]]) son[son[root][1]][0] = 0;
	}
} tree;

int main()
{
	freopen("IN", "r", stdin);
	freopen("OUT", "w", stdout);
	int opt, x, q;
	tree.init();
	tree.insert(INF), tree.insert(-INF);
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 1) tree.insert(x);
		else if (opt == 2) tree.erase(x);
		else if (opt == 3) printf("%d\n", tree.qryrank(x));
		else if (opt == 4) printf("%d\n", tree.qrykth(x + 1));
		else if (opt == 5)
		{
			tree.insert(x);
			printf("%d\n", tree.key[tree.getpre(tree.findx(x))]);
			tree.erase(x);
		}
		else
		{
			tree.insert(x);
			printf("%d\n", tree.key[tree.getnext(tree.findx(x))]);
			tree.erase(x);
		}
	}
	return 0;
}
