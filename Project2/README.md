|Thread<br>Count|Wall Clock<br>Time|User Time|System Time|Speedup|
|:--:|--:|--:|--:|:--:|
|1|14.47|13.85| 0.51|1.00|
|2| 7.66|14.22| 0.53| 1.89|
|3| 5.78|15.47| 0.78| 2.50|
|4| 4.75|16.65| 0.80| 3.05|
|5| 3.94|16.55| 0.96| 3.67|
|6| 3.47|16.83| 1.06| 4.17|
|7| 3.07|16.83| 1.19| 4.71|
|8| 2.79|16.81| 1.33| 5.19|
|16| 2.02|17.95| 3.01| 7.16|
|24| 1.94|18.80| 6.71| 7.46|
|32| 1.92|18.16|13.83| 7.54|
|40| 1.95|17.66|16.99| 7.42|
|48| 1.93|17.15|26.98| 7.50|
|56| 1.96|16.91|27.07| 7.38|
|64| 1.93|17.26|28.66| 7.50|
|72| 1.91|16.98|28.93| 7.58|
|80| 1.96|17.46|25.60| 7.38|

![speedup_plot](https://github.com/user-attachments/assets/1555e821-43d5-4fc9-9ce4-134a332f5f2e)

## Amdahl’s‑Law Prediction for 16 Threads

**Timings (1 thread):**
main program 0.007619994 s
results output 0.108451951 s
total run time 7.031054051 s



Compute the serial fraction \(s\) and parallel fraction \(p\):


s = \frac{0.007619994 + 0.108451951}{7.031054051} = 0.016505 \quad(1.65\%)  
p = 1 - s = 0.983495
Plug into Amdahl’s formula with 
𝑛
=
16
n=16:

$$
\mathrm{speedup}(16)
= \frac{1}{\,s + \dfrac{p}{16}\,}
= \frac{1}{\,0.016505 + \dfrac{0.983495}{16}\,}
\approx 12.82
$$
Linear Trend & Curve Flattening
Early‑thread slope (1 → 7 threads):

𝑆
7
−
𝑆
1
7
−
1
=
4.71
−
1.00
6
≈
0.62
7−1
S 
7
​
 −S 
1
​
 
​
 = 
6
4.71−1.00
​
 ≈0.62
Late‑thread slope (32 → 40 threads):

𝑆
40
−
𝑆
32
40
−
32
=
7.42
−
7.54
8
≈
−
0.015
40−32
S 
40
​
 −S 
32
​
 
​
 = 
8
7.42−7.54
​
 ≈−0.015
Why it flattens:
Even with ≈ 98 % of the work parallelizable, overhead from thread‑creation and synchronization, cache‑coherency traffic, and limited memory‑bandwidth means that after ~32 cores adding more threads yields diminishing—or even negative—returns. It’s just like too many people crowding a single turnstile: beyond a certain point extra folks only increase waiting time rather than throughput.


