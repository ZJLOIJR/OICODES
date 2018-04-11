#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 3;

int root = 0, tot = 0;
int q, opt, x;
struct SplayTree
{
	int fa[N], son[N][2], cnt[N], siz[N], key[N];

	int get(int x) { return son[fa[x]][1] == x; }
	void upd(int x) { if (x) siz[x] = siz[son[x][0]] + siz[son[x][1]] + 1; }
	void rotate(int x)
	{
		int y = fa[x], z = fa[y], kind = get(x);
		son[y][kind] = son[x][!kind], fa[son[x][!kind]] = y;
		fa[x] = z, son[z][get(y)] = x;
		son[x][!kind] = y, fa[y] = x;
		upd(y), upd(x);
	}
	void splay(int x, int anc)
	{
		while (fa[x] != anc)
		{
			int y = fa[x];
			if (fa[y] == anc) rotate(x);
			else rotate(get(x) == get(y) ? y : x);
			printf("splay\n");
		}
		if (anc == 0) root = x;
	}
	int search(int x)
	{
		int now = root;
		while (1)
		{
			if (!now) return 0;
			if (key[now] == x) return now;
			now = son[now][x > key[now]];
			printf("search\n");
		}
		return 0;
	}
	
	void insert(int x)
	{
		if (!root)
			root = ++tot, fa[tot] = 0, son[tot][0] = son[tot][1] = 0, cnt[tot] = 1, siz[tot] = 1, key[tot] = x;
		else
		{
			int tmp = search(x);
			if (tmp) { cnt[tmp]++; return; }
			int now = root;
			while (1)
			{
				siz[now]++;
				if (!son[now][x > key[now]])
				{
					son[now][x > key[now]] = ++tot;
					fa[tot] = now, son[tot][0] = son[tot][1] = 0, cnt[tot] = 1, siz[tot] = 1, key[tot] = x;
					splay(tot, 0);
					break;
				}
				now = son[now][x > key[now]];
				printf("insert\n");
			}
		}
	}

	void erase(int x)
	{
		int now = search(x);
		if (cnt[now] > 1) cnt[now]--;
		else
		{
			splay(now, 0);
			if (!son[now][0])
			{
				root = son[now][1];
				fa[root] = 0;
				upd(root);
			}
			else
			{
				int tmp = son[now][0];
				while (son[tmp][1]) tmp = son[tmp][1];
				splay(tmp, now);
				root = tmp;
				son[tmp][1] = son[now][1], fa[son[now][1]] = tmp;
				upd(root);
			}
		}
	}

	int getpre(int x)
	{
		insert(x);
		int now = search(x);
		splay(now, 0);
		int tmp = son[now][0];
		while (son[tmp][1]) tmp = son[tmp][1];
		erase(x);
		return tmp;
	}
	
	int getnex(int x)
	{
		insert(x);
		int now = search(x);
		splay(now, 0);
		int tmp = son[now][1];
		while (son[tmp][0]) tmp = son[tmp][0];
		erase(x);
		return tmp;
	}

	int getrank(int x)
	{
		insert(x);
		int now = root, ret = 0;
		while (1)
		{
			if (x == key[now]) { ret += siz[son[now][0]] + 1; break; }
			if (x > key[now]) ret += siz[son[now][0]] + 1;
			now = son[now][x > key[now]];
		}
		erase(x);
		return ret;
	}

	int getkth(int k)
	{
		int now = root, cnt;
		while (1)
		{
			cnt = siz[son[now][0]];
			if (cnt == k - 1) break;
			else if (cnt < k - 1) now = son[now][1], k -= cnt + 1;
			else now = son[now][0];
		}
		return now;
	}
} tree;

int main()
{
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &opt, &x);
		if (opt == 1) tree.insert(x);
		else if (opt == 2) tree.erase(x);
		else if (opt == 3) printf("%d\n", tree.getrank(x));
		else if (opt == 4) printf("%d\n", tree.key[tree.getkth(x)]);
		else if (opt == 5) printf("%d\n", tree.key[tree.getpre(x)]);
		else if (opt == 6) printf("%d\n", tree.key[tree.getnex(x)]);
	}
	return 0;
}
//5632
