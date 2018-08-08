#include <map>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

inline int max(int a, int b) { return a > b ? a : b; }
const int N = 2e6 + 7;

struct node
{
	node* link;
	map<char, node*> next;
	int len, size;
};
node* t0; node* last; node* p; node* q; node* np; node* nq;
node* tmp[N << 1]; node* arr[N << 1];
int tot, length, buc[N];
char str[N];

int k, x, mx[N];
void add(int po, int val) { for (; po <= length; po += (po & (-po))) mx[po] = max(mx[po], val); }
int getmax(int po) { int ret = 0; for (; po; po -= (po & (-po))) ret = max(ret, mx[po]); return ret; }

node* newnode()
{
	node* ret = new node;
	tmp[++tot] = ret;
	ret->link = NULL, ret->next = map<char, node*>(), ret->len = 0, ret->size = 0;
	return ret;
}

void extend(char ch)
{
	p = last, np = newnode(), last = np;
	np->len = p->len + 1, np->size++;
	while (p && !p->next[ch]) p->next[ch] = np, p = p->link;
	if (!p) np->link = t0;
	else
	{
		q = p->next[ch];
		if (p->len + 1 == q->len) np->link = q;
		else
		{
			nq = newnode(), nq->len = p->len + 1;
			nq->next = q->next, nq->link = q->link;
			np->link = q->link = nq;
			while (p && p->next[ch] == q) p->next[ch] = nq, p = p->link;
		}
	}
}

int main()
{
	freopen("input", "r", stdin);
	freopen("output", "w", stdout);
	t0 = last = newnode();
	scanf("%s", str + 1);
	length = strlen(str + 1);
	for (int i = 1; i <= length; i++) extend(str[i]);
	for (int i = 1; i <= tot; i++) buc[tmp[i]->len]++;
	for (int i = 1; i <= length; i++) buc[i] += buc[i - 1];
	for (int i = 1; i <= tot; i++) arr[buc[tmp[i]->len]--] = tmp[i];
	for (int i = tot; i >= 2; i--) if (arr[i]->link) arr[i]->link->size += arr[i]->size;
	for (int i = 2; i <= tot; i++) add(length - arr[i]->size + 1, arr[i]->len);
	scanf("%d", &k);
	while (k--)
	{
		scanf("%d", &x);
		if (x > length) printf("0\n");
		else printf("%d\n", getmax(length - x + 1));
	}
	return 0;
}
