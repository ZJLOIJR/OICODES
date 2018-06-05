#include <cstdio>
#include <cstring>
#include <cstdlib>

const int N = 1e6 + 7;

int top1 = 0, top2 = 0;
bool num[N];
char opt[N];

int level(char c)
{
	if (c == '!') return 3;
	else if (c == '&') return 2;
	else if (c == '|') return 1;
	else if (c == '(') return 0;
}

void calc()
{
	if (opt[top2] == '&')
	{
		bool a = num[top1--], b = num[top1--];
		num[++top1] = a & b;
	}
	else if (opt[top2] == '|')
	{
		bool a = num[top1--], b = num[top1--];
		num[++top1] = a | b;
	}
	else
	{
		bool a = num[top1--];
		num[++top1] = !a;
	}
}

int main()
{
	freopen("boolean.in", "r", stdin);
	freopen("boolean.out", "w", stdout);
	
	for (char ch = getchar(); ch != EOF; ch = getchar())
		if (ch == '(') opt[++top2] = '(';
		else if (ch == 'V' || ch == 'F') num[++top1] = ch == 'V' ? true : false;
		else if (ch == '&' || ch == '|' || ch == '!')
		{
			if (ch != '!') while (top2 && level(opt[top2]) >= level(ch)) calc(), top2--;
			opt[++top2] = ch;
		}
		else if (ch == ')')
		{
			while (opt[top2] != '(') calc(), top2--;
			top2--;
		}
	while (top2) calc(), top2--;
	putchar(num[1] == true ? 'V' : 'F');

	fclose(stdin);
	fclose(stdout);
	return 0;
}
