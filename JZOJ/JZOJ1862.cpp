#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e3 + 3;

int m, n, x, ans = 0, t = 0;
int meo[N];

inline int inmeo(int x)
{
	for (int i = 1; i <= t; i++) if (meo[i] == x) return 1;
	return 0;
}

int main()
{
	scanf("%d%d", &m, &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d", &x);
		if (!inmeo(x))
		{
			ans++;
			if (t < m) meo[++t] = x;
			else
			{
				for (int j = 1; j <= t - 1; j++) meo[j] = meo[j + 1];
				meo[t] = x;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}
