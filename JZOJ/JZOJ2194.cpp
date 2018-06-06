#include <cstdio>
#include <cstring>
#include <cstdlib>
#define lson rt << 1
#define rson rt << 1 | 1

const int N = 1e5 + 7;

int n, m;
char str[27];

int mi[N << 2], mx[N << 2], ans[N << 2];

inline int max(int a, int b) { return a > b ? a : b; }
inline int min(int a, int b) { return a < b ? a : b; }

void build(int rt, int l, int r)
{
	mi[rt] = mx[rt] = -1, ans[rt] = 0x3f3f3f3f;
	if (l == r) return;
	int mid = l + r >> 1;
	build(lson, l, mid), build(rson, mid + 1, r);
}

void insert(int rt, int l, int r, int po, int val)
{
	if (l == r)
	{
		if (val) mi[rt] = mx[rt] = po;
		else mi[rt] = mx[rt] = -1, ans[rt] = 0x3f3f3f3f;
		return;
	}
	int mid = l + r >> 1;
	if (po <= mid) insert(lson, l, mid, po, val);
	else insert(rson, mid + 1, r, po, val);
	if (~mi[lson]) mi[rt] = mi[lson];
	else if (~mi[rson]) mi[rt] = mi[rson];
	else mi[rt] = -1;
	if (~mx[rson]) mx[rt] = mx[rson];
	else if (~mx[lson]) mx[rt] = mi[lson];
	else mx[rt] = -1;
	ans[rt] = min(ans[lson], ans[rson]);
	if (~mi[rson] && ~mx[lson]) ans[rt] = min(ans[rt], mi[rson] - mx[lson]);
}

int main()
{
	scanf("%d", &n);
	build(1, 1, N - 7);
	for (int i = 1; i <= n; i++)
	{
		scanf("%s", str);
		if (str[0] == 'g') scanf("%d", &m), insert(1, 1, N - 7, m, 1);
		else if (str[0] == 'r') scanf("%d", &m), insert(1, 1, N - 7, m, 0);
		else printf("%d\n", ans[1] == 0x3f3f3f3f ? -1 : ans[1]);
	}
	return 0;
}
