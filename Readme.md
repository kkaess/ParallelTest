# ParallelTest

A test of the C++17 STL Parallel TS, along with OpenMP 5.0 code that performs the same task.

This is based on a code snippet from https://en.cppreference.com/w/cpp/experimental/reduce

In my experience, std::reduce beats OpenMP __most__ of the time, but not always.


