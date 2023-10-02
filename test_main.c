#include "ft_printf.h"
#include <stdio.h>

int	main()
{
	int	ret;
	int ft_ret;
	char *str;

	str = "STRING";


	int	ftest;

	ftest = 5;
	ft_ret = ft_printf("abc%i\ndef% ", 4242);
	printf("ft_ret: %d\n", ft_ret);

	ret = printf("abc%i\ndef% ", 4242);
	printf("ret: %d\n", ret);

	//ft_printf("%0+   #   +--+1046.  30s\n\n\n", "abc");

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
