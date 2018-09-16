//这语文题做对的可以去做病句修改题了
#include <cstdio>
#include <cstring>
#include <cstdlib>

typedef long long ll;
const ll P = 1e9 + 7;
ll calc(ll n) { return n * (n + 1) % P * (2 * n + 1) % P * 166666668LL % P; }
char str[1000007];

int main()
{
	freopen("absurdity.in", "r", stdin);
	freopen("absurdity.out", "w", stdout);

	scanf("%*d%s", str);
	printf("%lld\n", calc(strlen(str)));

	fclose(stdin);
	fclose(stdout);
	return 0;
}
