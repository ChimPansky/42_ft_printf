#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

void print_test(char *format, int mine)
{
	int ret;
	if (mine)
	{
	//	printf("Mine    : ");
		ret = ft_printf(format, '0', 0, '0');
		printf("\nMy Return Val      : %d\n", ret);
	}
	else
	{
	//	printf("Expected: ");
		ret = printf(format, '0', 0, '0');
		printf("\nExpected Return Val: %d\n\n\n", ret);
	}
}

int	main()
{
	int	i;
	int ret;
	char *format;
	int x;

	i = 1;

	format = "%c %c %c";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, '0', 0, '0');
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, '0', 0, '0');
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = "%c";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, '0' - 256);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, '0' - 256);
	printf("\nExpected Return Val: %d\n\n\n", ret);


	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, LONG_MIN, LONG_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, LONG_MIN, LONG_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, INT_MIN, INT_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, INT_MIN, INT_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";
	ft_putendl_fd(format, 1);
	ret = ft_printf(format, ULONG_MAX, -ULONG_MAX);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, ULONG_MAX, -ULONG_MAX);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = " %p %p ";

	ft_putendl_fd(format, 1);
	ret = ft_printf(format, 1, 0);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, 1, 0);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	format = "%%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %%%c%%%s%%%d%%%i%%%u%%%x%%%X%%%% %c%%";

	ft_putendl_fd(format, 1);
	ret = ft_printf(format, 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	printf("\nMy Return Val      : %d\n", ret);
	ret = printf(format, 'A', "42", 42, 42 ,42 , 42, 42, 'B', "-42", -42, -42 ,-42 ,-42, 42, 'C', "0", 0, 0 ,0 ,0, 42, 0);
	printf("\nExpected Return Val: %d\n\n\n", ret);

	int	ft_ret;
	ret = printf("%05d%%%whaaat", 'X', "def");
	printf("\n");
	ft_ret = ft_printf("%05d%%%whaaat", 'X', "def");
	printf("\n");
	printf("ret: %d\n", ret);
	printf("ft_ret: %d\n", ft_ret);

	//ret = ft_strlen ('a');
	//printf("%d\n", ret);
	ret = ft_printf("%c", 0);
	printf("%d\n\n\n\n", ret);

	ret = ft_printf("%10c|\n", 'A');
	ret = ft_printf("%-10c|\n", 'A');

	ret = printf("%10c|\n", 'A');
	ret = printf("%-10c|\n", 'A');
	//printf("%d\n", ret);


	//ft_printf('a');

/*
	format = "%c %c %c";
	x = printf("Test 1: \"%s\"\n", format);
	x = printf("Mine    : ");
	my_ret = ft_printf(format, '0', 0, '0');
	x = printf("\nMy Return Val      : %d\n", my_ret);
	x = printf("Expected: ");
	xp_ret = printf(format, '0', 0, '0');./a
	x = printf("\nExpected Return Val: %d\n\n\n", xp_ret);

	x = printf("Test 1: \"%s\" \n", format);
*/
/*
32: 	TEST(8, print(" %c %c %c ", '2', '1', 0));
33: 	TEST(9, print(" %c %c %c ", 0, '1', '2'));
*/
	//printf("lpad: %s\n", ft_strlpad("abc", 'O', 15));

    return 0;
}
