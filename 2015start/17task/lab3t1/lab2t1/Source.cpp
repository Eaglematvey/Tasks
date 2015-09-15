#undef UNICODE

#include <windows.h>
#include <string>

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
	HDC hdc;
	PAINTSTRUCT ps;

	static RECT r;
	static string str = "Text";
	static LOGFONT lf;
	static HFONT f1;

	switch (uMsg) {
	case WM_CREATE:
		lf.lfCharSet = DEFAULT_CHARSET;
		lf.lfPitchAndFamily = DEFAULT_PITCH;
		strcpy_s(lf.lfFaceName, "Times New Roman");
		lf.lfHeight = 20;
		lf.lfWeight = FW_NORMAL;
		lf.lfEscapement = FE_FONTSMOOTHINGCLEARTYPE;
		f1 = CreateFontIndirect(&lf);
		break;
	case WM_SIZE:
		GetClientRect(hwnd, &r);
		InvalidateRect(hwnd, 0, 1);
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case '+':
			lf.lfHeight++;
			lf.lfWeight++;
			f1 = CreateFontIndirect(&lf);
			str += '+';
			InvalidateRect(hwnd, 0, 1);
			break;
		case '-':
			if (lf.lfHeight > 1)
				lf.lfHeight--;
				lf.lfWeight--;	
			f1 = CreateFontIndirect(&lf);
			str += '-';
			InvalidateRect(hwnd, 0, 1);
			break;
		default:
			break;
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		(HFONT)SelectObject(hdc, f1);
		DrawText(hdc, str.data(), str.size(), &r, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return (DefWindowProc(hwnd, uMsg, wParam, lParam));
	}
	return (0);
}