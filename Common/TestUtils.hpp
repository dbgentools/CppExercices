#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>
#include <chrono>
#include <random>
#include <iostream>
#include <intrin.h>

#define _EVAL1(...) __VA_ARGS__
#define _TEST_PRINT_DBG(t,l,r) std::cerr << "Test '" << t << "' at " << __FILE__ << ":" << __LINE__ << " failed : " << "expected " << r << " got " << l << "\n"
#define _TEST_BLK_DBG(t,l,r) { _TEST_PRINT_DBG(t,l,r); __debugbreak(); _EVAL1(assert(0)); }

#define TEST_NO_DIE(t) _TEST_BLK_DBG(t,"died","run")
#define TEST_EQ(t,l,r) if(l != r) _TEST_BLK_DBG(t, l,r)
#define TEST_PTR(t,ptr) if(!ptr) _TEST_BLK_DBG(t, 0,"valid ptr")
#define TEST_EQ_D(l,r) TEST_EQ_E(l,r,std::numeric_limits<double>::epsilon())

std::int64_t random(std::int64_t _min, std::int64_t _max) {
  static std::default_random_engine reng{};
  static std::uniform_int_distribution<std::int64_t> dist{ _min,_max };
  return dist(reng);
}

static std::uint64_t _bench_counter = 0;
namespace benchmark {
  template<typename _ArgTy, typename _ArgRet, typename _DurTy = std::chrono::milliseconds,
    typename _ChTy>
  void bench(_ChTy&& name, _ArgRet(*fnc)(_ArgTy), _ArgTy _min = 0,
    _ArgTy _max = std::numeric_limits<_ArgTy>::max(), std::size_t count = 10000000)
    requires std::is_same_v<const char*, std::decay_t<_ChTy>> {
    std::default_random_engine reng{};
    std::uniform_int_distribution<_ArgTy> dist{ _min,_max };
    std::chrono::high_resolution_clock clk{};
    _ArgRet r;
    auto start = clk.now();
    for (uint64_t i{ 0 }; i < count; ++i)
      r = fnc(dist(reng));
    auto end = clk.now();
    std::cerr << "Benchmark n" << _bench_counter++ << " (" << std::forward<const char*>(name)
      << ") : " << std::chrono::duration_cast<_DurTy>(end - start) << "\n";
  }
}

#define ads_autobench(fnc) benchmark::bench(ADS_STR(fnc), fnc)