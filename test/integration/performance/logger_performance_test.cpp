#include <log/log_target_ostream.hpp>
#include <log/logger.hpp>
#include <benchmark/benchmark.h>

static void BM_LoggerLogWithoutTarget(benchmark::State& state)
{
    for (auto _ : state) {
        jt::Logger logger;

        for (auto i = 0u; i != 200u; ++i) {
            logger.verbose("abcd1", { "b", "c" });
            logger.debug("abcd2", { "b", "c" });
            logger.info("abcd3", { "b", "c" });
            logger.warning("abcd4", { "b", "c" });
            logger.error("abcd5", { "b", "c" });
            logger.fatal("abcd6", { "b", "c" });
        }
    }
}

static void BM_LoggerLogWithCoutTargetSetToOff(benchmark::State& state)
{
    for (auto _ : state) {
        jt::Logger logger;
        auto target = std::make_shared<jt::LogTargetOstream>();
        target->setLogLevel(jt::LogLevel::Off);
        logger.addLogTarget(target);

        for (auto i = 0u; i != 200u; ++i) {
            logger.verbose("abcd1", { "b", "c" });
            logger.debug("abcd2", { "b", "c" });
            logger.info("abcd3", { "b", "c" });
            logger.warning("abcd4", { "b", "c" });
            logger.error("abcd5", { "b", "c" });
            logger.fatal("abcd6", { "b", "c" });
        }
    }
}

BENCHMARK(BM_LoggerLogWithoutTarget)->Unit(benchmark::kMillisecond);
BENCHMARK(BM_LoggerLogWithCoutTargetSetToOff)->Unit(benchmark::kMillisecond);
