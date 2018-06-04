#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int n, a[N];
long long ans = 0;

long long solve(int l, int r)
{
	if (l > r) return 0;
	int mi = 0x3f3f3f3f, po = 0;
	for (int i = l; i <= r; i++) if (a[i] < mi) mi = a[i], po = i;
	for (int i = l; i <= r; i++) a[i] -= mi;
	return mi + solve(l, po - 1) + solve(po + 1, r);
}

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	printf("%lld\n", solve(1, n));
	return 0;
}
