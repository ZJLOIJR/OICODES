#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

typedef long long ll;
const int N = 2e5 + 7;

int max(int a, int b) { return a > b ? a : b; }

int n, m, x, y, ans;

ll sum[N << 2]; int mx[N << 2];
void change(int rt, int l, int r, int po, int val)
{
	if (l == r) { sum[rt] = mx[rt] = val; return; }
	int mid = l + r >> 1;
	if (po <= mid) change(lson, l, mid, po, val);
	else change(rson, mid + 1, r, po, val);
	sum[rt] = sum[lson] + sum[rson];
	mx[rt] = max(mx[lson], mx[rson]);
}
ll qrysum(int rt, int l, int r, int ql, int qr)
{
	if (ql < 1 || qr > n || ql > qr) return 0;
	if (ql <= l && r <= qr) return sum[rt];
	int mid = l + r >> 1; ll ret = 0;
	if (ql <= mid) ret += qrysum(lson, l, mid, ql, qr);
	if (mid + 1 <= qr) ret += qrysum(rson, mid + 1, r, ql, qr);
	return ret;
}
int qrymax(int rt, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return mx[rt];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret = max(ret, qrymax(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = max(ret, qrymax(rson, mid + 1, r, ql, qr));
	return ret;
}

int main()
{
	freopen("challenge.in", "r", stdin);
	freopen("challenge.out", "w", stdout);

	scanf("%d%d", &n, &m);
	ans = n + 1;
	for (int i = 1, p, sum = 0; i <= n; i++)
	{
		scanf("%d", &p);
		if (p == sum && ans > n) ans = i;
		sum += p;
		change(1, 1, n, i, p);
	}
	while (m--)
	{
		scanf("%d%d", &x, &y);
		change(1, 1, n, x, y);
		if (x <= ans)
		{
			int t = x, flag = 0;
			while (1)
			{
				if (qrysum(1, 1, n, 1, t - 1) == qrysum(1, 1, n, t, t)) { flag = 1; break; }
				int l = t + 1, r = n, tmp = -1;
				while (l <= r)
				{
					int mid = l + r >> 1;
					if (qrymax(1, 1, n, l, mid) < qrysum(1, 1, n, 1, t)) l = mid + 1;
					else r = mid - 1, tmp = mid;
				}
				if (tmp == -1) { flag = 0; break; }
				t = tmp;
			}
			if (!flag) ans = n + 1;
			else ans = t;
		}
		printf("%d\n", ans > n ? -1 : ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}
