// time.cpp

#include <iostream>
#include <chrono>
#include "tictoc.h"

using namespace std;

TicToc::TicToc()
{
  time_start = chrono::steady_clock::now();
  time_end = chrono::steady_clock::now();
  time_elapsed_seconds = time_end-time_start;
}

void TicToc::tic()
{
  time_start = chrono::steady_clock::now();
}

void TicToc::toc()
{
  time_end = chrono::steady_clock::now();
  time_elapsed_seconds = time_end-time_start;
}

ostream& operator<<(ostream& os, const TicToc& time_in)
{
  return os << "(time elapsed: " << time_in.time_elapsed_seconds.count() << " s)";
}
