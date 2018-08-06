#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 3e3 + 7;
const double eps = 1e-9;

int n, x[N], y[N];
double slope[N];
ll ans = 0;

int main()
{
	freopen("triangle.in", "r", stdin);
	freopen("triangle.out", "w", stdout);
	
	scanf("%d", &n);
	ans = n * 1LL * (n - 1) * (n - 2) / 6;
	for (int i = 1; i <= n; i++) scanf("%d%d", x + i, y + i);
	for (int i = 3; i <= n; i++)
	{
		for (int j = 1; j <= i - 1; j++) slope[j] = x[j] == x[i] ? 233333333.0 : (y[j] - y[i]) * 1.0 / (x[j] - x[i]);
		sort(slope + 1, slope + i);
		int j = 2, last = 1;
		while (j <= i - 1)
		{
			if (slope[j] - slope[last] >= eps) ans -= (j - last) * 1LL * (j - last - 1) / 2, last = j;
			j++;
		}
		ans -= (j - last) * 1LL * (j - last - 1) / 2;
	}
	printf("%lld\n", ans);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
