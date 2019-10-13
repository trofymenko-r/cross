#ifndef __STRL_H
#define __STRL_H

#include <stddef.h>

#ifdef  __cplusplus
extern "C"  {
#endif

size_t	 strlcpy(char *dst, const char *src, size_t dstsize);

size_t	 strlcat(char *dst, const char *src, size_t dstsize);

#ifdef  __cplusplus
}
#endif

#endif  //  __STRL_H
