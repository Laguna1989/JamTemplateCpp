#ifndef JAMTEMPLATE_CONSOLE_HPP
#define JAMTEMPLATE_CONSOLE_HPP

#include <game_object.hpp>
#include <log/log_entry.hpp>
#include <log/log_history_interface.hpp>
#include <imgui.h>
#include <memory>
#include <string>
#include <vector>

namespace jt {

class Console : public jt::GameObject {
public:
    Console();

    int inputUserCallback(ImGuiInputTextCallbackData* data) const;

private:
    std::shared_ptr<jt::LogHistoryInterface> m_history;

    mutable bool m_showConsole { false };
    mutable bool m_focus { false };
    mutable int m_historyPos { -1 };
    mutable std::vector<std::string> History;
    mutable std::vector<char> m_inputBufferFilter;
    mutable std::vector<char> m_inputBufferAction;
    mutable std::string m_lastCommand { "" };
    mutable bool m_drawLevel { true };
    mutable bool m_drawTag { true };
    mutable bool m_drawTime { false };
    mutable bool m_drawSource { false };

    void doCreate() override;
    void doUpdate(float const /*elapsed*/) override;
    void doDraw() const override;

    void renderOneLogEntry(jt::LogEntry const& entry) const;
    void storeInputInCommand() const;
    void clearInput() const;
    void storeActionInCommand() const;
    void handleCommand() const;
    void drawFilter() const;
};

} // namespace jt

#endif // JAMTEMPLATE_CONSOLE_HPP
