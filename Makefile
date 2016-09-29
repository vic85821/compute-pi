CC = gcc
CFLAGS = -O0 -std=gnu99 -Wall -fopenmp -mavx 
EXECUTABLE = \
	time_test_baseline time_test_leibniz_baseline time_test_eular_baseline\
    time_test_openmp_2 time_test_openmp_4 \
	time_test_avx time_test_avxunroll \
	benchmark_clock_gettime \
    time_test_openmp_8 time_test_openmp_16 \
    confidence_interval

default: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DBASELINE -o time_test_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DLEIBNIZ_BASELINE -o time_test_leibniz_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DEULAR_BASELINE -o time_test_eular_baseline -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVX -o time_test_avx -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DAVXUNROLL -o time_test_avxunroll -lm
	$(CC) $(CFLAGS) computepi.o benchmark_clock_gettime.c -o benchmark_clock_gettime -lm
	$(CC) $(CFLAGS) confidence_interval.c -o confidence_interval -lm	
.PHONY: clean default

compare_thread: computepi.o
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_2 -o time_test_openmp_2 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_4 -o time_test_openmp_4 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_8 -o time_test_openmp_8 -lm
	$(CC) $(CFLAGS) computepi.o time_test.c -DOPENMP_16 -o time_test_openmp_16 -lm
	$(CC) $(CFLAGS) confidence_interval.c -o confidence_interval -lm

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

check: default
	time ./time_test_baseline
	time ./time_test_openmp_2
	time ./time_test_openmp_4
	time ./time_test_avx
	time ./time_test_avxunroll


gencsv: default
	for i in `seq 100 1000 100000`; do \
		for j in `seq 1 1 100`; do \
			printf "%d," $$i;\
			./benchmark_clock_gettime $$i; \
		done > result_clock_gettime.csv ; \
        ./confidence_interval; \
	done > result_clock_gettime_refine.csv

gencsv: compare_thread
	for i in `seq 100 1000 100000`; do \
		for j in `seq 1 1 100`; do \
			printf "%d," $$i;\
			./benchmark_clock_gettime $$i; \
		done > result_clock_gettime.csv ; \
        ./confidence_interval; \
	done > result_clock_gettime_refine.csv

plot: gencsv
	gnuplot runtime.gp

plot_thread: gencsv
	gnuplot runtime_thread.gp


clean:
	rm -f $(EXECUTABLE) *.o *.s result_clock_gettime.csv *.png 
