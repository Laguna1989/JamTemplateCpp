#ifndef GAME_MAIN_HPP
#define GAME_MAIN_HPP

// win32 is also defined in 64bit builds
#if defined WIN32 && !defined(JT_ENABLE_DEBUG) // release mode
#include <windows.h>
void hideConsoleInRelease()
{
    HWND hWin = GetForegroundWindow();
    ShowWindow(hWin, SW_HIDE);
}

#else

void hideConsoleInRelease()
{
    // nothing to do in debug mode or non-windows builds
}

#endif

#endif
