#define _CRT_SECURE_NO_WARNINGS
#include <windows.h> // ���������� �������� � ��������� API
#include "resource.h"
#include <string.h>;
#include<iostream>;
using namespace std;
#define changeicon             1
#define CHANGE_CURSOR          2
#define CHANGECAPTION          3
#define ABOUT				   4	

char buffer[500];
HINSTANCE hInst; 	//���������� ��������	
LPCTSTR szWindowClass = TEXT("STOROZHENKO SERGII |BIHUNOV MAKSYM");
LPCTSTR szTitle = TEXT("����� ��������");

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
	NWC.hInstance = hInst; 			//���������� ��������
	NWC.hIcon = LoadIcon(NULL, IDI_INFORMATION); 		//���������� ������
	NWC.hCursor = LoadCursor(NULL, IDC_NO); 	//���������� �������
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
	hInst = hInstance; //������ ���������� ������� � ����� hInst
	hWnd = CreateWindow(szWindowClass, 	// ��� ����� ����
		szTitle, 				// ����� ��������
		WS_OVERLAPPED | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,		// ����� ����
		0, 			// ��������� �� �	
		250,			// ��������� �� Y	
		500, 			// ����� �� �
		400, 			// ����� �� Y
		NULL, 					// ���������� ������������ ����	
		NULL, 					// ���������� ���� ����
		hInstance, 				// ���������� ��������
		NULL); 				// ��������� ���������.

	if (!hWnd) 	//���� ���� �� ���������, ������� ������� FALSE
	{
		return FALSE;
	}
	ShowWindow(hWnd, nCmdShow); 		//�������� ����
	UpdateWindow(hWnd); 				//������� ����
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
			DialogBox(hInst, 				//���������� �������, �� ������ ���� ����
				MAKEINTRESOURCE(IDD_DIALOG1),	//������ ���� ����
				hWnd, 				//���������� ������������ ����
				DlgProc				//��������� ���������� ����
			);
		break;

		default:
			break;
		}
		break;
	case WM_CREATE: 	
		MainWndAddMenus(hWnd);//����������� ��������� ��� �������� ����
		break;

	case WM_PAINT: 				//������������ ����
		hdc = BeginPaint(hWnd, &ps); 	//������ ��������� ����	
		GetClientRect(hWnd, &rt); 		//������� ���� ��� ���������
		DrawText(hdc, TEXT("Gutten tag!"), -1, &rt, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps); 		//�������� ��������� ����	
		break;

	case WM_CLOSE: 				//���������� ������
		DialogBox(hInst, 				//���������� �������, �� ������ ���� ����
			MAKEINTRESOURCE(IDD_DIALOG2),	//������ ���� ����
			hWnd, 				//���������� ������������ ����
			DlgProc2				//��������� ���������� ����
		);
		break;
	
	default:
		//������� ����������, �� �� �������� ������������
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
}

int CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:  //����������� ����������� ��������� ��������� �����
		return TRUE;

		//���� ������� ���������� �������� �� ���� ���������� ����
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
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
	case WM_INITDIALOG:  //����������� ����������� ��������� ��������� �����
		return TRUE;

		//���� ������� ���������� �������� �� ���� ���������� ����
	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case IDCANCEL:
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
			return TRUE;
		}
		case IDOK:
		{
			EndDialog(hDlg, LOWORD(wParam));//�������� ���������� ���������� ����
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


