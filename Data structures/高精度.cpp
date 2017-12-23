struct largeint
{
	int len;
	int arr[LEN];
	
	void init()
	{
		memset(arr, 0, sizeof(arr));
	}

	largeint& operator=(int x)
	{
		len = 0;
		while (x)
		{
			arr[++len] = x % 10;
			x /= 10;
		}
		return *this;
	}

	largeint& operator=(largeint a)
	{
		len = a.len;
		memcpy(arr, a.arr, sizeof(a.arr));
		return *this;
	}

	largeint& operator+(largeint a)
	{
		int mxlen = len > a.len ? len : a.len;
		int c[LEN];
		memset(c, 0, sizeof(c));
		for (int i = 1; i <= mxlen; i++)
		{
			c[i] += arr[i] + a.arr[i];
			c[i + 1] = c[i] / 10;
			c[i] %= 10;
		}
		if (c[mxlen + 1] > 0)
			mxlen++;
		len = mxlen;
		memcpy(arr, c, sizeof(c));
		return *this;
	}
};
