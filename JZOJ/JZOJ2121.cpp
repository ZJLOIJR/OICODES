#include <cstdio>
#include <cstring>
#include <cstdlib>

const int INF = 0x3f3f3f3f;

int T, n, ans, space, ball;
char ch, str[20];

struct status { char arr[20]; } start, end[20];
void trans(status S)
{
	space = 1;
	while (S.arr[space] != ' ') space++;
	ball = 0;
	for (int i = 1; i <= 2 * n; i++) if (S.arr[i] != ' ') ball = ball * 2 + (S.arr[i] - 'a');
}

int head, tail;
status que[20 * (1 << 14)];
int dis[20][1 << 14];
void bfs()
{
	head = 1, tail = 0;
	memset(dis, 0, sizeof(dis));
	que[++tail] = start;
	trans(start), dis[space][ball] = 1;
	while (head <= tail)
	{
		status now = que[head++], next;
		trans(now);
		int spnow = space, banow = ball;
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			if (now.arr[i] == ' ' || now.arr[i + 1] == ' ') continue;
			memcpy(next.arr, now.arr, sizeof(now.arr));
			next.arr[spnow] = now.arr[i], next.arr[spnow + 1] = now.arr[i + 1];
			next.arr[i] = next.arr[i + 1] = ' ';
			trans(next);
			if (!dis[space][ball]) dis[space][ball] = dis[spnow][banow] + 1, que[++tail] = next;
		}
	}
}

int main()
{
	scanf("%d", &T);
	while (T--)
	{
		scanf("%d", &n);
		getchar(); ch = getchar();
		for (int i = 1; i <= 2 * n; i++, ch = getchar()) str[i] = ch;
		memcpy(start.arr, str, sizeof(str));
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			memset(end[i].arr, 0, sizeof(end[i].arr));
			end[i].arr[i] = end[i].arr[i + 1] = ' ';
			for (int j = 1, cnt = 0; j <= 2 * n, cnt < n - 1; j++)
				if (end[i].arr[j] != ' ' && end[i].arr[j] != 'b') end[i].arr[j] = 'a', cnt++;
			for (int j = 1, cnt = 0; j <= 2 * n, cnt < n - 1; j++)
				if (end[i].arr[j] != ' ' && end[i].arr[j] != 'a') end[i].arr[j] = 'b', cnt++;
		}
		bfs();
		ans = INF;
		for (int i = 1; i <= 2 * n - 1; i++)
		{
			trans(end[i]);
			if (dis[space][ball] && dis[space][ball] < ans) ans = dis[space][ball];
		}
		if (ans == INF) printf("-1\n");
		else printf("%d\n", ans - 1);
	}
	return 0;
}
