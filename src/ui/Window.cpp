#include "ui/Window.h"
#include <windowsx.h>
#include <cwchar>
#include <cstdio>
#include <cstdint>
#include <cstdarg>
#include <commctrl.h>
#include <richedit.h>
#include <cassert>
#include <crtdbg.h>

#pragma comment(lib, "comctl32.lib")

// 启用调试模式的断言
#ifdef _DEBUG
#define DEBUG_ASSERT(condition) \
    do { \
        if (!(condition)) { \
            _CrtDbgBreak(); \
        } \
    } while(0)
#else
#define DEBUG_ASSERT(condition) ((void)0)
#endif

namespace Evolution {

// 静态常量
const wchar_t* Window::CLASS_NAME = L"EvolutionGameWindow";
// static const int ID_BTN_EVENTS = 206; // 如果需要兼容性或仅作为注释则在此定义。
// Window.h中有静态常量定义，如果在switch中使用则必须有效。
// 我们从头文件中移除了它，但确保我们不会使用它。

Window::Window()
    : hwnd_(nullptr)
    , hInstance_(nullptr)
    , hLabelVersion_(nullptr)
    , hLabelIdentity_(nullptr)
    , hLabelRNA_(nullptr)
    , hBtnRNA_(nullptr)
    , hLabelDNA_(nullptr)
    , hBtnDNA_(nullptr)
    , hBtnOrganelle_(nullptr)
    , hBtnMembrane_(nullptr)
    , hBtnNucleus_(nullptr)
    , hBtnMitochondria_(nullptr)
    , hBtnEukaryote_(nullptr)
        , hBtnSettings_(nullptr)
    , hBtnLog_(nullptr)
    , hBtnProgress_(nullptr)
    // hBtnEvents_(nullptr) // 已移除
    , hBtnSexual_(nullptr)
    , hBtnAsexual_(nullptr)
    , hBtnPhagocytosis_(nullptr)
    , hBtnChloroplast_(nullptr)
    , hBtnChitin_(nullptr)
    , hBtnSentience_(nullptr)
    , hBtnMulticellular_(nullptr)
    , hBtnBilateral_(nullptr)
    , rnaCount_(0)
    , rnaMax_(100)
    , rnaRate_(0)
    , dnaCount_(0)
    , dnaMax_(100)
    , dnaRate_(0)
    , isDnaUnlocked_(false)
    , organelleCount_(0)
    , membraneCount_(0)
    , nucleusCount_(0)
    , mitochondriaCount_(0)
    , eukaryoteCount_(0)
    , isOrganelleUnlocked_(false)
    , isMembraneUnlocked_(false)
    , isNucleusUnlocked_(false)
    , isMitochondriaUnlocked_(false)
    , isEukaryoteUnlocked_(false)
    , isReproductionUnlocked_(false)
    , hasChosenReproduction_(false)
    , isSexual_(false)
    , hasChosenEvolution_(false)
    , isSentienceUnlocked_(false)
    , evolutionChoice_(0)
    , isSpeciesUnlocked_(false)
    , isCivilizationUnlocked_(false)
    , isGovSelectionUnlocked_(false)
    , isGameEnded_(false)
        , hBtnDemon_(nullptr)
    , hBtnBalrog_(nullptr)
    , hBtnHeaven_(nullptr)
    , hBtnHumanoid_(nullptr)
    , hBtnDwarf_(nullptr)
    , hBtnGiant_(nullptr)
    , hBtnBeast_(nullptr)
    , hBtnEggLayer_(nullptr)
    , hBtnReptile_(nullptr)
    , hBtnAquatic_(nullptr)
    , hBtnFae_(nullptr)
    , hBtnDesert_(nullptr)
    , hBtnFlame_(nullptr)
    , hBtnPolar_(nullptr)
    , hBtnArthropod_(nullptr)
    , hBtnAberration_(nullptr)
    , hBtnGovernment_(nullptr)
    , hBtnAnarchy_(nullptr)
    , hBtnAutocracy_(nullptr)
    , hBtnDemocracy_(nullptr)
    , hBtnOligarchy_(nullptr)
    , hBtnTheocracy_(nullptr)
    , hBtnRepublic_(nullptr)
    , hBtnSocialism_(nullptr)
    , hBtnCorpBureaucracy_(nullptr)
    , hBtnTechBureaucracy_(nullptr)
    , hBtnFederalism_(nullptr)
    , hBtnMagocracy_(nullptr)
    , hBtnDictatorship_(nullptr)
    , hTooltip_(nullptr)
{
}

Window::~Window() {
    if (hwnd_) {
        DestroyWindow(hwnd_);
    }
}

bool Window::Create(HINSTANCE hInstance, int nCmdShow) {
    hInstance_ = hInstance;

    // 注册窗口类
    if (!RegisterWindowClass()) {
        return false;
    }

    // 创建窗口
    // 标题：进化游戏 v1.5.8
    hwnd_ = CreateWindowExW(
        0,                              // 扩展样式
        CLASS_NAME,                     // 类名
        L"\u8FDB\u5316\u6E38\u620F v1.5.8",      // 窗口标题
        WS_OVERLAPPEDWINDOW,            // 窗口样式
        CW_USEDEFAULT, CW_USEDEFAULT,   // 位置
        1000, 700,                     // 大小
        nullptr,                        // 父窗口
        nullptr,                        // 菜单
        hInstance,                      // 实例
        this                           // 附加数据
    );

    if (!hwnd_) {
        return false;
    }

    // 设置被动生成定时器（1秒）
    SetTimer(hwnd_, ID_TIMER_PASSIVE, 1000, nullptr);

    // 显示窗口
    ShowWindow(hwnd_, nCmdShow);
    UpdateWindow(hwnd_);

    return true;
}

bool Window::RegisterWindowClass() {
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(Window*);
    wc.hInstance = hInstance_;
    wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = CLASS_NAME;
    wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);

    return RegisterClassExW(&wc) != 0;
}

LRESULT CALLBACK Window::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    Window* pThis = nullptr;

    if (uMsg == WM_NCCREATE) {
        CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
        pThis = (Window*)pCreate->lpCreateParams;
        SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
        pThis->hwnd_ = hwnd;
    } else {
        pThis = (Window*)GetWindowLongPtr(hwnd, GWLP_USERDATA);
    }

    // 确保我们有有效的窗口实例
    DEBUG_ASSERT(pThis != nullptr && "Window::WindowProc - pThis is null");

    if (pThis) {
        return pThis->HandleMessage(hwnd, uMsg, wParam, lParam);
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

void Window::CreateControls() {
    // 确保主窗口句柄有效
    DEBUG_ASSERT(hwnd_ != nullptr && "Window::CreateControls - hwnd_ is null");
    DEBUG_ASSERT(hInstance_ != nullptr && "Window::CreateControls - hInstance_ is null");

    // 初始创建时大小为0，将由WM_SIZE调整

    // --- 左列：信息和统计 ---
    hLabelVersion_ = CreateWindowW(L"STATIC", L"\u53F2\u524D v1.4.9", WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_LABEL_VERSION, hInstance_, nullptr);
    DEBUG_ASSERT(hLabelVersion_ != nullptr && "Failed to create version label");
    hLabelIdentity_ = CreateWindowW(L"STATIC", L"\u73A9\u5BB6\u8EAB\u4EFD\uFF1A\u539F\u59CB\u8F6F\u6CE5\u4E2D\u7684\u539F\u751F\u8D28", WS_CHILD | WS_VISIBLE | SS_LEFT, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_LABEL_IDENTITY, hInstance_, nullptr);
    hLabelRNA_ = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_LABEL_RNA, hInstance_, nullptr);
    hLabelDNA_ = CreateWindowW(L"STATIC", L"", WS_CHILD | WS_VISIBLE | SS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_LABEL_DNA, hInstance_, nullptr);

    // --- 中央列：操作和游戏循环（网格布局）---
    hBtnRNA_ = CreateWindowW(L"BUTTON", L"\u751F\u6210 RNA", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_RNA, hInstance_, nullptr);
    hBtnDNA_ = CreateWindowW(L"BUTTON", L"\u751F\u6210 DNA\n(-2 RNA)", WS_CHILD | WS_VISIBLE | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DNA, hInstance_, nullptr);
    hBtnOrganelle_ = CreateWindowW(L"BUTTON", L"", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_ORGANELLE, hInstance_, nullptr);
    hBtnMembrane_ = CreateWindowW(L"BUTTON", L"", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_MEMBRANE, hInstance_, nullptr);

    hBtnNucleus_ = CreateWindowW(L"BUTTON", L"", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_NUCLEUS, hInstance_, nullptr);
    hBtnMitochondria_ = CreateWindowW(L"BUTTON", L"", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_MITOCHONDRIA, hInstance_, nullptr);
    hBtnEukaryote_ = CreateWindowW(L"BUTTON", L"", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_EUKARYOTE, hInstance_, nullptr);
    hBtnSexual_ = CreateWindowW(L"BUTTON", L"\u6709\u6027\u7e41\u6b96\n(-175 DNA)", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_SEXUAL, hInstance_, nullptr);

    hBtnAsexual_ = CreateWindowW(L"BUTTON", L"\u65e0\u6027\u7e41\u6b96\n(-175 DNA)", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_ASEXUAL, hInstance_, nullptr);
    hBtnPhagocytosis_ = CreateWindowW(L"BUTTON", L"\u7ec6\u80de\u541e\u566c", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_PHAGOCYTOSIS, hInstance_, nullptr);
    hBtnChloroplast_ = CreateWindowW(L"BUTTON", L"\u53f6\u7eff\u4f53", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_CHLOROPLAST, hInstance_, nullptr);
    hBtnChitin_ = CreateWindowW(L"BUTTON", L"\u51e0\u4e01\u8d28", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_CHITIN, hInstance_, nullptr);

    hBtnSentience_ = CreateWindowW(L"BUTTON", L"\u611f\u77e5\n(-300 RNA, -300 DNA)", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_SENTIENCE, hInstance_, nullptr);
    hBtnMulticellular_ = CreateWindowW(L"BUTTON", L"\u591a\u7ec6\u80de\u751f\u7269\n(-200 DNA)", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_MULTICELLULAR, hInstance_, nullptr);
    hBtnBilateral_ = CreateWindowW(L"BUTTON", L"\u5de6\u53f3\u5bf9\u79f0\n(-250 DNA)", WS_CHILD | BS_MULTILINE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_BILATERAL, hInstance_, nullptr);

    hBtnGovernment_ = CreateWindowW(L"BUTTON", L"\u653f\u5e9c", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_GOVERNMENT, hInstance_, nullptr);
    hBtnAnarchy_ = CreateWindowW(L"BUTTON", L"\u65e0\u653f\u5e9c", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_ANARCHY, hInstance_, nullptr);

    hBtnDemon_ = CreateWindowW(L"BUTTON", L"\u6076\u9b54", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DEMON, hInstance_, nullptr);
    hBtnBalrog_ = CreateWindowW(L"BUTTON", L"\u708E\u9b54", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_BALROG, hInstance_, nullptr);
    hBtnHeaven_ = CreateWindowW(L"BUTTON", L"\u5929\u5802", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_HEAVEN, hInstance_, nullptr);
    hBtnHumanoid_ = CreateWindowW(L"BUTTON", L"\u7C7B\u4EBA", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_HUMANOID, hInstance_, nullptr);
    
    hBtnDwarf_ = CreateWindowW(L"BUTTON", L"\u77EE\u4EBA", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DWARF, hInstance_, nullptr);
    hBtnGiant_ = CreateWindowW(L"BUTTON", L"\u5DE8\u4EBA", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_GIANT, hInstance_, nullptr);
    hBtnBeast_ = CreateWindowW(L"BUTTON", L"\u54FA\u4E73\u52A8\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_BEAST, hInstance_, nullptr);
    hBtnEggLayer_ = CreateWindowW(L"BUTTON", L"\u86CB\u58F3\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_EGGLAYER, hInstance_, nullptr);
    
    hBtnReptile_ = CreateWindowW(L"BUTTON", L"\u6C34\u751F\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_REPTILE, hInstance_, nullptr);
    hBtnAquatic_ = CreateWindowW(L"BUTTON", L"\u6D77\u6D0B\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_AQUATIC, hInstance_, nullptr);
    hBtnFae_ = CreateWindowW(L"BUTTON", L"\u7CBE\u602A", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_FAE, hInstance_, nullptr);
    hBtnDesert_ = CreateWindowW(L"BUTTON", L"\u6C99\u6F20\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DESERT, hInstance_, nullptr);
    
    hBtnFlame_ = CreateWindowW(L"BUTTON", L"\u70C8\u7130\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_FLAME, hInstance_, nullptr);
    hBtnPolar_ = CreateWindowW(L"BUTTON", L"\u6781\u5730\u751F\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_POLAR, hInstance_, nullptr);
    hBtnArthropod_ = CreateWindowW(L"BUTTON", L"\u8282\u80A2\u52A8\u7269", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_ARTHROPOD, hInstance_, nullptr);
    hBtnAberration_ = CreateWindowW(L"BUTTON", L"\u5F02\u9B54", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_ABERRATION, hInstance_, nullptr);

    hBtnAutocracy_ = CreateWindowW(L"BUTTON", L"\u4e13\u5236", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_AUTOCRACY, hInstance_, nullptr);
    hBtnDemocracy_ = CreateWindowW(L"BUTTON", L"\u6c11\u4e3b", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DEMOCRACY, hInstance_, nullptr);
    hBtnOligarchy_ = CreateWindowW(L"BUTTON", L"\u5be1\u5934", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_OLIGARCHY, hInstance_, nullptr);
    hBtnTheocracy_ = CreateWindowW(L"BUTTON", L"\u795e\u6743", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_THEOCRACY, hInstance_, nullptr);

    hBtnRepublic_ = CreateWindowW(L"BUTTON", L"\u5171\u548c", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_REPUBLIC, hInstance_, nullptr);
    hBtnSocialism_ = CreateWindowW(L"BUTTON", L"\u793e\u4f1a\u4e3b\u4e49", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_SOCIALISM, hInstance_, nullptr);
    hBtnCorpBureaucracy_ = CreateWindowW(L"BUTTON", L"\u516c\u53f8\u5b98\u50da\u4e3b\u4e49", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_CORP_BUREAUCRACY, hInstance_, nullptr);
    hBtnTechBureaucracy_ = CreateWindowW(L"BUTTON", L"\u6280\u672f\u5b98\u50da\u4e3b\u4e49", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_TECH_BUREAUCRACY, hInstance_, nullptr);

    hBtnFederalism_ = CreateWindowW(L"BUTTON", L"\u8054\u90a6\u5236", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_FEDERALISM, hInstance_, nullptr);
    hBtnMagocracy_ = CreateWindowW(L"BUTTON", L"\u9b54\u6cd5\u653f\u5e9c", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_MAGOCRACY, hInstance_, nullptr);
    hBtnDictatorship_ = CreateWindowW(L"BUTTON", L"\u72ec\u88c1", WS_CHILD | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_DICTATORSHIP, hInstance_, nullptr);

    // --- 右列：菜单 ---
    hBtnLog_ = CreateWindowW(L"BUTTON", L"\u65E5\u5FD7\u8BB0\u5F55", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_LOG, hInstance_, nullptr);
    hBtnProgress_ = CreateWindowW(L"BUTTON", L"\u8FDB\u5EA6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_PROGRESS, hInstance_, nullptr);
    // hBtnEvents_ = CreateWindowW(L"BUTTON", L"\u4E8B\u4EF6", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_EVENTS, hInstance_, nullptr); // 已移除
    hBtnSettings_ = CreateWindowW(L"BUTTON", L"\u8BBE\u7F6E", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_BTN_SETTINGS, hInstance_, nullptr);
    
    // 原生质下的嵌入式日志视图 (ListBox)
    hLogView_ = CreateWindowExW(WS_EX_NOPARENTNOTIFY, L"LISTBOX", L"", 
        WS_CHILD | WS_VSCROLL | WS_CLIPSIBLINGS | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | WS_BORDER, 
        0, 0, 0, 0, hwnd_, (HMENU)(intptr_t)ID_LIST_LOGVIEW, hInstance_, nullptr);
    HFONT hFontLog = CreateFontW(18, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei");
    SendMessage(hLogView_, WM_SETFONT, (WPARAM)hFontLog, TRUE);
    ShowWindow(hLogView_, SW_HIDE);

    // 设置字体（较大）
    HFONT hFont = CreateFontW(24, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei");
    HFONT hFontBold = CreateFontW(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei");

    SendMessage(hLabelVersion_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hLabelIdentity_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hLabelRNA_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnRNA_, WM_SETFONT, (WPARAM)hFontBold, TRUE);
    SendMessage(hLabelDNA_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnDNA_, WM_SETFONT, (WPARAM)hFontBold, TRUE);
    
    SendMessage(hBtnOrganelle_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnMembrane_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnNucleus_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnMitochondria_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnEukaryote_, WM_SETFONT, (WPARAM)hFont, TRUE);

    SendMessage(hBtnSexual_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnAsexual_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnPhagocytosis_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnChloroplast_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnChitin_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnMulticellular_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnBilateral_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnSentience_, WM_SETFONT, (WPARAM)hFont, TRUE);

    SendMessage(hBtnDemon_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnBalrog_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnHeaven_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnHumanoid_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnDwarf_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnGiant_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnBeast_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnEggLayer_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnReptile_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnAquatic_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnFae_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnDesert_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnFlame_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnPolar_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnArthropod_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnAberration_, WM_SETFONT, (WPARAM)hFont, TRUE);

    SendMessage(hBtnGovernment_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnAnarchy_, WM_SETFONT, (WPARAM)hFont, TRUE);

    SendMessage(hBtnAutocracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnDemocracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnOligarchy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnTheocracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnRepublic_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnSocialism_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnCorpBureaucracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnTechBureaucracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnFederalism_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnMagocracy_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnDictatorship_, WM_SETFONT, (WPARAM)hFont, TRUE);

    SendMessage(hBtnLog_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnProgress_, WM_SETFONT, (WPARAM)hFont, TRUE);
    // SendMessage(hBtnEvents_, WM_SETFONT, (WPARAM)hFont, TRUE);
    SendMessage(hBtnSettings_, WM_SETFONT, (WPARAM)hFont, TRUE);

    // --- 工具提示 ---
    InitTooltips();
    AddTooltip(hBtnRNA_, L"Function: Generate 1 RNA\nCost: None");
    AddTooltip(hBtnDNA_, L"Function: Synthesize 1 DNA\nCost: 2 RNA\nRequirement: 50 RNA to Unlock");
    AddTooltip(hBtnOrganelle_, L"Function: +1 RNA/s\nCost: 12 RNA, 4 DNA");
    AddTooltip(hBtnMembrane_, L"Function: +10 RNA Cap\nCost: 4 RNA");
    AddTooltip(hBtnNucleus_, L"Function: +1 DNA/s\nCost: 38 RNA, 18 DNA\nRequirement: 10 Organelles");
    AddTooltip(hBtnMitochondria_, L"Function: +5 RNA/s, +2 DNA/s\nCost: 125 RNA, 100 DNA\nRequirement: Nucleus");
    AddTooltip(hBtnEukaryote_, L"Function: Unlock Evolution Stage\nCost: 40 RNA, 52 DNA\nRequirement: Nucleus");
    AddTooltip(hBtnSexual_, L"Function: Unlock Sexual Reproduction Path\nCost: 175 DNA\nRequirement: Eukaryote");
    AddTooltip(hBtnAsexual_, L"Function: Unlock Asexual Reproduction Path\nCost: 175 DNA\nRequirement: Eukaryote");
    AddTooltip(hBtnSentience_, L"Function: Awaken Sentience\nCost: 300 RNA, 300 DNA\nRequirement: Species Selected");
    
    AddTooltip(hBtnPhagocytosis_, L"Function: Evolve Phagocytosis (Animal Path)\nCost: 175 DNA\nRequirement: Sexual Reproduction");
    AddTooltip(hBtnChloroplast_, L"Function: Evolve Chloroplasts (Plant Path)\nCost: 175 DNA\nRequirement: Asexual Reproduction");
    AddTooltip(hBtnChitin_, L"Function: Evolve Chitin (Fungi Path)\nCost: 175 DNA\nRequirement: Asexual Reproduction");
    AddTooltip(hBtnMulticellular_, L"Function: Evolve Multicellularity\nCost: 200 DNA\nRequirement: Evolution Direction Chosen");
    AddTooltip(hBtnBilateral_, L"Function: Evolve Bilateral Symmetry\nCost: 250 DNA\nRequirement: Multicellular Organism");

    UpdateUIDisplay();
}

void Window::ResizeControls(int width, int height) {
    // 确保尺寸有效
    DEBUG_ASSERT(width > 0 && "ResizeControls - width is invalid");
    DEBUG_ASSERT(height > 0 && "ResizeControls - height is invalid");
    DEBUG_ASSERT(hwnd_ != nullptr && "ResizeControls - hwnd_ is null");

    if (width == 0 || height == 0) return;

    // 布局比例
    // 左侧.*中央.*右侧: 20%
    int padding = 10;
    
    int leftW = (int)(width * 0.20) - (padding * 2);
    int rightW = (int)(width * 0.20) - (padding * 2);
    int centerW = width - leftW - rightW - (padding * 6); // 剩余宽度减去间隙
    
    int leftX = padding;
    int centerX = leftX + leftW + (padding * 2);
    int rightX = centerX + centerW + (padding * 2);

    int contentY = 20;

    // --- 左列：信息和统计 ---
    MoveWindow(hLabelVersion_, leftX, contentY, leftW, 30, TRUE);
    MoveWindow(hLabelIdentity_, leftX, contentY + 40, leftW, 50, TRUE);
    MoveWindow(hLabelRNA_, leftX, contentY + 110, leftW, 40, TRUE);
    MoveWindow(hLabelDNA_, leftX, contentY + 160, leftW, 40, TRUE);

    // --- 中央列：操作 ---
    // 根据内容动态计算按钮大小
    int btnGap = 15;
    int btnH = 50; // 按钮高度

    // 对于不同场景，使用不同的按钮宽度
    int earlyGameBtnW = (centerW - (btnGap * 3)) / 4;  // 游戏早期4列布局
    int threeColBtnW = (centerW - (btnGap * 2)) / 3;    // 种群/政府3列布局
    int twoColBtnW = (centerW - btnGap) / 2;            // 居中成对按钮的2列布局
    int singleBtnW = centerW;                           // 单个按钮居中
    
    int gridY = 80; // 从更高位置开始
    int row2Y = gridY + btnH + btnGap;
    int row3Y = row2Y + btnH + btnGap;
    int row4Y = row3Y + btnH + btnGap;
    int row5Y = row4Y + btnH + btnGap;
    int row6Y = row5Y + btnH + btnGap;
    int row7Y = row6Y + btnH + btnGap;
    int row8Y = row7Y + btnH + btnGap;
    int row9Y = row8Y + btnH + btnGap;
    int row10Y = row9Y + btnH + btnGap;
    int row11Y = row10Y + btnH + btnGap;
    int row12Y = row11Y + btnH + btnGap;
    int row13Y = row12Y + btnH + btnGap;

    // 行.*资源.*结构 (4 columns for early game)
    // 游戏早期按钮宽度 is already declared above
    MoveWindow(hBtnRNA_, centerX, gridY, earlyGameBtnW, btnH, TRUE);
    MoveWindow(hBtnDNA_, centerX + earlyGameBtnW + btnGap, gridY, earlyGameBtnW, btnH, TRUE);
    MoveWindow(hBtnOrganelle_, centerX + (earlyGameBtnW + btnGap) * 2, gridY, earlyGameBtnW, btnH, TRUE);
    MoveWindow(hBtnMembrane_, centerX + (earlyGameBtnW + btnGap) * 3, gridY, earlyGameBtnW, btnH, TRUE);

    // 行：结构（4列）)
    MoveWindow(hBtnNucleus_, centerX, row2Y, earlyGameBtnW, btnH, TRUE);
    MoveWindow(hBtnMitochondria_, centerX + earlyGameBtnW + btnGap, row2Y, earlyGameBtnW, btnH, TRUE);
    MoveWindow(hBtnEukaryote_, centerX + (earlyGameBtnW + btnGap) * 2, row2Y, earlyGameBtnW, btnH, TRUE);
    // 第4个位置为空或留作将来使用

    // 行：繁殖（第4阶段）（2个按钮，完全居中）)
    int reproBtnW = (centerW - btnGap) / 2;
    int reproOffsetX = (centerW - (reproBtnW * 2 + btnGap)) / 2;
    MoveWindow(hBtnSexual_, centerX + reproOffsetX, row3Y, reproBtnW, btnH, TRUE);
    MoveWindow(hBtnAsexual_, centerX + reproOffsetX + reproBtnW + btnGap, row3Y, reproBtnW, btnH, TRUE);

    // 行：进化方向/步骤（响应式布局）)
    // 单个按钮（细胞吞噬）居中
    MoveWindow(hBtnPhagocytosis_, centerX, row4Y, singleBtnW, btnH, TRUE);
    // 对于无性繁殖：两个按钮居中
    MoveWindow(hBtnChloroplast_, centerX, row4Y, twoColBtnW, btnH, TRUE);
    MoveWindow(hBtnChitin_, centerX + twoColBtnW + btnGap, row4Y, twoColBtnW, btnH, TRUE);

    // 行：多细胞和双侧对称（居中，2列）)
    MoveWindow(hBtnMulticellular_, centerX + twoColBtnW/2, row5Y, twoColBtnW, btnH, TRUE);
    MoveWindow(hBtnBilateral_, centerX + twoColBtnW * 1.5 + btnGap, row5Y, twoColBtnW, btnH, TRUE);

    // 行：感知按钮（居中，全宽）)
    MoveWindow(hBtnSentience_, centerX, row6Y, singleBtnW, btnH, TRUE);

    // 行：种群选择（3列，响应式布局）)
    // 对于有性繁殖路径：9个种群按钮以3x3网格排列
    int speciesStartRow = row7Y;
    // 按钮已通过使用threeColBtnW宽度居中

    // 种族的行（3个按钮）)
    MoveWindow(hBtnBeast_, centerX, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnEggLayer_, centerX + threeColBtnW + btnGap, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnReptile_, centerX + (threeColBtnW + btnGap) * 2, speciesStartRow, threeColBtnW, btnH, TRUE);

    // 种族的行（3个按钮）)
    speciesStartRow += btnH + btnGap;
    MoveWindow(hBtnFae_, centerX, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnDesert_, centerX + threeColBtnW + btnGap, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnFlame_, centerX + (threeColBtnW + btnGap) * 2, speciesStartRow, threeColBtnW, btnH, TRUE);

    // 种族的行（3个按钮）)
    speciesStartRow += btnH + btnGap;
    MoveWindow(hBtnPolar_, centerX, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnArthropod_, centerX + threeColBtnW + btnGap, speciesStartRow, threeColBtnW, btnH, TRUE);
    MoveWindow(hBtnAberration_, centerX + (threeColBtnW + btnGap) * 2, speciesStartRow, threeColBtnW, btnH, TRUE);

    // 对于无性繁殖：使两个按钮居中（已在上方定位）)
    // MoveWindow(hBtnChloroplast_, centerX, row4Y, twoColBtnW, btnH, TRUE);
    // MoveWindow(hBtnChitin_, centerX + twoColBtnW + btnGap, row4Y, twoColBtnW, btnH, TRUE);

    // 行：文明开始（2个按钮，完全居中）- 移至感知按钮下方
    int civBtnW = (centerW - btnGap) / 2;
    int civOffsetX = (centerW - (civBtnW * 2 + btnGap)) / 2;
    MoveWindow(hBtnGovernment_, centerX + civOffsetX, row7Y, civBtnW, btnH, TRUE);
    MoveWindow(hBtnAnarchy_, centerX + civOffsetX + civBtnW + btnGap, row7Y, civBtnW, btnH, TRUE);

    // 行：政府类型（红框区域中的3-4-4布局）)
    // 使用现有的行变量（已在上方定义）)

    // 计算每行按钮的宽度
    int threeBtnW = (centerW - (btnGap * 2)) / 3;
    int fourBtnW = (centerW - (btnGap * 3)) / 4;

    // 行：政府类型 (aligned with Government/Anarchy above)
    int row1OffsetX = (centerW - (threeBtnW * 3 + btnGap * 2)) / 2;
    MoveWindow(hBtnAutocracy_, centerX + row1OffsetX, row8Y, threeBtnW, btnH, TRUE);
    MoveWindow(hBtnDemocracy_, centerX + row1OffsetX + threeBtnW + btnGap, row8Y, threeBtnW, btnH, TRUE);
    MoveWindow(hBtnOligarchy_, centerX + row1OffsetX + (threeBtnW + btnGap) * 2, row8Y, threeBtnW, btnH, TRUE);

    // 行：政府类型
    int row2OffsetX = (centerW - (fourBtnW * 4 + btnGap * 3)) / 2;
    MoveWindow(hBtnTheocracy_, centerX + row2OffsetX, row9Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnRepublic_, centerX + row2OffsetX + fourBtnW + btnGap, row9Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnSocialism_, centerX + row2OffsetX + (fourBtnW + btnGap) * 2, row9Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnCorpBureaucracy_, centerX + row2OffsetX + (fourBtnW + btnGap) * 3, row9Y, fourBtnW, btnH, TRUE);

    // 行：政府类型
    int row3OffsetX = (centerW - (fourBtnW * 4 + btnGap * 3)) / 2;
    MoveWindow(hBtnTechBureaucracy_, centerX + row3OffsetX, row10Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnFederalism_, centerX + row3OffsetX + fourBtnW + btnGap, row10Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnMagocracy_, centerX + row3OffsetX + (fourBtnW + btnGap) * 2, row10Y, fourBtnW, btnH, TRUE);
    MoveWindow(hBtnDictatorship_, centerX + row3OffsetX + (fourBtnW + btnGap) * 3, row10Y, fourBtnW, btnH, TRUE);


    // --- 右列：菜单 ---
    int menuH = 50;
    int menuGap = 20;

    MoveWindow(hBtnLog_, rightX, contentY, rightW, menuH, TRUE);
    MoveWindow(hBtnProgress_, rightX, contentY + menuH + menuGap, rightW, menuH, TRUE);
    // MoveWindow(hBtnEvents_, rightX, contentY + (menuH + menuGap) * 2, rightW, menuH, TRUE);
    MoveWindow(hBtnSettings_, rightX, contentY + (menuH + menuGap) * 2, rightW, menuH, TRUE);
    // 日志视图位于设置下方
    int logY = contentY + (menuH + menuGap) * 3;
    int logH = height - logY - padding;  // 使用窗口高度而不是未定义的panelH
    if (logH < 120) logH = 120;
    MoveWindow(hLogView_, rightX, logY, rightW, logH, TRUE);

    // 重绘窗口以更新背景面板
    InvalidateRect(hwnd_, nullptr, TRUE);
}

void Window::CheckUnlocks() {
    // 细胞器解锁：DNA >= 4
    if (!isOrganelleUnlocked_ && dnaCount_ >= 4) {
        isOrganelleUnlocked_ = true;
        AddEvent(L"Unlocked: Organelle (Requires DNA >= 4)");
    }
    
    // 细胞膜解锁：细胞器 >= 1
    if (!isMembraneUnlocked_ && organelleCount_ >= 1) {
        isMembraneUnlocked_ = true;
        AddEvent(L"Unlocked: Membrane (Requires Organelle >= 1)");
    }

    // 细胞核解锁：细胞膜 >= 2 且 细胞器 >= 2
    if (!isNucleusUnlocked_ && membraneCount_ >= 2 && organelleCount_ >= 2) {
        isNucleusUnlocked_ = true;
        AddEvent(L"Unlocked: Nucleus (Requires Membrane >= 2, Organelle >= 2)");
    }

    // 线粒体解锁：细胞核 >= 1
    if (!isMitochondriaUnlocked_ && nucleusCount_ >= 1) {
        isMitochondriaUnlocked_ = true;
        AddEvent(L"Unlocked: Mitochondria (Requires Nucleus >= 1)");
    }

    // 真核细胞解锁：细胞核 >= 1
    if (!isEukaryoteUnlocked_ && nucleusCount_ >= 1) {
        isEukaryoteUnlocked_ = true;
        AddEvent(L"Unlocked: Eukaryote (Requires Nucleus >= 1)");
    }

    // 繁殖解锁：真核细胞 >= 1
    if (!isReproductionUnlocked_ && eukaryoteCount_ >= 1) {
        isReproductionUnlocked_ = true;
        AddEvent(L"Unlocked: Reproduction (Requires Eukaryote >= 1)");
    }
}

void Window::UpdateUIDisplay() {
    CheckUnlocks();

    wchar_t buffer[256];

    // 更新进度按钮以显示当前阶段
    std::wstring progressText = L"进度: " + GetProgressDescription();
    SetWindowTextW(hBtnProgress_, progressText.c_str());

    // 更新RNA
    swprintf(buffer, 256, L"RNA: %d / %d (+%d/s)", rnaCount_, rnaMax_, rnaRate_);
    SetWindowTextW(hLabelRNA_, buffer);

    // 更新DNA
    if (isDnaUnlocked_) {
        ShowWindow(hLabelDNA_, SW_SHOW);
        ShowWindow(hBtnDNA_, SW_SHOW);
        
        swprintf(buffer, 256, L"DNA: %d / %d (+%d/s)", dnaCount_, dnaMax_, dnaRate_);
        SetWindowTextW(hLabelDNA_, buffer);

        // 检查DNA按钮是否应该启用（RNA >= 2）
        // bool canCreateDNA = (rnaCount_ >= 2) && (dnaCount_ < dnaMax_);
        EnableWindow(hBtnDNA_, TRUE); // 始终启用以便显示提示/红色文本
    } else {
        ShowWindow(hLabelDNA_, SW_HIDE);
        ShowWindow(hBtnDNA_, SW_HIDE);
    }

    // --- 按钮可见性状态机 ---

    // 1. 繁殖前期阶段
    if (!hasChosenReproduction_) {
        // 如果已解锁则显示结构按钮
        ShowWindow(hBtnRNA_, SW_SHOW);
        // DNA handled above
        ShowWindow(hBtnOrganelle_, isOrganelleUnlocked_ ? SW_SHOW : SW_HIDE);
        ShowWindow(hBtnMembrane_, isMembraneUnlocked_ ? SW_SHOW : SW_HIDE);
        ShowWindow(hBtnNucleus_, isNucleusUnlocked_ ? SW_SHOW : SW_HIDE);
        ShowWindow(hBtnMitochondria_, isMitochondriaUnlocked_ ? SW_SHOW : SW_HIDE);
        ShowWindow(hBtnEukaryote_, isEukaryoteUnlocked_ ? SW_SHOW : SW_HIDE);
        
        ShowWindow(hBtnSexual_, isReproductionUnlocked_ ? SW_SHOW : SW_HIDE);
        ShowWindow(hBtnAsexual_, isReproductionUnlocked_ ? SW_SHOW : SW_HIDE);

        // 隐藏未来的状态
        ShowWindow(hBtnPhagocytosis_, SW_HIDE);
        ShowWindow(hBtnChloroplast_, SW_HIDE);
        ShowWindow(hBtnChitin_, SW_HIDE);
        ShowWindow(hBtnSentience_, SW_HIDE);
        
        // 隐藏种群
        ShowWindow(hBtnDemon_, SW_HIDE);
        ShowWindow(hBtnBalrog_, SW_HIDE);
        ShowWindow(hBtnHeaven_, SW_HIDE);
        ShowWindow(hBtnHumanoid_, SW_HIDE);
        ShowWindow(hBtnDwarf_, SW_HIDE);
        ShowWindow(hBtnGiant_, SW_HIDE);
        ShowWindow(hBtnBeast_, SW_HIDE);
        ShowWindow(hBtnEggLayer_, SW_HIDE);
        ShowWindow(hBtnReptile_, SW_HIDE);
        ShowWindow(hBtnAquatic_, SW_HIDE);
        ShowWindow(hBtnFae_, SW_HIDE);
        ShowWindow(hBtnDesert_, SW_HIDE);
        ShowWindow(hBtnFlame_, SW_HIDE);
        ShowWindow(hBtnPolar_, SW_HIDE);
        ShowWindow(hBtnArthropod_, SW_HIDE);
        ShowWindow(hBtnAberration_, SW_HIDE);

        // 隐藏文明
        ShowWindow(hBtnGovernment_, SW_HIDE);
        ShowWindow(hBtnAnarchy_, SW_HIDE);
        ShowWindow(hBtnAutocracy_, SW_HIDE);
        ShowWindow(hBtnDemocracy_, SW_HIDE);
        ShowWindow(hBtnOligarchy_, SW_HIDE);
        ShowWindow(hBtnTheocracy_, SW_HIDE);
        ShowWindow(hBtnRepublic_, SW_HIDE);
        ShowWindow(hBtnSocialism_, SW_HIDE);
        ShowWindow(hBtnCorpBureaucracy_, SW_HIDE);
        ShowWindow(hBtnTechBureaucracy_, SW_HIDE);
        ShowWindow(hBtnFederalism_, SW_HIDE);
        ShowWindow(hBtnMagocracy_, SW_HIDE);
        ShowWindow(hBtnDictatorship_, SW_HIDE);

        // 更新文本
        if (isOrganelleUnlocked_) {
            swprintf(buffer, 256, L"\u7EC6\u80DE\u5668: %d\n(-12 RNA, -4 DNA)", organelleCount_);
            SetWindowTextW(hBtnOrganelle_, buffer);
            EnableWindow(hBtnOrganelle_, TRUE);
        }
        if (isMembraneUnlocked_) {
            swprintf(buffer, 256, L"\u7EC6\u80DE\u819C: %d\n(-4 RNA)", membraneCount_);
            SetWindowTextW(hBtnMembrane_, buffer);
            EnableWindow(hBtnMembrane_, TRUE);
        }
        if (isNucleusUnlocked_) {
            swprintf(buffer, 256, L"\u7EC6\u80DE\u6838: %d\n(-38 RNA, -18 DNA)", nucleusCount_);
            SetWindowTextW(hBtnNucleus_, buffer);
            EnableWindow(hBtnNucleus_, TRUE);
        }
        if (isMitochondriaUnlocked_) {
            swprintf(buffer, 256, L"\u7EBF\u7C92\u4F53: %d\n(-125 RNA, -100 DNA)", mitochondriaCount_);
            SetWindowTextW(hBtnMitochondria_, buffer);
            EnableWindow(hBtnMitochondria_, TRUE);
        }
        if (isEukaryoteUnlocked_) {
            swprintf(buffer, 256, L"\u771F\u6838\u7EC6\u80DE: %d\n(-40 RNA, -52 DNA)", eukaryoteCount_);
            SetWindowTextW(hBtnEukaryote_, buffer);
            EnableWindow(hBtnEukaryote_, TRUE);
        }
        if (isReproductionUnlocked_) {
            EnableWindow(hBtnSexual_, TRUE);
            EnableWindow(hBtnAsexual_, TRUE);
        }
    }
    // 2. Reproduction Chosen (Evolution Choice Phase)
    else if (!hasChosenEvolution_) {
        // 隐藏过去的状态
        ShowWindow(hBtnRNA_, SW_HIDE);
        ShowWindow(hBtnDNA_, SW_HIDE);
        ShowWindow(hBtnOrganelle_, SW_HIDE);
        ShowWindow(hBtnMembrane_, SW_HIDE);
        ShowWindow(hBtnNucleus_, SW_HIDE);
        ShowWindow(hBtnMitochondria_, SW_HIDE);
        ShowWindow(hBtnEukaryote_, SW_HIDE);
        ShowWindow(hBtnSexual_, SW_HIDE);
        ShowWindow(hBtnAsexual_, SW_HIDE);

        // 显示当前状态（方向按钮）
        if (isSexual_) {
            // 有性繁殖首先显示细胞吞噬
            ShowWindow(hBtnPhagocytosis_, SW_SHOW);
            ShowWindow(hBtnChloroplast_, SW_HIDE);
            ShowWindow(hBtnChitin_, SW_HIDE);
            EnableWindow(hBtnPhagocytosis_, TRUE);
        } else {
            // 无性繁殖直接显示叶绿体和几丁质
            ShowWindow(hBtnPhagocytosis_, SW_HIDE);
            ShowWindow(hBtnChloroplast_, SW_SHOW);
            ShowWindow(hBtnChitin_, SW_SHOW);
            EnableWindow(hBtnChloroplast_, TRUE);
            EnableWindow(hBtnChitin_, TRUE);
        }

        // 隐藏未来的状态
        ShowWindow(hBtnMulticellular_, SW_HIDE);
        ShowWindow(hBtnBilateral_, SW_HIDE);
        ShowWindow(hBtnSentience_, SW_HIDE);
        // ...
    }
    // 3. 已选择进化方向（感知阶段）
    else if (evolutionProgress_ == 2) {
        // 隐藏过去的状态
        ShowWindow(hBtnPhagocytosis_, SW_HIDE);
        ShowWindow(hBtnChloroplast_, SW_HIDE);
        ShowWindow(hBtnChitin_, SW_HIDE);
        // 在感知阶段隐藏DNA按钮
        ShowWindow(hBtnDNA_, SW_HIDE);

        // 显示当前状态
        ShowWindow(hBtnSentience_, SW_SHOW);
        EnableWindow(hBtnSentience_, TRUE);

        // 隐藏未来的状态
        if (isSexual_) {
            // 为有性繁殖路径隐藏种群
            ShowWindow(hBtnBeast_, SW_HIDE);
            ShowWindow(hBtnEggLayer_, SW_HIDE);
            ShowWindow(hBtnReptile_, SW_HIDE);
            ShowWindow(hBtnFae_, SW_HIDE);
            ShowWindow(hBtnDesert_, SW_HIDE);
            ShowWindow(hBtnFlame_, SW_HIDE);
            ShowWindow(hBtnPolar_, SW_HIDE);
            ShowWindow(hBtnArthropod_, SW_HIDE);
            ShowWindow(hBtnAberration_, SW_HIDE);
        } else {
            // 为无性繁殖路径隐藏叶绿体和几丁质
            ShowWindow(hBtnChloroplast_, SW_HIDE);
            ShowWindow(hBtnChitin_, SW_HIDE);
        }
    }
    // 4. 已选择感知 - 根据繁殖路径显示不同选项
    else if (evolutionProgress_ == 5) {
        // 隐藏过去的状态
        ShowWindow(hBtnSentience_, SW_HIDE);

        // 隐藏所有不属于可用选项的种群选择按钮
        ShowWindow(hBtnDemon_, SW_HIDE);
        ShowWindow(hBtnBalrog_, SW_HIDE);
        ShowWindow(hBtnHeaven_, SW_HIDE);
        ShowWindow(hBtnHumanoid_, SW_HIDE);
        ShowWindow(hBtnDwarf_, SW_HIDE);
        ShowWindow(hBtnGiant_, SW_HIDE);

        if (isSexual_) {
            // 为有性繁殖显示种群按钮
            ShowWindow(hBtnBeast_, SW_SHOW);
            ShowWindow(hBtnEggLayer_, SW_SHOW);
            ShowWindow(hBtnReptile_, SW_SHOW);
            ShowWindow(hBtnFae_, SW_SHOW);
            ShowWindow(hBtnDesert_, SW_SHOW);
            ShowWindow(hBtnFlame_, SW_SHOW);
            ShowWindow(hBtnPolar_, SW_SHOW);
            ShowWindow(hBtnArthropod_, SW_SHOW);
            ShowWindow(hBtnAberration_, SW_SHOW);

            EnableWindow(hBtnBeast_, TRUE);
            EnableWindow(hBtnEggLayer_, TRUE);
            EnableWindow(hBtnReptile_, TRUE);
            EnableWindow(hBtnFae_, TRUE);
            EnableWindow(hBtnDesert_, TRUE);
            EnableWindow(hBtnFlame_, TRUE);
            EnableWindow(hBtnPolar_, TRUE);
            EnableWindow(hBtnArthropod_, TRUE);
            EnableWindow(hBtnAberration_, TRUE);

            // 隐藏植物/真菌选项
            ShowWindow(hBtnChloroplast_, SW_HIDE);
            ShowWindow(hBtnChitin_, SW_HIDE);
        } else {
            // 为无性繁殖显示叶绿体和几丁质
            ShowWindow(hBtnChloroplast_, SW_SHOW);
            ShowWindow(hBtnChitin_, SW_SHOW);
            EnableWindow(hBtnChloroplast_, TRUE);
            EnableWindow(hBtnChitin_, TRUE);

            // 隐藏动物选项
            ShowWindow(hBtnBeast_, SW_HIDE);
            ShowWindow(hBtnEggLayer_, SW_HIDE);
            ShowWindow(hBtnReptile_, SW_HIDE);
            ShowWindow(hBtnFae_, SW_HIDE);
            ShowWindow(hBtnDesert_, SW_HIDE);
            ShowWindow(hBtnFlame_, SW_HIDE);
            ShowWindow(hBtnPolar_, SW_HIDE);
            ShowWindow(hBtnArthropod_, SW_HIDE);
            ShowWindow(hBtnAberration_, SW_HIDE);
        }
    }
    // 7. 文明开始阶段（已达成感知）
    else if (isCivilizationUnlocked_ && !isGovSelectionUnlocked_ && !isGameEnded_) {
        // 隐藏过去的状态
        ShowWindow(hBtnSentience_, SW_HIDE);

        // 隐藏过去的状态 (All Species)
        ShowWindow(hBtnBeast_, SW_HIDE);
        ShowWindow(hBtnEggLayer_, SW_HIDE);
        ShowWindow(hBtnReptile_, SW_HIDE);
        ShowWindow(hBtnFae_, SW_HIDE);
        ShowWindow(hBtnDesert_, SW_HIDE);
        ShowWindow(hBtnFlame_, SW_HIDE);
        ShowWindow(hBtnPolar_, SW_HIDE);
        ShowWindow(hBtnArthropod_, SW_HIDE);
        ShowWindow(hBtnAberration_, SW_HIDE);
        ShowWindow(hBtnDemon_, SW_HIDE);
        ShowWindow(hBtnBalrog_, SW_HIDE);
        ShowWindow(hBtnHeaven_, SW_HIDE);
        ShowWindow(hBtnHumanoid_, SW_HIDE);
        ShowWindow(hBtnDwarf_, SW_HIDE);
        ShowWindow(hBtnGiant_, SW_HIDE);
        ShowWindow(hBtnAquatic_, SW_HIDE);
        ShowWindow(hBtnChloroplast_, SW_HIDE);
        ShowWindow(hBtnChitin_, SW_HIDE);

        // 显示当前状态
        ShowWindow(hBtnGovernment_, SW_SHOW);
        ShowWindow(hBtnAnarchy_, SW_SHOW);
        EnableWindow(hBtnGovernment_, TRUE);
        EnableWindow(hBtnAnarchy_, TRUE);

        // 隐藏未来的状态
        ShowWindow(hBtnAutocracy_, SW_HIDE);
        ShowWindow(hBtnDemocracy_, SW_HIDE);
        ShowWindow(hBtnOligarchy_, SW_HIDE);
        ShowWindow(hBtnTheocracy_, SW_HIDE);
        ShowWindow(hBtnRepublic_, SW_HIDE);
        ShowWindow(hBtnSocialism_, SW_HIDE);
        ShowWindow(hBtnCorpBureaucracy_, SW_HIDE);
        ShowWindow(hBtnTechBureaucracy_, SW_HIDE);
        ShowWindow(hBtnFederalism_, SW_HIDE);
        ShowWindow(hBtnMagocracy_, SW_HIDE);
        ShowWindow(hBtnDictatorship_, SW_HIDE);
    }
    // 6. 政府选择阶段
    else if (isGovSelectionUnlocked_ && !isGameEnded_) {
        // 隐藏过去的状态
        ShowWindow(hBtnGovernment_, SW_HIDE);
        ShowWindow(hBtnAnarchy_, SW_HIDE);

        // 显示当前状态
        ShowWindow(hBtnAutocracy_, SW_SHOW);
        ShowWindow(hBtnDemocracy_, SW_SHOW);
        ShowWindow(hBtnOligarchy_, SW_SHOW);
        ShowWindow(hBtnTheocracy_, SW_SHOW);
        ShowWindow(hBtnRepublic_, SW_SHOW);
        ShowWindow(hBtnSocialism_, SW_SHOW);
        ShowWindow(hBtnCorpBureaucracy_, SW_SHOW);
        ShowWindow(hBtnTechBureaucracy_, SW_SHOW);
        ShowWindow(hBtnFederalism_, SW_SHOW);
        ShowWindow(hBtnMagocracy_, SW_SHOW);
        ShowWindow(hBtnDictatorship_, SW_SHOW);

        EnableWindow(hBtnAutocracy_, TRUE);
        EnableWindow(hBtnDemocracy_, TRUE);
        EnableWindow(hBtnOligarchy_, TRUE);
        EnableWindow(hBtnTheocracy_, TRUE);
        EnableWindow(hBtnRepublic_, TRUE);
        EnableWindow(hBtnSocialism_, TRUE);
        EnableWindow(hBtnCorpBureaucracy_, TRUE);
        EnableWindow(hBtnTechBureaucracy_, TRUE);
        EnableWindow(hBtnFederalism_, TRUE);
        EnableWindow(hBtnMagocracy_, TRUE);
        EnableWindow(hBtnDictatorship_, TRUE);
    }
    // 7. 游戏结束
    else if (isGameEnded_) {
        // 隐藏所有内容
        ShowWindow(hBtnGovernment_, SW_HIDE);
        ShowWindow(hBtnAnarchy_, SW_HIDE);
        ShowWindow(hBtnAutocracy_, SW_HIDE);
        ShowWindow(hBtnDemocracy_, SW_HIDE);
        ShowWindow(hBtnOligarchy_, SW_HIDE);
        ShowWindow(hBtnTheocracy_, SW_HIDE);
        ShowWindow(hBtnRepublic_, SW_HIDE);
        ShowWindow(hBtnSocialism_, SW_HIDE);
        ShowWindow(hBtnCorpBureaucracy_, SW_HIDE);
        ShowWindow(hBtnTechBureaucracy_, SW_HIDE);
        ShowWindow(hBtnFederalism_, SW_HIDE);
        ShowWindow(hBtnMagocracy_, SW_HIDE);
        ShowWindow(hBtnDictatorship_, SW_HIDE);

        // 隐藏所有进化按钮
        ShowWindow(hBtnRNA_, SW_HIDE);
        ShowWindow(hBtnDNA_, SW_HIDE);
        ShowWindow(hBtnOrganelle_, SW_HIDE);
        ShowWindow(hBtnMembrane_, SW_HIDE);
        ShowWindow(hBtnNucleus_, SW_HIDE);
        ShowWindow(hBtnMitochondria_, SW_HIDE);
        ShowWindow(hBtnEukaryote_, SW_HIDE);
        ShowWindow(hBtnSexual_, SW_HIDE);
        ShowWindow(hBtnAsexual_, SW_HIDE);
        ShowWindow(hBtnPhagocytosis_, SW_HIDE);
        ShowWindow(hBtnChloroplast_, SW_HIDE);
        ShowWindow(hBtnChitin_, SW_HIDE);
        ShowWindow(hBtnSentience_, SW_HIDE);
        ShowWindow(hBtnMulticellular_, SW_HIDE);
        ShowWindow(hBtnBilateral_, SW_HIDE);

        // 隐藏所有种群按钮
        ShowWindow(hBtnDemon_, SW_HIDE);
        ShowWindow(hBtnBalrog_, SW_HIDE);
        ShowWindow(hBtnHeaven_, SW_HIDE);
        ShowWindow(hBtnHumanoid_, SW_HIDE);
        ShowWindow(hBtnDwarf_, SW_HIDE);
        ShowWindow(hBtnGiant_, SW_HIDE);
        ShowWindow(hBtnBeast_, SW_HIDE);
        ShowWindow(hBtnEggLayer_, SW_HIDE);
        ShowWindow(hBtnReptile_, SW_HIDE);
        ShowWindow(hBtnAquatic_, SW_HIDE);
        ShowWindow(hBtnFae_, SW_HIDE);
        ShowWindow(hBtnDesert_, SW_HIDE);
        ShowWindow(hBtnFlame_, SW_HIDE);
        ShowWindow(hBtnPolar_, SW_HIDE);
        ShowWindow(hBtnArthropod_, SW_HIDE);
        ShowWindow(hBtnAberration_, SW_HIDE);

        // 保持菜单按钮可见
        // 注意：游戏结束时菜单按钮也应该保持可见

        // 更新标签以显示游戏结束信息
        SetWindowTextW(hLabelIdentity_, L"");
        SetWindowTextW(hLabelRNA_, L"");
        SetWindowTextW(hLabelDNA_, L"");
        SetWindowTextW(hLabelVersion_, L"");

        // 强制重绘窗口以显示干净的游戏结束画面
        InvalidateRect(hwnd_, nullptr, TRUE);
        UpdateWindow(hwnd_);
    }
}

void Window::ProcessPassiveGeneration() {
    // 1. 计算速率
    int rnaGen = 0;
    int rnaCon = 0;
    int dnaGen = 0;
    
    // Organelle: +1 RNA/s
    rnaGen += organelleCount_ * 1;

    // Nucleus: -2 RNA -> +1 DNA/s
    int nucleusActive = 0;
    if (dnaCount_ < dnaMax_) {
        int maxPossibleByRNA = rnaCount_ / 2;
        nucleusActive = (nucleusCount_ < maxPossibleByRNA) ? nucleusCount_ : maxPossibleByRNA;
    }

    // 应用细胞器生成
    rnaCount_ += rnaGen;
    if (rnaCount_ > rnaMax_) rnaCount_ = rnaMax_;

    // Apply Nucleus Generation (Consume RNA, Produce DNA)
    if (dnaCount_ < dnaMax_) {
        int rnaNeeded = nucleusCount_ * 2;
        int actualNucleusWorking = nucleusCount_;

        if (rnaCount_ < rnaNeeded) {
            actualNucleusWorking = rnaCount_ / 2;
        }

        rnaCount_ -= actualNucleusWorking * 2;
        dnaCount_ += actualNucleusWorking * 1;
        
        if (dnaCount_ > dnaMax_) dnaCount_ = dnaMax_;
    }

    // Update Display Rates for UI (Approximation)
    rnaRate_ = rnaGen;
    if (dnaCount_ < dnaMax_) {
        rnaRate_ -= (nucleusCount_ * 2); // 显示理论消耗
        dnaRate_ = nucleusCount_ * 1;
    } else {
        dnaRate_ = 0;
    }

    UpdateUIDisplay();
}

LRESULT Window::HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
    case WM_CREATE:
        hwnd_ = hwnd;
        CreateControls();
        return 0;

    case WM_TIMER:
        if (wParam == ID_TIMER_PASSIVE) {
            ProcessPassiveGeneration();
        }
        return 0;

    case WM_SIZE: {
        int width = LOWORD(lParam);
        int height = HIWORD(lParam);
        DEBUG_ASSERT(width >= 0 && "WM_SIZE - invalid width");
        DEBUG_ASSERT(height >= 0 && "WM_SIZE - invalid height");
        ResizeControls(width, height);
        return 0;
    }

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        // 1. 全局背景（深灰色）
        RECT clientRect;
        GetClientRect(hwnd, &clientRect);
        HBRUSH bgBrush = CreateSolidBrush(RGB(30, 30, 32));
        FillRect(hdc, &clientRect, bgBrush);
        DeleteObject(bgBrush);

        // 2. 面板绘制（分区）- 基于客户区大小动态调整
        int width = clientRect.right - clientRect.left;
        int height = clientRect.bottom - clientRect.top;
        
        // 使用与ResizeControls相同的计算以保持一致性
        int padding = 10;
        int leftW = (int)(width * 0.20) - (padding * 2);
        int rightW = (int)(width * 0.20) - (padding * 2);
        int centerW = width - leftW - rightW - (padding * 6);
        
        int leftX = padding;
        int centerX = leftX + leftW + (padding * 2);
        int rightX = centerX + centerW + (padding * 2);

        // 绘制面板的辅助lambda函数
        auto DrawPanel = [&](int x, int y, int w, int h) {
            RECT panelRect = { x, y, x + w, y + h };
            HBRUSH panelBrush = CreateSolidBrush(RGB(40, 40, 42));
            FillRect(hdc, &panelRect, panelBrush);
            DeleteObject(panelBrush);
            
            HBRUSH borderBrush = CreateSolidBrush(RGB(60, 60, 65));
            FrameRect(hdc, &panelRect, borderBrush);
            DeleteObject(borderBrush);
        };

        // 绘制面板
        int panelH = height - (padding * 2);
        DrawPanel(leftX, padding, leftW, panelH);
        DrawPanel(centerX, padding, centerW, panelH);
        DrawPanel(rightX, padding, rightW, panelH);

        // 3. 进化进度条（底部）
        if (evolutionProgress_ > 0 && evolutionProgress_ < 6) {
            int barH = 20;
            int barY = height - barH - padding;
            int barTotalW = centerW; // 使用中央列宽度
            int barX = centerX;

            // 绘制背景轨道
            RECT trackRect = { barX, barY, barX + barTotalW, barY + barH };
            HBRUSH trackBrush = CreateSolidBrush(RGB(20, 20, 20));
            FillRect(hdc, &trackRect, trackBrush);
            DeleteObject(trackBrush);
            
            // 绘制段
            int segments = 5; // Total steps before Civ
            int segW = barTotalW / segments;
            
            for (int i = 0; i < evolutionProgress_; i++) {
                RECT segRect = { barX + (i * segW), barY, barX + ((i + 1) * segW) - 2, barY + barH }; // -2 for gap
                HBRUSH segBrush = CreateSolidBrush(RGB(0, 191, 255)); // Deep Sky Blue
                FillRect(hdc, &segRect, segBrush);
                DeleteObject(segBrush);
            }

            // Draw Border
            HBRUSH borderBrush = CreateSolidBrush(RGB(100, 100, 100));
            FrameRect(hdc, &trackRect, borderBrush);
            DeleteObject(borderBrush);
            
            // Draw Label
            wchar_t progText[64];
            swprintf(progText, 64, L"Evolution Progress: Stage %d / 5", evolutionProgress_);
            SetTextColor(hdc, RGB(200, 200, 200));
            SetBkMode(hdc, TRANSPARENT);
            RECT textRect = { barX, barY - 20, barX + barTotalW, barY };
            DrawTextW(hdc, progText, -1, &textRect, DT_CENTER | DT_BOTTOM | DT_SINGLELINE);
        }

        // Draw game over message in center area if game has ended
        if (isGameEnded_) {
            const wchar_t* gameOverText = L"文明的齿轮正在缓慢转动，游戏结束";

            // Calculate center area (excluding right menu)
            int padding = 10;
            int leftW = (int)(width * 0.20) - (padding * 2);
            int rightW = (int)(width * 0.20) - (padding * 2);
            int centerW = width - leftW - rightW - (padding * 6);
            int leftX = padding;
            int centerX = leftX + leftW + (padding * 2);

            // Calculate font size based on window size (1/10 of center area width)
            int fontSize = (centerW / 10 < 20) ? 20 : ((centerW / 10 > 80) ? 80 : centerW / 10);

            // Create gradient colors for rainbow effect
            COLORREF colors[] = {
                RGB(255, 0, 0),     // Red
                RGB(255, 127, 0),   // Orange
                RGB(255, 255, 0),   // Yellow
                RGB(0, 255, 0),     // Green
                RGB(0, 0, 255),     // Blue
                RGB(75, 0, 130),    // Indigo
                RGB(148, 0, 211)    // Violet
            };
            int colorCount = sizeof(colors) / sizeof(colors[0]);

            // Create font for game over text
            LOGFONTW lf = {0};
            lf.lfHeight = -fontSize;  // Dynamic font size
            lf.lfWeight = FW_BOLD;
            lf.lfCharSet = DEFAULT_CHARSET;
            wcscpy_s(lf.lfFaceName, L"微软雅黑");
            HFONT hGameOverFont = CreateFontIndirectW(&lf);

            if (hGameOverFont) {
                HFONT hOldFont = (HFONT)SelectObject(hdc, hGameOverFont);

                // Set text background to transparent
                SetBkMode(hdc, TRANSPARENT);

                // Calculate text rectangle in center area
                RECT textRect;
                textRect.left = centerX;
                textRect.right = centerX + centerW;
                textRect.top = padding;
                textRect.bottom = height - padding;

                // Draw text with gradient color effect
                // Split text into two lines for better display
                std::wstring line1 = L"文明的齿轮正在缓慢转动";
                std::wstring line2 = L"游戏结束";

                // Calculate vertical position for two lines
                int lineHeight = fontSize * 1.5;
                int totalHeight = lineHeight * 2;
                int startY = textRect.top + (textRect.bottom - textRect.top - totalHeight) / 2;

                // Draw first line with gradient colors
                int x = textRect.left;
                int y = startY;
                for (size_t i = 0; i < line1.length(); i++) {
                    wchar_t charStr[2] = {line1[i], 0};

                    // Use different color for each character
                    SetTextColor(hdc, colors[i % colorCount]);

                    // Check if we need to wrap to next line
                    SIZE charSize;
                    GetTextExtentPoint32W(hdc, charStr, 1, &charSize);
                    if (x + charSize.cx > textRect.right && i > 0) {
                        x = textRect.left;
                        y += lineHeight;
                    }

                    RECT charRect = {x, y, textRect.right, y + lineHeight};
                    DrawTextW(hdc, charStr, 1, &charRect, DT_LEFT | DT_TOP);

                    x += charSize.cx;
                }

                // Draw second line centered
                y = startY + lineHeight;
                int line2Width = 0;
                SIZE totalSize = {0};
                GetTextExtentPoint32W(hdc, line2.c_str(), line2.length(), &totalSize);
                line2Width = totalSize.cx;
                x = textRect.left + (textRect.right - textRect.left - line2Width) / 2;

                for (size_t i = 0; i < line2.length(); i++) {
                    wchar_t charStr[2] = {line2[i], 0};

                    // Use different color for each character
                    SetTextColor(hdc, colors[(i + line1.length()) % colorCount]);

                    RECT charRect = {x, y, textRect.right, y + lineHeight};
                    DrawTextW(hdc, charStr, 1, &charRect, DT_LEFT | DT_TOP);

                    SIZE charSize;
                    GetTextExtentPoint32W(hdc, charStr, 1, &charSize);
                    x += charSize.cx;
                }

                SelectObject(hdc, hOldFont);
                DeleteObject(hGameOverFont);
            }
        }

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_CTLCOLORLISTBOX: {
        HDC hdcList = (HDC)wParam;
        SetTextColor(hdcList, RGB(200, 200, 200));
        SetBkColor(hdcList, RGB(40, 40, 42));
        SetBkMode(hdcList, OPAQUE);
        static HBRUSH hListBgBrush = CreateSolidBrush(RGB(40, 40, 42));
        return (LRESULT)hListBgBrush;
    }

    case WM_DRAWITEM: {
        LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
        HDC hdc = pDIS->hDC;
        RECT rc = pDIS->rcItem;

        // --- BUTTONS ---
        if (pDIS->CtlType == ODT_BUTTON) {
            bool isPressed = (pDIS->itemState & ODS_SELECTED);
            bool isDisabled = (pDIS->itemState & ODS_DISABLED);

            // Check Affordability logic (Manual check to style enabled buttons as disabled)
            bool affordable = true;
            int id = pDIS->CtlID;
            if (id == ID_BTN_DNA) affordable = (rnaCount_ >= 2);
            else if (id == ID_BTN_ORGANELLE) affordable = (rnaCount_ >= 12 && dnaCount_ >= 4);
            else if (id == ID_BTN_MEMBRANE) affordable = (rnaCount_ >= 4);
            else if (id == ID_BTN_NUCLEUS) affordable = (rnaCount_ >= 38 && dnaCount_ >= 18);
            else if (id == ID_BTN_MITOCHONDRIA) affordable = (rnaCount_ >= 125 && dnaCount_ >= 100);
            else if (id == ID_BTN_EUKARYOTE) affordable = (rnaCount_ >= 40 && dnaCount_ >= 52);
            else if (id == ID_BTN_SEXUAL || id == ID_BTN_ASEXUAL) affordable = (dnaCount_ >= 175);
            else if (id == ID_BTN_SENTIENCE) affordable = (rnaCount_ >= 300 && dnaCount_ >= 300);

            // Treat unaffordable as visually disabled (Gray instead of Red)
            bool visuallyDisabled = isDisabled || !affordable;

            // 1. Background (Flat Style)
            COLORREF bgColor;
            if (visuallyDisabled) bgColor = RGB(20, 20, 20);      // Very Dark Grey
            else if (isPressed) bgColor = RGB(60, 60, 60);  // Dark Grey (Pressed)
            else bgColor = RGB(0, 0, 0);                    // Black (Normal)

            HBRUSH hBrush = CreateSolidBrush(bgColor);
            FillRect(hdc, &rc, hBrush);
            DeleteObject(hBrush);

            // 2. Border (Flat 1px)
            COLORREF borderColor;
            if (visuallyDisabled) borderColor = RGB(40, 40, 40);
            else if (isPressed) borderColor = RGB(100, 100, 100);
            else borderColor = RGB(80, 80, 80);

            HBRUSH hBorderBrush = CreateSolidBrush(borderColor);
            FrameRect(hdc, &rc, hBorderBrush);
            DeleteObject(hBorderBrush);

            // 3. Text
            COLORREF textColor = RGB(255, 255, 255);
            if (visuallyDisabled) {
                textColor = RGB(100, 100, 100); // Gray text
            }

            SetTextColor(hdc, textColor);
            SetBkMode(hdc, TRANSPARENT);

            wchar_t buffer[256];
            GetWindowTextW(pDIS->hwndItem, buffer, 256);

            RECT textRect = rc;
            if (isPressed) OffsetRect(&textRect, 1, 1); // Subtle shift

            // Center Text Calculation
            RECT measureRect = textRect;
            DrawTextW(hdc, buffer, -1, &measureRect, DT_CENTER | DT_WORDBREAK | DT_CALCRECT);
            int textHeight = measureRect.bottom - measureRect.top;
            int buttonHeight = textRect.bottom - textRect.top;
            int topOffset = (buttonHeight - textHeight) / 2;
            
            textRect.top += topOffset;
            textRect.bottom = textRect.top + textHeight;

            DrawTextW(hdc, buffer, -1, &textRect, DT_CENTER | DT_WORDBREAK);
            return TRUE;
        }
        
        // --- STATIC LABELS (Progress Bars) ---
        else if (pDIS->CtlType == ODT_STATIC) {
            int ctrlID = pDIS->CtlID;

            if (ctrlID == ID_LABEL_RNA || ctrlID == ID_LABEL_DNA) {
                // Background (Panel Color)
                HBRUSH bgBrush = CreateSolidBrush(RGB(40, 40, 42)); 
                FillRect(hdc, &rc, bgBrush);
                DeleteObject(bgBrush);

                // Determine Values
                int current = 0, max = 100;
                COLORREF barColor = RGB(50, 205, 50); // Default Green
                const wchar_t* label = L"";

                wchar_t textBuffer[256];
                
                if (ctrlID == ID_LABEL_RNA) {
                    current = rnaCount_;
                    max = rnaMax_;
                    barColor = RGB(50, 205, 50); // Lime Green
                    swprintf(textBuffer, 256, L"RNA: %d / %d (+%d/s)", rnaCount_, rnaMax_, rnaRate_);
                } else {
                    current = dnaCount_;
                    max = dnaMax_;
                    barColor = RGB(30, 144, 255); // Dodger Blue (Distinct from RNA)
                    swprintf(textBuffer, 256, L"DNA: %d / %d (+%d/s)", dnaCount_, dnaMax_, dnaRate_);
                }

                // 1. Draw Progress Bar Background (Track)
                RECT barRect = rc;
                barRect.top += 25; // Move bar to bottom
                barRect.bottom -= 5;
                
                HBRUSH trackBrush = CreateSolidBrush(RGB(20, 20, 20));
                FillRect(hdc, &barRect, trackBrush);
                DeleteObject(trackBrush);

                // 2. Draw Progress Fill
                if (max > 0) {
                    int barWidth = (barRect.right - barRect.left) * current / max;
                    if (barWidth > (barRect.right - barRect.left)) barWidth = barRect.right - barRect.left;
                    
                    RECT fillRect = barRect;
                    fillRect.right = fillRect.left + barWidth;
                    
                    HBRUSH fillBrush = CreateSolidBrush(barColor);
                    FillRect(hdc, &fillRect, fillBrush);
                    DeleteObject(fillBrush);
                }

                // 3. Draw Text
                SetTextColor(hdc, barColor); // Text matches bar color
                SetBkMode(hdc, TRANSPARENT);
                
                RECT textRect = rc;
                textRect.bottom = barRect.top; // Text above bar
                DrawTextW(hdc, textBuffer, -1, &textRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
                
                return TRUE;
            }
        }
        break;
    }

    case WM_CTLCOLORSTATIC: {
        HDC hdcStatic = (HDC)wParam;
        int ctrlID = GetDlgCtrlID((HWND)lParam);
        
        COLORREF textColor = RGB(255, 255, 255); // Default White

        if (ctrlID == ID_LABEL_VERSION) {
            textColor = RGB(0, 255, 255); // Cyan
        } else if (ctrlID == ID_LABEL_IDENTITY) {
            textColor = RGB(255, 215, 0); // Gold
        } else if (ctrlID == ID_LABEL_RNA || ctrlID == ID_LABEL_DNA) {
            textColor = RGB(50, 205, 50); // Lime Green
        }

        SetTextColor(hdcStatic, textColor);
        SetBkMode(hdcStatic, TRANSPARENT);
        static HBRUSH hBgBrush = CreateSolidBrush(RGB(45, 45, 48));
        return (LRESULT)hBgBrush;
    }

    case WM_COMMAND: {
        int wmId = LOWORD(wParam);
        switch (wmId) {
        case ID_BTN_RNA:
            if (rnaCount_ < rnaMax_) {
                SaveState(); // Save before change
                rnaCount_++;
                if (!isDnaUnlocked_ && rnaCount_ >= 2) {
                    isDnaUnlocked_ = true;
                    AddEvent(L"Unlocked: DNA (Requires RNA >= 2)");
                }
                AddLog(L"\u70B9\u51FB\u751F\u6210 RNA \u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d", rnaCount_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_DNA:
            if (rnaCount_ >= 2 && dnaCount_ < dnaMax_) {
                SaveState(); // Save
                rnaCount_ -= 2;
                dnaCount_++;
                AddLog(L"\u70B9\u51FB\u751F\u6210 DNA \u6210\u529F (\u6D88\u8017 2 RNA)\u3002\u5F53\u524D\u603B\u6570: %d", dnaCount_);
                
                UpdateUIDisplay();
            }
            break;
            
        case ID_BTN_ORGANELLE:
            // Cost: 12 RNA + 4 DNA
            if (rnaCount_ >= 12 && dnaCount_ >= 4) {
                SaveState(); // Save
                rnaCount_ -= 12;
                dnaCount_ -= 4;
                organelleCount_++;
                if (!isMembraneUnlocked_) isMembraneUnlocked_ = true;
                AddLog(L"\u8D2D\u4E70\u7EC6\u80DE\u5668\u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d", organelleCount_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_MEMBRANE:
            // Cost: 4 RNA
            if (rnaCount_ >= 4) {
                SaveState(); // Save
                rnaCount_ -= 4;
                membraneCount_++;
                // Recalculate Max
                rnaMax_ = 100 + membraneCount_ * (5 + (mitochondriaCount_ > 0 ? 5 : 0));
                AddLog(L"\u8D2D\u4E70\u7EC6\u80DE\u819C\u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d. RNA \u4E0A\u9650: %d", membraneCount_, rnaMax_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_NUCLEUS:
            // Cost: 38 RNA + 18 DNA
            if (rnaCount_ >= 38 && dnaCount_ >= 18) {
                SaveState(); // Save
                rnaCount_ -= 38;
                dnaCount_ -= 18;
                nucleusCount_++;
                AddLog(L"\u8D2D\u4E70\u7EC6\u80DE\u6838\u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d", nucleusCount_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_MITOCHONDRIA:
            // Cost: 125 RNA + 100 DNA
            if (rnaCount_ >= 125 && dnaCount_ >= 100) {
                SaveState(); // Save
                rnaCount_ -= 125;
                dnaCount_ -= 100;
                mitochondriaCount_++;
                // Recalculate Max
                rnaMax_ = 100 + membraneCount_ * (5 + (mitochondriaCount_ > 0 ? 5 : 0));
                dnaMax_ = 100 + eukaryoteCount_ * (10 + (mitochondriaCount_ > 0 ? 10 : 0));
                AddLog(L"\u8D2D\u4E70\u7EBF\u7C92\u4F53\u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d. \u8D44\u6E90\u4E0A\u9650\u5DF2\u63D0\u5347\u3002", mitochondriaCount_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_EUKARYOTE:
            // Cost: 40 RNA + 52 DNA
            if (rnaCount_ >= 40 && dnaCount_ >= 52) {
                SaveState(); // Save
                rnaCount_ -= 40;
                dnaCount_ -= 52;
                eukaryoteCount_++;
                // Recalculate Max
                dnaMax_ = 100 + eukaryoteCount_ * (10 + (mitochondriaCount_ > 0 ? 10 : 0));
                AddLog(L"\u8D2D\u4E70\u771F\u6838\u7EC6\u80DE\u6210\u529F\u3002\u5F53\u524D\u603B\u6570: %d. DNA \u4E0A\u9650: %d", eukaryoteCount_, dnaMax_);
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_SEXUAL:
            // Cost: 175 DNA
            if (dnaCount_ >= 175) {
                SaveState(); // Save
                dnaCount_ -= 175;
                hasChosenReproduction_ = true;
                isSexual_ = true;
                evolutionProgress_ = 1; // Stage 1
                AddEvent(L"Chosen: Sexual Reproduction");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE); // Redraw for progress bar
            }
            break;

        case ID_BTN_ASEXUAL:
            // Cost: 175 DNA
            if (dnaCount_ >= 175) {
                SaveState(); // Save
                dnaCount_ -= 175;
                hasChosenReproduction_ = true;
                isSexual_ = false;
                evolutionProgress_ = 1; // Stage 1
                AddEvent(L"Chosen: Asexual Reproduction");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE); // Redraw
            }
            break;

        case ID_BTN_PHAGOCYTOSIS:
            // No cost requirement
            SaveState(); // Save
            hasChosenEvolution_ = true;
            evolutionChoice_ = 1;
            evolutionProgress_ = 2; // Stage 2
            isMulticellularUnlocked_ = true; // Unlock next
            AddEvent(L"Evolution Path: Cell Phagocytosis (Animal)");
            
            UpdateUIDisplay();
            InvalidateRect(hwnd_, nullptr, TRUE);
            break;
        case ID_BTN_CHLOROPLAST:
            {
                // No cost requirement
                SaveState(); // Save

                hasChosenEvolution_ = true;
                evolutionChoice_ = 2;  // Chloroplast path
                evolutionProgress_ = 2; // Stage 2

                // Hide chloroplast and chitin buttons
                ShowWindow(hBtnChloroplast_, SW_HIDE);
                ShowWindow(hBtnChitin_, SW_HIDE);

                // Show sentience button
                isSentienceUnlocked_ = true;

                AddEvent(L"Evolution Path: Chloroplast (Plant)");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
                break;
            }
        case ID_BTN_CHITIN:
            {
                // No cost requirement
                SaveState(); // Save

                hasChosenEvolution_ = true;
                evolutionChoice_ = 3;  // Chitin path
                evolutionProgress_ = 2; // Stage 2

                // Hide chloroplast and chitin buttons
                ShowWindow(hBtnChloroplast_, SW_HIDE);
                ShowWindow(hBtnChitin_, SW_HIDE);

                // Show sentience button
                isSentienceUnlocked_ = true;

                AddEvent(L"Evolution Path: Chitin (Fungi)");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
                break;
            }

        case ID_BTN_MULTICELLULAR:
            // Cost: 200 DNA
            if (dnaCount_ >= 200) {
                SaveState();
                dnaCount_ -= 200;
                evolutionProgress_ = 3; // Stage 3
                isBilateralUnlocked_ = true; // Unlock next
                AddEvent(L"Evolved: Multicellular Organism");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
            }
            break;

        case ID_BTN_BILATERAL:
            // Cost: 250 DNA
            if (dnaCount_ >= 250) {
                SaveState();
                dnaCount_ -= 250;
                evolutionProgress_ = 4; // Stage 4
                isSpeciesUnlocked_ = true; // Unlock next (Species Selection)
                AddEvent(L"Evolved: Bilateral Symmetry");
                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
            }
            break;

        case ID_BTN_SENTIENCE:
            // Cost: 300 RNA + 300 DNA
            if (rnaCount_ >= 300 && dnaCount_ >= 300) {
                SaveState(); // Save
                rnaCount_ -= 300;
                dnaCount_ -= 300;

                if (!isSexual_) {
                    // Asexual reproduction: end evolution stage and randomly assign race
                    std::vector<std::wstring> allRaces;
                    std::wstring groupName;

                    // Check evolution choice to determine race pool
                    if (evolutionChoice_ == 2) {  // Chloroplast path
                        // Plant races
                        allRaces = {L"树人", L"仙人掌", L"捕虫堇"};
                        groupName = L"植物界";
                    } else if (evolutionChoice_ == 3) {  // Chitin path
                        // Fungi races
                        allRaces = {L"孢子虫", L"蘑菇人", L"霉菌人"};
                        groupName = L"真菌界";
                    } else {  // Default or phagocytosis path
                        // For asexual with phagocytosis, also use plant/fungi pools
                        allRaces = {L"树人", L"仙人掌", L"捕虫堇", L"孢子虫", L"蘑菇人", L"霉菌人"};
                        groupName = (rand() % 2 == 0) ? L"植物界" : L"真菌界";
                    }

                    int idx = rand() % allRaces.size();
                    std::wstring species = allRaces[idx];

                    // If mixed pool, determine correct group
                    if (evolutionChoice_ != 2 && evolutionChoice_ != 3) {
                        groupName = (idx < 3) ? L"植物界" : L"真菌界";
                    }

                    wchar_t buffer[256];
                    swprintf(buffer, 256, L"您已分配至 %ls - %ls", groupName.c_str(), species.c_str());
                    SetWindowTextW(hLabelIdentity_, buffer);
                    AddEvent(L"种族分配: %ls", species.c_str());

                    ShowCustomMessageBox(L"种族分配", buffer);

                    // Show civilization stage prompt with options
                    ShowCustomMessageBox(L"文明阶段", L"您即将进入文明阶段，请祈愿文明管理架构：\n\n选择「政府」→ 从以下类型中任选 1 个：\n专制、民主、寡头、神权、共和、社会主义、公司官僚主义、技术官僚主义、联邦制、魔法政府、独裁\n\n选择「无政府」→ 直接触发结局");

                    // End evolution stage and unlock civilization choice
                    isCivilizationUnlocked_ = true;
                    isGovSelectionUnlocked_ = false; // Player needs to choose Government or Anarchy first
                    evolutionProgress_ = 6; // Stage 6 (Civ)
                } else {
                    // Sexual reproduction: show species selection
                    isSpeciesUnlocked_ = true;
                    evolutionProgress_ = 5; // Stage 5 (Show species options)
                    AddEvent(L"Achieved Sentience. Choosing specialization...");
                }

                
                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
            }
            break;

        case ID_BTN_DEMON:
        case ID_BTN_BALROG:
        case ID_BTN_HEAVEN:
        case ID_BTN_HUMANOID:
        case ID_BTN_DWARF:
        case ID_BTN_GIANT:
        case ID_BTN_BEAST:
        case ID_BTN_EGGLAYER:
        case ID_BTN_REPTILE:
        case ID_BTN_AQUATIC:
        case ID_BTN_FAE:
        case ID_BTN_DESERT:
        case ID_BTN_FLAME:
        case ID_BTN_POLAR:
        case ID_BTN_ARTHROPOD:
        case ID_BTN_ABERRATION:
        {
            // Helper for species assignment
            auto AssignSpecies = [&](const std::vector<std::wstring>& speciesList, const std::wstring& groupName) {
                if (speciesList.empty()) return;

                // Filter out empty strings
                std::vector<std::wstring> filteredSpecies;
                for (const auto& s : speciesList) {
                    if (!s.empty()) {
                        filteredSpecies.push_back(s);
                    }
                }

                if (filteredSpecies.empty()) return;

                int idx = rand() % filteredSpecies.size();
                std::wstring species = filteredSpecies[idx];
                
                wchar_t buffer[256];
                swprintf(buffer, 256, L"\u60A8\u5DF2\u88AB\u5206\u914D\u81F3 %ls - %ls", groupName.c_str(), species.c_str());
                SetWindowTextW(hLabelIdentity_, buffer);
                AddEvent(L"\u79CD\u65CF\u5206\u914D: %ls", species.c_str());
                
                // End evolution stage
                isCivilizationUnlocked_ = true;  // Enable next stage
                isGovSelectionUnlocked_ = false; // Player needs to choose Government or Anarchy first
                evolutionProgress_ = 6; // Stage 6 (Civ)

                // 隐藏所有种群按钮
                ShowWindow(hBtnDemon_, SW_HIDE);
                ShowWindow(hBtnBalrog_, SW_HIDE);
                ShowWindow(hBtnHeaven_, SW_HIDE);
                ShowWindow(hBtnHumanoid_, SW_HIDE);
                ShowWindow(hBtnDwarf_, SW_HIDE);
                ShowWindow(hBtnGiant_, SW_HIDE);
                ShowWindow(hBtnBeast_, SW_HIDE);
                ShowWindow(hBtnEggLayer_, SW_HIDE);
                ShowWindow(hBtnReptile_, SW_HIDE);
                ShowWindow(hBtnAquatic_, SW_HIDE);
                ShowWindow(hBtnFae_, SW_HIDE);
                ShowWindow(hBtnDesert_, SW_HIDE);
                ShowWindow(hBtnFlame_, SW_HIDE);
                ShowWindow(hBtnPolar_, SW_HIDE);
                ShowWindow(hBtnArthropod_, SW_HIDE);
                ShowWindow(hBtnAberration_, SW_HIDE);

                UpdateUIDisplay();
                InvalidateRect(hwnd_, nullptr, TRUE);
                
                // Show alert
                ShowCustomMessageBox(L"\u79CD\u65CF\u5206\u914D", buffer); // "Species Assigned"

                // Show civilization stage prompt with options
                ShowCustomMessageBox(L"文明阶段", L"您即将进入文明阶段，请祈愿文明管理架构：\n\n选择「政府」→ 从以下类型中任选 1 个：\n专制、民主、寡头、神权、共和、社会主义、公司官僚主义、技术官僚主义、联邦制、魔法政府、独裁\n\n选择「无政府」→ 直接触发结局");
            };

            if (wmId == ID_BTN_DEMON) {
                AssignSpecies({L"\u5c0f\u6076\u9b54", L"", L""}, L"\u6076\u9b54\u708e\u9b54");
            } else if (wmId == ID_BTN_BALROG) {
                AssignSpecies({L"", L"", L""}, L"\u6076\u9b54\u708e\u9b54");
            } else if (wmId == ID_BTN_HEAVEN) {
                AssignSpecies({L"\u5927\u5929\u4f7f", L"\u72ec\u89d2\u517d", L""}, L"\u5929\u5802");
            } else if (wmId == ID_BTN_HUMANOID) {
                AssignSpecies({L"\u4eba\u7c7b", L"\u7cbe\u7075", L"\u517d\u4eba"}, L"\u7c7b\u4eba");
            } else if (wmId == ID_BTN_DWARF) {
                AssignSpecies({L"\u72d7\u5934\u4eba", L"\u54e5\u5e03\u6797", L"\u4f11\u5112"}, L"\u77ee\u4eba");
            } else if (wmId == ID_BTN_GIANT) {
                AssignSpecies({L"\u98df\u4eba\u9b54", L"\u72ec\u773c\u5de8\u4eba", L"\u5de8\u9b54"}, L"\u5de8\u4eba");
            } else if (wmId == ID_BTN_BEAST) {
                AssignSpecies({L"\u732b\u65cf", L"\u72fc\u4eba", L"\u5996\u72d0"}, L"\u54fa\u4e73\u52a8\u7269 (\u91ce\u517d)");
            } else if (wmId == ID_BTN_EGGLAYER) {
                AssignSpecies({L"\u9646\u884C\u9E1F", L"\u7FFC\u624B\u9F99", L"\u5929\u9F99"}, L"\u86CB\u58F3\u751F\u7269");
            } else if (wmId == ID_BTN_REPTILE) {
                AssignSpecies({L"\u4E4C\u9F9F\u4EBA", L"\u6C34\u8C5A", L"\u58C1\u864E\u4EBA"}, L"\u6C34\u751F\u751F\u7269");
            } else if (wmId == ID_BTN_AQUATIC) {
                AssignSpecies({L"\u9CA8\u9C7C\u4EBA", L"\u516B\u722A\u9C7C", L"\u5A1C\u8FE6"}, L"\u6D77\u6D0B\u751F\u7269");
            } else if (wmId == ID_BTN_FAE) {
                AssignSpecies({L"\u6811\u5996", L"\u8428\u63D0\u5C14", L""}, L"\u7CBE\u602A");
            } else if (wmId == ID_BTN_DESERT) {
                AssignSpecies({L"\u5854\u65AF\u80AF", L"\u9A86\u9A7C\u4EBA", L""}, L"\u6C99\u6F20\u751F\u7269");
            } else if (wmId == ID_BTN_FLAME) {
                AssignSpecies({L"\u4E0D\u6B7B\u9E1F", L"\u706B\u8725\u8734", L""}, L"\u70C8\u7130\u751F\u7269");
            } else if (wmId == ID_BTN_POLAR) {
                AssignSpecies({L"\u96EA\u602A", L"\u6E29\u8FEA\u6208", L""}, L"\u6781\u5730\u751F\u7269");
            } else if (wmId == ID_BTN_ARTHROPOD) {
                AssignSpecies({L"\u87B3\u8782\u4EBA", L"\u874E\u5B50\u4EBA", L"\u8682\u8681\u4EBA"}, L"\u8282\u80A2\u52A8\u7269");
            } else if (wmId == ID_BTN_ABERRATION) {
                AssignSpecies({L"\u5996\u9B3C", L"\u4FEE\u683C\u65AF", L""}, L"\u5F02\u9B54");
            }
        }
        break;

        case ID_BTN_GOVERNMENT:
            isGovSelectionUnlocked_ = true;
            
            UpdateUIDisplay();
            break;

        case ID_BTN_ANARCHY:
        case ID_BTN_AUTOCRACY:
        case ID_BTN_DEMOCRACY:
        case ID_BTN_OLIGARCHY:
        case ID_BTN_THEOCRACY:
        case ID_BTN_REPUBLIC:
        case ID_BTN_SOCIALISM:
        case ID_BTN_CORP_BUREAUCRACY:
        case ID_BTN_TECH_BUREAUCRACY:
        case ID_BTN_FEDERALISM:
        case ID_BTN_MAGOCRACY:
        case ID_BTN_DICTATORSHIP:
            if (!isGameEnded_) { // Only trigger once
                isGameEnded_ = true;
                AddEvent(L"Game Over. Civilization Architecture Chosen.");
                
                
                // Show Game Over Dialog
                ShowCustomMessageBox(L"\u6E38\u620F\u7ED3\u675F", L"\u6587\u660E\u7684\u9F7F\u8F6E\u6B63\u5728\u7F13\u6162\u8F6C\u52A8\uFF0C\u6E38\u620F\u7ED3\u675F");
                
                UpdateUIDisplay();
            }
            break;

        case ID_BTN_LOG:
            UpdateLogView();
            ShowWindow(hLogView_, SW_SHOW);
            SetFocus(hLogView_);
            break;
        case ID_BTN_PROGRESS:
            ShowProgressDialog();
            break;
        // case ID_BTN_EVENTS: // 已移除
        //    ShowEventsDialog();
        //    break;
        case ID_BTN_SETTINGS:
            ShowSettingsDialog();
            break;
        }
        return 0;
    }

    case WM_DESTROY:
        KillTimer(hwnd_, ID_TIMER_PASSIVE);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int Window::Run() {
    MSG msg = {};
    while (GetMessage(&msg, nullptr, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

void Window::AddLog(const wchar_t* format, ...) {
    // Assert valid parameters
    DEBUG_ASSERT(format != nullptr && "AddLog - format is null");

    wchar_t buffer[1024];
    va_list args;
    va_start(args, format);
    int result = vswprintf(buffer, 1024, format, args);
    va_end(args);
    DEBUG_ASSERT(result > 0 && "AddLog - vswprintf failed");

    logs_.push_back(buffer);
    // Keep only last 100 logs
    if (logs_.size() > 100) {
        logs_.erase(logs_.begin());
    }
    // If embedded log view is visible, insert newest on top
    if (hLogView_ && IsWindowVisible(hLogView_)) {
        SendMessage(hLogView_, LB_INSERTSTRING, 0, (LPARAM)buffer);
        SendMessage(hLogView_, LB_SETTOPINDEX, 0, 0);
    }
}

void Window::AddEvent(const wchar_t* format, ...) {
    wchar_t buffer[1024];
    va_list args;
    va_start(args, format);
    vswprintf(buffer, 1024, format, args);
    va_end(args);

    events_.push_back(buffer);
    // Keep only last 50 events
    if (events_.size() > 50) {
        events_.erase(events_.begin());
    }
    
    // Also add to log
    AddLog(L"[EVENT] %s", buffer);
}


    // Implement State Management
    void Window::SaveState() {
        GameState state;
        state.rnaCount = rnaCount_;
        state.rnaMax = rnaMax_;
        state.rnaRate = rnaRate_;
        state.dnaCount = dnaCount_;
        state.dnaMax = dnaMax_;
        state.dnaRate = dnaRate_;
        state.isDnaUnlocked = isDnaUnlocked_;
        state.organelleCount = organelleCount_;
        state.membraneCount = membraneCount_;
        state.nucleusCount = nucleusCount_;
        state.mitochondriaCount = mitochondriaCount_;
        state.eukaryoteCount = eukaryoteCount_;
        state.isOrganelleUnlocked = isOrganelleUnlocked_;
        state.isMembraneUnlocked = isMembraneUnlocked_;
        state.isNucleusUnlocked = isNucleusUnlocked_;
        state.isMitochondriaUnlocked = isMitochondriaUnlocked_;
        state.isEukaryoteUnlocked = isEukaryoteUnlocked_;
        state.isReproductionUnlocked = isReproductionUnlocked_;
        state.hasChosenReproduction = hasChosenReproduction_;
        state.isSexual = isSexual_;
        state.hasChosenEvolution = hasChosenEvolution_;
        state.isSentienceUnlocked = isSentienceUnlocked_;
        state.evolutionChoice = evolutionChoice_;
        state.evolutionProgress = evolutionProgress_;
        state.isSpeciesUnlocked = isSpeciesUnlocked_;
        state.isCivilizationUnlocked = isCivilizationUnlocked_;
        state.isGovSelectionUnlocked = isGovSelectionUnlocked_;
        state.isGameEnded = isGameEnded_;
        
        wchar_t buffer[256];
        GetWindowTextW(hLabelIdentity_, buffer, 256);
        state.identityText = buffer;

        history_.push_back(state);
        // Limit history size to 50
        if (history_.size() > 50) {
            history_.erase(history_.begin());
        }
    }

    void Window::RestoreState() {
        if (history_.empty()) {
            ShowCustomMessageBox(L"\u63D0\u793A", L"\u6CA1\u6709\u53EF\u6062\u590D\u7684\u8BB0\u5F55\u3002"); // No history
            return;
        }

        GameState state = history_.back();
        history_.pop_back();

        rnaCount_ = state.rnaCount;
        rnaMax_ = state.rnaMax;
        rnaRate_ = state.rnaRate;
        dnaCount_ = state.dnaCount;
        dnaMax_ = state.dnaMax;
        dnaRate_ = state.dnaRate;
        isDnaUnlocked_ = state.isDnaUnlocked;
        organelleCount_ = state.organelleCount;
        membraneCount_ = state.membraneCount;
        nucleusCount_ = state.nucleusCount;
        mitochondriaCount_ = state.mitochondriaCount;
        eukaryoteCount_ = state.eukaryoteCount;
        isOrganelleUnlocked_ = state.isOrganelleUnlocked;
        isMembraneUnlocked_ = state.isMembraneUnlocked;
        isNucleusUnlocked_ = state.isNucleusUnlocked;
        isMitochondriaUnlocked_ = state.isMitochondriaUnlocked;
        isEukaryoteUnlocked_ = state.isEukaryoteUnlocked;
        isReproductionUnlocked_ = state.isReproductionUnlocked;
        hasChosenReproduction_ = state.hasChosenReproduction;
        isSexual_ = state.isSexual;
        hasChosenEvolution_ = state.hasChosenEvolution;
        isSentienceUnlocked_ = state.isSentienceUnlocked;
        evolutionChoice_ = state.evolutionChoice;
        evolutionProgress_ = state.evolutionProgress;
        isSpeciesUnlocked_ = state.isSpeciesUnlocked;
        isCivilizationUnlocked_ = state.isCivilizationUnlocked;
        isGovSelectionUnlocked_ = state.isGovSelectionUnlocked;
        isGameEnded_ = state.isGameEnded;
        
        SetWindowTextW(hLabelIdentity_, state.identityText.c_str());

        AddLog(L"\u5DF2\u6062\u590D\u81F3\u4E0A\u4E00\u6B65\u3002"); // Restored
        UpdateUIDisplay();
    }

    void Window::ResetGame() {
        // Reset all variables
        rnaCount_ = 0;
        dnaCount_ = 0;
        organelleCount_ = 0;
        membraneCount_ = 0;
        nucleusCount_ = 0;
        mitochondriaCount_ = 0;
        eukaryoteCount_ = 0;
        
        isDnaUnlocked_ = false;
        isOrganelleUnlocked_ = false;
        isMembraneUnlocked_ = false;
        isNucleusUnlocked_ = false;
        isMitochondriaUnlocked_ = false;
        isEukaryoteUnlocked_ = false;
        isReproductionUnlocked_ = false;
        hasChosenReproduction_ = false;
        isSexual_ = false;
        hasChosenEvolution_ = false;
        isSentienceUnlocked_ = false;
        evolutionChoice_ = 0;
        isSpeciesUnlocked_ = false;
        isCivilizationUnlocked_ = false;
        isGovSelectionUnlocked_ = false;
        isGameEnded_ = false;

        history_.clear();
        logs_.clear();
        events_.clear();
        AddLog(L"\u6E38\u620F\u5DF2\u91CD\u7F6E\u3002"); // "Game Restarted."
        AddEvent(L"\u65B0\u7684\u65F6\u95F4\u7EBF\u5DF2\u5F00\u542F\u3002"); // "New Timeline Started."
        
        // Reset Identity
        SetWindowTextW(hLabelIdentity_, L"\u73A9\u5BB6\u8EAB\u4EFD\uFF1A\u539F\u59CB\u8F6F\u6CE5\u4E2D\u7684\u539F\u751F\u8D28");

        UpdateUIDisplay();

        // Force window redraw to clear game over text
        InvalidateRect(hwnd_, nullptr, TRUE);
        UpdateWindow(hwnd_);
    }

    // --- Custom Dialog Implementation ---

    // Static variables for Dialog Proc to access content
    static std::wstring g_DlgTitle;
    static std::wstring g_DlgContent;
    static bool g_DlgResult = false;
    static bool g_IsConfirmation = false;
    static bool g_IsSettings = false; // New Flag
    static int g_SettingsAction = 0; // 0=None, 1=Reset, 2=Undo
    static HFONT g_hDlgFont = nullptr;
    static HFONT g_hDlgContentFont = nullptr;
    static HBRUSH g_hEditBgBrush = nullptr; // Global brush for Edit control
    static HWND g_hContentEdit = nullptr;
    static WNDPROC g_RichEditOrigProc = nullptr;
    static LRESULT CALLBACK RichEditSubclassProc(HWND h, UINT m, WPARAM w, LPARAM l) {
        switch (m) {
        case WM_ERASEBKGND: {
            HDC hdc = (HDC)w;
            RECT rc;
            GetClientRect(h, &rc);
            HBRUSH bg = CreateSolidBrush(RGB(40, 40, 42));
            FillRect(hdc, &rc, bg);
            DeleteObject(bg);
            return 1;
        }
        }
        return CallWindowProcW(g_RichEditOrigProc, h, m, w, l);
    }

    LRESULT CALLBACK EvolutionDialogProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
        switch (uMsg) {
        case WM_CREATE: {
            // Desired Client Size (Content Area)
            int clientW = 600;
            int clientH = 400;
            
            // Calculate Window Size required for this Client Size
            RECT rc = { 0, 0, clientW, clientH };
            DWORD style = GetWindowLong(hwnd, GWL_STYLE);
            DWORD exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
            AdjustWindowRectEx(&rc, style, FALSE, exStyle);
            
            int w = rc.right - rc.left;
            int h = rc.bottom - rc.top;
            
            // Center on owner
            RECT rcOwner;
            HWND hParent = GetParent(hwnd);
            if (hParent) {
                GetWindowRect(hParent, &rcOwner);
            } else {
                rcOwner = { 0, 0, 1000, 700 }; // Fallback
            }

            int x = rcOwner.left + (rcOwner.right - rcOwner.left - w) / 2;
            int y = rcOwner.top + (rcOwner.bottom - rcOwner.top - h) / 2;
            SetWindowPos(hwnd, nullptr, x, y, w, h, SWP_NOZORDER);

            // Create Fonts and Brush
            g_hDlgFont = CreateFontW(28, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei");
            g_hDlgContentFont = CreateFontW(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_SWISS, L"Microsoft YaHei");
            if (!g_hEditBgBrush) g_hEditBgBrush = CreateSolidBrush(RGB(40, 40, 42));

            // Title Label
            HWND hTitle = CreateWindowW(L"STATIC", g_DlgTitle.c_str(), WS_CHILD | WS_VISIBLE | SS_CENTER, 20, 20, 560, 40, hwnd, nullptr, nullptr, nullptr);
            SendMessage(hTitle, WM_SETFONT, (WPARAM)g_hDlgFont, TRUE);

            // Content
            if (!g_IsSettings) {
                LoadLibraryW(L"Msftedit.dll");
                HWND hContent = CreateWindowExW(WS_EX_NOPARENTNOTIFY, MSFTEDIT_CLASS, L"", 
                    WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_CLIPSIBLINGS | ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL | ES_NOHIDESEL | ES_SUNKEN, 
                    30, 70, 540, 250, hwnd, (HMENU)1005, nullptr, nullptr);
                SendMessage(hContent, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);
                SendMessage(hContent, EM_SETLIMITTEXT, (WPARAM)0, (LPARAM)0);
                SendMessage(hContent, EM_SETTEXTMODE, (WPARAM)TM_PLAINTEXT, 0);
                SendMessage(hContent, EM_SETOPTIONS, (WPARAM)ECOOP_OR, (LPARAM)(ECO_READONLY | ECO_AUTOVSCROLL | ECO_NOHIDESEL));
                SendMessage(hContent, EM_SETEVENTMASK, 0, (LPARAM)(ENM_SCROLL | ENM_UPDATE));
                SendMessage(hContent, EM_SETBKGNDCOLOR, 0, (LPARAM)RGB(40,40,42));
                CHARFORMAT2W cf = {};
                cf.cbSize = sizeof(CHARFORMAT2W);
                cf.dwMask = CFM_COLOR | CFM_FACE | CFM_SIZE;
                cf.crTextColor = RGB(200,200,200);
                wcscpy_s(cf.szFaceName, L"Microsoft YaHei");
                cf.yHeight = 22 * 20;
                SendMessage(hContent, EM_SETCHARFORMAT, SCF_ALL, (LPARAM)&cf);
                g_RichEditOrigProc = (WNDPROC)SetWindowLongPtrW(hContent, GWLP_WNDPROC, (LONG_PTR)RichEditSubclassProc);
                g_hContentEdit = hContent;
                SetWindowTextW(hContent, g_DlgContent.c_str());
            }

            // Buttons
            if (g_IsSettings) {
                 // Reset Game Button
                 HWND hBtnReset = CreateWindowW(L"BUTTON", L"\u91CD\u7F6E\u6E38\u620F", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 100, 100, 400, 50, hwnd, (HMENU)1001, nullptr, nullptr);
                 SendMessage(hBtnReset, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);

                 // Undo Button
                 HWND hBtnUndo = CreateWindowW(L"BUTTON", L"\u6062\u590D\u4E0A\u4E00\u6B65", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 100, 180, 400, 50, hwnd, (HMENU)1002, nullptr, nullptr);
                 SendMessage(hBtnUndo, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);

                 // Close Button
                 HWND hBtnClose = CreateWindowW(L"BUTTON", L"\u5173\u95ED", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 240, 340, 120, 40, hwnd, (HMENU)IDCANCEL, nullptr, nullptr);
                 SendMessage(hBtnClose, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);

            } else if (g_IsConfirmation) {
                HWND hBtnYes = CreateWindowW(L"BUTTON", L"\u786E\u8BA4", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 150, 340, 120, 40, hwnd, (HMENU)IDYES, nullptr, nullptr);
                HWND hBtnNo = CreateWindowW(L"BUTTON", L"\u53D6\u6D88", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 330, 340, 120, 40, hwnd, (HMENU)IDNO, nullptr, nullptr);
                SendMessage(hBtnYes, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);
                SendMessage(hBtnNo, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);
            } else {
                HWND hBtnOK = CreateWindowW(L"BUTTON", L"\u5173\u95ED", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | BS_OWNERDRAW, 240, 340, 120, 40, hwnd, (HMENU)IDOK, nullptr, nullptr);
                SendMessage(hBtnOK, WM_SETFONT, (WPARAM)g_hDlgContentFont, TRUE);
            }
            return 0;
        }

        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            
            // Exclude content edit area from parent painting
            HWND hContent = GetDlgItem(hwnd, 1005);
            if (hContent) {
                RECT rcChild;
                GetWindowRect(hContent, &rcChild);
                MapWindowPoints(nullptr, hwnd, (POINT*)&rcChild, 2);
                ExcludeClipRect(hdc, rcChild.left, rcChild.top, rcChild.right, rcChild.bottom);
            }

            // Background
            HBRUSH bgBrush = CreateSolidBrush(RGB(30, 30, 32));
            FillRect(hdc, &rc, bgBrush);
            DeleteObject(bgBrush);

            // Border
            HBRUSH borderBrush = CreateSolidBrush(RGB(100, 100, 100)); // Lighter border
            FrameRect(hdc, &rc, borderBrush);
            DeleteObject(borderBrush);

            EndPaint(hwnd, &ps);
            return 0;
        }

        case WM_CTLCOLORSTATIC: {
            HDC hdcStatic = (HDC)wParam;
            // Normal Static Controls (Labels)
            SetTextColor(hdcStatic, RGB(220, 220, 220));
            SetBkMode(hdcStatic, TRANSPARENT);
            static HBRUSH hBgBrush = CreateSolidBrush(RGB(30, 30, 32));
            return (LRESULT)hBgBrush;
        }
        
        case WM_CTLCOLOREDIT: {
            HDC hdcEdit = (HDC)wParam;
            SetTextColor(hdcEdit, RGB(200, 200, 200));
            SetBkColor(hdcEdit, RGB(40, 40, 42)); // Slightly lighter for edit box
            SetBkMode(hdcEdit, OPAQUE); // Ensure opaque for safety
            return (LRESULT)g_hEditBgBrush;
        }
        
        case WM_ERASEBKGND: {
            HDC hdc = (HDC)wParam;
            RECT rc;
            GetClientRect(hwnd, &rc);
            // Exclude content edit area from parent erase
            if (g_hContentEdit) {
                RECT rcChild;
                GetWindowRect(g_hContentEdit, &rcChild);
                MapWindowPoints(nullptr, hwnd, (POINT*)&rcChild, 2);
                ExcludeClipRect(hdc, rcChild.left, rcChild.top, rcChild.right, rcChild.bottom);
            }
            HBRUSH bg = CreateSolidBrush(RGB(30, 30, 32));
            FillRect(hdc, &rc, bg);
            DeleteObject(bg);
            return 1;
        }
        
        case WM_NOTIFY: {
            NMHDR* pNM = (NMHDR*)lParam;
            if (pNM && pNM->idFrom == 1005) {
                if (pNM->code == EN_VSCROLL || pNM->code == EN_UPDATE) {
                    if (g_hContentEdit) InvalidateRect(g_hContentEdit, nullptr, TRUE);
                }
            }
            break;
        }

        case WM_DRAWITEM: {
            LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
            if (pDIS->CtlType == ODT_BUTTON) {
                HDC hdc = pDIS->hDC;
                RECT rc = pDIS->rcItem;
                bool isPressed = (pDIS->itemState & ODS_SELECTED);

                // Button Style
                HBRUSH hBrush = CreateSolidBrush(isPressed ? RGB(80, 80, 80) : RGB(60, 60, 60));
                FillRect(hdc, &rc, hBrush);
                DeleteObject(hBrush);

                HBRUSH hBorder = CreateSolidBrush(RGB(100, 100, 100));
                FrameRect(hdc, &rc, hBorder);
                DeleteObject(hBorder);

                SetTextColor(hdc, RGB(255, 255, 255));
                SetBkMode(hdc, TRANSPARENT);
                
                wchar_t buffer[256];
                GetWindowTextW(pDIS->hwndItem, buffer, 256);
                DrawTextW(hdc, buffer, -1, &rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                return TRUE;
            }
            break;
        }

        case WM_COMMAND: {
            int id = LOWORD(wParam);
            if (g_IsSettings) {
                if (id == 1001) { // Reset
                    g_SettingsAction = 1;
                    DestroyWindow(hwnd);
                } else if (id == 1002) { // Undo
                    g_SettingsAction = 2;
                    DestroyWindow(hwnd);
                } else if (id == IDCANCEL) {
                    g_SettingsAction = 0;
                    DestroyWindow(hwnd);
                }
            } else {
                if (id == IDOK || id == IDYES) {
                    g_DlgResult = true;
                    DestroyWindow(hwnd);
                } else if (id == IDNO || id == IDCANCEL) {
                    g_DlgResult = false;
                    DestroyWindow(hwnd);
                }
            }
            return 0;
        }
        
        case WM_DESTROY:
            if (g_hDlgFont) DeleteObject(g_hDlgFont);
            if (g_hDlgContentFont) DeleteObject(g_hDlgContentFont);
            if (g_hEditBgBrush) DeleteObject(g_hEditBgBrush);
            g_hEditBgBrush = nullptr; // Reset to avoid reuse if window created again (though static remains)
            PostQuitMessage(0); // Exit the modal loop
            return 0;
        }
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    void Window::ShowSettingsDialog() {
        g_DlgTitle = L"\u8BBE\u7F6E"; // Settings
        g_IsSettings = true;
        g_IsConfirmation = false;
        g_SettingsAction = 0;

        WNDCLASSEXW wc = {};
        if (!GetClassInfoExW(hInstance_, L"EvolutionDialog", &wc)) {
            wc.cbSize = sizeof(WNDCLASSEXW);
            wc.lpfnWndProc = EvolutionDialogProc;
            wc.hInstance = hInstance_;
            wc.lpszClassName = L"EvolutionDialog";
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            RegisterClassExW(&wc);
        }

        HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST | WS_EX_COMPOSITED, L"EvolutionDialog", g_DlgTitle.c_str(), 
            WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 600, 400, hwnd_, nullptr, hInstance_, nullptr);

        EnableWindow(hwnd_, FALSE);
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        EnableWindow(hwnd_, TRUE);
        SetForegroundWindow(hwnd_);

        if (g_SettingsAction == 1) { // Reset
            if (ShowCustomConfirmationBox(L"\u91CD\u7F6E\u6E38\u620F", L"\u786E\u5B9A\u8981\u91CD\u7F6E\u6E38\u620F\u5417\uFF1F\u6240\u6709\u8FDB\u5EA6\u5C06\u4E22\u5931\u3002")) {
                ResetGame();
            }
        } else if (g_SettingsAction == 2) { // Undo
            RestoreState();
        }
    }

    void Window::ShowLogDialog() {
        std::wstring content = L"";
        for (auto it = logs_.rbegin(); it != logs_.rend(); ++it) {
            content += *it + L"\r\n"; // Edit control needs \r\n
        }
        // Embedded view now used; no popup
        (void)content;
    }

    // --- Log & Events ---
    // void Window::ShowEventsDialog() { // 已移除
    //     std::wstring content = L"";
    //     for (auto it = events_.rbegin(); it != events_.rend(); ++it) {
    //         content += *it + L"\r\n";
    //     }
    //     ShowCustomMessageBox(L"\u4E8B\u4EF6\u5386\u53F2", content); // "Events History"
    // }

    void Window::ShowProgressDialog() {
        // This function now just shows the progress dialog for detailed view
        // The actual progress display is handled by GetProgressDescription()
        wchar_t buffer[1024];
        std::wstring phase = L"\u672A\u77E5"; // Unknown

        if (isGameEnded_) phase = L"\u6587\u660E (\u7ED3\u675F)"; // Civilization (Ended)
        else if (isCivilizationUnlocked_) phase = L"\u6587\u660E (\u5F62\u6210)"; // Civilization (Formation)
        else if (isSpeciesUnlocked_) phase = L"\u611F\u77E5 (\u79CD\u65CF\u9009\u62E9)"; // Sentience (Species Selection)
        else if (isSentienceUnlocked_) phase = L"\u611F\u77E5 (\u89C9\u9192)"; // Sentience (Awakening)
        else if (hasChosenEvolution_) phase = L"\u8FDB\u5316 (\u65B9\u5411)"; // Evolution (Direction)
        else if (hasChosenReproduction_) phase = L"\u8FDB\u5316 (\u7E41\u6B96)"; // Evolution (Reproduction)
        else if (eukaryoteCount_ > 0) phase = L"\u7ED3\u6784 (\u771F\u6838\u7EC6\u80DE)"; // Structure (Eukaryote)
        else if (nucleusCount_ > 0) phase = L"\u7ED3\u6784 (\u7EC6\u80DE\u6838)"; // Structure (Nucleus)
        else if (organelleCount_ > 0) phase = L"\u7ED3\u6784 (\u7EC6\u80DE\u5668)"; // Structure (Organelle)
        else phase = L"\u539F\u59CB (\u539F\u751F\u8D28)"; // Primordial (Protoplasm)

        swprintf(buffer, 1024,
            L"\u5F53\u524D\u9636\u6BB5: %s\r\n\r\n" // Current Phase
            L"\u8D44\u6E90:\r\n" // Resources
            L"RNA: %d / %d (+%d/s)\r\n"
            L"DNA: %d / %d (+%d/s)\r\n\r\n"
            L"\u7ED3\u6784:\r\n" // Structures
            L"\u7EC6\u80DE\u5668: %d\r\n"
            L"\u7EC6\u80DE\u819C: %d\r\n"
            L"\u7EC6\u80DE\u6838: %d\r\n"
            L"\u7EBF\u7C92\u4F53: %d\r\n"
            L"\u771F\u6838\u7EC6\u80DE: %d\r\n",
            phase.c_str(),
            rnaCount_, rnaMax_, rnaRate_,
            dnaCount_, dnaMax_, dnaRate_,
            organelleCount_, membraneCount_, nucleusCount_, mitochondriaCount_, eukaryoteCount_
        );

        ShowCustomMessageBox(L"\u8FDB\u5EA6\u6982\u89C8", buffer); // "Progress Overview"
    }

    std::wstring Window::GetProgressDescription() {
        // Return the current evolution stage description
        if (isGameEnded_) return L"文明已经形成";
        else if (isCivilizationUnlocked_) return L"进入文明阶段";
        else if (isSpeciesUnlocked_) return L"选择种群";
        else if (isSentienceUnlocked_) return L"进化出感知能力";
        else if (hasChosenEvolution_) {
            if (evolutionChoice_ == 1) return L"进化出吞噬能力";
            else if (evolutionChoice_ == 2) return L"进化出光合作用";
            else if (evolutionChoice_ == 3) return L"进化出几丁质外壳";
            else return L"进化方向已选择";
        }
        else if (hasChosenReproduction_) {
            if (isSexual_) return L"选择有性繁殖";
            else return L"选择无性繁殖";
        }
        else if (eukaryoteCount_ > 0) return L"进化出真核细胞";
        else if (mitochondriaCount_ > 0) return L"进化出线粒体";
        else if (nucleusCount_ > 0) return L"进化出细胞核";
        else if (membraneCount_ > 0) return L"进化出细胞膜";
        else if (organelleCount_ > 0) return L"进化出细胞器";
        else if (dnaCount_ > 0) return L"进化出DNA";
        else if (rnaCount_ > 0) return L"正在合成RNA";
        else return L"原始物质";
    }

    void Window::UpdateLogView() {
        if (!hLogView_) return;
        SendMessage(hLogView_, LB_RESETCONTENT, 0, 0);
        for (auto it = logs_.rbegin(); it != logs_.rend(); ++it) {
            SendMessage(hLogView_, LB_ADDSTRING, 0, (LPARAM)it->c_str());
        }
        // Ensure first item visible
        SendMessage(hLogView_, LB_SETTOPINDEX, 0, 0);
    }
    void Window::ShowCustomMessageBox(const std::wstring& title, const std::wstring& content) {
        g_DlgTitle = title;
        g_DlgContent = content;
        g_IsConfirmation = false;
        g_IsSettings = false; // Reset settings flag

        // Register Class if not exists (Simple check)
        WNDCLASSEXW wc = {};
        if (!GetClassInfoExW(hInstance_, L"EvolutionDialog", &wc)) {
            wc.cbSize = sizeof(WNDCLASSEXW);
            wc.lpfnWndProc = EvolutionDialogProc;
            wc.hInstance = hInstance_;
            wc.lpszClassName = L"EvolutionDialog";
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            RegisterClassExW(&wc);
        }

        HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST | WS_EX_COMPOSITED, L"EvolutionDialog", title.c_str(), 
            WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 600, 400, hwnd_, nullptr, hInstance_, nullptr);

        // Modal Loop
        EnableWindow(hwnd_, FALSE);
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        EnableWindow(hwnd_, TRUE);
        SetForegroundWindow(hwnd_);
    }

    bool Window::ShowCustomConfirmationBox(const std::wstring& title, const std::wstring& content) {
        g_DlgTitle = title;
        g_DlgContent = content;
        g_IsConfirmation = true;
        g_IsSettings = false; // Reset settings flag
        g_DlgResult = false;

        WNDCLASSEXW wc = {};
        if (!GetClassInfoExW(hInstance_, L"EvolutionDialog", &wc)) {
            wc.cbSize = sizeof(WNDCLASSEXW);
            wc.lpfnWndProc = EvolutionDialogProc;
            wc.hInstance = hInstance_;
            wc.lpszClassName = L"EvolutionDialog";
            wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
            wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
            RegisterClassExW(&wc);
        }

        HWND hDlg = CreateWindowExW(WS_EX_DLGMODALFRAME | WS_EX_TOPMOST | WS_EX_COMPOSITED, L"EvolutionDialog", title.c_str(), 
            WS_POPUP | WS_VISIBLE | WS_CAPTION | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 600, 400, hwnd_, nullptr, hInstance_, nullptr);

        EnableWindow(hwnd_, FALSE);
        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0)) {
            if (msg.message == WM_QUIT) break;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        EnableWindow(hwnd_, TRUE);
        SetForegroundWindow(hwnd_);
        
        return g_DlgResult;
    }

    void Window::InitTooltips() {
        INITCOMMONCONTROLSEX iccex;
        iccex.dwSize = sizeof(INITCOMMONCONTROLSEX);
        iccex.dwICC = ICC_WIN95_CLASSES;
        InitCommonControlsEx(&iccex);

        // NULL for HMENU parameter is correct for tooltip controls
        hTooltip_ = CreateWindowEx(NULL, TOOLTIPS_CLASS, NULL,
            WS_POPUP | TTS_ALWAYSTIP | TTS_NOPREFIX,
            CW_USEDEFAULT, CW_USEDEFAULT,
            CW_USEDEFAULT, CW_USEDEFAULT,
            hwnd_, NULL, hInstance_, NULL);
        DEBUG_ASSERT(hTooltip_ != nullptr && "Failed to create tooltip control");

        SetWindowPos(hTooltip_, HWND_TOPMOST, 0, 0, 0, 0,
            SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        
        // Adjust delay times for better UX
        SendMessage(hTooltip_, TTM_SETDELAYTIME, TTDT_INITIAL, 200);
        SendMessage(hTooltip_, TTM_SETDELAYTIME, TTDT_RESHOW, 100);
        SendMessage(hTooltip_, TTM_SETDELAYTIME, TTDT_AUTOPOP, 10000); // Show for 10 seconds
        
        // Set Max Width for multi-line support
        SendMessage(hTooltip_, TTM_SETMAXTIPWIDTH, 0, 400);
    }

    void Window::AddTooltip(HWND hBtn, const wchar_t* text) {
        DEBUG_ASSERT(hBtn != nullptr && "AddTooltip - hBtn is null");
        DEBUG_ASSERT(hTooltip_ != nullptr && "AddTooltip - hTooltip_ is null");
        DEBUG_ASSERT(text != nullptr && "AddTooltip - text is null");

        if (!hBtn || !hTooltip_) return;
        TOOLINFOW ti = { 0 };
        ti.cbSize = sizeof(TOOLINFOW);
        ti.uFlags = TTF_SUBCLASS | TTF_IDISHWND;
        ti.hwnd = hwnd_;
        ti.uId = (UINT_PTR)hBtn;
        ti.lpszText = const_cast<LPWSTR>(text);
        SendMessage(hTooltip_, TTM_ADDTOOL, 0, (LPARAM)&ti);
    }

} // namespace Evolution
