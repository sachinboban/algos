/******************************************************************************
 * DOCUMENTATION
 ******************************************************************************
 * Subsequence
 *	A sequence Z=<z1...zm> is a subsequence of X =<x1....xn>, if there exists
 *	a strictly increasing sequence <i1,i2...im> of indices of X such that
 )*	xij = zj
 *
 * Prefix
 *	Given a sequence X=<x1,x2,...xm>, then the prefix of X Xi is given by
 *	Xi=<x1,x2...xi> and x0=<> i.e. an empty sequence
 *
 * Optimal Substructure of an LCS
 *	Consider two sequences X=<x1,x2...xm> and Y=<y1,y2...yn> and Z<z1...zk>
 *	=LCS(X,Y). Then,
 *	1. if xm = yn then zk = xn = yn  and Z(k-1) = LCS(Xm-1,Yn-1)
 *	2. if xm !=yn then
 *		a. if zk != xm implies Z = LCS(Xm-1, Y)
 *		b. if zk != yn implies Z = LCS(X, Yn-1)
 *****************************************************************************/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_LEN			256
#define INDEX(n, i , j)	(n * (i) + (j))
#define MV_UP			1
#define MV_DIAG			2
#define MV_LEFT			3

/*
 * If MORE_INFO is enabled it also prints the arrays used in dynamic
 * programming
 */
#define MORE_INFO		0

/*
 * seq_struct
 * @string		character string
 * @len			length of string
 *
 * structure representing a sequence. It is typecasted as seq_t
 */
struct seq_struct {
	char string[MAX_LEN];
	int len;
};

typedef struct seq_struct seq_t;

void lcs_print(int *opt_choice, seq_t *seq, int len_x, int len_y);
int lcs(seq_t *seq_x, seq_t *seq_y);

int main()
{
	seq_t seq_x, seq_y;

	/*
	 * gets() is deprecated. Instead we have to use fgets)_. But fgets() also
	 * read <newline> character into the string. It does not create any problem
	 * for the lcs method, but we just remove the <newline> character by
	 * replacing it with null character.
	 */
	fgets(seq_x.string, MAX_LEN, stdin);
	fgets(seq_y.string, MAX_LEN, stdin);

	seq_x.string[strlen(seq_x.string) - 1] = '\0';
	seq_y.string[strlen(seq_y.string) - 1] = '\0';

	seq_x.len = strlen(seq_x.string);
	seq_y.len = strlen(seq_y.string);

	lcs(&seq_x, &seq_y);

	return 0;
}

int lcs(seq_t *seq_x, seq_t *seq_y)
{
	int *len = NULL,		//len[i,j] will give the length of LCS(Xi, Yj)
		*opt_choice = NULL;	//opt_choice helps to construct the optimal soln
	int idx_x, idx_y, m, n;

	if(!seq_x || !seq_y) {
		printf("ERROR: No sequences specified.\n");
		return -1;
	}

	m = seq_x->len;
	n = seq_y->len;

	len = (int *)malloc(sizeof(int) * (m + 1) * (n + 1));
	if(!len) {
		printf("[%d]ERROR: malloc()\n", __LINE__);
		return 0;
	}

	opt_choice = (int *)malloc(sizeof(int) * m * n);
	if(!opt_choice) {
		printf("[%d]ERROR: malloc()\n", __LINE__);
		free(len);
		return 0;
	}

	memset(len, 0, sizeof(int) * (m + 1) * (n + 1));
	memset(opt_choice, -1, sizeof(int) * m * n);

	for(idx_x = 1; idx_x <= m; idx_x += 1) {
		for(idx_y = 1; idx_y <= n; idx_y +=1) {
			if(seq_x->string[idx_x - 1] == seq_y->string[idx_y - 1]) {
				len[INDEX(m, idx_x, idx_y)] = len[INDEX(m, idx_x - 1, idx_y - 1)] + 1;
				opt_choice[INDEX(m, idx_x - 1, idx_y - 1)] = MV_DIAG;
			} else if(len[INDEX(m, idx_x - 1, idx_y)] >= len[INDEX(m, idx_x, idx_y - 1)]) {
				len[INDEX(m, idx_x, idx_y)] = len[INDEX(m, idx_x - 1, idx_y)];
				opt_choice[INDEX(m, idx_x - 1, idx_y - 1)] = MV_UP;
			} else {
				len[INDEX(m, idx_x, idx_y)] = len[INDEX(m, idx_x, idx_y - 1)];
				opt_choice[INDEX(m, idx_x - 1, idx_y - 1)] = MV_LEFT;
			}
		}
	}

	lcs_print(opt_choice, seq_x, m, n);

	printf("\n");

	if(MORE_INFO) {
		for(idx_x = 0; idx_x <= m; idx_x += 1) {
			for(idx_y = 0; idx_y <= n; idx_y += 1) {
				printf("%d", len[INDEX(m, idx_x, idx_y)]);
				if(idx_x>0 && idx_y>0) {
					switch(opt_choice[INDEX(m, idx_x-1, idx_y-1)]) {
						case MV_UP:
							printf("[U] ");
							break;

						case MV_DIAG:
							printf("[D] ");
							break;

						case MV_LEFT:
							printf("[L] ");
							break;
					}
				}else
					printf("[ ] ");
			}
			printf("\n");
		}
	}


	free(opt_choice);
	free(len);

	return 0;
}

void lcs_print(int *opt_choice, seq_t *seq, int len_x, int len_y)
{
	int m;

	if(!seq || !opt_choice)
		return;

	m = seq->len;

	if(len_x == 0 || len_y == 0)
		return;

	if(opt_choice[INDEX(m, len_x - 1, len_y - 1)] == MV_DIAG) {
		lcs_print(opt_choice, seq, len_x - 1, len_y - 1);
		printf("%c", seq->string[len_x - 1]);
	}else if(opt_choice[INDEX(m, len_x - 1, len_y - 1)] == MV_UP)
		lcs_print(opt_choice, seq, len_x - 1, len_y);
	else
		lcs_print(opt_choice, seq, len_x, len_y - 1);
}
