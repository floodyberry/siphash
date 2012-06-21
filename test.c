#include <stdio.h>
#include "siphash.h"

#if defined(_MSC_VER)
	static uint64_t INLINE
	get_ticks(void) {
		return __rdtsc();
	}
#else
	static uint64_t INLINE
	get_ticks(void) {
		uint32_t lo, hi;
		__asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
		return ((uint64_t)lo | ((uint64_t)hi << 32));
	}
#endif

int main() {
	static unsigned char key[16] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f};
	static unsigned char msg[15] = {0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e};
	static unsigned char buf[1024] = {0xff};
	static const size_t outer_reps = 80, inner_reps = 128;
	size_t i, j, len;
	uint64_t t, sum, tempsum;
	double cycles;

	uint64_t res = siphash(key, msg, 15);
	if (res != 0xa129ca6149be45e5ull) {
		printf("fail\n");
		return 0;
	}

	for (i = 0; i < 500000; i++)
		key[0] += (unsigned char)siphash(key, buf, 1024);

	for (len = 1; len < 1024; len++) {
		sum = 1000000000000000ull;
		t = get_ticks();
		for (j = 0; j < outer_reps; j++) {
			for (i = 0; i < inner_reps; i++)
				key[0] += (unsigned char)siphash(key, buf, len);
			tempsum = (get_ticks() - t);
			if (tempsum < sum)
				sum = tempsum;
		}
		
		cycles = (double)sum / (double)inner_reps;
		printf("%u bytes, %.4f cycles/byte, %.4f cycles\n", (uint32_t)len, cycles / len, cycles);
	}

	return 0;
}