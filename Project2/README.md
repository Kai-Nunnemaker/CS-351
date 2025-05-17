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

## Amdahl’s‑Law Prediction (16 cores)

Using the 1‑thread timings  

| stage | time (s) |
|-------|---------|
| main program (init) | 0.007 62 |
| results output      | 0.108 45 |
| total run‑time      | 7.031 05 |

$$
s \;=\;\frac{0.007619994 + 0.108451951}{7.031054051}\;=\;0.01651,
\qquad
p \;=\;1-s\;=\;0.98349
$$

Speed‑up for \(n = 16\) threads:

$$
\text{speedup}(16)
= \frac{1}{1 - p + \dfrac{p}{n}}
= \frac{1}{\,0.01651 + \dfrac{0.98349}{16}\,}
\approx 12.83
$$

---

## Linear‑region slope & why the curve flattens

*Early slope* (1 → 7 threads):  

\[
\frac{S_7 - S_1}{7 - 1}
= \frac{4.71 - 1.00}{6}
\approx 0.62
\]

*Late slope* (32 → 40 threads):  

\[
\frac{S_{40} - S_{32}}{40 - 32}
= \frac{7.42 - 7.54}{8}
\approx -0.015
\]

The curve flattens because thread‑management overhead, cache‑coherency traffic, and limited memory bandwidth grow with thread count; after ≈ 32 cores those costs outweigh the benefit of adding more workers—like crowding too many people through a single turnstile.





