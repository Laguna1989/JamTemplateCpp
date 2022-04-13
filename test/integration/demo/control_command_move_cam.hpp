#ifndef JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP
#define JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP

#include <cam_interface.hpp>
#include <input/control_commands/control_command_once.hpp>
#include <vector.hpp>
#include <memory>

class ControlCommandMoveCam : public jt::ControlCommandOnce {
public:
    explicit ControlCommandMoveCam(jt::Vector2f scrollDirection, jt::CamInterface& camera);
    void doExecute(float elapsed) override;

private:
    jt::Vector2f m_scrollDirection;
    jt::CamInterface& m_camera;
};

#endif // JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP
