#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const int N = 1e5 + 7;
const ll P = 1000000007LL;

int n;
ll f[N];

int main()
{
	f[1] = f[2] = 0, f[3] = 1;
	for (int i = 4; i <= N - 7; i++) f[i] = ((f[i - 1] + f[i - 2] % P) * (i - 1) % P + f[i - 3]) % P;
	while (~scanf("%d", &n)) printf("%lld\n", (f[n] - f[n - 1] + P) % P);
	return 0;
}
