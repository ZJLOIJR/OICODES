#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1
inline int min(int a, int b) { return a < b ? a : b; }
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e5 + 7;

int n, q, l, r, len, mx = 0, id;
char s[N], str[N << 1];
int rad[N << 1];

int mxv[N << 4];
void build(int rt, int l, int r)
{
	if (l == r) { mxv[rt] = rad[l]; return; }
	int mid = l + r >> 1;
	build(lson, l, mid), build(rson, mid + 1, r);
	mxv[rt] = max(mxv[lson], mxv[rson]);
}
int qrymax(int rt, int l, int r, int ql, int qr)
{
	if (ql <= l && r <= qr) return mxv[rt];
	int mid = l + r >> 1, ret = 0;
	if (ql <= mid) ret = max(ret, qrymax(lson, l, mid, ql, qr));
	if (mid + 1 <= qr) ret = max(ret, qrymax(rson, mid + 1, r, ql, qr));
	return ret;
}

int main()
{
	scanf("%d%s", &n, s + 1);
	str[0] = '!', str[++len] = '#';
	for (int i = 1; i <= n; i++) str[++len] = s[i], str[++len] = '#';
	str[++len] = '$';
	for (int i = 1; i <= len; i++)
	{
		if (mx > i) rad[i] = min(rad[id * 2 - i], mx - i);
		else rad[i] = 1;
		while (str[i + rad[i]] == str[i - rad[i]]) rad[i]++;
		if (i + rad[i] > mx) mx = i + rad[i], id = i;
	}
	build(1, 1, len);
	scanf("%d", &q);
	while (q--)
	{
		scanf("%d%d", &l, &r);
		l = (l + 1) * 2, r = (r + 1) * 2;
		int lower = 0, upper = r - l + 1, ret = 1, mid;
		while (lower <= upper)
		{
			mid = lower + upper >> 1;
			if (qrymax(1, 1, len, l + mid - 1, r - mid + 1) - 1 >= mid) lower = mid + 1, ret = mid;
			else upper = mid - 1;
		}
		printf("%d\n", ret);
	}
	return 0;
}
