# Setup

This directory contains pre-built libxml2 source code. It was built using the following commands:

```bash
CC=afl-clang-fast ./autogen.sh
AFL_USE_ASAN=1 make -j 4
```

If you want, you can manually download the libxml2 source code and build it on your own:
```
git clone --branch 726f67e2f140f8d936dfe993bf9ded3180d750d2 https://gitlab.gnome.org/GNOME/libxml2.git
```

# Harness

At this point, we have our instrumented subject ready to be fuzzed. We now need to write a proper harness. 

Open `harness.c`. It contains all the necessary code to fuzz libxml2. The only part that is missing is between the comment lines:  

```c
// ----------------------------------
// write your code here
// ----------------------------------
```

Write a harness that will invoke [xmlReadFile()](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-parser.html#xmlReadFile) API in libxml2. Don't forget to clean up the `xmlDocPtr` that `xmlReadFile()` returns using [xmlFreeDoc()](https://gnome.pages.gitlab.gnome.org/libxml2/devhelp/libxml2-tree.html#xmlFreeDoc). 


## Building the harness

Use the following command to build the harness:
```bash
AFL_USE_ASAN=1 afl-clang-fast ./harness.c -I libxml2/include libxml2/.libs/libxml2.a -lz -lm -o fuzzer
```

Here, `AFL_USE_ASAN=1` tells the compiler to instrument the code with address sanitizer. `afl-clang-fast` is a modified version of a Clang C compiler with instrumentation capabilities. AFL needs the programs to be instrumented in order to work efficiently.  

# Running AFL

Let's first create an input seed:
```c
mkdir input
echo "<hi></hi>" > input/hi.xml
```

And now use the following command to run AFL:

```c
afl-fuzz -i input/ -o output/ ./fuzzer @@
```

`@@` at the end is used to tell AFL how to pass a filename to the target program. 

# Harness in non-persistent mode

The loop in `harness.c`:

```c
while (__AFL_LOOP(1000))
{
    // ----------------------------------
    // write your code here
    // ----------------------------------
}
```

allows AFL to run in persistent mode as explained [here](https://github.com/AFLplusplus/AFLplusplus/blob/stable/instrumentation/README.persistent_mode.md#:~:text=In%20persistent%20mode%2C%20AFL%2B%2B,professional%20fuzzing%20uses%20this%20mode.). 

Now, run AFL in non-persistent mode (by removing the loop but keeping its body).

# When to stop fuzzing?

Since fuzzing is a random process, it is hard to tell how much time is needed for AFL to find a bug. For some perspective, it took us 30m once, 1h the second time, 1h10m the third time to find the first bug with 6000 executions/sec. Once, it didn't even find a bug in 2h30m at the same rate of 6000 executions/sec. Patience is key. 

# Deliverables

## 1. Harness code

Provide the code you wrote for harness as part of your assignment submission.

## 2. Plots

You will find `plot_data` file inside the `out/default/` directory. Plot a graph with `unix_time` on y-axis and `paths_total` on x-axis. `unix_time` is described [here](https://en.wikipedia.org/wiki/Unix_time), and `paths_total` is the total number of paths covered. Make two such plots, one for AFL in persistent mode, one for AFL in non-persistent mode. Both of the plots should be on the same plane. 

Include the following in your assignment submission:  
1. An image containing two plots (persistent, non-persistent).
2. A paragraph with your description of the plots. 
3. Code you wrote to obtain the plots. 