#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> // підключення бібліотеки з функціями API
#include "resource.h"
#include <string.h>;
#include<iostream>;
using namespace std;
#define changeicon             1
#define CHANGE_CURSOR          2
#define CHANGECAPTION          3
#define ABOUT				   4	

char buffer[500];
HINSTANCE hInst; 	//Дескриптор програми	
LPCTSTR szWindowClass = TEXT("STOROZHENKO SERGII |BIHUNOV MAKSYM");
LPCTSTR szTitle = TEXT("ПЕРША ПРОГРАМА");

void MainWndAddMenus(HWND hWnd);
ATOM NewWindowClass(HINSTANCE hInst);
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) {

	NewWindowClass(hInst);
	MSG msg;
	if (!InitInstance(hInst, ncmdshow))
	{
		return FALSE;
	}


	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}
ATOM NewWindowClass(HINSTANCE hInst) {
	WNDCLASSEX NWC = { };
	NWC.cbSize = sizeof(WNDCLASSEX);
	NWC.style = CS_HREDRAW | CS_VREDRAW  | CS_DBLCLKS;
	NWC.hInstance = hInst; 			//дескриптор програми
	NWC.hIcon = LoadIcon(NULL, IDI_INFORMATION); 		//визначення іконки
	NWC.hCursor = LoadCursor(NULL, IDC_NO); 	//визначення курсору
	NWC.hbrBackground = GetSysColorBrush(47);
	NWC.lpszClassName = szWindowClass;
	NWC.lpfnWndProc = WndProc;
	NWC.cbClsExtra = 0;
	NWC.cbWndExtra = 0;
	NWC.hIconSm = NULL;



	return RegisterClassEx(&NWC);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;
	hInst = hInstance; //зберігає дескриптор додатка в змінній hInst
	hWnd = CreateWindow(szWindowClass, 	// ім’я класу вікна
		szTitle, 				// назва програми
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,		// стиль вікна
		0, 			// положення по Х	
		250,			// положення по Y	
		500, 			// розмір по Х
		400, 			// розмір по Y
		NULL, 					// дескриптор батьківського вікна	
		NULL, 					// дескриптор меню вікна
		hInstance, 				// дескриптор програми
		NULL); 				// параметри створення.

	if (!hWnd) 	//Якщо вікно не творилось, функція повертає FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//Показати вікно
	UpdateWindow(hWnd); 				//Оновити вікно
	return TRUE;
}



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	RECT rt;
	WCHAR temp[100];
	switch (message)
	{
	case WM_COMMAND:
		switch (wParam)
		{
		case changeicon:
			SetClassLong(hWnd, GCL_HICON, (long)LoadIcon(hInst, MAKEINTRESOURCE(IDI_ICON1)));
			break;
		case CHANGE_CURSOR:
			SetClassLong(hWnd, GCL_HCURSOR, (long)LoadCursor(hInst, MAKEINTRESOURCE(IDC_CURSOR1)));
			break;
		case CHANGECAPTION:
			LoadString(hInst, IDS_STRING103, temp, 100);
			SetWindowText(hWnd, temp);
			break;
		case ABOUT:
			DialogBox(hInst, 				//дескриптор додатка, що містить клас вікна
				MAKEINTRESOURCE(IDD_DIALOG1),	//власне клас вікна
				hWnd, 				//дескриптор батьківського вікна
				DlgProc				//процедура діалогового вікна
			);
		break;

		default:
			break;
		}
		break;
	case WM_CREATE: 	
		MainWndAddMenus(hWnd);//Повідомлення приходить при створенні вікна
		break;

	case WM_PAINT: 				//Перемалювати вікно
		hdc = BeginPaint(hWnd, &ps); 	//Почати графічний вивід	
		GetClientRect(hWnd, &rt); 		//Область вікна для малювання
		DrawText(hdc, TEXT("Gutten tag!"), -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//Закінчити графічний вивід	
		break;

	case WM_CLOSE: 				//Завершення роботи
		DialogBox(hInst, 				//дескриптор додатка, що містить клас вікна
			MAKEINTRESOURCE(IDD_DIALOG2),	//власне клас вікна
			hWnd, 				//дескриптор батьківського вікна
			DlgProc2				//процедура діалогового вікна
		);
		break;
	
	default:
		//Обробка повідомлень, які не оброблені користувачем
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

int CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		//цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
			return TRUE;

		}
		case IDOK:
		{
			PostQuitMessage(0);
			break;
		}
		break;
		}

	}
	return FALSE;
}
int CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //ініціалізація функціоналу керування діалоговим вікном
		return TRUE;

		//цикл обробки натискання елементів на формі діалогового вікна
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
			return TRUE;
		}
		case IDOK:
		{
			EndDialog(hDlg, LOWORD(wParam));//знищення модального діалогового вікна
			return TRUE;
		}
		break;
		}
	}
	return FALSE;
}


void MainWndAddMenus(HWND hWnd) {
	HMENU RootMenu = CreateMenu();
	HMENU SubMENU = CreateMenu();
	AppendMenu(SubMENU, MF_STRING,changeicon, L"icon");
	AppendMenu(SubMENU, MF_STRING, CHANGECAPTION, L"header");
	AppendMenu(SubMENU, MF_STRING, CHANGE_CURSOR, L"cursor");
	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SubMENU, L"change");
	AppendMenu(RootMenu, MF_POPUP, ABOUT, L"about");
	SetMenu(hWnd, RootMenu);
}


