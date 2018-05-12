#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
using namespace std;

const int N = 2e2 + 3;

int n, totx, toty, ans;
int x[N][2], y[N][2], c[N], arrx[N], arry[N], col[N][N], buc[N * N];

int main()
{
	totx = toty = ans = 0;
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
	{
		scanf("%d%d%d%d%d", &x[i][0], &y[i][0], &x[i][1], &y[i][1], c + i);
		arrx[++totx] = x[i][0], arrx[++totx] = x[i][1];
		arry[++toty] = y[i][0], arry[++toty] = y[i][1];
	}
	sort(arrx + 1, arrx + totx + 1);
	totx = unique(arrx + 1, arrx + totx + 1) - arrx - 1;
	sort(arry + 1, arry + toty + 1);
	toty = unique(arry + 1, arry + toty + 1) - arry - 1;
	for (int i = 1; i <= n; i++)
	{
		x[i][0] = lower_bound(arrx + 1, arrx + totx + 1, x[i][0]) - arrx;
		x[i][1] = lower_bound(arrx + 1, arrx + totx + 1, x[i][1]) - arrx;
		y[i][0] = lower_bound(arry + 1, arry + toty + 1, y[i][0]) - arry;
		y[i][1] = lower_bound(arry + 1, arry + toty + 1, y[i][1]) - arry;
		for (int j = x[i][0] + 1; j <= x[i][1]; j++)
			for (int k = y[i][0] + 1; k <= y[i][1]; k++)
				col[j][k] += c[i];
	}
	for (int i = 1; i <= N - 3; i++)
		for (int j = 1; j <= N - 3; j++)
			if (col[i][j] && !buc[col[i][j]])
				ans++, buc[col[i][j]] = 1;
	printf("%d\n", ans);
	return 0;
}
