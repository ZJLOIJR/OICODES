#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

typedef long long ll;
const int N = 5e4 + 7;

int n;
ll p, q, a[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i);
	sort(a + 1, a + n + 1);
	for (int i = 1; i <= n; i++)
		if (i & 1) p += a[i];
		else q += a[i];
	printf("%lld\n", p > q ? p - q : q - p);
	return 0;
}
