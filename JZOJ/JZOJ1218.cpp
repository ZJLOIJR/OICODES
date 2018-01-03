#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 200007;

int n;

struct SplayTree
{
	int fa[N], son[N][2], key[N], siz[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void update(int x)
	{
		siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
	}

	void rotate(int x, int kind)
	{
		int y = fa[x], z = fa[y];
		son[y][!kind] = son[x][kind];
		if (son[x][kind])
			fa[son[x][kind]] = y;
		fa[x] = z;
		if (z)
			son[z][son[z][1] == y] = x;
		son[x][kind] = y, fa[y] = x;
	}

	void splay(int x, int anc)
	{
		while (fa[x] != anc)
		{
			int y = fa[x], z = fa[y];
			if (z == anc)
				rotate(x, x == son[y][0]);
			else
			{
				if ((y == son[z][0]) == (x == son[y][0]))
				{
					rotate(y, y == son[z][0]);
					rotate(x, x == son[y][0]);
				}
				else
				{
					rotate(x, x == son[y][0]);
					rotate(x, x == son[z][0]);
				}
			}
		}
		if (anc == 0)
			root = x;
	}

	void insert(int x)
	{
		if (!root)
			root = ++tot, fa[root] = 0, key[root] = x, siz[root] = 1;
		else
		{
			int now = root;
			while (2333)
			{
				siz[now]++;
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, fa[tot] = now, key[tot] = x, siz[tot] = 1;
					break;
				}
				now = son[now][x > key[now]];
			}
			splay(tot, 0);
		}
	}

	int qrykth(int k)
	{
		int now = root;
		while (2333)
		{
		}
	}
} tree;
