Basic+SSE2+SSSE3 implementation of [SipHash-2-4](http://131002.net/siphash/) based off the paper. On an E5200, icc gives 
the best speeds for all SSE versions & 32bit versions, gcc gives the best speed for 64bit basic

done to see how difficult implementing the spec was as their source is not up (yet), and curious about 32bit performance

Performance on an E5200

<table>
<thead><tr><th>Best Impl.</th><th>7 bytes</th><th>128 bytes</th><th>1024 bytes</th></tr></thead>
<tbody>
<tr><td>icc 32bit</td><td>202 cycles</td><td>1015 cycles</td><td>6.7 cpb</td></tr>
<tr><td>icc 32bit sse2</td><td>135 cycles</td><td>688 cycles</td><td>4.48 cpb</td></tr>
<tr><td>icc 32bit ssse3</td><td>125 cycles</td><td>614 cycles</td><td>3.98 cpb</td></tr>
<tr><td>gcc 64bit</td><td>61 cycles</td><td>276 cycles</td><td>1.81 cpb</td></tr>
</tbody>
</table>

#### License

Public Domain
