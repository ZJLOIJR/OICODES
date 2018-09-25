#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

typedef long long ll;
const int N = 1e3 + 7;

int n, m;
ll h[N], ans[N][N], arr[N], ret;

ll sum[N << 2]; int cnt[N << 2];
void insert(int rt, int l, int r, int po, int val)
{
	cnt[rt] += val;
	if (l == r) { sum[rt] += val * arr[po]; return; }
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po, val);
	else insert(rson, mid + 1, r, po, val);
	sum[rt] = sum[lson] + sum[rson];
}

ll qrysum(int rt, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
	return ret;
}

int qrycnt(int rt, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return cnt[rt];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret += qrycnt(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrycnt(rson, mid + 1, r, ql, qr);
	return ret;
}

int findkth(int rt, int l, int r, int k)
{
	if (l == r) return l;
	int mid = l + r >> 1;
	if (k <= cnt[lson]) return findkth(lson, l, mid, k);
	else return findkth(rson, mid + 1, r, k - cnt[lson]);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", h + i);
	memcpy(arr, h, sizeof(h));
	sort(arr + 1, arr + n + 1);
	for (int i = 1; i <= n; i++) h[i] = lower_bound(arr + 1, arr + n + 1, h[i]) - arr;
	for (int i = 1; i <= n; i++)
	{
		for (int j = i; j <= n; j++)
		{
			insert(1, 1, n, h[j], 1);
			int midnum = findkth(1, 1, n, (j - i + 2) / 2);
			ll s = qrysum(1, 1, n, 1, midnum); int c = qrycnt(1, 1, n, 1, midnum);
			ans[i][j] += c * arr[midnum] - s;
			s = qrysum(1, 1, n, midnum, n), c = qrycnt(1, 1, n, midnum, n);
			ans[i][j] += s - c * arr[midnum];
		}
		for (int j = i; j <= n; j++) insert(1, 1, n, h[j], -1);
	}
	while (m--)
	{
		int l, r;
		scanf("%d%d", &l, &r);
		ret += ans[l][r];
	}
	printf("%lld\n", ret);
	return 0;
}
