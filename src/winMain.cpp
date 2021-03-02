#include "window.h"
int CALLBACK WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPreInstance,
    LPSTR nCmdLine,
    int nCmdshow)
{
    ShowWindow(FindWindow("ConsoleWindowClass", NULL), SW_HIDE);
    window w1(hInstance);
    winClass c1(hInstance, "d3d", "resource\\icon.ico");
    w1.createWindow(&c1, 100, 100, 640, 480, "a window");
    w1.createWindow(&c1, 0, 100, 666, 555, "two window");

    while(1){
        if(const auto ecode =w1.processer())
            return *ecode;
        w1.doFrame();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// #include <win.h>

// LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

// int CALLBACK WinMain(       //? winmain is the user provided entry point for a graphical windows-based application
//     HINSTANCE hInstance,    //? hInstance is a handle to the current instance of the application
//     HINSTANCE hPreInstance, //? hPreInstance is a handle to the previous instance of the application,
//                             //? which is allways NULL, but if you wanna detect wheather another instance already exists
//                             //? you can create a uniquely named mutex using the CreateMutex function.
//                             //? CreateMutex will succeed even if the mutex already exists,
//                             //? but the function will return
//                             //! ERROR_ALREADY_EXISTS.
//                             //? This indicates that another instance of
//                             //! your application exists,
//                             //! because it created the mutex first. However,
//                             //? a malicious user can create this mutex before you do and prevent your application from starting.
//                             //? To prevent this situation,
//                             //? create a randomly named mutex and store the name so that it can only be obtained by an authorized user.
//                             //? Alternatively, you can use a file for this purpose. To limit your application to one instance per user,
//                             //? create a locked file in the user's profile directory.
//     LPSTR lpCmdLine,        //? LPSTR is a 32bits pointer which points a ANSI char* which ended as a \0,
//                             //? similarly LPWSTR is a 64bits pointer which points a 2byte char* which ended as NULL
//                             //? lpCmdLine is the command line for the application,
//                             //! excluding the program name
//                             //? to retrieve the command line, use GetCommandLine function
//     int nCmdShow)           //? nCmdShow is a return value.
//                             //? If the function succeeds,
//                             //? terminating when it receives a WM_QUIT message,
//                             //* it should return the exit value contained in that message's wParam parameter.
//                             //! If the function terminates before entering the message loop,
//                             //! it should return zero.
// {
//     const auto pClassName = _T("d3d");
//     //register window class
//     WNDCLASSEX wc = {0};      //? this structure contains window class information
//                               //? it's used with the RegisterClassEx and GetClassInfoEx functions.
//                               //? WNDCLASSEX is similar to WNDCLASS,
//                               //? WNDCLASS is added cbSize menber which specifies the size of the structure,
//                               //? and hIconSm menber which contains a handle to a small icon associated with the window class
//     wc.cbSize = sizeof(wc);   //! Be sure to set this member before calling the GetClassInfoEx function.
//     wc.style = CS_OWNDC;      //? The class style(s). This member can be any combination of the Class Styles.
//                               //? more about see https://docs.microsoft.com/en-us/windows/win32/winmsg/window-class-styles
//     wc.lpfnWndProc = WndProc; //? A pointer to the window procedure.
//                               //? You must use the CallWindowProc function to call the window procedure.
//     wc.cbClsExtra = 0;        //? The number of extra bytes to allocate following the window-class structure.
//                               //? The system initializes the bytes to zero.
//     wc.cbWndExtra = 0;        //? the number of extra bytes to allocate following the window instance.
//                               //? The system initializes the bytes to zero.
//                               //? If an application uses WNDCLASSEX to register a dialog box created by using the CLASS directive in the resource file,
//                               //? it must set this member to DLGWINDOWEXTRA.
//     wc.hInstance = hInstance;
//     wc.hIcon = nullptr;         //? A handle to the class icon. This member must be a handle to an icon resource.
//                                 //? If this member is NULL, the system provides a default icon.
//     wc.hCursor = nullptr;       //? A handle to the class cursor.
//                                 //? This member must be a handle to a cursor resource.
//                                 //? If this member is NULL,
//                                 //? an application must explicitly set the cursor shape whenever the mouse moves into the application's window.
//     wc.hbrBackground = nullptr; //? A handle to the class background brush.
//                                 //? This member can be a handle to the brush to be used for painting the background,
//                                 //? or it can be a color value.
//     wc.lpszMenuName = nullptr;  //? Pointer to a null-terminated character string that specifies the resource name of the class menu,
//                                 //? as the name appears in the resource file.
//     wc.lpszClassName = pClassName;
//     wc.hIconSm = nullptr;
//     RegisterClassEx(&wc);
//     //create window instance
//     HWND hWnd = CreateWindowEx(
//         0, pClassName,
//         _T("a window "),
//         WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
//         200, 200, 640, 480,
//         nullptr, nullptr, hInstance, nullptr);
//     //show it
//     ShowWindow(hWnd, SW_SHOW);

//     //message pump
//     MSG msg;
//     BOOL gResult;
//     while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
//     {
//         TranslateMessage(&msg);
//         DispatchMessage(&msg);
//     }
//     if (gResult == -1) //exit with errors
//         return -1;
//     else
//         return msg.wParam; //? there we get code 010(octal)(9) if the program exit normally
// }
// LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
// {
//     switch (msg)
//     {
//     case WM_CLOSE:
//         PostQuitMessage(9); //? calling this functions to tell the system,
//                             //? that a thread has made a request to terminate,
//                             //? besides, its parameter nExitCode equals message lopp's wParam
//         break;
//     case WM_KEYDOWN:
//     {
//         if (wParam == 'F')
//         {
//             SetWindowText(hWnd, _T("F?"));
//         }
//         break;
//     }
//     case WM_KEYUP:
//     {
//         SetWindowText(hWnd, _T("a window"));
//         break;
//     }
//     case WM_CHAR:
//     {
//         static std::string title;
//         title.push_back(wParam);
//         SetWindowText(hWnd, _T(title.c_str()));
//         break;
//     }
//     case WM_LBUTTONDOWN:
//     {
//         POINTS pts = MAKEPOINTS(lParam);
//         std::stringstream ss;
//         ss << "x:" << pts.x << ",y:" << pts.y;
//         SetWindowText(hWnd, _T(ss.str().c_str()));
//         break;
//     }
//     default:
//         break;
//     }

//     return DefWindowProc(hWnd, msg, wParam, lParam);
// }