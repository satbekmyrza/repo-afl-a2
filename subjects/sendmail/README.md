# Setup

This repository contains self-contained part of Sendmail with CVE-1999-0206.  

# Building the harness

This subject comes with a ready harness `main.c`.

Building the harness and Sendmail: 

```bash
afl-clang-fast -g -o m1-bad mime1-bad.c main.c -I .
```

# Running AFL

Let's create an input seed:
```bash
mkdir input
echo hello > input/1
```

```bash
afl-fuzz -i input/ -o out/ ./m1-bad @@
```

`@@` at the end is used to tell AFL how to pass a filename to the target program. 

# Seeds

Choosing good seeds speeds up AFL's bug finding capabilities. Try experimenting with some other inputs that speed up AFL. 

Note that the target program is a [MIME](https://en.wikipedia.org/wiki/MIME) parser. If you know the format, you can come up with a few hand-written examples. 

If you see any changes in AFL's speed, think about why this happens. 

# When to stop fuzzing?

It doesn't take long to fuzz Sendmail. For some perspective, almost all the time it was less than a minute. 

# Deliverables

## 1. Plot

You will find `plot_data` file inside the `out/default/` directory. Plot a graph with `unix_time` on y-axis and `paths_total` on x-axis. `unix_time` is described [here](https://en.wikipedia.org/wiki/Unix_time), and `paths_total` is the total number of paths covered. Make two such plots, one when fuzzing with 'slow' (takes AFL longer to find a bug) input, and another when fuzzing with 'fast' input. 

Include the following in your assignment submission:  
1. An image containing two plots.
2. A paragraph with your description of the plots and the inputs.
3. Code you wrote to obtain the plots.
