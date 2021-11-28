#include "control_command_move_cam.hpp"

ControlCommandMoveCam::ControlCommandMoveCam(
    jt::Vector2 scrollDirection, std::weak_ptr<jt::CamInterface> camera)
{
    m_scrollDirection = scrollDirection;
    m_camera = camera;
}

void ControlCommandMoveCam::execute(float elapsed)
{
    auto cam = m_camera.lock();

    if (cam) {
        cam->move(m_scrollDirection * elapsed);
    }
}
