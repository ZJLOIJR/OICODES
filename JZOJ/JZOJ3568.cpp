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
const ll P = 1e9 + 7;

int n, m, block, a[N], b[N], buc[N];
struct ques { int l, r, id; } q[N];
ll tmp, ans[N];

int cmp(ques x, ques y) { return b[x.l] == b[y.l] ? x.r < y.r : x.l < y.l; }

ll power(ll x, ll y)
{
	ll ret = 1;
	while (y)
	{
		if (y & 1) ret = ret * x % P;
		x = x * x % P, y >>= 1;
	}
	return ret;
}

void add(int po, int typ)
{
	if (typ == 1)
	{
		if (!buc[a[po]]) tmp = (tmp + a[po]) % P, buc[a[po]]++;
		else
		{
			tmp = (tmp - power(a[po], buc[a[po]]) + P) % P;
			buc[a[po]]++;
			tmp = (tmp + power(a[po], buc[a[po]])) % P;
		}
	}
	else
	{
		tmp = (tmp - power(a[po], buc[a[po]]) + P) % P;
		buc[a[po]]--;
		if (buc[a[po]]) tmp = (tmp + power(a[po], buc[a[po]])) % P;
	}
}

int main()
{
	n = read(), m = read(), block = sqrt(n);
	for (int i = 1; i <= n; i++) a[i] = read(), b[i] = (i - 1) / block + 1;
	for (int i = 1; i <= m; i++) q[i].l = read(), q[i].r = read(), q[i].id = i;
	sort(q + 1, q + m + 1, cmp);
	for (int i = 1, l = 1, r = 0; i <= m; i++)
	{
		while (r < q[i].r) add(r + 1, 1), r++;
		while (r > q[i].r) add(r, -1), r--;
		while (l < q[i].l) add(l, -1), l++;
		while (l > q[i].l) add(l - 1, 1), l--;
		ans[q[i].id] = tmp;
	}
	for (int i = 1; i <= m; i++) printf("%lld\n", ans[i]);
	return 0;
}
