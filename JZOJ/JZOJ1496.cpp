#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

int n, tot = 0, st = 0, en = 0, flag = 0, a[10], buc[200], pow[10];
int head = 1, tail = 0, que[10000007];
map<int, int> dis;

int getdigit(int s, int po) { return s / pow[n - po] % n; }

int main()
{
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), buc[a[i]] = 1;
	pow[0] = 1; for (int i = 1; i <= n; i++) pow[i] = pow[i - 1] * n;
	for (int i = 160; i <= 190; i++)
		if (buc[i])
		{
			tot++;
			for (int j = 1; j <= n; j++) if (a[j] == i) a[j] = tot;
		}
	for (int i = 1; i <= n; i++) st = st * n + (a[i] - 1);
	for (int i = 1; i <= n; i++) en = en * n + (i - 1);
	que[++tail] = st, dis[st] = 0;
	while (head <= tail)
	{
		int S = que[head++];
		if (S == en) { flag = 1; break; }
		int middle = getdigit(S, (n + 1) / 2), left = S / pow[(n + 1) / 2] % pow[n / 2], right = S % pow[n / 2];
		int S1 = S - middle * pow[n / 2] - right + middle + right * pow[1]; //放到队尾
		int S2 = S - middle * pow[n / 2] - left * pow[(n + 1) / 2] + middle * pow[n - 1] + left * pow[(n + 1) / 2 - 1]; //放到队头
		if (!dis[S1] && S1 != st) dis[S1] = dis[S] + 1, que[++tail] = S1;
		if (!dis[S2] && S2 != st) dis[S2] = dis[S] + 1, que[++tail] = S2;
	}
	if (flag) printf("%d\n", dis[en]);
	else printf("No Answer\n");
	return 0;
}
