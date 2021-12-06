#include "console.hpp"
#include "imgui.h"
#include "strutils.hpp"

namespace jt {

Console::Console(std::shared_ptr<jt::LogInterface> log)
    : m_log { log }
{
}

void Console::doUpdate(float const elapsed) { }

void Console::doDraw() const
{
    ImGui::Begin("Console");
    // Display contents in a scrolling region
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("ScrollingRegion");
    for (auto const& entry : m_log->getAllLogs()) {
        renderOneLogEntry(entry);
    }
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);
    ImGui::EndChild();
    ImGui::End();
}

void Console::renderOneLogEntry(jt::LogEntry const& entry) const
{
    ImVec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
    std::string text = entry.message;
    if (entry.level == LogLevel::LogLevelError) {
        color = ImVec4 { 1.0f, 0.4f, 0.4f, 1.0f };
        text = "[error]" + entry.message;
    }
    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::Text(text.c_str());
    ImGui::PopStyleColor();
}

} // namespace jt
