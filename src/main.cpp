#include <windows.h>
#include "ui/Window.h"

// Include legacy components - kept for historical reference but not used
#include "unused/LegacyComponents.h"

using namespace Evolution;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // 创建窗口
    Window window;
    if (!window.Create(hInstance, nCmdShow)) {
        return -1;
    }

    // 运行消息循环
    return window.Run();
}