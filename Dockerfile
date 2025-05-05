FROM ubuntu:22.04

USER root
COPY BSU /root/BSU
COPY settings/entrypoint.sh /entrypoint.sh
RUN chmod +x /entrypoint.sh
COPY settings/.bashrc /root/.bashrc
RUN echo "root:root" | chpasswd

# Update system and install packages
ENV DEBIAN_FRONTEND="noninteractive"
RUN apt-get update
RUN apt-get -y install pciutils git curl sudo wget python3-pip build-essential cmake ninja-build python3-venv python-is-python3 vim g++ make libtool autoconf automake autotools-dev python3 unzip net-tools gtkwave gdb
RUN apt-get -y install openssh-server
RUN echo "\nPermitRootLogin yes\n" >> /etc/ssh/sshd_config

# Cleanup
RUN apt-get autoremove -y && apt-get autoclean
RUN rm -rf /var/lib/apt/lists/* /tmp/* /var/tmp/* /var/log/*

EXPOSE 22

WORKDIR /root

# Download related repos
RUN git clone https://github.com/learnwithexamples/learnsystemc.git
RUN git clone https://github.com/hlslibs/ac_types.git
RUN git clone https://github.com/hlslibs/ac_math.git
RUN git clone https://github.com/hlslibs/ac_simutils.git
RUN git clone https://github.com/hlslibs/ac_ml.git
RUN git clone https://github.com/hlslibs/ac_dsp.git
RUN git clone https://github.com/hlslibs/matchlib_connections.git
RUN git clone https://github.com/hlslibs/matchlib_toolkit.git
RUN git clone https://github.com/hlslibs/hls_tutorials.git
RUN git clone https://github.com/fastmachinelearning/hls4ml.git
RUN git clone https://github.com/NVlabs/matchlib.git --recursive
RUN git clone https://github.com/accellera-official/systemc.git
RUN git clone https://github.com/boostorg/boost.git

# Build boost
RUN cd /root/boost && git checkout boost-1.68.0 && git submodule init && git submodule update --recursive && ./bootstrap.sh && ./b2 headers

# Build systemc
RUN cd /root/systemc && git checkout 2.3.3 && ./configure CXX=g++ CXXFLAGS="-std=c++11"  --enable-debug --enable-pthreads --with-arch-suffix=-linux64 && autoreconf -f -i && make -j8 && make install

ENTRYPOINT ["/entrypoint.sh"]
