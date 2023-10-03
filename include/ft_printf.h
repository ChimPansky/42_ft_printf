#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *format, ...);
int	ft_printf_fd(int fd, const char *format, ...);
int	ft_vprintf_fd(int fd, const char *format, va_list ap);

#endif  // FT_PRINTF_H
