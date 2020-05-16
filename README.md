# algorithms
Implementations for algorithms in CLRS and UTAustin CS388G (online) course in C++11, as well as algorithms that I found interesting.

## Introduction
[CLRS](https://en.wikipedia.org/wiki/Introduction_to_Algorithms) is an excellent algorithm book in great depth. It covers a huge range of different algorithms, and some of them can be difficult to understand and implement.

There are a lot of solutions available to the exercise of the book online, but there aren't many good implementations! What's more, implementing them can help understand the algorithms and the proofs better.

## Setup
The code is written in [C++11](https://en.cppreference.com/w/cpp/11). [Google test](https://github.com/google/googletest) is the framework for testing.

My development environment is [Visual Studio 2019](https://visualstudio.microsoft.com/vs/). However, I expect that it should work on any platform, and here is how you should setup:

1. Clone the repo
```
git clone https://github.com/HE-Xinyu/algorithms.git
cd algorithms
```
2. The source code is in `src` folder, and the tests are in `tests`.
3. If you want to try something out, simply modify anything you want and then compile and build.
4. For running Google test, if you open `algorithms.sln` with Visual Studio 2017 or later, it should be directly runnable [(here are the instructions)](https://docs.microsoft.com/en-us/visualstudio/test/how-to-use-google-test-for-cpp?view=vs-2019). For other IDEs, you may need to setup Google test on your own.

## Goals
1. The code should achieve optimal time complexity.
2. The code should be as clear as possible, even if it sacrifices some constant factor (e.g. using the std library for convenience).
3. DRY (don't repeat yourself)
4. The code should be easy to use as well. By simply copying and pasting, one should expect it working on any C++11 (and higher) environment.
5. There should be thorough tests to show that the code works correctly.
6. The code should work on 32-bit/64-bit Windows, Linux, and maxOS without modification.

## Things I won't do
1. Use techniques irrelevant to algorithms (e.g. parallel programming, SIMD instructions, etc.) to optimize the performance. Performance does matter, but I want to mainly focus on the algorithm itself.
2. Shrink the code size. As I've mentioned in the goals, readability is one of the keys to this project.


## Done
Chapter 30: DFT & IDFT (`fft.hpp`)

Chapter 26: Maximum Flow (`max_flow.hpp`): Edmonds-Karp algorithm, relabel-to-front algorithm, maximum bipartite algorithm (`matching.hpp`).

Chapter 24: Bellman Ford algorithm (`shortest_paths.hpp`)

Outside the book:

1. trie (`string.hpp`)

## TODO
Chapter 24: SSSP & APSP

Minimum-cost perfect matching (I didn't find it on the book)

## Contributions
Issues and pull requests are appreciated.

## License
[MIT](https://opensource.org/licenses/MIT)
