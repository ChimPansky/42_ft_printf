#include "ft_printf_p.h"

void write_ptr(int fd, t_ft_printf_format *f_descr, void *ptr)
{
	if (ptr == NULL)
		write_string(fd, f_descr, "(nil)");
	else
	{
		f_descr->conversion = 'x';
		f_descr->flags |= FT_F_HASH;
		f_descr->length_modifier = FT_L_z;
		write_unsigned(fd, f_descr, (size_t )ptr);
	}
}
