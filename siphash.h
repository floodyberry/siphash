#ifndef SIPHASH_H
#define SIPHASH_H

#if defined(_MSC_VER)
	typedef unsigned __int64 uint64_t;
#else
	#include <stdint.h>
	#include <stdlib.h>
#endif

uint64_t siphash(unsigned char key[16], const unsigned char *m, size_t len);

#endif // SIPHASH_H
