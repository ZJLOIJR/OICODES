#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;
inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

typedef long long ll;
const int N = 1e5 + 7;

int n, m, k;
int a[N], b[N], sum[N], buc[N << 1];
struct ques { int l, r, id; } q[N];
ll tmp = 0, ans[N];

inline int cmp(ques x, ques y) { return b[x.l] == b[y.l] ? x.r < y.r : b[x.l] < b[y.l]; }
void add(int po, int typ)
{
	if (typ == 1) tmp += buc[sum[po] ^ k], buc[sum[po]]++;
	else buc[sum[po]]--, tmp -= buc[sum[po] ^ k];
}

int main()
{
	n = read(), m = read(), k = read();
	int block = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read(), sum[i] = sum[i - 1] ^ a[i], b[i] = (i - 1) / block + 1;
	for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, l = 1, r = 0; i <= m; i++)
	{
		while (l < q[i].l) add(l, -1), l++;
		while (l > q[i].l) add(l - 1, 1), l--;
		while (r < q[i].r) add(r + 1, 1), r++;
		while (r > q[i].r) add(r, -1), r--;
		printf("%d %d %d\n", q[i].id, q[i].l, q[i].r);
		if (q[i].l == q[i].r) { ans[q[i].id] = 1; continue; }
		ans[q[i].id] = tmp;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
