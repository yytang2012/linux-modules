Measure how many ticks are consumed
1. we need to enable the performance counter in kernel level
    sudo insmod enable_the_performance_counter.ko
2. we rely on measureCPUTicks.c to read the delta ticks

Question: Sometime it may report the following results:
    panda> a.out
    Illegal instruction
    panda> a.out
    function took exactly 700059 cycles (27 overhead)
    panda> a.out
    Illegal instruction

Answer: It turns out that my Cortex-A15 has two cores, and hence has two sets of performance registers. When I load my kernel module to enable userland access to the performance monitors, only one of the cores gets its registers enabled. The others are still privileged.

I can use taskset to force my process onto the right core
panda> a.out
    panda> a.out
    Illegal instruction
    panda> taskset -c 0 a.out
    function took exactly 700065 cycles (27 overhead)
    panda> taskset -c 1 a.out
    Illegal instruction
