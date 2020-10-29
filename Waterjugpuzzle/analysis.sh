#!/bin/bash
make && \
valgrind --leak-check=yes --track-origins=yes -s  ./waterjugpuzzle 40 32 50 0 0 50 > /dev/null && \
echo "-----------------------------------------------------------------------" && \
valgrind --leak-check=yes --track-origins=yes -s  ./waterjugpuzzle 40 32 50 0 1 49 > /dev/null && \
echo "-----------------------------------------------------------------------" && \
valgrind --leak-check=yes --track-origins=yes -s  ./waterjugpuzzle 40 32 50 0 2 48 > /dev/null

echo "-----------------------------------------------------------------------"
echo "Timing large iteration count:"
echo "./waterjugpuzzle 2 999998 2000000 1 0 1999999"
time ./waterjugpuzzle 2 1999998 2000000 1 0 1999999 > /dev/null && \
time ./waterjugpuzzle 2 1999998 2000000 1 0 1999999 > /dev/null && \
time ./waterjugpuzzle 2 1999998 2000000 1 0 1999999 > /dev/null

echo "-----------------------------------------------------------------------"
echo "Timing large array building:"
echo "./waterjugpuzzle 2 999998 1000000 0 0 1000000"
time ./waterjugpuzzle 2 999998 1000000 0 0 1000000 > /dev/null && \
time ./waterjugpuzzle 2 999998 1000000 0 0 1000000 > /dev/null && \
time ./waterjugpuzzle 2 999998 1000000 0 0 1000000 > /dev/null

echo "-----------------------------------------------------------------------"
echo "Timing very large array building:"
echo "time ./waterjugpuzzle 10000 10000 10000 0 0 10000"
time ./waterjugpuzzle 10000 10000 10000 0 0 10000 > /dev/null && \
time ./waterjugpuzzle 10000 10000 10000 0 0 10000 > /dev/null && \
time ./waterjugpuzzle 10000 10000 10000 0 0 10000 > /dev/null

echo "-----------------------------------------------------------------------"
echo "Final test:"
./test_waterjugpuzzle.sh
echo "-----------------------------------------------------------------------"
echo "Recompiling..."
make
