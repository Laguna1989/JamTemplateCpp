#include "performance_measurement.hpp"
#include <nlohmann.hpp>
#include <sstream>
#include <thread>

std::atomic<size_t> g_index;
std::vector<jt::TimeMeasureObjectData> g_profilingData(1000);

float jt::getDurationInSecondsSince(std::chrono::time_point<std::chrono::steady_clock> const& since)
{
    auto const now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now - since).count() / 1000.0f
        / 1000.0f;
}

std::string to_string(std::thread::id id)
{
    std::stringstream ss;
    ss << id;
    return ss.str();
}

void jt::to_json(nlohmann::json& j, jt::TimeMeasureObjectData const& data)
{
    std::int64_t const start = std::chrono::time_point_cast<std::chrono::nanoseconds>(data.start)
                                   .time_since_epoch()
                                   .count();
    std::int64_t const duration
        = std::chrono::duration_cast<std::chrono::nanoseconds>(data.end - data.start).count();

    j["pid"] = 1;
    j["tid"] = to_string(data.threadId);
    j["cat"] = "PERF";
    j["displayTimeUnit"] = "ns";
    j["ph"] = "X";
    j["ts"] = start;
    j["dur"] = duration;
    j["name"] = data.name;
}

std::string jt::getTracingJson(std::vector<TimeMeasureObjectData> const& data)
{
    nlohmann::json j;
    j["traceEvents"] = data;
    return j.dump(4);
}

std::vector<jt::TimeMeasureObjectData> jt::getMeasurementData() { return g_profilingData; }

jt::TimeMeasureObject::TimeMeasureObject(std::string const& str)
    : m_start { std::chrono::steady_clock::now() }
    , m_name { str }
{
}

jt::TimeMeasureObject::~TimeMeasureObject()
{
    TimeMeasureObjectData measurement;
    measurement.name = m_name;
    measurement.start = m_start;
    measurement.end = std::chrono::steady_clock::now();
    measurement.threadId = std::this_thread::get_id();

    std::size_t const index = g_index.fetch_add(1) % g_profilingData.size();

    g_profilingData[index] = measurement;
}
