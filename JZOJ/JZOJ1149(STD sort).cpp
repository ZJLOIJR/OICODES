#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 2e5 + 3;

int n, a[N];

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	sort(a, a + n + 1);
	for (int i = 1; i <= n; i++) printf("%d\n", a[i]);
	return 0;
}
