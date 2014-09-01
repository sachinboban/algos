#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

/*
 * matrix_chain
 * @dimen_seq		array of dimentions of A(0)...A(n-1) matrices
 * @dimen_seq_len	length of dimention seq (n+1)
 *
 * Given are dimentions of n matrices A(0)...A(n-1) with dimentions of A(i) as
 * d(i)Xd(i+1). The procedure finds the optimal parenthization for the matrix
 * chain such the number of scalar multiplications is the minimum for the given
 * dimention sequence. The procedure follows bottom-up method, so that before
 * computing a subproblem all the smaller subproblem it depends on are solved
 * first.
 */
void matrix_chain(int *dimen_seq, int dimen_seq_len);

int main()
{
	int *dimen_seq = NULL;
	int idx, dimen_seq_len = 0;

	scanf("%d", &dimen_seq_len);

	dimen_seq = (int *)malloc(sizeof(int)  * dimen_seq_len);
	if(!dimen_seq) {
		printf("[%s]ERROR: malloc()\n", __FUNCTION__);
		return 0;
	}

	memset(dimen_seq, 0, sizeof(int) * dimen_seq_len);

	for(idx = 0; idx < dimen_seq_len; idx += 1)
		scanf("%d", &dimen_seq[idx]);

	matrix_chain(dimen_seq, dimen_seq_len);

	free(dimen_seq);
	return 0;
}

void matrix_chain(int *dimen_seq, int dimen_seq_len)
{
	int loop, row_idx, col_idx, temp, idx;
	int n = dimen_seq_len - 1;	//Number of matrices
	int *cost = NULL;			//Stores the optimal cost
	int *pos = NULL;			//Stores position of parenthization

	cost = (int *)malloc(sizeof(int) * n * n);
	if(!cost) {
		printf("[%s:%d]ERROR: malloc()\n", __FUNCTION__, __LINE__);
		return;
	}

	pos = (int *)malloc(sizeof(int) * n * n);
	if(!pos) {
		printf("[%s:%d]ERROR: malloc()\n", __FUNCTION__, __LINE__);
		free(cost);
		return;
	}

	memset(cost, 0, sizeof(int) * n * n);
	memset(pos, 0, sizeof(int) * n * n);

	/* Cost array is calculated diagonally, since we are using the bottom-up
	 * approach */
	for(loop = 1; loop < n; loop += 1) {
		for(row_idx = 0; row_idx < n - loop; row_idx += 1) {
			int k;

			col_idx = row_idx + loop;
			idx = row_idx * n + col_idx;

			cost[idx] = INT_MAX;

	/*
	 * cost(row_idx, col_idx) = min(cost(row_idx, k) + cost(k+1, col_idx)
	 *	 							+ d(row_idx) * d(k+1) * d(col_idx+1))
	 */
			for(k = row_idx; k < col_idx; k += 1) {
				temp = cost[row_idx * n + k]
						+ cost[(k + 1) *n + col_idx]
						+ (dimen_seq[row_idx] * dimen_seq[k + 1]
							* dimen_seq[col_idx + 1]);
				if(temp < cost[idx]) {
					cost[idx] = temp;
					pos[idx] = k + 1;
				}
			}
		}
	}

	for(row_idx = 0; row_idx < n; row_idx += 1) {
		printf("\n");
		for(col_idx = 0; col_idx < n; col_idx += 1) {
			if(row_idx >= col_idx)
				printf("%5.s ", "");
			else
				printf("%5.d ", cost[row_idx * n + col_idx]);
		}
	}

	for(row_idx = 0; row_idx < n; row_idx += 1) {
		printf("\n");
		for(col_idx = 0; col_idx < n; col_idx += 1) {
			if(row_idx >= col_idx)
				printf("%5.s ", "");
			else
				printf("%5.d ", pos[row_idx * n + col_idx]);
		}
	}

	free(pos);
	free(cost);
}
