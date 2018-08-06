#include <queue>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

char opt;
int n, a;
priority_queue<int> heap;

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n - 1; i++)
	{
		scanf(" %c%d", &opt, &a);
		if (opt == 'c') heap.push(-a);
		else while (heap.size() >= a) heap.pop();
	}
	scanf(" %c%d", &opt, &a);
	if (heap.size() < a) printf("-1\n");
	else
	{
		long long ans = 0;
		while (!heap.empty()) ans += -heap.top(), heap.pop();
		printf("%lld\n", ans);
	}
	return 0;
}
