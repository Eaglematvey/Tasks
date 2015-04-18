#undef UNICODE
#define TIMER_SEC 1

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

	// Заполняем структуру класса окна 
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

	// Регистрируем класс окна
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

	static RECT r;
	static int i = 0;
	static char b[10];
	sprintf_s(b, "%d", i);
	static int Cx, Cy;
	switch (uMsg) {
	case WM_CREATE:
		hdc = GetDC(hwnd);
		SetTimer(hwnd, TIMER_SEC, 1000, 0);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &r);
		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_TIMER:
		i++;
		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case '+':
			SetTimer(hwnd, TIMER_SEC, 1000, 0);
			break;
		case '-':
			KillTimer(hwnd, 1);
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'S':
			if (GetAsyncKeyState(VK_CONTROL))
			{
				i = 0;
				InvalidateRect(hwnd, 0, 1);
			}

			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		Cx = (r.right - r.left) / 2;
		Cy = (r.bottom - r.top) / 2;
		Ellipse(hdc, Cx - 100, Cy - 100, Cx + 100, Cy + 100);
		DrawText(hdc,b, -1, &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		ReleaseDC(hwnd, hdc);
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hwnd, uMsg, wParam, lParam));
	}
	return (0);
}