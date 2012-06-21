#include "siphash_impl.h"

static uint64_t INLINE
U8TO64_LE(const unsigned char *p) {
	return *(const uint64_t *)p;
}

/*
static void INLINE
U64TO8_LE(unsigned char *p, const uint64_t v) {
	*(uint64_t *)p = v;
}
*/

uint64_t
siphash(unsigned char key[16], const unsigned char *m, size_t len) {
	uint64_t v0, v1, v2, v3;
	uint64_t mi, k0, k1;
	unsigned char buf[8];
	size_t i;

	k0 = U8TO64_LE(key + 0);
	k1 = U8TO64_LE(key + 8);
	v0 = k0 ^ 0x736f6d6570736575ull;
	v1 = k1 ^ 0x646f72616e646f6dull;
	v2 = k0 ^ 0x6c7967656e657261ull;
	v3 = k1 ^ 0x7465646279746573ull;

	buf[7] = (unsigned char)len;
	if (len < 8) goto sip7bytesorless;

#define sipcompress() \
	v0 += v1; v2 += v3; \
	v1 = ROTL64(v1,13);	v3 = ROTL64(v3,16); \
	v1 ^= v0; v3 ^= v2; \
	v0 = ROTL64(v0,32); \
	v2 += v1; v0 += v3; \
	v1 = ROTL64(v1,17); v3 = ROTL64(v3,21); \
	v1 ^= v2; v3 ^= v0; \
	v2 = ROTL64(v2,32);

siploop:
	mi = U8TO64_LE(m);
	v3 ^= mi;
	sipcompress()
	sipcompress()
	v0 ^= mi;
	m += 8;
	len -= 8;
	if (len >= 8) goto siploop;

sip7bytesorless:
	for (i = 0; i < len; i++) buf[i] = m[i];
	for (; i < 7; i++) buf[i] = 0;
	mi = U8TO64_LE(buf);
	v3 ^= mi;
	sipcompress()
	sipcompress()
	v0 ^= mi;
	v2 ^= 0xff;
	sipcompress()
	sipcompress()
	sipcompress()
	sipcompress()
	return v0 ^ v1 ^ v2 ^ v3;
}

