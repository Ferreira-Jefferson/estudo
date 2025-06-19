#include <stdio.h>
#include <stdlib.h>
 
void verify_number(int number)
{
	if(number == 0)
	{
		printf("NULL\n");
		return ;
	}

	if(number & 0x1)
		printf("ODD ");
	else
		printf("EVEN ");

	if(number >  0)
		printf("POSITIVE\n");
	else
		printf("NEGATIVE\n");	
}

int main() { 
    int qtt;
	int i = 0;
	
	scanf("%d%*c", &qtt);

	int *nums = malloc(qtt * sizeof(int));

	while(i < qtt)
		scanf("%d%*c", &nums[i++]);

	i = 0;
 	while(i < qtt)
		verify_number(nums[i++]);
		
	free(nums);
    return 0;
}