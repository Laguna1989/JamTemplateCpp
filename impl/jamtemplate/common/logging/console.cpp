#include "console.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include "strutils.hpp"
#include <iostream>
#include <string.h>

namespace jt {

Console::Console(std::shared_ptr<jt::LoggerInterface> target)
    : m_logger { target }
{
    m_inputBuffer.resize(500);
}

void Console::doUpdate(float const elapsed)
{
    handleCommand();
    if (!getGame()->input() || !getGame()->input()->keyboard()) {
        return;
    }
    if (getGame()->input()->keyboard()->justPressed(jt::KeyCode::Home)) {

        m_showConsole = !m_showConsole;
    }
}
void Console::handleCommand() const
{
    if (m_lastCommand.empty()) {
        return;
    }

    std::cout << m_lastCommand.size() << std::endl;
    // TODO implement actual command callbacks
    if (m_lastCommand == "clear") {
        m_logger->clear();
    } else {

        m_logger->warning("unknown command '" + m_lastCommand + "'");
    }
    m_lastCommand = "";
}

void Console::doDraw() const
{
    if (m_showConsole) {
        ImGui::Begin("Console", &m_showConsole);
        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "");
        const float footer_height_to_reserve
            = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false,
            ImGuiWindowFlags_HorizontalScrollbar);
        for (auto& entry : m_logger->getHistory()) {
            renderOneLogEntry(entry);
        }
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();

        storeInputInCommand();
        ImGui::End();
    }
}
void Console::storeInputInCommand() const
{
    bool reclaim_focus = false;
    // TODO history and callback completion
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText("Input", m_inputBuffer.data(), m_inputBuffer.size(), input_text_flags)) {

        storeActionInCommand();

        clearInput();
        reclaim_focus = true;
    }

    // focus back on console input if return was pressed.
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus) {
        ImGui::SetKeyboardFocusHere(-1);
    }
}
void Console::storeActionInCommand() const
{
    std::string str = m_inputBuffer.data();
    strutil::trim(str);
    if (str.empty()) {
        return;
    }
    m_lastCommand = str;
    m_logger->action(str);
}
void Console::clearInput() const { strcpy(m_inputBuffer.data(), ""); }

void Console::renderOneLogEntry(jt::LogEntry const& entry) const
{
    // TODO filter by tag
    // TODO optional print filter
    ImVec4 color { 1.0f, 1.0f, 1.0f, 1.0f };
    std::string tagText = "";
    for (auto& t : entry.tags) {
        tagText += "<" + t + ">";
    }
    if (!entry.tags.empty()) {
        tagText += ": ";
    }
    std::string levelText = "";
    if (entry.level == LogLevel::LogLevelAction) {
        color = ImVec4 { 0.9f, 0.9f, 0.0f, 1.0f };
        levelText = "# ";
        tagText = "";
    } else if (entry.level == LogLevel::LogLevelFatal) {
        color = ImVec4 { 1.0f, 0.0f, 0.0f, 1.0f };
        levelText = "[fatal]";
    } else if (entry.level == LogLevel::LogLevelError) {
        color = ImVec4 { 1.0f, 0.5f, 0.5f, 1.0f };
        levelText = "[error]";
    }

    std::string text = levelText + tagText + entry.message;

    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::Text(text.c_str());
    ImGui::PopStyleColor();
}

} // namespace jt
