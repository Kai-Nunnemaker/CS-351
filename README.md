# CS-351
A repository for my computer architecture class 
Program	Opt	Real (s)	User (s)	Sys (s)	Mem (KB)	Through‑put† (MB/s)	Speed‑up vs hash‑00‡
hash‑00	 -g 	354.69	343.01	4.99	2 880	0.045	1.00
hash‑01	 -g 	17.88	16.31	1.25	2 880	0.895	19.84
hash‑02	 -g 	15.40	14.09	1.14	2 880	1.039	23.03
hash‑03	 -g 	16.44	15.09	1.13	2 880	0.973	21.57
hash‑04	 -g 	14.39	13.77	0.44	5 012 352	1.112	24.65
hash‑00	 ‑O2	339.04	329.01	4.41	2 880	0.047	1.00
hash‑01	 ‑O2	8.43	6.91	1.22	2 880	1.898	40.22
hash‑02	 ‑O2	8.20	6.86	1.15	2 880	1.951	41.35
hash‑03	 ‑O2	7.97	6.76	1.15	2 880	2.008	42.54
hash‑04	 ‑O2	7.23	6.64	0.46	5 012 352	2.213	46.89

† Through‑put = 16 MB ÷ real‑time
‡ Speed‑up = (real‑time of hash‑00 at same opt) ÷ (real‑time of current program)

Q 1  •  What dominates hash‑00’s runtime?
hash-00 scans a text file and extracts every byte with the formatted extractor input >> byte; inside the inner loop. Formatted extraction does character‑by‑character parsing, type conversion, and locale checks, making it orders of magnitude slower than straight binary reads.

Q 2  •  Do the two dynamic‑allocation styles differ much (hash‑01 vs hash‑02)?
hash‑01 allocates each buffer with new [] … delete [] (heap).

hash‑02 uses alloca, placing the buffer on the stack each iteration. 

With debug builds the alloca version is ~14 % faster; under ‑O2 the gap shrinks to ~3 %. Heap calls add overhead, but once the I/O cost is minimized the difference becomes modest.

Q 3  •  Does the fixed‑size array in hash‑03 help?
hash‑03 keeps one 10 KiB stack buffer for the whole run, eliminating all per‑hash allocations. 


Performance is essentially the same as hash‑02 (within ±3 %), showing that after we get rid of text‑parsing and heap traffic, the loop is I/O‑bound and CPU‑light.

Q 4  •  Why is hash‑04’s RSS huge?
hash‑04 memory‑maps the entire data file with mmap. 


The OS simply shares its page‑cache copy with the process, so the program’s resident‑set size includes every mapped page (~5 GB+) even though no extra copy is made. The other versions use read, which copies smaller chunks into a 10 KiB user buffer, keeping their RSS at ~3 MB.

Q 5  •  Other compiler options tried
* ‑O3 / ‑Ofast – virtually identical to ‑O2 (the code is I/O‑bound).
* ‑march=native – negligible change (<1 %).
* ‑flto – link‑time optimisation shaved ~0.1 s off the sub‑10‑second runs, again drowned out by I/O.

In short, once the text‑parsing bottleneck is removed, further optimisation gains are tiny compared with algorithmic/IO choices.
