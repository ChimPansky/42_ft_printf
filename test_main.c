#include "ft_printf.h"
#include <stdio.h>

int	main()
{
	int	ret;
	//printf("test %0-5d", "test");
	//printf("test %0-5d", 25);
	//ret = ft_printf("abc%%def\nghi");
	char *str;
	str = "STRING";
	//ret = ft_printf("%s", str);
	//ret = ft_printf("%s\n%d", "abcd", 42);
	//printf("\n\nret: %d\n", ret);

	int	ftest;

	ftest = 5;

	if (ftest & F_HASH)
		printf("1st: 1\n");
	else
		printf("1st: 0\n");
	if (ftest & F_ZERO)
		printf("2nd: 1\n");
	else
		printf("2nd: 0\n");
	if (ftest & F_MINUS)
		printf("3rd: 1\n");
	else
		printf("3rd: 0\n");
	if (ftest & 8)
		printf("4th: 1\n");
	else
		printf("4th: 0\n");

	char *form = "###  0d";
	char *s_flags = "-0# +";
	char *index;
	char c;

	index = ft_strchr(s_flags, *form);
	while (index && *form)
	{
		form++;
		printf("%s\n", index);
		index = ft_strchr(s_flags, *form);
	}
}
