# Game Of Life
This is a C++ implementation of the Conway's game of life and it's optimization. I have implemented 
several optimizations like utilizing less memory, bitwise operations, multithreading, loop reorder, minimizing abstractions etc.

More details are present in the source code of ThreadedConway.cpp

# Runtime Comparison

1. The original implementation of Game of life on a 2048 * 2048 board takes approx 6 minutes on Intel Core i5 8265U. 

2. The optimized code on the same machine takes 15 seconds.



## Compilation and Running

Run the following commands on your machine.
1. Change the iteration count and game board size by changing GAME_SIZE and NUM_ITER variables in main. cpp(for non-optimized version) and threadedConway.cpp (for the optimized version).

2. To Compile and run, use
```
    g++ -g -pthread -std=c++11 -o tgame threadedConway.cpp
    g++ -o game main.cpp ConwayGame.cpp


    ./game <seed1>
    ./tgame <seed2>



Where seed is a variable to initialize the psuedorandom function which sets the initial condition on the board.

3. To verify output, use (using the same seed)
```
    ./game <seed> > out1
    ./tgame <seed> > out2
    diff -q out1 out2
```

4. To check running times, use
```
    time ./game <seed>
    time ./tgame <seed>

```