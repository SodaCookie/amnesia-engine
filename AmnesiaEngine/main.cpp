#include "amnesia/core/engine.h"
#include "amnesia/primitive/segment.h"
#include "amnesia/primitive/vector.h"
#include <iostream>
#include <memory>

#include <cmath>
#include <ctime>
#include <tuple>

/* Returns the amount of milliseconds elapsed since the UNIX epoch. Works on
 * both
 * windows and linux. */

#ifdef _WIN32
#include <Windows.h>
#else
#include <ctime>
#include <sys/time.h>
#endif

/* Remove if already defined */
typedef long long int64;
typedef unsigned long long uint64;

uint64 GetTimeMs64() {
#ifdef _WIN32
  /* Windows */
  FILETIME ft;
  LARGE_INTEGER li;

  /* Get the amount of 100 nano seconds intervals elapsed since January 1, 1601
   * (UTC) and copy it
   * to a LARGE_INTEGER structure. */
  GetSystemTimeAsFileTime(&ft);
  li.LowPart = ft.dwLowDateTime;
  li.HighPart = ft.dwHighDateTime;

  uint64 ret = li.QuadPart;
  ret -= 116444736000000000LL; /* Convert from file time to UNIX epoch time. */
  ret /= 10000; /* From 100 nano seconds (10^-7) to 1 millisecond (10^-3)
                   intervals */

  return ret;
#else
  /* Linux */
  struct timeval tv;

  gettimeofday(&tv, NULL);

  uint64 ret = tv.tv_usec;
  /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
  ret /= 1000;

  /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
  ret += (tv.tv_sec * 1000);

  return ret;
#endif
}

int main(int argc, char *argv[]) {
  // std::shared_ptr<GameEngine> e = std::shared_ptr<GameEngine>(new
  // GameEngine());
  // e->run();
  int64 before;
  int num = 10000;
  Segment s = Segment(Vector(1, -1), Vector::up * 2);

  before = GetTimeMs64();
  // Timed code
  for (double i = 0; i < num; i += 1) {
    // Radially check parallel
    // auto v = s.intersect_segment(Segment(Vector(0, 0), Vector(3 *
    // cos(0.0174533 * i / num * 360), 3 * sin(0.0174533 * i / num *
    // 360))));
    // std::cout << Segment(Vector(0, 0), Vector(3 * cos(0.0174533 * i / 8 *
    // 360), 3 * sin(0.0174533 * i / 8 * 360))) << std::endl;
    // std::cout << v.first << " " << v.second << std::endl;
  }

  std::cout << GetTimeMs64() - before << std::endl;

  return 0;
}
