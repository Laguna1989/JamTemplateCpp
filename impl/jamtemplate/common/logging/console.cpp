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
    m_inputBufferAction.resize(500);
    m_inputBufferFilter.resize(200);
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

        drawFilter();

        ImGui::Checkbox("Time", &m_drawTime);
        ImGui::SameLine();
        ImGui::Checkbox("Level", &m_drawLevel);
        ImGui::SameLine();
        ImGui::Checkbox("Tags", &m_drawTag);

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

void Console::drawFilter() const
{
    ImGui::InputText("Filter", m_inputBufferFilter.data(), m_inputBufferFilter.size());
}

void Console::storeInputInCommand() const
{
    bool reclaim_focus = false;
    // TODO history and callback completion
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText(
            "Input", m_inputBufferAction.data(), m_inputBufferAction.size(), input_text_flags)) {

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
    std::string str = m_inputBufferAction.data();
    strutil::trim(str);
    if (str.empty()) {
        return;
    }
    m_lastCommand = str;
    m_logger->action(str);
}
void Console::clearInput() const { strcpy(m_inputBufferAction.data(), ""); }

void Console::renderOneLogEntry(jt::LogEntry const& entry) const
{
    ImVec4 color { 1.0f, 1.0f, 1.0f, 1.0f };

    std::string timeText = "";
    if (m_drawTime) {
        timeText = entry.time + ": ";
    }

    std::string tagText = "";
    if (m_drawTag) {
        for (auto& t : entry.tags) {
            tagText += "<" + t + ">";
        }
        if (!entry.tags.empty()) {
            tagText += ": ";
        }
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
    if (!m_drawLevel) {
        levelText = "";
    }

    std::string text = timeText + levelText + tagText + entry.message;

    std::string filterString = m_inputBufferFilter.data();
    strutil::trim(filterString);
    if (!filterString.empty()) {
        if (!strutil::contains(text, filterString)) {
            return;
        }
    }

    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::Text(text.c_str());
    ImGui::PopStyleColor();
}

} // namespace jt
