#include "console.hpp"
#include <game_interface.hpp>
#include <strutils.hpp>
#include <imgui.h>
#include <string.h>

jt::Console::Console()
{
    m_inputBufferAction.resize(500);
    m_inputBufferFilter.resize(200);
}

void jt::Console::doCreate() { m_history = getGame()->cache().getLogHistory(); }

void jt::Console::doUpdate(float const /*elapsed*/)
{
    handleCommand();
    if (getGame()->input().keyboard()->justPressed(jt::KeyCode::Home)) {
        m_showConsole = !m_showConsole;

        m_focus = m_showConsole;
    }
}

void jt::Console::handleCommand() const
{
    if (m_lastCommand.empty()) {
        return;
    }
    getGame()->actionCommandManager().executeCommand(m_lastCommand);
    m_lastCommand = "";
}

void jt::Console::doDraw() const
{
    if (m_showConsole) {
        ImGui::Begin("Console", &m_showConsole);

        drawFilter();

        ImGui::Checkbox("Time", &m_drawTime);
        ImGui::SameLine();
        ImGui::Checkbox("Level", &m_drawLevel);
        ImGui::SameLine();
        ImGui::Checkbox("Tags", &m_drawTag);
        ImGui::SameLine();
        ImGui::Checkbox("Source", &m_drawSource);

        // Display contents in a scrolling region
        ImGui::TextColored(ImVec4(1, 1, 0, 1), "");
        float const footer_height_to_reserve
            = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
        ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false,
            ImGuiWindowFlags_HorizontalScrollbar);
        for (auto& entry : m_history->getHistory()) {
            renderOneLogEntry(entry);
        }
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);
        ImGui::EndChild();

        storeInputInCommand();
        ImGui::End();
    }
}

void jt::Console::drawFilter() const
{
    ImGui::InputText("Filter", m_inputBufferFilter.data(), m_inputBufferFilter.size());
}

void jt::Console::storeInputInCommand() const
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

void jt::Console::storeActionInCommand() const
{
    std::string str = m_inputBufferAction.data();
    strutil::trim(str);
    if (str.empty()) {
        return;
    }
    m_lastCommand = str;
    m_historyPos = -1;
    History.push_back(m_lastCommand);
    getGame()->logger().action(str);
}

void jt::Console::clearInput() const { strcpy(m_inputBufferAction.data(), ""); }

void jt::Console::renderOneLogEntry(jt::LogEntry const& entry) const
{
    ImVec4 color { 1.0f, 1.0f, 1.0f, 1.0f };

    std::string timeText = "";
    if (m_drawTime) {
        timeText = entry.time + ": ";
    }

    std::string tagText = "";
    if (m_drawTag) {
        for (auto const& t : entry.tags) {
            tagText += "<" + t + ">";
        }
        if (!entry.tags.empty()) {
            tagText += ": ";
        }
    }

    std::string levelText = "";

    if (entry.level == LogLevel::Warning) {
        color = ImVec4 { 1.0f, 1.0f, 0.0f, 1.0f };
        levelText = "[warn]";
    } else if (entry.level == LogLevel::Action) {
        color = ImVec4 { 0.8f, 0.8f, 0.2f, 1.0f };
        levelText = "# ";
        tagText = "";
    } else if (entry.level == LogLevel::Fatal) {
        color = ImVec4 { 1.0f, 0.0f, 0.0f, 1.0f };
        levelText = "[fatal]";
    } else if (entry.level == LogLevel::Error) {
        color = ImVec4 { 1.0f, 0.5f, 0.5f, 1.0f };
        levelText = "[error]";
    }
    if (!m_drawLevel) {
        levelText = "";
    }

    std::string sourceText;
    std::string text = timeText + levelText + tagText + entry.message + sourceText;

    std::string filterString = m_inputBufferFilter.data();
    strutil::trim(filterString);
    if (!filterString.empty()) {
        if (!strutil::contains(text, filterString)) {
            return;
        }
    }

    ImGui::PushStyleColor(ImGuiCol_Text, color);
    ImGui::Text("%s", text.c_str());
    ImGui::PopStyleColor();
}

int jt::Console::inputUserCallback(ImGuiInputTextCallbackData* data) const
{
    if (data->EventFlag == ImGuiInputTextFlags_CallbackHistory) {
        // Example of HISTORY
        int const prev_history_pos = m_historyPos;
        if (data->EventKey == ImGuiKey_UpArrow) {
            if (m_historyPos == -1)
                m_historyPos = static_cast<int>(History.size()) - 1;
            else if (m_historyPos > 0)
                m_historyPos--;
        } else if (data->EventKey == ImGuiKey_DownArrow) {
            if (m_historyPos != -1)
                if (++m_historyPos >= static_cast<int>(History.size()))
                    m_historyPos = -1;
        }

        // A better implementation would preserve the data on the current input line along with
        // cursor position.
        if (prev_history_pos != m_historyPos) {
            std::string const history_str = (m_historyPos >= 0) ? History[m_historyPos] : "";
            data->DeleteChars(0, data->BufTextLen);
            data->InsertChars(0, history_str.c_str());
        }
    }

    return 0;
}
