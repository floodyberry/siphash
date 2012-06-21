deafult: gcc64
gcc64: gcc64_siphash gcc64_siphash_sse2 gcc64_siphash_ssse3
icc64: icc64_siphash icc64_siphash_sse2 icc64_siphash_ssse3
gcc32: gcc32_siphash gcc32_siphash_sse2 gcc32_siphash_ssse3
icc32: icc32_siphash icc32_siphash_sse2 icc32_siphash_ssse3

gcc64_siphash:
	gcc siphash.c test.c -m64 -O3 -o test_gcc64_siphash -Wall
gcc64_siphash_sse2:
	gcc siphash_sse2.c test.c -m64 -msse2 -O3 -o test_gcc64_siphash_sse2 -Wall
gcc64_siphash_ssse3:
	gcc siphash_ssse3.c test.c -m64 -mssse3 -O3 -o test_gcc64_siphash_ssse3 -Wall

icc64_siphash:
	icc siphash.c test.c -m64 -O3 -o test_icc64_siphash -Wall
icc64_siphash_sse2:
	icc siphash_sse2.c test.c -m64 -msse2 -O3 -o test_icc64_siphash_sse2 -Wall
icc64_siphash_ssse3:
	icc siphash_ssse3.c test.c -m64 -mssse3 -O3 -o test_icc64_siphash_ssse3 -Wall

gcc32_siphash:
	gcc siphash.c test.c -m32 -O3 -o test_gcc32_siphash -Wall
gcc32_siphash_sse2:
	gcc siphash_sse2.c test.c -m32 -msse2 -O3 -o test_gcc32_siphash_sse2 -Wall
gcc32_siphash_ssse3:
	gcc siphash_ssse3.c test.c -m32 -mssse3 -O3 -o test_gcc32_siphash_ssse3 -Wall

icc32_siphash:
	icc siphash.c test.c -m32 -O3 -o test_icc32_siphash -Wall
icc32_siphash_sse2:
	icc siphash_sse2.c test.c -m32 -msse2 -O3 -o test_icc32_siphash_sse2 -Wall
icc32_siphash_ssse3:
	icc siphash_ssse3.c test.c -m32 -mssse3 -O3 -o test_icc32_siphash_ssse3 -Wall

clean:
	rm -f test_*
