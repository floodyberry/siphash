#ifndef SIPHASH_H
#define SIPHASH_H

#include "siphash_impl.h"

uint64_t siphash(unsigned char key[16], const unsigned char *m, size_t len);

#endif // SIPHASH_H
