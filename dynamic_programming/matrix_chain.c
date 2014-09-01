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
	
	return 0;
}
