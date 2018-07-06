#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

const int N = 1e6 + 7;

int c, opt, a;

int root, tot, son[N][2], fa[N], siz[N], rev[N], val[N];
void swap(int &a, int &b) { int t = a; a = b, b = t; }
void init()
{
	root = 1, tot = 2, son[1][1] = 2, fa[2] = 1, siz[1] = 2, siz[2] = 1;
}
void upd(int x)
{
	siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1;
	if (!rev[x] || !x) return;
	swap(son[x][0], son[x][1]), rev[son[x][0]] ^= 1, rev[son[x][1]] ^= 1, rev[x] = 0;
}
void rotate(int x)
{
	int y = fa[x], z = fa[y], k = (son[y][1] == x);
	son[y][k] = son[x][!k]; if (son[x][!k]) fa[son[x][!k]] = y;
	son[x][!k] = y, fa[y] = x, fa[x] = z;
	if (z) son[z][son[z][1] == y] = x;
	upd(y), upd(x);
}
void splay(int x, int anc)
{
	for (int y, z; (y = fa[x]) != anc; rotate(x))
	{
		z = fa[y];
		if (z == anc) continue;
		rotate((son[z][1] == y) == (son[y][1] == x) ? y : x);
	}
	if (!anc) root = x;
}
int findkth(int k)
{
	int now = root;
	while (1)
	{
		upd(now);
		if (siz[son[now][0]] + 1 < k) k -= siz[son[now][0]] + 1, now = son[now][1];
		else if (k <= siz[son[now][0]]) now = son[now][0];
		else return now;
	}
}

int main()
{
	init();
	c = read();
	while (1)
	{
		opt = read();
		if (!opt) break;
		if (opt == 1)
		{
			a = read();
			int x = findkth(siz[root] - 1), y = findkth(siz[root]);
			splay(x, 0), splay(y, x);
			son[y][0] = ++tot, fa[tot] = y, val[tot] = a, siz[tot] = 1;
			while (y) siz[y]++, y = fa[y];
		}
		else if (opt == 2)
		{
			if (siz[root] <= 2) printf("Error: the stack is empty!\n");
			else
			{
				int x = findkth(siz[root] - 2), y = findkth(siz[root]);
				splay(x, 0), splay(y, x);
				printf("%d\n", val[son[y][0]]);
				son[y][0] = 0;
				while (y) siz[y]--, y = fa[y];
			}
		}
		else
		{
			if (siz[root] - 2 < c) printf("Error: less than %d elements in the stack!\n", c);
			else
			{
				int x = findkth(siz[root] - c - 1), y = findkth(siz[root]);
				splay(x, 0), splay(y, x);
				rev[son[y][0]] ^= 1;
			}
		}
	}
	return 0;
}
