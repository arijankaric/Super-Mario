#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "Game.hpp"

const int ID_TIMER = 1;
const int IDT_TIMER3 = 50;
const int ID_TIMER_PIRANHA_UP = 0;
const int ID_TIMER_PIRANHA_DOWN = 1;

const int DX = 1;
const int DY = 1;

std::shared_ptr<Object> Object::mario = nullptr;
Object::vektorObjekata Object::objects = nullptr;

/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpszArgument,
                    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
               0,                   /* Extended possibilites for variation */
               szClassName,         /* Classname */
               _T("Code::Blocks Template Windows App"),       /* Title Text */
               (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MINIMIZEBOX ^ WS_SYSMENU), /* default window */
               700,       /* Windows decides the position */
               300,       /* where the window ends up on the screen */
               SIRINAPROZORA,                 /* The programs width */
               VISINAPROZORA,                 /* and height in pixels */
               HWND_DESKTOP,        /* The window is a child-window to desktop */
               NULL,                /* No menu */
               hThisInstance,       /* Program Instance handler */
               NULL                 /* No Window Creation data */
           );
    Game game1;
    game1.hwnd = hwnd;

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

//    Initalize(hwnd);
    DWORD vrijeme_pocetak;

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (TRUE)
    {

        if(PeekMessage(&messages, NULL, 0,0, PM_REMOVE))
        {
            if(messages.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }

        vrijeme_pocetak = GetTickCount(); // DWORD GetTickCount(); The return value is the number of milliseconds that have elapsed since the system was started.

        game1.CheckInput();
//        std::cout << "checkInput izvrsen\n";
        game1.Update();
//        std::cout << "update izvrsen\n";
        game1.Render();
//        std::cout << "render izvrsen\n";

        while(GetTickCount()- vrijeme_pocetak < 16.66666666666667) // 1000/60 = 16.66666666666667; 55 prethodna vrijednost
        {
//            std::cout << "sleep(1)" << std::endl;
            Sleep(1);
        }
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)                  /* handle the messages */
    {
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        break;
    case WM_TIMER:
        std::cout << "WM_TIMER wParam: " << wParam << std::endl;
        switch (wParam)
        {
        case ID_TIMER_PIRANHA_UP:
            std::cout << "PIRANHA_UP_TIMER\n";
            KillTimer(hwnd, ID_TIMER_PIRANHA_UP);
            return 0;

        case ID_TIMER_PIRANHA_DOWN:
            std::cout << "PIRANHA_DOWN_TIMER\n";
            KillTimer(hwnd, ID_TIMER_PIRANHA_DOWN);
            return 0;
        }
    default:                      /* for messages that we don't deal with */
        return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}
