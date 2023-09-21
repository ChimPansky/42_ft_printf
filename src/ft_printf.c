#include "../include/ft_printf.h"

/*int	ft_printf(const char *, ...)
{
	// TK:
	// handle variadic parameters...
	//iterate format string and output simple characters, or call conversion functions for every % encountered....

}
*/
int	main(void)
{
	enum e_flags	fflags;
	t_format	d_format;

	d_format.flags = 0;
	if ('#' == '#')
		d_format.flags += F_HASH;
	if ('0' == '0')
		d_format.flags += F_MINUS;
	if ('-' == '-')
		d_format.flags += F_MINUS;
	if (' ' == 'X')
		d_format.flags += F_SPACE;
	if ('.' == '.')
		d_format.flags += F_DOT;

	if (d_format.flags & F_HASH)
		printf("flags has Hash\n");

	printf("format.flags: %d\n", d_format.flags);
	return (0);
}
