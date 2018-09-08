#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 3e5 + 7;

long long ans;
int n, k, a[N], sum[N];

int tot, cnt[N * 40], lson[N * 40], rson[N * 40], root[N];
void insert(int &rt, int fa, int l, int r, int po)
{
	if (!rt) rt = ++tot;
	cnt[rt] = cnt[fa] + 1;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) rson[rt] = rson[fa], insert(lson[rt], lson[fa], l, mid, po);
	else lson[rt] = lson[fa], insert(rson[rt], rson[fa], mid + 1, r, po);
}
int query(int rt, int l, int r, int po)
{
	if (!rt) return 0;
	if (l == r) return cnt[rt];
	int mid = l + r >> 1;
	if (po <= mid) return query(lson[rt], l, mid, po);
	else return query(rson[rt], mid + 1, r, po);
}

void solve(int l, int r)
{
	if (l >= r) return;
	int maxv = 0, maxpo;
	for (int i = l; i <= r; i++) if (a[i] > maxv) maxv = a[i], maxpo = i;
	if (r - maxpo < maxpo - l)
	{
		for (int i = maxpo; i <= r; i++)
		{
			int v = (sum[i] - maxv % k + k) % k;
			if (maxpo - 1 >= 0) ans += query(root[maxpo - 1], 0, k - 1, v);
			if (l - 2 >= 0) ans -= query(root[l - 2], 0, k - 1, v);
		}
		ans--;
	}
	else
	{
		for (int i = l; i <= maxpo; i++)
		{
			int v = (sum[i - 1] + maxv % k) % k;
			ans += query(root[r], 0, k - 1, v) - query(root[maxpo - 1], 0, k - 1, v);
		}
		ans--;
	}
	solve(l, maxpo - 1), solve(maxpo + 1, r);
}

int main()
{
	freopen("interval.in", "r", stdin);
	freopen("interval.out", "w", stdout);
	
	scanf("%d%d", &n, &k);
	insert(root[0], root[0], 0, k - 1, 0);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", a + i), sum[i] = (sum[i - 1] + a[i]) % k;
		insert(root[i], root[i - 1], 0, k - 1, sum[i]);
	}
	solve(1, n);
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
