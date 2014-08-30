/*
 * Given a rod of length n and the selling pice for rods of length 1...n.
 * Assuming cutting the rods is free of cost. FInd the optimal cutting to get
 * maximum revenue frm the rod.
 * The solution can be done in two ways, in top-down fashion or bottom-up
 * fashion.
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<limits.h>

#define MODE_BOTTOM_UP	0
#define MODE_TOP_DOWN	1
#define MALLOC(len)	(int *)malloc(sizeof(int) * len)

/*
 * rod_cut_bottom_up
 * @price		array containing prices for rods of length 1...n
 * @len			length of the rod
 * @opt_rev		array for storing optimal revenue from rods of lenght 1...n
 * @opt_cut		array giving the optimal solution as where to cut
 *
 * Finds the optimal value as well as the optimal solution in bottom-up
 * approach. Before finding the optimal solution for a length 'n', we find
 * optimal solutions for length less than n on which the optimal solution for
 * length n depends and store it in opt_value.
 */
int rod_cut_bottom_up(int *price, int len, int *opt_rev, int *opt_cut);

/*
 * rod_cut
 * @price		array containing prices for rods of length 1...n
 * @len			length of the rod
 * @mode		bottom-up or top-down
 *
 * Wrapper function for rod_cut_bottom_up() and rod_cut_top_down(). Depending
 * upon the mode specified, it selects the function for the corresspoding
 * approach.
 */
int rod_cut(int *price, int len, int mode);

int main()
{
	int idx, mode, len, ret = 0;
	int *price = NULL;

	scanf("%d", &len);
	scanf("%d", &mode);

	price = MALLOC(len);
	if(!price) {
		printf("[%s]ERROR: malloc\n", __FUNCTION__);
		return 0;
	}

	for(idx = 0; idx < len; idx += 1)
		scanf("%d", &price[idx]);
	
	ret = rod_cut(price, len, mode);

	return ret;
}

int rod_cut(int *price, int len, int mode)
{
	int ret = 0;
	int *opt_rev = NULL, *opt_cut = NULL;

	opt_rev = MALLOC(len);
	if(!opt_rev) {
		ret = 1;
		goto error_malloc1;
	}

	opt_cut = MALLOC(len);
	if(!opt_cut) {
		ret = 1;
		goto error_malloc2;
	}

	memset(opt_rev, INT_MIN, len);
	memset(opt_cut, 0, len);

	switch(mode) {
		case MODE_BOTTOM_UP:
			ret = rod_cut_bottom_up(price, len, opt_rev, opt_cut);
			break;

		/*case MODE_TOP_DOWN:
			ret = rod_cut_top_down(price, len, opt_rev, opt_cut);
			break;*/
		
		default:
			printf("[%s]ERROR: unknown mode[%d]\n", __FUNCTION__, mode);
			ret = 1;
	}

	if(ret)
		goto error_rod_cut_fail;
	
error_rod_cut_fail:
	free(opt_cut);
error_malloc2:
	free(opt_rev);
error_malloc1:

	return ret;
}
