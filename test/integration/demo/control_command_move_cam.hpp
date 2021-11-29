#ifndef GUARD_JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP
#define GUARD_JAMTEMPLATE_CONTROL_COMMAND_MOVECAM_HPP

#include "input/control_command_once.hpp"
#include "vector.hpp"
#include <cam_interface.hpp>
#include <memory>

class ControlCommandMoveCam : public jt::ControlCommandOnce {
public:
    explicit ControlCommandMoveCam(
        jt::Vector2 scrollDirection, std::weak_ptr<jt::CamInterface> camera);
    void doExecute(float elapsed) override;

private:
    jt::Vector2 m_scrollDirection;
    std::weak_ptr<jt::CamInterface> m_camera;
};

#endif // GUARD_JAMTEMAPLTE_CONTROL_COMMAND_MOVECAM_HPP
