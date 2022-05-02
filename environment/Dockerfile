FROM ubuntu:20.04

RUN echo 'debconf debconf/frontend select Noninteractive' | debconf-set-selections

# We want manpages in the container - the base image excludes them
RUN rm /etc/dpkg/dpkg.cfg.d/excludes

# llvm-11
RUN apt-get update && apt-get install -y --no-install-recommends wget ca-certificates gnupg2 && rm -rf /var/lib/apt/lists
RUN echo deb http://apt.llvm.org/focal/ llvm-toolchain-focal-11 main >> /etc/apt/sources.list
RUN wget -O - https://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - 

# Packages
RUN apt-get update && apt-get install -y \
    git build-essential curl libssl-dev sudo libtool libtool-bin libglib2.0-dev bison flex automake \
    python3 python3-dev python3-setuptools python-is-python3 libpixman-1-dev gcc-9-plugin-dev cgroup-tools \
    clang-11 clang-tools-11 libc++1-11 libc++-11-dev libc++abi1-11 libc++abi-11-dev libclang1-11 \
    libclang-11-dev libclang-common-11-dev libclang-cpp11 libclang-cpp11-dev liblld-11 liblld-11-dev \
    liblldb-11 liblldb-11-dev libllvm11 libomp-11-dev libomp5-11 lld-11 lldb-11 python3-lldb-11 llvm-11 llvm-11-dev llvm-11-runtime llvm-11-tools \
    rsync autopoint bison gperf autoconf texinfo gettext \
    libtool pkg-config libz-dev python2.7-dev \
    awscli openssh-server ncat \
    emacs vim nano screen htop man manpages-posix-dev wget httpie bash-completion ripgrep \
    gdb byobu \
    && rm -rf /var/lib/apt/lists

RUN echo y | unminimize

# Users & SSH
RUN apt-get install -y openssh-server
RUN mkdir /var/run/sshd
RUN echo 'root:root' | chpasswd
RUN sed -ri 's/^#?PermitRootLogin\s+.*/PermitRootLogin yes/' /etc/ssh/sshd_config
RUN sed -ri 's/UsePAM yes/#UsePAM yes/g' /etc/ssh/sshd_config
RUN mkdir /root/.ssh
RUN apt-get clean && \
    rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/*

# AFL
RUN update-alternatives --install /usr/bin/clang clang $(which clang-11) 1 && \
    update-alternatives --install /usr/bin/clang++ clang++ $(which clang++-11) 1 && \
    update-alternatives --install /usr/bin/llvm-config llvm-config $(which llvm-config-11) 1 && \
    update-alternatives --install /usr/bin/llvm-symbolizer llvm-symbolizer $(which llvm-symbolizer-11) 1 && \
    update-alternatives --install /usr/bin/llvm-cov llvm-cov $(which llvm-cov-11) 1 && \
    update-alternatives --install /usr/bin/llvm-profdata llvm-profdata $(which llvm-profdata-11) 1

WORKDIR /root
RUN git clone https://github.com/AFLplusplus/AFLplusplus
WORKDIR /root/AFLplusplus
RUN git checkout 3.0c && make distrib && sudo make install

WORKDIR /root
RUN git clone https://github.com/satbekmyrza/repo-afl-a2 assignment2

EXPOSE 22
CMD    ["/usr/sbin/sshd", "-D"]
