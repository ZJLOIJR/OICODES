#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1000007, INF = 0x7fffffff;
typedef long long ll; //不开long long,WA临头

int n, q, l, r, mid, ans = 0;
int lef[N], rig[N]; //必需存下每个人的需求
ll a[N], c[N], w[N];

int check(int m)
{
	for (int i = 1; i <= n; i++) c[i] = a[i] - a[i - 1]; //初始化差分数组
	ll sum = 0;
	for (int i = 1; i <= m; i++)
		c[lef[i]] += w[i], c[rig[i] + 1] -= w[i]; //参考上面所说的
	for (int i = 1; i <= n; i++)
	{
		sum += c[i]; //计算c的前i项的和得到a[i]
		if (sum < 0) return 0; //a[i] < 0即a[i]为负数,前mid个人无法满足
	}
	return 1; //可以满足
}

inline ll read() //读入优化,卡常大法好
{
	ll x = 0, f = 0;
	char c = getchar();
	for (; c < '0' || c > '9'; c = getchar()) if (c == '-') f = 1;
	for (; c >= '0' && c <= '9'; c = getchar()) x = (x << 1) + (x << 3) + c - '0';
	return f ? -x : x;
}

int main()
{
	n = read(), q = read();
	for (int i = 1; i <= n; i++)
		*(a + i) = read(), //骚读入
		c[i] = a[i] - a[i - 1];
	for (int i = 1; i <= q; i++)
		*(w + i) = read(), *(lef + i) = read(), *(rig + i) = read(), //骚读入
		w[i] = -w[i]; //由于是要-w[i]所以这里取反
	l = 1, r = q;
	while (l <= r)
	{
		mid = l + r >> 1; //二分答案
		if (check(mid)) l = mid + 1, ans = mid; //记录答案
		else r = mid - 1;
	}
	if (ans + 1 > q) printf("0\n"); //全部都能满足
	else printf("-1\n%d\n", ans + 1); //输出答案+1
	return 0;
}
