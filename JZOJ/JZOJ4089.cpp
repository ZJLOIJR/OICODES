#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 5e4 + 7;

int n, m, block, a[N], b[N];
struct ques { int l, r, id; } q[N];
ll tmp = 0, sum[N], ans[N];

int lowbit(int x) { return x & (-x); }
void plus(int po, int val) { for (; po <= N - 7; po += lowbit(po)) sum[po] += val; }
ll getsum(int po) { ll ret = 0; for (; po; po -= lowbit(po)) ret += sum[po]; return ret; }

int cmp(ques x, ques y) { return b[x.l] == b[y.l] ? x.r < y.r : x.l < y.l; }
void add1(int po, int typ)
{
	if (typ == -1) plus(a[po], typ), tmp -= getsum(a[po] - 1);
	else tmp += getsum(a[po] - 1), plus(a[po], typ);
}
void add2(int po, int typ)
{
	if (typ == -1) plus(a[po], typ), tmp -= getsum(N - 7) - getsum(a[po]);
	else tmp += getsum(N - 7) - getsum(a[po]), plus(a[po], typ);
}

int main()
{
	freopen("file.in", "r", stdin);
	freopen("file.out", "w", stdout);

	scanf("%d", &n), block = sqrt(n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), b[i] = i / block + 1;
	scanf("%d", &m);
	for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0; tmp = 0;
	for (int i = 1; i <= m; i++)
	{
		while (l < q[i].l) add1(l, -1), l++;
		while (l > q[i].l) add1(l - 1, 1), l--;
		while (r < q[i].r) add2(r + 1, 1), r++;
		while (r > q[i].r) add2(r, -1), r--;
		ans[q[i].id] = tmp;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
