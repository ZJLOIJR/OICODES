#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 3;

int root = 0, tot = 0;
struct SplayTree
{
	int fa[N], son[N][2], cnt[N], siz[N], key[N];

	int get(int x) { return son[fa[x]][1] == x; }
	void rotate(int x)
	{
		int y = fa[x], z = fa[y], kind = get(x);
		son[y][kind] = son[x][!kind], fa[son[x][!kind]] = y;
		fa[x] = z, son[z][get(y)] = x;
		son[x][!kind] = y, fa[y] = x;
	}

	void splay(int x, int anc)
	{
		while (fa[x] != anc)
		{
			int y = fa[x];
			if (fa[y] == anc) rotate(x);
			else rotate(get(x) == get(y) ? y : x);
		}
		if (anc == 0) root = x;
	}

	int search(int x)
	{
		int now = root;
		while (1)
		{
			if (!now) break;
			if (key[now] == x)
			{
				splay(now, 0);
				return now;
			}
			now = son[now][x > key[now]];
		}
		return 0;
	}

	void insert(int x)
	{
		if (!root)
			root = ++tot, fa[tot] = 0, son[tot][0] = son[tot][1] = 0, cnt[tot] = 1, siz[tot] = 1, key[tot] = x;
		else
		{
			int id = search(x);
			if (id) { cnt[id]++; return; }
			int now = root;
			while (1)
			{
				siz[now]++;
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot;
					fa[tot] = now, son[tot][0] = son[tot][1] = 0, cnt[tot] = 1, ;
					splay(tot, 0);
					break;
				}
				now = son[now][x > key[now]];
			}
		}
	}

	int getpre(int x)
	{
		insert(x);
		splay(search(x), 0);

		
	}
}

int main()
{
	return 0;
}
//5632
