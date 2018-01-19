#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 100007, P = 99999997;

int n, ans = 0;
struct arr { int val, pos; } a[N], b[N];
int c[N], tree[N];

inline void add(int p, int v)
{ for (; p <= n; p += p & (-p)) tree[p] += v; }

inline int get(int p)
{ int ret = 0; for (; p; p -= p & (-p)) ret += tree[p]; return ret; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", &a[i].val), a[i].pos = i;
	for (int i = 1; i <= n; i++) scanf("%d", &b[i].val), b[i].pos = i;
	sort(a + 1, a + n + 1, [](arr x, arr y){ return x.val < y.val; });
	sort(b + 1, b + n + 1, [](arr x, arr y){ return x.val < y.val; });
	for (int i = 1; i <= n; i++) c[a[i].pos] = b[i].pos;
	for (int i = n; i >= 1; i--)
	{
		ans = (ans + get(c[i] - 1)) % P;
		add(c[i], 1);
	}
	printf("%d\n", ans);
	return 0;
}
