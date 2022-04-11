# Assignment 2

## Introduction

In this assignment, you will use a fuzzing tool called [AFL++](https://github.com/AFLplusplus/AFLplusplus) which is a community-maintained fork of the original fuzzing tool called [AFL](https://github.com/google/AFL). 

Since there is no fundamental difference between AFL++ and AFL, we will refer to AFL++ just as AFL. 

Part 1 will help you set up your environment.  

Part 2 will guide you through a demo where you will fuzz a dummy library using AFL++. This part will help you understand what test harnesses are used for.  

In Part 3 of the assignment, you will need to fuzz three open-source projects `libxml2`, `OpenSSL`, and `Sendmail`. This is the graded part of the assignment.

## Part 1

For your convenience, the environment is packaged in a Docker image. All you need to do is to install Docker and pull the image using this command:  

```
docker pull satbekmyrza/se-a2-afl
```

After that, create a container from the image you pulled:

```
docker run --privileged -p 1100:22 --name se-a2-afl -d --restart always satbekmyrza/se-a2-afl:latest
```

The password to the container is `root`. 

Use `ssh -p 1100 root@localhost` to create a terminal session in your container (CLI only).

(Optional) For GUI experience with the container, try [remote development in VSCode](https://code.visualstudio.com/docs/remote/ssh).  

## Part 2

In this part of the assignment, you will learn what test harnesses are and why we need them while fuzzing with AFL. Follow the instructions provided in the `README.md` of the `harness/` directory.

## Part 3 

In this part of the assignment, you will fuzz three open source projects `libxml2`, `OpenSSL`, and `Sendmail` to find vulnerabilities in them. 

You will try to find [CVE-2015-8317](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-2015-8317) in `libxml2`, [CVE-2014-0160](https://heartbleed.com/) (a.k.a. Heartbleed) in `OpenSSL`, and [CVE-1999-0206](https://cve.mitre.org/cgi-bin/cvename.cgi?name=CVE-1999-0206) in `Sendmail`.

Please follow the instructions in `README.md` for each vulnerability in each of their respective folders under `subjects/`. 

## Deliverables

Everything you need to submit as part of your assignment is written in the **Deliverables** section of `README.md`'s in `subjects/*/`. Only **Part 3** of the assignment is graded. 

## How to Submit

to be filled...

## FAQ
We will post answers some of the questions here. 