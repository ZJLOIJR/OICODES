#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

const int N = 200007;

int n, a, q, l, r;

void swap(int &a, int &b) { int t = a; a = b; b = t; }

struct SplayTree
{
	int fa[N], son[N][2], key[N], rev[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void down(int x)
	{
		if (rev[x] == 0) return;
		rev[son[x][0]] ^= 1;
		rev[son[x][1]] ^= 1;
		swap(son[x][0], son[x][1]);
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
			root = ++tot, fa[root] = 0, son[root][0] = son[root][1] = 0, key[root] = x;
		else
		{
			int now = root;
			while (1)
			{
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, fa[tot] = now, key[tot] = x;
					break;
				}
				now = son[now][x > key[now]];
			}
			splay(tot, 0);
		}
	}

	void reverse(int l, int r)
	{
		splay(r + 1, 0);
		splay(l - 1, 0);
		rev[son[son[root][1]][0]] ^= 1;
	}

	void qrymid(int x)
	{
		down(x);
		if (son[x][0])
			qrymid(son[x][0]);
		printf("%d ", key[x]);
		if (son[x][1])
			qrymid(son[x][1]);
	}
} tree;

int main()
{
	scanf("%d%d", &n, &q);
	for (int i = 1; i <= n; i++)
		tree.insert(i);
	while (q--)
	{
		scanf("%d%d", &l, &r);
		tree.reverse(l, r);
		tree.qrymid(tree.root);
		putchar('\n');
	}
	return 0;
}
