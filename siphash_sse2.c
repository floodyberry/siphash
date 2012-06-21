#include "siphash_impl.h"

/* 0,2,1,3 */
static const packedelem64 siphash_init[2] = {
	{{0x736f6d6570736575ull,0x6c7967656e657261ull}},
	{{0x646f72616e646f6dull,0x7465646279746573ull}}
};

static const packedelem64 siphash_final = {
	{0x0000000000000000ull,0x00000000000000ffull}
};

uint64_t
siphash(unsigned char key[16], const unsigned char *m, size_t len) {
	xmmi k;
	xmmi v02,v20,v13,v11,v33;
	xmmi mi;
	uint64_t MM16 res[2];
	unsigned char buf[8];
	size_t i;

	k = _mm_loadu_si128((xmmi *)(key + 0));
	v02 = siphash_init[0].v;
	v13 = siphash_init[1].v;
	v02 = _mm_xor_si128(v02, _mm_unpacklo_epi64(k, k));
	v13 = _mm_xor_si128(v13, _mm_unpackhi_epi64(k, k));

	buf[7] = (unsigned char)len;
	if (len < 8) goto sip7bytesorless;

/*
#define sipcompress() \
	v11 = v13; \
	v33 = _mm_shuffle_epi32(v13, _MM_SHUFFLE(1,0,3,2)); \
	v11 = _mm_or_si128(_mm_slli_epi64(v11, 13), _mm_srli_epi64(v11, 64-13)); \
	v02 = _mm_add_epi64(v02, v13); \
	v33 = _mm_or_si128(_mm_slli_epi64(v33, 16), _mm_srli_epi64(v33, 64-16)); \
	v13 = _mm_unpacklo_epi64(v11, v33); \
	v13 = _mm_xor_si128(v13, v02); \
	v20 = _mm_shuffle_epi32(v02, _MM_SHUFFLE(0,1,3,2)); \
	v11 = v13; \
	v33 = _mm_shuffle_epi32(v13, _MM_SHUFFLE(1,0,3,2)); \
	v11 = _mm_or_si128(_mm_slli_epi64(v11, 17), _mm_srli_epi64(v11, 64-17)); \
	v20 = _mm_add_epi64(v20, v13); \
	v33 = _mm_or_si128(_mm_slli_epi64(v33, 21), _mm_srli_epi64(v33, 64-21)); \
	v13 = _mm_unpacklo_epi64(v11, v33); \
	v13 = _mm_unpacklo_epi64(v11, v33); \
	v02 = _mm_shuffle_epi32(v20, _MM_SHUFFLE(0,1,3,2)); \
	v13 = _mm_xor_si128(v13, v20);	
*/

#define sipcompress() \
	v02 = _mm_add_epi64(v02, v13); \
	v11 = _mm_or_si128(_mm_slli_epi64(v13, 13), _mm_srli_epi64(v13, 64-13)); \
	v33 = _mm_or_si128(_mm_slli_epi64(v13, 16), _mm_srli_epi64(v13, 64-16)); \
	v13 = _mm_unpacklo_epi64(v11, _mm_shuffle_epi32(v33, _MM_SHUFFLE(1,0,3,2))); \
	v13 = _mm_xor_si128(v13, v02); \
	v20 = _mm_shuffle_epi32(v02, _MM_SHUFFLE(0,1,3,2)); \
	v20 = _mm_add_epi64(v20, v13); \
	v11 = _mm_or_si128(_mm_slli_epi64(v13, 17), _mm_srli_epi64(v13, 64-17)); \
	v33 = _mm_or_si128(_mm_slli_epi64(v13, 21), _mm_srli_epi64(v13, 64-21)); \
	v13 = _mm_unpacklo_epi64(v11, _mm_shuffle_epi32(v33, _MM_SHUFFLE(1,0,3,2))); \
	v13 = _mm_xor_si128(v13, v20); \
	v02 = _mm_shuffle_epi32(v20, _MM_SHUFFLE(0,1,3,2));

siploop:
	mi = _mm_loadl_epi64((xmmi *)(m + 0));
	v13 = _mm_xor_si128(v13, _mm_slli_si128(mi, 8));
	sipcompress()
	sipcompress()
	v02 = _mm_xor_si128(v02, mi);
	m += 8;
	len -= 8;
	if (len >= 8) goto siploop;

sip7bytesorless:
	for (i = 0; i < len; i++) buf[i] = m[i];
	for (; i < 7; i++) buf[i] = 0;
	mi = _mm_loadl_epi64((xmmi *)(buf + 0));
	v13 = _mm_xor_si128(v13, _mm_slli_si128(mi, 8));
	sipcompress()
	sipcompress()
	v02 = _mm_xor_si128(v02, mi);
	v02 = _mm_xor_si128(v02, siphash_final.v);
	sipcompress()
	sipcompress()
	sipcompress()
	sipcompress()

	v02 = _mm_xor_si128(v02, v13);
	v02 = _mm_xor_si128(v02, _mm_shuffle_epi32(v02, _MM_SHUFFLE(1,0,3,2)));
	_mm_store_si128((xmmi *)res, v02);
	return res[0];
}