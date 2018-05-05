#include <cstdio>

const int N = 1e3 + 3;

int n, sg[N];

int main()
{
	for (int i = 1; i <= N - 3; i++)
		for (int j = 1; j <= i; j <<= 1)
			if (sg[i - j] == 0) { sg[i] = 1; break; }
	while (~scanf("%d", &n))
	{
		if (sg[n]) printf("Kiki\n");
		else printf("Cici\n");
	}
	return 0;
}
