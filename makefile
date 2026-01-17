CC=gcc

all: memory swap network_in_out cpu gpu

memory: memory.c
swap: swap.c
network_in_out: network_in_out.c
cpu: cpu.c
gpu: gpu.c -lrocm_smi64
