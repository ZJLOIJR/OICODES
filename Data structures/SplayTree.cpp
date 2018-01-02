#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 200007;

int n;

struct SplayTree
{
	int fa[N], son[N][2], key[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void rotate(int x, int kind)
	{
		int y = fa[x], z = fa[y];
		son[y][!kind] = son[x][kind];
		if (!son[x][kind])
			fa[son[x][kind]] = y;
		fa[x] = z;
		if (!z)
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
				
			}
		}
		if (anc == 0)
			root = x;
	}

	void insert(int x)
	{
		if (!root)
			root = ++tot, fa[root] = 0, son[root][0] = son[root][1] = 0, key[root] = x;
		else
		{
			int now = root, pre = 0;
			while (1)
			{
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, fa[tot] = pre, key[tot] = x;
					break;
				}
				pre = now;
				now = son[now][x > key[now]];
			}
			splay(tot, 1);
		}
	}
}

int main()
{
	return 0;
}
