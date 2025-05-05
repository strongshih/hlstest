# nerf_sim
## Install docker

```bash
apt-get install -y docker nvidia-docker2 // google how to install it
systemctl restart docker
```

## Setup environment

- Setup

```bash
git clone https://github.com/strongshih/codetest.git
cd codetest/
sudo docker build -t test_dev .
sudo docker run -p 12345:22 --name=test -it -v $PWD:/root/test_dev test_dev /bin/bash
```

- Test

```bash
cd /root/matchlib_toolkit/examples/05_push_pop
make build
./sim_sc
```

## Example implementation

- Swap vectors

```
cd /root/BSU
make build
```

- Output

```
        SystemC 2.3.3-Accellera --- May  5 2025 14:36:55
        Copyright (c) 1996-2018 by all Contributors,
        ALL RIGHTS RESERVED
Connections Clock: top.clk Period: 1 ns

Info: (I702) default timescale unit used for tracing: 1 ps (trace.vcd)
Input:
57 80 34 12 49 61 29 32 73 25 48 42 92 4 41 95 73 92 99 9 48 78 78 40 82 16 84 96 88 81 48 50
98 27 61 85 58 49 86 18 49 58 13 21 4 8 23 63 15 73 19 67 35 1 64 46 22 80 28 16 46 79 75 74
15 32 60 21 2 2 46 14 89 35 74 57 62 99 7 50 86 90 100 7 51 18 22 54 78 2 41 53 63 64 12 63
Output:
50 48 81 88 96 84 16 82 40 78 78 48 9 99 92 73 95 41 4 92 42 48 25 73 32 29 61 49 12 34 80 57  @ 106 ns
74 75 79 46 16 28 80 22 46 64 1 35 67 19 73 15 63 23 8 4 21 13 58 49 18 86 49 58 85 61 27 98  @ 107 ns
63 12 64 63 53 41 2 78 54 22 18 51 7 100 90 86 50 7 99 62 57 74 35 89 14 46 2 2 21 60 32 15  @ 108 ns

Info: /OSCI/SystemC: Simulation stopped by user.
```
