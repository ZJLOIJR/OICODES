//Expect: woyebuzhidao points
#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

typedef long long ll;
const int N = 1e4 + 7;

ll ans, a[N], x, y;
priority_queue<ll> heap;
int n;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), heap.push(-a[i]);
	while (heap.size() > 1)
	{
		x = -heap.top(), heap.pop();
		y = -heap.top(), heap.pop();
		ans += x + y, heap.push(-(x + y));
	}
	printf("%lld\n", ans);
	return 0;
}
