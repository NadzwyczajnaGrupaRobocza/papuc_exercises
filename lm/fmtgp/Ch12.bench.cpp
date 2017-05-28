#include "Ch12.hpp"

#include <benchmark/benchmark.h>

#include <vector>
#include <algorithm>
#include <random>

std::vector<std::pair<int, int>>& random_test_vector()
{
    static bool initialized = false;
    static std::vector<std::pair<int, int>> random_data;

    if (not initialized)
    {
        std::random_device r{};
        std::seed_seq seed{r(), r(), r(), r(), r(), r(), r(), r()};
        std::mt19937 engine{seed};
        std::uniform_int_distribution<int> uniform_dist(1 << 16, 1 << 30);

        std::generate_n(std::back_inserter(random_data), 20, [&]()
                        {
                            return std::make_pair(uniform_dist(engine), uniform_dist(engine));
                        });

        initialized = true;
    }

    return random_data;
}

static void CustomArg(benchmark::internal::Benchmark* b)
{
    const auto& test_vector = random_test_vector();
    std::for_each(test_vector.begin(), test_vector.end(),
                  [&](const auto& datum){ b->Args({datum.first, datum.second}); });
}

static void BenchmarkSteinGCD(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        int x = 0;
        benchmark::DoNotOptimize(x = stein_GCD(state.range(0), state.range(1)));
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BenchmarkSteinGCD)->Apply(CustomArg);

static void BenchmarkEuclidGCD(benchmark::State& state)
{
    while (state.KeepRunning())
    {
        int x = 0;
        benchmark::DoNotOptimize(x = euclid_GCD(state.range(0), state.range(1)));
        benchmark::ClobberMemory();
    }
}

BENCHMARK(BenchmarkEuclidGCD)->Apply(CustomArg);

BENCHMARK_MAIN()
