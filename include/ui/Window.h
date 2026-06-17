#pragma once

#include <windows.h>
#include <vector>
#include <string>

namespace Evolution {

// 窗口类
class Window {
public:
    Window();
    ~Window();

    // 创建窗口
    bool Create(HINSTANCE hInstance, int nCmdShow);

    // 获取窗口句柄
    HWND GetHandle() const { return hwnd_; }

    // 运行消息循环
    int Run();

    // 窗口过程.*静态)
    static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg,
                                      WPARAM wParam, LPARAM lParam);

    // 处理窗口消息
    LRESULT HandleMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
    HWND hwnd_;
    HINSTANCE hInstance_;
    static const wchar_t* CLASS_NAME;

    // UI控件
    HWND hLabelVersion_;
    HWND hLabelIdentity_;
    HWND hLabelRNA_;
    HWND hBtnRNA_;        // 点击生成RNA
    HWND hLabelDNA_;      // 显示DNA状态
    HWND hBtnDNA_;        // 点击生成DNA
    
    // 结构按钮
    HWND hBtnOrganelle_;
    HWND hBtnMembrane_;
    HWND hBtnNucleus_;
    HWND hBtnMitochondria_;
    HWND hBtnEukaryote_;

        HWND hBtnSettings_;
    HWND hBtnLog_;
    HWND hBtnProgress_;
    // HWND hBtnEvents_; // Removed
    HWND hLogView_;      // 原生质下嵌入的日志视图

    // 游戏状态
    int rnaCount_;
    int rnaMax_;
    int rnaRate_;
    
    int dnaCount_;
    int dnaMax_;
    int dnaRate_;
    bool isDnaUnlocked_;

    // 结构数量
    int organelleCount_;
    int membraneCount_;
    int nucleusCount_;
    int mitochondriaCount_;
    int eukaryoteCount_;

    // 结构解锁标志
    bool isOrganelleUnlocked_;
    bool isMembraneUnlocked_;
    bool isNucleusUnlocked_;
    bool isMitochondriaUnlocked_;
    bool isEukaryoteUnlocked_;

    // 第四阶段：繁殖与进化
    HWND hBtnSexual_;       // 有性繁殖
    HWND hBtnAsexual_;      // 无性繁殖
    HWND hBtnPhagocytosis_; // 细胞吞噬
    HWND hBtnChloroplast_;  // Chloroplast
    HWND hBtnChitin_;       // Chitin
    HWND hBtnSentience_;    // Sentience

    // Evolution Steps
    HWND hBtnMulticellular_;
    HWND hBtnBilateral_;

    // Phase 5: Species & Civilization
    // Species Groups
    HWND hBtnDemon_;
    HWND hBtnBalrog_;
    HWND hBtnHeaven_;
    HWND hBtnHumanoid_;
    HWND hBtnDwarf_;
    HWND hBtnGiant_;
    HWND hBtnBeast_;    // Was Mammal
    HWND hBtnEggLayer_;
    HWND hBtnReptile_;  // Was part of Aquatic? New group
    HWND hBtnAquatic_;
    HWND hBtnFae_;
    HWND hBtnDesert_;
    HWND hBtnFlame_;
    HWND hBtnPolar_;
    HWND hBtnArthropod_;
    HWND hBtnAberration_;
    // Plant/Fungi buttons if needed, or reuse above slots dynamically?
    // Let's stick to the 16 slots plan:
    // 1. Demon 2. Balrog 3. Heaven 4. Humanoid
    // 5. Dwarf 6. Giant 7. Beast 8. Egg
    // 9. Reptile 10. Aquatic 11. Fae 12. Desert
    // 13. Flame 14. Polar 15. Arthropod 16. Aberration

    // Remove old specific ones if unused or map them
    // hBtnMammal_ -> hBtnBeast_


    // Civilization Choices
    HWND hBtnGovernment_;
    HWND hBtnAnarchy_;

    // Government Types
    HWND hBtnAutocracy_;
    HWND hBtnDemocracy_;
    HWND hBtnOligarchy_;
    HWND hBtnTheocracy_;
    HWND hBtnRepublic_;
    HWND hBtnSocialism_;
    HWND hBtnCorpBureaucracy_;
    HWND hBtnTechBureaucracy_;
    HWND hBtnFederalism_;
    HWND hBtnMagocracy_;
    HWND hBtnDictatorship_;

    bool isReproductionUnlocked_;
    bool hasChosenReproduction_;
    bool isSexual_; // true if sexual, false if asexual
    bool hasChosenEvolution_;
    bool isSentienceUnlocked_;
    int evolutionChoice_; // 1=Phagocytosis, 2=Chloroplast, 3=Chitin
    
    bool isMulticellularUnlocked_;
    bool isBilateralUnlocked_;
    int evolutionProgress_; // 0-6

    bool isSpeciesUnlocked_;
    bool isCivilizationUnlocked_;
    bool isGovSelectionUnlocked_;
    bool isGameEnded_;

    // Control IDs
    static const int ID_LABEL_VERSION = 101;
    static const int ID_LABEL_IDENTITY = 102;
    static const int ID_LABEL_RNA = 103;
    static const int ID_LABEL_DNA = 104;
        static const int ID_BTN_SETTINGS = 202;
    static const int ID_BTN_LOG = 204;
    static const int ID_BTN_PROGRESS = 205;
    // static const int ID_BTN_EVENTS = 206; // Removed
    static const int ID_LIST_LOGVIEW = 207;
    static const int ID_BTN_RNA = 209;
    static const int ID_BTN_DNA = 210;
    static const int ID_BTN_ORGANELLE = 301;
    static const int ID_BTN_MEMBRANE = 302;
    static const int ID_BTN_NUCLEUS = 303;
    static const int ID_BTN_MITOCHONDRIA = 304;
    static const int ID_BTN_EUKARYOTE = 305;
    
    static const int ID_BTN_SEXUAL = 401;
    static const int ID_BTN_ASEXUAL = 402;
    static const int ID_BTN_PHAGOCYTOSIS = 403;
    static const int ID_BTN_CHLOROPLAST = 404;
    static const int ID_BTN_CHITIN = 405;
    static const int ID_BTN_SENTIENCE = 406;
    static const int ID_BTN_MULTICELLULAR = 407;
    static const int ID_BTN_BILATERAL = 408;

    static const int ID_BTN_DEMON = 501;
    static const int ID_BTN_BALROG = 502;
    static const int ID_BTN_HEAVEN = 503;
    static const int ID_BTN_HUMANOID = 504;
    static const int ID_BTN_DWARF = 505;
    static const int ID_BTN_GIANT = 506;
    static const int ID_BTN_BEAST = 507;
    static const int ID_BTN_EGGLAYER = 508;
    static const int ID_BTN_REPTILE = 509;
    static const int ID_BTN_AQUATIC = 510;
    static const int ID_BTN_FAE = 511;
    static const int ID_BTN_DESERT = 512;
    static const int ID_BTN_FLAME = 513;
    static const int ID_BTN_POLAR = 514;
    static const int ID_BTN_ARTHROPOD = 515;
    static const int ID_BTN_ABERRATION = 516;

    static const int ID_BTN_GOVERNMENT = 601;
    static const int ID_BTN_ANARCHY = 602;

    static const int ID_BTN_AUTOCRACY = 701;
    static const int ID_BTN_DEMOCRACY = 702;
    static const int ID_BTN_OLIGARCHY = 703;
    static const int ID_BTN_THEOCRACY = 704;
    static const int ID_BTN_REPUBLIC = 705;
    static const int ID_BTN_SOCIALISM = 706;
    static const int ID_BTN_CORP_BUREAUCRACY = 707;
    static const int ID_BTN_TECH_BUREAUCRACY = 708;
    static const int ID_BTN_FEDERALISM = 709;
    static const int ID_BTN_MAGOCRACY = 710;
    static const int ID_BTN_DICTATORSHIP = 711;

    static const int ID_TIMER_PASSIVE = 901;

    // Helper functions
    bool RegisterWindowClass();
    void CreateControls();
    void ResizeControls(int width, int height); // New function
    void UpdateUIDisplay();
    void CheckUnlocks();
    void ProcessPassiveGeneration();
    
    // Log & Events
    std::vector<std::wstring> logs_;
    std::vector<std::wstring> events_;
    void AddLog(const wchar_t* format, ...);
    void AddEvent(const wchar_t* format, ...);
    void ShowLogDialog();
    // void ShowEventsDialog(); // Removed
    void ShowProgressDialog();
    void UpdateLogView();

    // 游戏状态 History for Undo
    struct GameState {
        int rnaCount, rnaMax, rnaRate;
        int dnaCount, dnaMax, dnaRate;
        bool isDnaUnlocked;
        int organelleCount, membraneCount, nucleusCount, mitochondriaCount, eukaryoteCount;
        bool isOrganelleUnlocked, isMembraneUnlocked, isNucleusUnlocked, isMitochondriaUnlocked, isEukaryoteUnlocked;
        bool isReproductionUnlocked, hasChosenReproduction, isSexual;
        bool hasChosenEvolution, isSentienceUnlocked;
        int evolutionChoice;
        bool isMulticellularUnlocked, isBilateralUnlocked;
        int evolutionProgress;
        bool isSpeciesUnlocked, isCivilizationUnlocked, isGovSelectionUnlocked, isGameEnded;
        std::wstring identityText;
    };
    std::vector<GameState> history_;
    void SaveState();
    void RestoreState();
    void ResetGame();

    // Settings Dialog
    void ShowSettingsDialog();

    // Test Settings Dialog
    
    // Tooltip Handle
    HWND hTooltip_;
    void InitTooltips();
    void AddTooltip(HWND hBtn, const wchar_t* text);

    // Custom Dialogs
    void ShowCustomMessageBox(const std::wstring& title, const std::wstring& content);
    bool ShowCustomConfirmationBox(const std::wstring& title, const std::wstring& content);

    // Progress
    std::wstring GetProgressDescription();
};

} // namespace Evolution
