#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
inline int max(int a, int b) { return a > b ? a : b; }

const int N = 1e5 + 7;

int n, len, num[64];
int tot = 1, son[N * 64][2];
long long a[N], ans = 0;

void insert()
{
	int now = 1;
	for (int i = len; i >= 1; i--)
	{
		if (!son[now][num[i]]) son[now][num[i]] = ++tot;
		now = son[now][num[i]];
	}
}

long long getans()
{
	int now = 1; long long ret = 0;
	for (int i = len; i >= 1; i--)
	{
		if (son[now][!num[i]]) now = son[now][!num[i]];
		else now = son[now][num[i]];
	}
	return ret;
}

int main()
{
	//freopen("xor.in", "r", stdin);
	//freopen("xor.out", "w", stdout);
	
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%lld", a + i);
		len = 0;
		long long tmp = a[i];
		while (tmp) num[++len] = tmp & 1, tmp >>= 1;
		insert();
	}
	for (int i = 1; i <= n; i++)
	{
		len = 0;
		long long tmp = a[i];
		while (tmp) num[++len] = tmp & 1, tmp >>= 1;
		ans = max(ans, a[i] ^ getans());
	}
	printf("%lld\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}
