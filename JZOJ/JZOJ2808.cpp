#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int n, m, id[N];
int tot, root[N], lson[N * 20], rson[N * 20], sum[N * 20];

void insert(int &rt, int l, int r, int po)
{
	if (!rt) rt = ++tot;
	sum[rt]++;
	if (l == r) return;
	int mid = l + r >> 1;
	if (po <= mid) insert(lson[rt], l, mid, po);
	else insert(rson[rt], mid + 1, r, po);
}
int qrykth(int rt, int l, int r, int k)
{
	if (l == r) return l;
	int mid = l + r >> 1;
	if (k <= sum[lson[rt]]) return qrykth(lson[rt], l, mid, k);
	else return qrykth(rson[rt], mid + 1, r, k - sum[lson[rt]]);
}
void merge(int x, int y)
{
	if (x == y) return;
	sum[y] += sum[x];
	if (!lson[x]) lson[x] = lson[y];
	else if (!lson[y]) lson[y] = lson[x];
	else merge(lson[x], lson[y]);
	if (!rson[x]) rson[x] = rson[y];
	else if (!rson[y]) rson[y] = rson[x];
	else merge(rson[x], rson[y]);
}


void swap(int &a, int &b) { int t = a; a = b, b = t; }
int fa[N], size[N];
int getfa(int x) { return fa[x] == x ? x : getfa(fa[x]); }
void link(int x, int y)
{
	x = getfa(x), y = getfa(y);
	if (size[x] > size[y]) swap(x, y);
	fa[x] = y, size[y] += size[x], merge(root[x], root[y]);
}

int main()
{
	scanf("%d%d", &n, &m);
	for (int i = 1, a; i <= n; i++) scanf("%d", &a), id[a] = i, fa[i] = i, insert(root[i], 1, n, a);
	while (m--)
	{
		int u, v;
		scanf("%d%d", &u, &v);
		link(u, v);
	}
	scanf("%d", &m);
	while (m--)
	{
		char ch; int u, v;
		scanf(" %c%d%d", &ch, &u, &v);
		if (ch == 'B') link(u, v);
		else printf("%d\n", v > sum[root[getfa(u)]] ? -1 : id[qrykth(root[getfa(u)], 1, n, v)]);
	}
	return 0;
}
