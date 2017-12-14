//一般图最大匹配,邻接阵形式,复杂度 O(n^3)
//返回匹配顶点对数,match 返回匹配,未匹配顶点 match 值为-1
//传入图的顶点数 n 和邻接阵 mat
#define MAXN 100
int aug(int n, int mat[][MAXN], int* match, int* v, int now) {
	int i, ret = 0;
	v[now] = 1;
	for (i = 0; i<n; i++)
		if (!v[i] && mat[now][i]) {
			if (match[i]<0)
				match[now] = i, match[i] = now, ret = 1;
			else {
				v[i] = 1;
				if (aug(n, mat, match, v, match[i]))
					match[now] = i, match[i] = now, ret = 1;
				v[i] = 0;
			}
			if (ret)
				break;
		}
	v[now] = 0;
	return ret;
}
int graph_match(int n, int mat[][MAXN], int* match) {
	int v[MAXN], i, j;
	for (i = 0; i<n; i++)
		v[i] = 0, match[i] = -1;
	for (i = 0, j = n; i<n&&j >= 2;)
		if (match[i]<0 && aug(n, mat, match, v, i))
			i = 0, j -= 2;
		else
			i++;
	for (i = j = 0; i<n; i++)
		j += (match[i] >= 0);
	return j / 2;
}