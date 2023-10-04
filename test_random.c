#include <stdlib.h>
#include <stdio.h>
#include "include/libft.h"

int main()
{
	char	*str1;
	char	*str2;
	char	*str3;
	char	*result1;
	char	*result2;

	str1 = malloc(10);
	str2 = malloc(10);
	str1[0] = 'A';
	str1[1] = 'B';
	str1[2] = 'C';
	str1[3] = '\0';
	str2[0] = 'X';
	str2[1] = '\0';

	result1 = ft_strjoin_free(str1, str2, 3);
	printf("result1: %s\n", result1);
	//printf("str1: %s\n", str1);
	//printf("str2: %s\n", str2);

	str3 = malloc(10);
	str3[0] = 'A';
	str3[1] = 'B';
	str3[2] = 'C';
	str3[3] = '\0';


	result2 = ft_substr_free(str3, 0, 2, 1);
	printf("result2: %s\n", result2);
	//printf("str3: %s\n", str3);
	free(result1);
	free(result2);

	char *str4 = malloc(10);
	str4[0] = 'x';
	str4[1] = 'y';
	str4[2] = 'z';
	str4[3] = '\0';


	char *result4 = ft_strrpad_free(str4, '0', 10, 1);
	printf("result2: %s\n", result4);
	free(result4);



}
