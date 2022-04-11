# Setup

This directory contains pre-built OpenSSL source code. It was built using the following commands:

```bash
CC=afl-clang-fast CXX=afl-clang-fast++ ./config -d
AFL_USE_ASAN=1 make
```

(Optional) If you want, you can manually download the OpenSSL source code and build it on your own:

```
git clone --branch 0d8776344cd7965fadd870e361503985df9c45bb https://github.com/openssl/openssl.git
```

# Harness

At this point, we have our instrumented subject ready to be fuzzed. We now need to write a proper harness. 

Open `handshake.cc`. It contains all the necessary code to fuzz OpenSSL. The only part that is missing is between the comment lines:

```c
// ----------------------------------
/* TODO: To spoof one end of the handshake, we need to write data to sinbio here */
BIO_write(sinbio, data, size);
// ----------------------------------
```

`data` is array of `uint8_t`'s.   
`size` is the number of elements that should be read from `data`.  

Your task is to complete the harness code by adding lines that read from `stdin` and pass the data to `BIO_write()`.


## Building the harness

After you complete the harness, use the following command to build it:
```bash
AFL_USE_ASAN=1 afl-clang-fast++ -g handshake.cc openssl/libssl.a openssl/libcrypto.a -o handshake -I openssl/include -ldl
```

Here, `AFL_USE_ASAN=1` tells the compiler to instrument the code with address sanitizer. `afl-clang-fast++` is a modified version of a Clang C++ compiler with instrumentation capabilities. AFL needs the programs to be instrumented in order to work efficiently. 

# Running AFL

First, create some dummy seed input(s) in `input/`. Then, use the following command to run AFL:

```c
afl-fuzz -i input/ -o out/ ./handshake
```

# When to stop fuzzing?

It should not take long to find Heartbleed using AFL. For some perspective, it consistently took up to two minutes with 600 executions/sec for several times we ran AFL. 

# Deliverables

## 1. Harness code

Provide the code you wrote for harness as part of your assignment submission.

## 2. Heartbleed explanation

You can read one of the Heartbleed explanations [here](https://www.theregister.com/2014/04/09/heartbleed_explained/). As part of your assignment submission, explain the bug with the concrete values you observed as the basis of your explanation. 