#include <action_commands/action_command_manager.hpp>
#include <log/logger_null.hpp>
#include <array>
#include <benchmark/benchmark.h>

static void BM_GetAllCommands(benchmark::State& state)
{
    for (auto _ : state) {
        jt::null_objects::LoggerNull logger;
        jt::ActionCommandManager acm { logger };
        constexpr auto size = 40u;
        std::array<std::shared_ptr<bool>, size> myarray;
        for (std::size_t i = 0u; i != size; ++i) {
            myarray[i]
                = acm.registerTemporaryCommand(std::to_string(i), [](auto const& /*unused*/) {});
        }

        for (int i = 0; i != 100; ++i) {
            auto commands = acm.getAllCommands();
            for (auto const& c : commands) {
                (void)c;
                /*noop*/
            }
        }
    }
}

BENCHMARK(BM_GetAllCommands)->Unit(benchmark::kMillisecond);
