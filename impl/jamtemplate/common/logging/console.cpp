#include "console.hpp"
#include "game_interface.hpp"
#include "imgui.h"
#include "strutils.hpp"
#include <iostream>
#include <string.h>

namespace jt {

Console::Console(jt::LoggerInterface& logger)
    : m_logger { logger }
{
    m_inputBufferAction.resize(500);
    m_inputBufferFilter.resize(200);
}

void Console::doUpdate(float const elapsed)
{
    handleCommand();
    if (!getGame()->input().keyboard()) {
        return;
    }
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Home)) {
        m_showConsole = !m_showConsole;

        m_focus = m_showConsole;
    }
}
void Console::handleCommand() const
{
    if (m_lastCommand.empty()) {
        return;
    }
    getGame()->getActionCommandManager().executeCommand(m_lastCommand);
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
        for (auto& entry : m_logger.getHistory()) {
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
    m_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue
        | ImGuiInputTextFlags_CallbackCompletion | ImGuiInputTextFlags_CallbackHistory;
    if (ImGui::InputText(
            "Input", m_inputBufferAction.data(), m_inputBufferAction.size(), input_text_flags,
            [](auto data) {
                Console* console = (Console*)data->UserData;
                console->inputUserCallback(data);
                return 0;
            },
            (void*)this)) {

        storeActionInCommand();

        clearInput();
        m_focus = true;
    }

    // focus back on console input if return was pressed.
    ImGui::SetItemDefaultFocus();
    if (m_focus) {
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
    HistoryPos = -1;
    History.push_back(m_lastCommand);
    m_logger.action(str);
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
int Console::inputUserCallback(ImGuiInputTextCallbackData* data)
{
    switch (data->EventFlag) {
    case ImGuiInputTextFlags_CallbackHistory: {
        // Example of HISTORY
        const int prev_history_pos = HistoryPos;
        if (data->EventKey == ImGuiKey_UpArrow) {
            if (HistoryPos == -1)
                HistoryPos = static_cast<int>(History.size()) - 1;
            else if (HistoryPos > 0)
                HistoryPos--;
        } else if (data->EventKey == ImGuiKey_DownArrow) {
            if (HistoryPos != -1)
                if (++HistoryPos >= History.size())
                    HistoryPos = -1;
        }

        // A better implementation would preserve the data on the current input line along with
        // cursor position.
        if (prev_history_pos != HistoryPos) {
            std::string history_str = (HistoryPos >= 0) ? History[HistoryPos] : "";
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, history_str.c_str());
        }
    }
    }
    return 0;
}

} // namespace jt
