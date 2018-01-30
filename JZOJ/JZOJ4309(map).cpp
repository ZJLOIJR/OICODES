#include <map>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

const int M = 107;

int n, m, opt, num, tot = 0;
map<int, int> buc, arr;
int numbers[M];

int main()
{
	freopen("problem.in", "r", stdin);
	freopen("problem.out", "w", stdout);

	scanf("%d%d", &n, &m);
	while (m--)
	{
		scanf("%d", &opt);
		if (opt == 1)
		{
			scanf("%d", &num);
			numbers[++tot] = num;
			buc[num] = -1;
		}
		else if (opt == 2)
		{
			scanf("%d", &num);
			numbers[++tot] = num;
			if (buc[num] != -1)
				buc[num] = 1;
		}
		else
		{
			arr.clear();
			for (int i = tot, cnt = 0; i > 0 && cnt < 20; i--)
				if (arr[numbers[i]] == 0 && buc[numbers[i]] == 1)
					printf("%d ", numbers[i]), cnt++, arr[numbers[i]] = 1;
			printf("\n");
		}
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}