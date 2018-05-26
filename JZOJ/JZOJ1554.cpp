#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const ll P = 1000000007;
int T, n;
ll a[51], ans;

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		ans = 1;
		for (int i = 1; i <= n; i++) scanf("%lld", a + i);
		sort(a + 1, a + n + 1);
		for (int i = 1; i <= n; i++) ans = ans * (a[i] - i + 1) % P;
		printf("%lld\n", (ans + P) % P);
	}
	return 0;
}
