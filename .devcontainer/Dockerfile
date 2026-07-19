FROM mcr.microsoft.com/devcontainers/base:ubuntu-24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
        build-essential \
        cmake \
        ninja-build \
        gdb-multiarch \
        gcc-arm-none-eabi \
        binutils-arm-none-eabi \
        openocd \
        stlink-tools \
        git \
        python3 \
        python3-pip \
        usbutils \
        ca-certificates \
        libnewlib-arm-none-eabi \
        bash-completion \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Ensure programmable completion (including git completion) is enabled
# for interactive bash shells in VS Code terminals.
RUN printf '\nif ! shopt -oq posix; then\n  [ -f /usr/share/bash-completion/bash_completion ] && . /usr/share/bash-completion/bash_completion\n  [ -f /usr/share/bash-completion/completions/git ] && . /usr/share/bash-completion/completions/git\nfi\n' >> /etc/bash.bashrc

# Keep locale and shell behavior predictable in VS Code terminals.
ENV LANG=C.UTF-8
ENV LC_ALL=C.UTF-8
