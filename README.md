Basic+SSE2+SSSE3 implementation of [SipHash-2-4](http://131002.net/siphash/) based off the paper. On an E5200, icc gives 
the best speeds for all SSE versions & 32bit versions, gcc gives the best speed for 64bit basic

done to see how difficult implementing the spec was as their source is not up (yet), and curious about 32bit performance
