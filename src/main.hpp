#ifndef GAME_MAIN_HPP_GUARD_12345
#define GAME_MAIN_HPP_GUARD_12345

// win32 is also defined in 64bit builds
#if defined WIN32 && defined NDEBUG // release mode
#include <windows.h>
void hideConsoleInRelease()
{
    HWND hWin = GetForegroundWindow();
    ShowWindow(hWin, SW_HIDE);
}

#else

void hideConsoleInRelease()
{
    // nothing to do in debug mode
}

#endif

#endif
