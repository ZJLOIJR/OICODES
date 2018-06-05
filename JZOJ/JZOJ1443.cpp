#include <cstdio>
#include <cstring>

int n, a, b, ans;
int buc1[101], buc2[101], tmp1[101], tmp2[101];

inline int max(int a, int b) { return a > b ? a : b; }

int main()
{
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d%d", &a, &b);
		buc1[a]++, buc2[b]++;
		memcpy(tmp1, buc1, sizeof(buc1));
		memcpy(tmp2, buc2, sizeof(buc2));
		ans = 0;
		int i = 1, j = 100;
		while (i <= 100 && j >= 1)
		{
			while (!tmp1[i] && i <= 100) i++;
			while (!tmp2[j] && j >= 1) j--;
			if (i > 100 || j < 1) break;
			ans = max(ans, i + j);
			if (tmp1[i] > tmp2[j]) tmp1[i] -= tmp2[j], tmp2[j] = 0;
			else tmp2[j] -= tmp1[i], tmp1[i] = 0;
		}
		printf("%d\n", ans);
	}
	return 0;
}
