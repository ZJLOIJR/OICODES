#pragma GCC optimize(3)
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
using namespace std;

const int N = 200007;

int n, m, x, k = 0, tot = 0;
int qry[N], a[N];

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

struct SplayTree
{
	int fa[N], son[N][2], key[N], siz[N];
	int root, tot;

	void init() { tot = 0, root = 0; }

	void update(int x)
	{
		if (x)
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
		update(y);
		update(x);
		update(z);
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
			if (now == 0)
				return 0;
			int cnt = siz[son[now][1]];
			if (cnt == k - 1)
			{
				splay(now, 0);
				return now;
			}
			if (cnt > k - 1)
				now = son[now][1];
			else
			{
				now = son[now][0];
				k = k - cnt - 1;
			}
		}
	}
} tree;

void init()
{
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read();
}

void solve()
{
	for (int i = 1; i <= m; i++)
	{
		*(qry + i) = read();
		for (int j = qry[i - 1] + 1; j <= qry[i]; j++)
			tree.insert(a[j]), tot++;
		k++;
		printf("%d\n", tree.key[tree.qrykth(tot - k + 1)]);
	}
}

int main()
{
	init();
	solve();
	return 0;
}
