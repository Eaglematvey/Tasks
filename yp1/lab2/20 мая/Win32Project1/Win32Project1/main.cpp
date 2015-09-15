#undef UNICODE 
#include<windows.h>
#include "resource.h"
#include<vector>
#include<string>
#include <cstdlib>
#include<string.h>
#include <iomanip>
using namespace std;
extern "C" char* _fastcall Sum(char*, char*);
extern "C" char*_fastcall Cats(char*, char*);

INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInstance;
int APIENTRY WinMain(HINSTANCE , HINSTANCE, LPTSTR , int )
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}
char c1[1000], c2[1000], res1[2000], res2[2000], temp1[1000], temp2[1000];

INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			
			MessageBox(hDlg, "The end!", "Info", MB_OK | MB_ICONINFORMATION);
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		case IDC_BUTTON2:
			strcpy_s(c1, "0");
			strcpy_s(c2, "0");
			strcpy_s(temp1, "00000000000000000000");
			strcpy_s(temp2, "00000000000000000000");
			GetDlgItemText(hDlg, IDC_EDIT1, c1, 1000);
			GetDlgItemText(hDlg, IDC_EDIT2, c2, 1000);
			Cats(temp1, c1);
			Cats(temp2, c2);
			SetDlgItemText(hDlg, IDC_EDIT3, Sum(temp1, temp2));
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}