#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 3007, V = 10007;
int f[V];
int n, v, sum = 0, ans = 0;
struct thing
{
	int t, c;
} things[N];

int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d%d", &n, &v);
	for (int i = 1; i <= n; i++)
		scanf("%d%d", &things[i].t, &things[i].c);
	sort(things + 1, things + n + 1, [](thing a, thing b){ return a.t * b.c < b.t * a.c; });
	for (int i = 1; i <= n; i++)
		for (int j = v; j >= things[i].t; j--)
		{
			f[j] = max(f[j], f[j - things[i].t] + (v - j + things[i].t) * things[i].c);
			ans = max(f[j], ans);
		}
	printf("%d\n", ans);
	return 0;
}