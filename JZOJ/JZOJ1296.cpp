#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 2e4 + 5e3 + 3;

int n, x, y;
int a[N], b[N];
ll ans = 0;

inline int read()
{
	int x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + (c ^ '0');
	return f ? -x : x;
}

int main()
{
	freopen("sandcas.in", "r", stdin);
	freopen("sandcas.out", "w", stdout);

	n = read(), x = read(), y = read();
	for (int i = 1; i <= n; i++) a[i] = read(), b[i] = read();
	sort(a + 1, a + n + 1);
	sort(b + 1, b + n + 1);
	for (int i = 1; i <= n; i++)
	{
		if (a[i] < b[i]) ans += (b[i] - a[i]) * x;
		else ans += (a[i] - b[i]) * y;
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
