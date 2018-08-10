#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;

int tot;
ll n, rt, arr[20000007];

void check(ll a)
{
	if ((a + 1) % 2 > 0 || (a + 1) / 2 == 1) return;
	arr[++tot] = n / a * (a - 1);
}

int main()
{
	freopen("math.in", "r", stdin);
	freopen("math.out", "w", stdout);

	scanf("%lld", &n);
	rt = sqrt(n);
	for (ll i = 1; i <= rt; i++)
		if (n % i == 0)
		{
			check(i);
			if (n / i != i) check(n / i);
		}
	sort(arr + 1, arr + tot + 1);
	printf("%d ", tot);
	for (int i = 1; i <= tot; i++) printf("%lld ", arr[i]);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
