#undef UNICODE
#define TIMER_SEC1 1
#define TIMER_SEC2 2
#define TIMER_SEC3 3

#include <windows.h>
#include <stdio.h>
#include <string>
#include <cmath>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "ClassName";

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS wcApp;

	// ��������� ��������� ������ ���� 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance = hInstance;
	wcApp.lpfnWndProc = WndProc;
	wcApp.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName = 0;
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style = 0;	//CS_HREDRAW | CS_VREDRAW;
	wcApp.cbClsExtra = 0;
	wcApp.cbWndExtra = 0;

	// ������������ ����� ����
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hwnd = CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static HDC hdc;
	PAINTSTRUCT ps;
	static int x, y;
	static RECT r;
	static HBRUSH hbrush1, hbrush2, hbrush3, hbrushOld;
	static int d1 = 0, d2 = 0, d3 = 0;
	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		hbrush1 = CreateSolidBrush(RGB(255, 0, 0));
		hbrush2 = CreateSolidBrush(RGB(255, 255, 0));
		hbrush3 = CreateSolidBrush(RGB(0, 255, 0));
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &r);
		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case TIMER_SEC1:
			if (!d1) d1 = 10;
			else d1 = 0;
			InvalidateRect(hwnd, 0, 1);
			break;
		case TIMER_SEC2:
			if (!d2) d2 = 10;
			else d2 = 0;
			InvalidateRect(hwnd, 0, 1);
			break;
		case TIMER_SEC3:
			if (!d3) d3 = 10;
			else d3 = 0;
			InvalidateRect(hwnd, 0, 1);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if (GetPixel(hdc, x, y) == RGB(255, 0, 0))
		{
			SetTimer(hwnd, TIMER_SEC1, 1000, 0); 
			d1 = 10;
		}
		if (GetPixel(hdc, x, y) == RGB(255, 255, 0))
		{
			SetTimer(hwnd, TIMER_SEC2, 1000, 0);
			d2 = 10;
		}
		if (GetPixel(hdc, x, y) == RGB(0, 255, 0))
		{
			SetTimer(hwnd, TIMER_SEC3, 1000, 0);
			d3 = 10;
		}

		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_LBUTTONUP:
		//d1 = 0; d2 = 0; d3 = 0;
		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_RBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		if ( GetPixel(hdc, x, y) == RGB(255, 0, 0))
			KillTimer(hwnd, 1);
		if ( GetPixel(hdc, x, y) == RGB(255, 255, 0))
			KillTimer(hwnd, 2);
		if (GetPixel(hdc, x, y) == RGB(0, 255, 0))
			KillTimer(hwnd, 3);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		//r1.left = r.right / 2 - 75; r1.top = r.bottom / 2 - 200; r1.right = r.right / 2 + 75; r1.bottom = r.bottom / 2 + 200;
		//Rectangle(hdc, r.right / 2 - 75, r.bottom / 2 - 200, r.right / 2 + 75, r.bottom / 2 + 200);
		hbrushOld = (HBRUSH)SelectObject(hdc,hbrush1);
		Ellipse(hdc, r.right / 2 - 40 + d1, r.bottom / 2 - 150 + d1, r.right / 2 + 40 - d1, r.bottom / 2 - 70 - d1);
		SelectObject(hdc, hbrush2);
		Ellipse(hdc, r.right / 2 - 40 + d2, r.bottom / 2 - 40 + d2, r.right / 2 + 40 - d2, r.bottom / 2 + 40 - d2);
		SelectObject(hdc, hbrush3);
		Ellipse(hdc, r.right / 2 - 40 + d3, r.bottom / 2 + 70 + d3, r.right / 2 + 40 - d3, r.bottom / 2 + 150 - d3);
		SelectObject(hdc, hbrushOld);
		break;
	case WM_DESTROY:
		DeleteObject(hbrush3);
		DeleteObject(hbrush2);
		DeleteObject(hbrush3);
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hwnd, uMsg, wParam, lParam));
	}
	return (0);
}