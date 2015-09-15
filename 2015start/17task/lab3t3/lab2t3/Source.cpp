#undef UNICODE

#include <windows.h>
#include <vector>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
char szClassName[] = "ClassName";

struct Points
{
	int  Cx, Cy, r;
	Points(int a, int b, int c) :Cx(a), Cy(b), r(c){};
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE HPrevInst, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hWnd;
	MSG msg;
	WNDCLASS wcApp;

	// Заполняем структуру класса окна 
	wcApp.lpszClassName = szClassName;
	wcApp.hInstance = hInstance;
	wcApp.lpfnWndProc = WndProc;
	wcApp.hCursor = LoadCursor(NULL, IDC_CROSS);
	wcApp.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcApp.lpszMenuName = 0;
	wcApp.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcApp.style = CS_HREDRAW | CS_VREDRAW;
	wcApp.cbClsExtra = 0;
	wcApp.cbWndExtra = 0;

	// Регистрируем класс окна
	if (!RegisterClass(&wcApp)){
		MessageBox(NULL, "Class hasn't been registered", "RegisterClass", MB_OK);
		return 0;
	}

	hWnd = CreateWindow(szClassName, "Simple Windows Program", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, 0, 0, 0, hInstance, 0);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	while (GetMessage(&msg, 0, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	static std::vector<Points> curve;
	std::vector<Points>::iterator it;
	static int lw, hw, r;
	static HDC hDC;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (uMsg) {
	case WM_CREATE:
		hDC = GetDC(hWnd);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		for (auto c:curve)
		  Ellipse(hdc, c.Cx - c.r, c.Cy - c.r, c.Cx + c.r, c.Cy + c.r);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		ReleaseDC(hWnd, hDC);
		break;
	case WM_LBUTTONDOWN:
		lw = LOWORD(lParam),
	    hw = HIWORD(lParam);
		r = 50;
		it = curve.end();
		if (!curve.empty())
		{
			it--;
			for (;;)
			{
				if ((lw - it->Cx)*(lw - it->Cx) + (hw - it->Cy)*(hw - it->Cy) < it->r*it->r)
				{
					r = it->r + 50;
					lw = it->Cx;
					hw = it->Cy;
					curve.erase(it);
					InvalidateRect(hWnd, NULL, TRUE);
					break;
				}
	     		if(it>curve.begin()) 
					it--;
				else break;
			} 
	
		}
		curve.push_back(Points(lw, hw,r));
		Ellipse(hDC, lw-r, hw-r, lw+r, hw+r);
		break;
	default:
		return (DefWindowProc(hWnd, uMsg, wParam, lParam));
	}
	return (0);
}
