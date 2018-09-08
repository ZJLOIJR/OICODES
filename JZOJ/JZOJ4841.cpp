#pragma GCC optimize(2)
#include <map>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int N = 22;

int n, mid, ans, a[N];
int vis[1 << 20];
struct note { int val, status; };
vector<note> list[60000];
int tot = 0;
map<int, int> id;

inline int bit(int x) { return (1 << (x - 1)); }

void insert(note x)
{
	if (!id[x.val]) id[x.val] = ++tot;
	list[id[x.val]].push_back(x);
}

void find(note x)
{
	if (!id[x.val]) return;
	int tmpid = id[x.val], siz = list[tmpid].size();
	for (int i = 0; i < siz; i++)
		if (!vis[x.status | list[tmpid][i].status])
		{
			vis[x.status | list[tmpid][i].status] = 1;
			ans++;
		}
}

void dfs1(int now, int sum, int s)
{
	if (now > mid) { insert((note){sum, s}); return; }
	dfs1(now + 1, sum + a[now], s | bit(now));
	dfs1(now + 1, sum - a[now], s | bit(now));
	dfs1(now + 1, sum, s);
}

void dfs2(int now, int sum, int s)
{
	if (now > n)
	{
		find((note){sum, s});
		return;
	}
	dfs2(now + 1, sum + a[now], s | bit(now));
	dfs2(now + 1, sum - a[now], s | bit(now));
	dfs2(now + 1, sum, s);
}

int main()
{
	freopen("subset.in", "r", stdin);
	freopen("subset.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	mid = (1 + n) / 2;
	dfs1(1, 0, 0);
	dfs2(mid + 1, 0, 0);
	printf("%d\n", ans - 1);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
