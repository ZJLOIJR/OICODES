#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int LEN = 15;

int len;
char str[LEN];
long long x, ans = 0;

void dfs(int dep, long long sum)
{
	if (dep > len)
	{
		if (sum > x) ans++;
		return;
	}
	if (str[dep] == '?')
		for (int i = 0; i < 10; i++)
			dfs(dep + 1, sum * 10 + i);
	else
		dfs(dep + 1, sum * 10 + str[dep] - '0');
}

int main()
{
	scanf("%s%lld", str + 1, &x);
	len = strlen(str + 1);
	dfs(1, 0);
	printf("%lld\n", ans);
	return 0;
}
