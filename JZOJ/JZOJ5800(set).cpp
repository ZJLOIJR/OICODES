#include <set>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
const int N = 8e4 + 7;

struct Pair { int y, id; } tmp; set<Pair> s;
int operator<(Pair p, Pair q) { return p.y < q.y; }
set<int> tmp, col[N];

int ans[N];
int n, m, len, x1[N], y1[N], x2[N], y2[N];

struct note { int x, y, id, val; } arr[N * 3];
int cmp(note p, note q) { return p.x == q.x ? p.id > q.id : p.x < q.x; }

int tot, st[N], to[N], nx[N], anc[N][21];
void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }
void dfs(int u)
{
	for (int i = st[u]; i; i = nx[i])
	{
		dfs(to[i]);
		col[u].insert(col[to[i]].begin(), col[to[i]].end());
		col[to[i]].clear();
	}
	ans[u] = col[u].size();
}

int in(int x1, int y1, int x2, int y2, int xx1, int yy1, int xx2, int yy2)
{
	return x1 <= xx1 && xx2 <= x2 && y1 <= yy1 && yy2 <= y2;
}

int main()
{
	//freopen("plahte.in", "r", stdin);
	//freopen("plahte.out", "w", stdout);
	
	x1[0] = 0, y1[0] = 0, x2[0] = 1e9 + 7, y2[0] = 1e9 + 7;
	n = read(), m = read();
	for (int i = 1; i <= n; i++)
	{
		x1[i] = read(), y1[i] = read(), x2[i] = read(), y2[i] = read();
		arr[++len] = (note){x1[i], y2[i], i, 1};
		arr[++len] = (note){x2[i] + 1, y2[i], i, -1};
	}
	for (int i = 1, x, y, k; i <= m; i++)
	{
		x = read(), y = read(), k = read();
		arr[++len] = (note){x, y, 0, k};
	}
	sort(arr + 1, arr + len + 1, cmp);
	for (int i = 1; i <= len; i++)
	{
		if (arr[i].id)
		{
			if (arr[i].val > 0)
			{
				int ths = arr[i].id;
				tmp = *(s.lower_bound((Pair){arr[i].y, 0}));
				int fa = tmp.id;
				if (in(x1[fa], y1[fa], x2[fa], y2[fa], x1[ths], y1[ths], x2[ths], y2[ths])) anc[ths][0] = fa;
				else
				{
					for (int j = 20; j >= 0; j--)
						if (!in(x1[anc[fa][j]], y1[anc[fa][j]], x2[anc[fa][j]], y2[anc[fa][j]], x1[ths], y1[ths], x2[ths], y2[ths]))
							fa = anc[fa][j];
					fa = anc[fa][0];
					anc[ths][0] = fa;
				}
				for (int j = 1; j <= 20; j++) anc[ths][j] = anc[anc[ths][j - 1]][j - 1];
				s.insert((Pair){arr[i].y, arr[i].id});
			}
			else s.erase((Pair){arr[i].y, arr[i].id});
		}
		else
		{
			tmp = *(s.lower_bound((Pair){arr[i].y, 0}));
			int fa = tmp.id;
			if (in(x1[fa], y1[fa], x2[fa], y2[fa], arr[i].x, arr[i].y, arr[i].x, arr[i].y)) col[fa].insert(arr[i].val);
			else
			{
				for (int j = 20; j >= 0; j--)
					if (!in(x1[anc[fa][j]], y1[anc[fa][j]], x2[anc[fa][j]], y2[anc[fa][j]], arr[i].x, arr[i].y, arr[i].x, arr[i].y))
						fa = anc[fa][j];
				fa = anc[fa][0];
				col[fa].insert(arr[i].val);
			}
		}
	}
	for (int i = 1; i <= n; i++) add(anc[i][0], i);
	dfs(0);
	for (int i = 1; i <= n; i++) printf("%d\n", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
