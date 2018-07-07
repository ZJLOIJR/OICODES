#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
using namespace std;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 5e4 + 7;

int mx[N << 2], inc[N << 2];
void down(int rt, int l, int r)
{
	if (!inc[rt]) return;
	if (l != r) inc[lson] += inc[rt], inc[rson] += inc[rt];
	mx[rt] += inc[rt], inc[rt] = 0;
}
void plus(int rt, int l, int r, int ql, int qr, int val)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) { inc[rt] += val; return; }
	int mid = l + r >> 1;
	if (ql <= mid) plus(lson, l, mid, ql, qr, val);
	if (mid + 1 <= qr) plus(rson, mid + 1, r, ql, qr, val);
	down(lson, l, mid), down(rson, mid + 1, r);
	mx[rt] = max(mx[lson], mx[rson]);
}
int query(int rt, int l, int r, int ql, int qr)
{
	down(rt, l, r);
	if (ql <= l && r <= qr) return mx[rt];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret = max(ret, query(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = max(ret, query(rson, mid + 1, r, ql, qr));
	return ret;
}

int n, m, k, ans = 0, tmp = 0;
struct note { int po, val; };
vector<note> arr[N];

int main()
{
	n = read(), m = read(), k = read();
	while (m--)
	{
		int x = read(), y = read(), z = read();
		arr[x].push_back((note){y, z});
	}
	for (int i = 1; i <= k + 1; i++)
	{
		int len = arr[i].size();
		for (int j = 0; j < len; j++)
		{
			int l = max(1, arr[i][j].po - k), r = arr[i][j].po;
			plus(1, 1, n, l, r, arr[i][j].val);
		}
	}
	for (int u = 1, v = k + 1; v <= n; u++, v++)
	{
		ans = max(ans, query(1, 1, n, 1, n));
		if (v + 1 <= n)
		{
			int len = arr[u].size();
			for (int j = 0; j < len; j++)
			{
				int l = max(1, arr[u][j].po - k), r = arr[u][j].po;
				plus(1, 1, n, l, r, -arr[u][j].val);
			}
			len = arr[v + 1].size();
			for (int j = 0; j < len; j++)
			{
				int l = max(1, arr[v + 1][j].po - k), r = arr[v + 1][j].po;
				plus(1, 1, n, l, r, arr[v + 1][j].val);
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
