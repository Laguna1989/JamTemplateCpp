#include "command_recorder.hpp"

void CommandRecorder::execute(float elapsed) { m_executed = true; }
void CommandRecorder::reset() { m_reset = true; }
