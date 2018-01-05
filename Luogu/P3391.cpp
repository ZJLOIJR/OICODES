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
	int fa[N], son[N][2], key[N], tag[N], siz[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void down(int x)
	{
		if (!x || tag[x] == 0) return;
		swap(son[x][0], son[x][1]);
		tag[son[x][0]] ^= 1, tag[son[x][1]] ^= 1;
		tag[x] = 0;
	}

	void update(int x) { siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }

	int get(int x) { return son[fa[x]][1] == x; }

	void rotate(int x)
	{
		int y = fa[x], z = fa[y], kind = !get(x);
		son[y][!kind] = son[x][kind];
		if (son[x][kind])
			fa[son[x][kind]] = y;
		fa[x] = z;
		if (z)
			son[z][get(y)] = x;
		son[x][kind] = y, fa[y] = x;
		down(y), down(x);
		update(z), update(x), update(y);
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
			root = ++tot, fa[root] = 0, key[root] = x, tag[root] = 0, siz[root] = 1;
		else
		{
			int now = root;
			while (2333)
			{
				siz[now]++;
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot, fa[tot] = now, key[tot] = x, tag[tot] = 0, siz[tot] = 1;
					break;
				}
				now = son[now][x > key[now]];
			}
			splay(tot, 0);
		}
	}

	int findkth(int k)
	{
		int now = root, cnt;
		while (2333)
		{
			down(now);
			cnt = siz[son[now][0]];
			if (k - 1 == cnt) return now;
			else if (k - 1 < cnt) now = son[now][0];
			else now = son[now][1], k -= cnt + 1;
		}
	}

	/*void reverse(int l, int r)
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
			splay(l - 1, 0);
			splay(r + 1, l - 1);
			tag[son[son[root][1]][0]] ^= 1;
		}
	}*/

	void reverse(int l, int r)
	{
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
	//freopen("IN", "r", stdin);
	//freopen("OUT", "w", stdout);
	tree.init();
	n = read(), q = read();
	tree.insert(-2147483647);
	for (int i = 1; i <= n; i++)
		tree.insert(i);
	tree.insert(2147483647);
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
