#include <iostream>
#include <windows.h>
#include <shobjidl.h>



void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

BOOL SetProgramIcon(const wchar_t* iconPath, HWND hWnd);

int main() {
    HWND hwnd = GetConsoleWindow();
    SetConsoleTitleW(L"自定义窗口图标");
    OPENFILENAME ofn;
    wchar_t szFile[MAX_PATH] = L"";
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = L'\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = L"Icon Files (*.ico)\0*.ico\0All Files (*.*)\0*.*\0";
    ofn.nFilterIndex = 1;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    if (GetOpenFileName(&ofn)) {
        if (SetProgramIcon(szFile, GetConsoleWindow())) {
            MessageBox(NULL, L"程序图标已设置成功！", L"成功", MB_ICONINFORMATION);
        }
        else {
            MessageBox(NULL, L"无法设置程序图标。", L"错误", MB_ICONERROR);
        }
    }

    SetConsoleTitleW(L"自定义到期时间");

    std::cout << "[";
    setColor(10); 
    std::cout << "Info";
    setColor(7); 

    std::cout << "]";
    std::cout << "请依次输入天数 小时 分钟 秒" << std::endl;

    std::string days, hours, minutes, who;

    std::cin >> days >> hours >> minutes >> who;

    system("cls");

    SetConsoleTitleW(L"Authentification");

    std::cout << "[";
    setColor(10); 
    std::cout << "Info ";
    setColor(7); 
    std::cout << "]";

    std::cout << "Successfully logged in." << std::endl;
    std::cout << "[";
    setColor(10); 
    std::cout << "Info ";
    setColor(7); 
    std::cout << "]";
    std::cout << "License will expire in " << days << " day[s] " << hours << " hour[s] " << minutes << " minute[s] " << who << " second[s]." << std::endl;

    std::cout << "[";
    setColor(10);
    std::cout << "Info ";
    setColor(7);
    std::cout << "]";
    std::cout << "Console will close in 5 seconds." << std::endl;

    
    Sleep(9999999);

    return 0;

}


BOOL SetProgramIcon(const wchar_t* iconPath, HWND hWnd) {
    HICON hIcon = (HICON)LoadImage(NULL, iconPath, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
    if (hIcon == NULL) {
        return FALSE;
    }

    WNDCLASSEX wcex;
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = 0;
    wcex.lpfnWndProc = DefWindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = GetModuleHandle(NULL);
    wcex.hIcon = hIcon;
    wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = L"MyHiddenWindowClass";
    wcex.hIconSm = NULL;

    if (!RegisterClassEx(&wcex)) {
        return FALSE;
    }

    HWND hiddenWindow = CreateWindow(L"MyHiddenWindowClass", L"", 0, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, GetModuleHandle(NULL), NULL);
    if (hiddenWindow == NULL) {
        return FALSE;
    }

    SetProp(hiddenWindow, L"MY_HIDDEN_PROP", (HANDLE)hIcon);

    SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
    SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);

    return TRUE;
}
