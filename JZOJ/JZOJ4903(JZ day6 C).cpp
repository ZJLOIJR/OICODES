#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e5 + 7;

int n, m, x, y, now = 0;

struct person
{
	int forward;
	char job[30];
} a[N];

int main()
{
	freopen("toy.in", "r", stdin);
	freopen("toy.out", "w", stdout);

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++) scanf("%d%s", &a[i].forward, &a[i].job);
	while (m--)
	{
		scanf("%d%d", &x, &y);
		if (a[now].forward) x ^= 1;
		if (x == 0) now = (now - y + n) % n;
		else now = (now + y) % n;
	}
	printf("%s\n", a[now].job);

	fclose(stdin);
	fclose(stdout);
	return 0;
}