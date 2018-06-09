#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 5e4 + 7;

int n, m, block, c[N], b[N];
struct ques { int l, r, id; } q[N];
ll tmp = 0, sum[N], ans[N][2];

int cmp(ques x, ques y) { return b[x.l] == b[y.l] ? x.r < y.r : x.l < y.l; }
void add(int po, int typ) { tmp -= sum[c[po]] * sum[c[po]], sum[c[po]] += typ, tmp += sum[c[po]] * sum[c[po]]; }
ll gcd(ll a, ll b) { return b ? gcd(b, a % b) : a; }

int main()
{
	scanf("%d%d", &n, &m);
	block = sqrt(n);
	for (int i = 1; i <= n; i++) scanf("%d", c + i), b[i] = i / block + 1;
	for (int i = 1; i <= m; i++) scanf("%d%d", &q[i].l, &q[i].r), q[i].id = i;
	sort(q + 1, q + m + 1, cmp);
	int l = 1, r = 0; tmp = 0;
	for (int i = 1; i <= m; i++)
	{
		while (l < q[i].l) add(l, -1), l++;
		while (l > q[i].l) add(l - 1, 1), l--;
		while (r < q[i].r) add(r + 1, 1), r++;
		while (r > q[i].r) add(r, -1), r--;
		if (q[i].l == q[i].r) { ans[q[i].id][0] = 0, ans[q[i].id][1] = 1; continue; }
		ll a = tmp - (q[i].r - q[i].l + 1), b = (q[i].r - q[i].l + 1LL) * (q[i].r - q[i].l), g = gcd(a, b);
		ans[q[i].id][0] = a / g, ans[q[i].id][1] = b / g;
	}
	for (int i = 1; i <= m; i++) printf("%lld\/%lld\n", ans[i][0], ans[i][1]);
	return 0;
}
