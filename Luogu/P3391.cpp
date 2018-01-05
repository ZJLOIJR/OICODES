#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100007;

int n, q, u, v;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

inline void swap(int &a, int &b)
{
	int t = a;
	a = b, b = t;
}

struct SplayTree
{
	int fa[N], son[N][2], key[N], tag[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void down(int x)
	{
		if (!x || tag[x] == 0) return;
		swap(son[x][0], son[x][1]);
		tag[son[x][0]] ^= 1, tag[son[x][1]] ^= 1;
		tag[x] = 0;
	}

	void rotate(int x, int kind)
	{
		int y = fa[x], z = fa[y];
		down(z);
		down(y);
		down(x);
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
					rotate(y, y == son[z][0]), rotate(x, x == son[y][0]);
				else
					rotate(x, x == son[y][0]), rotate(x, x == son[z][0]);
			}
		}
		if (anc == 0)
			root = x;
	}

	void insert(int x)
	{
		if (!root)
			root = ++tot, fa[root] = 0, key[root] = x, tag[root] = 0;
		else
		{
			int now = root;
			while (2333)
			{
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, fa[tot] = now, key[tot] = x, tag[tot] = 0;
					break;
				}
				now = son[now][x > key[now]];
			}
			splay(tot, 0);
		}
	}

	void reverse(int l, int r)
	{
		if (l - 1 < 1 && r + 1 > n)
			tag[root] ^= 1;
		else if (l - 1 < 1)
		{
			splay(r + 1, 0);
			tag[son[root][0]] ^= 1;
		}
		else if (r + 1 > n)
		{
			splay(l - 1, 0);
			tag[son[root][1]] ^= 1;
		}
		else
		{
			splay(r + 1, 0);
			splay(l - 1, 0);
			tag[son[son[root][1]][0]] ^= 1;
		}
	}

	void print(int x)
	{
		if (x == 0)
			return;
		down(x);
		print(son[x][0]);
		printf("%d ", x);
		print(son[x][1]);
	}
} tree;

int main()
{
	freopen("IN", "r", stdin);
	freopen("OUT", "w", stdout);
	tree.init();
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		tree.insert(i);
	while (q--)
	{
		u = read(), v = read();
		tree.reverse(u, v);
		//tree.print(tree.root);
		//putchar('\n');
		//printf("%d\n", q);
	}
	tree.print(tree.root);
	return 0;
}
