#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 1e5 + 7, LogN = 20;

int n, dfn;
int tot, st[N], to[N << 1], nx[N << 1], tid[N], out[N], dep[N], anc[N][21];

void add(int u, int v) { to[++tot] = v, nx[tot] = st[u], st[u] = tot; }

void dfs(int u)
{
	tid[u] = ++dfn;
	for (int i = st[u]; i; i = nx[i])
		if (!tid[to[i]])
			dep[to[i]] = dep[u] + 1, anc[to[i]][0] = u, dfs(to[i]);
	out[u] = dfn;
}

ll ans;
struct note { int y1, y2, val; };
vector<note> line[N];
void addnote(int l1, int r1, int l2, int r2)
{
	if (l1 > r1 || l2 > r2) return;
	if (l1 > l2) swap(l1, l2), swap(r1, r2);
	line[l1].push_back((note){l2, r2, 1});
	line[r1 + 1].push_back((note){l2, r2, -1});
}

#define lson rt << 1
#define rson rt << 1 | 1
int sum[N * LogN * 8];
double cnt[N * LogN * 8];
void upd(int rt, int l, int r)
{
	if (sum[rt]) cnt[rt] = r - l + 1
	;
	else if (l == r) cnt[rt] = 0;
	else cnt[rt] = cnt[lson] + cnt[rson];
}
void change(int rt, int l, int r, int ql, int qr, int val)
{
	if (ql <= l && r <= qr) { sum[rt] += val, upd(rt, l, r); return; }
	int mid = l + r >> 1;
	if (ql <= mid) change(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) change(rson, mid + 1, r, ql, qr, val);
	upd(rt, l, r);
}

int main()
{
	//freopen("a.in", "r", stdin);
	//freopen("a.out", "w", stdout);

	scanf("%d", &n);
	for (int i = 1, u, v; i < n; i++) scanf("%d%d", &u, &v), add(u, v), add(v, u);
	dep[1] = 1, dfs(1);
	for (int j = 1; j <= 20; j++)
		for (int i = 1; i <= n; i++)
			anc[i][j] = anc[anc[i][j - 1]][j - 1];
	for (int i = 1; i <= n; i++)
		for (int j = i + i; j <= n; j += i)
		{
			if (tid[i] <= tid[j] && out[j] <= out[i])
			{
				int now = j;
				for (int k = 20; k >= 0; k--) if (dep[anc[now][k]] > dep[i]) now = anc[now][k];
				addnote(1, tid[now] - 1, tid[j], out[j]);
				addnote(out[now] + 1, n, tid[j], out[j]);
			}
			else if (tid[j] <= tid[i] && out[i] <= out[j])
			{
				int now = i;
				for (int k = 20; k >= 0; k--) if (dep[anc[now][k]] > dep[j]) now = anc[now][k];
				addnote(1, tid[now] - 1, tid[i], out[i]);
				addnote(out[now] + 1, n, tid[i], out[i]);
			}
			else addnote(tid[i], out[i], tid[j], out[j]);
		}
	for (int i = 1; i <= n; i++)
	{
		int s = line[i].size();
		for (int j = 0; j < s; j++) change(1, 1, n, line[i][j].y1, line[i][j].y2, line[i][j].val);
		ans += cnt[1];
	}
	ll ret = 1LL * n * (n - 1) / 2 - (ll)ans;
	printf("%lld\n", ret);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
