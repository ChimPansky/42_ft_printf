#include "ft_printf.h"
#include <limits.h>
#include <stdio.h>

int	main(void)
{
	char *s2 = "Mussum Ipsum, cacilds vidis litro abertis. Posuere libero varius. Nullam a nisl ut ante blandit hendrerit. Aenean sit amet nisi. Atirei o pau no gatis, per gatis num morreus.";

	/*
	//TEST(8, print(" %s %s %s %s %s", " - ", "", "4", "", s2));
	printf("%d\n",ft_printf(" %s %s %s %s %s", " - ", "", "4", "", s2));
	printf("%d\n",ft_printf("%s\n", s2));
	printf("\n");
	printf("%d",printf(" %s %s %s %s %s", " - ", "", "4", "", s2)) ;
	*/
	//printf("%d",printf("%p", NULL));
	//printf("long max test: %u\n", LONG_MAX);
	//ft_printf("long max test: %u\n", LONG_MAX);
	int a = ft_printf("%x", -25);
	printf("\na: %d\n", a);
	int b = printf("%x", -25);
	printf("\nb: %d\n", b);
	return (0);
}
