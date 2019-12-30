#include <xdebug.h>

#define berr(format, ...)   xdbg_printf(XDBG_DEBUG_ERROR,   format, ##__VA_ARGS__)
#define binfo(format, ...)  xdbg_printf(XDBG_DEBUG_GENERAL, format, ##__VA_ARGS__)
