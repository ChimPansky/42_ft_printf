#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

int	main()
{
	int	ret;
	int ft_ret;
	char *str;

	//ft_printf("%0+   #   +--+1046.  30s\n\n\n", "abc");
/*
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



	long ltest = 2147483648;
	int	itest = -3215634;
	unsigned int uitest = (unsigned int)itest;


	printf("ltest: %li\n", ltest);
	printf("itest: %i\n", itest);
	printf("uitest: %lu\n", uitest);


    printf("The largest number a long can hold is     : %ld\n", LONG_MAX);
	printf("The largest number a long long can hold is: %lld\n", LLONG_MAX);
	printf("pointer test -10: %p\n", -10);
	printf("pointer test abc: %p\n", &"abc");
	int a = 15;
	int *ptrtest = &a;
	printf("pointer test ptrtest: %p\n", ptrtest);
	char *ibtest = ft_itoa_base_unsigned((size_t)ptrtest, "0123456789abcdef");
	printf("ibtest: %s\n", ibtest);
	printf("printf ibtest: %p\n", ibtest);
	printf("o test: %o\n\n\n\n\n", -0);


	//ptrtest = NULL;
	char *str1 = NULL;

	ret = printf("%p\n", ptrtest);
	printf("ret: %d\n", ret);
	ft_ret = ft_printf("%p\n", ptrtest);
	printf("ft_ret: %d\n", ft_ret);
	ft_ret = ft_printf("char: %c\n", 68);
	printf("ret: %d\n", ft_ret);
	ft_ret = ft_printf("str1: %s\n", str1);
	printf("ret: %d\n\n", ft_ret);
*/
	int a = 15;
	int *ptrtest = &a;

	ret = printf("plus: % +  20.6d\n", 324);
	printf("ret: %d\n", ret);
	ft_ret = ft_printf("plus: %   + 20.6d\n", 324);
	printf("ft_ret: %d\n", ft_ret);

	//printf("lpad: %s\n", ft_strlpad("abc", 'O', 15));

    return 0;
}
