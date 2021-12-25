#include "control_command_move_cam.hpp"

ControlCommandMoveCam::ControlCommandMoveCam(jt::Vector2f scrollDirection, jt::CamInterface& camera)
    : m_camera { camera }
{
    m_scrollDirection = scrollDirection;
}

void ControlCommandMoveCam::doExecute(float elapsed) { m_camera.move(m_scrollDirection * elapsed); }
