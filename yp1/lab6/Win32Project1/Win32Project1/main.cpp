#undef UNICODE 
#include<windows.h>
#include "resource.h"
#include <stdlib.h>
#include <iomanip>
extern "C" double _fastcall Calcsin(double*);
extern "C" double _fastcall Calccos(double*);
extern "C" double _fastcall Calcln(double*);
extern "C" int  _fastcall Calcnumdiv(double*);
using namespace std;
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);

HINSTANCE hInstance;
int APIENTRY WinMain(HINSTANCE , HINSTANCE, LPTSTR , int )
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}

void SetNum(HWND hDlg, int idc, char* str)
{
	char mas[100];
	GetDlgItemText(hDlg,idc,mas,100);
	strcat_s(mas, str);
	SetDlgItemText(hDlg, idc, mas);
}
void SetNewNum(HWND hDlg, int idc, char* str)
{
	char mas[100];
	strcpy_s(mas, str);
	SetDlgItemText(hDlg, idc, mas);
}
double SetVal1(HWND hDlg, int idc)
{
	double value1;
	char mas[1000];
	GetDlgItemText(hDlg, idc, mas, 1000);
	value1 = atof(mas);
	strcpy_s(mas, "");
	SetDlgItemText(hDlg, idc, mas);
	return value1;
}
void PrintNum(HWND hDlg, int idc, char* str,bool& newline)
{
	if (!newline)
		SetNum(hDlg, idc, str);
	else
	{
		newline = 0;
		SetNewNum(hDlg, idc, str);
	}
}
INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int No_operat = 0;
	static int temp;
	static char mas1[1000], mas2[1000];
	static double value1 = 0, value2 = 0, value3 = 0;
	static bool newline = 0;
	static int rep = 0;
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		   PrintNum(hDlg, IDC_EDIT1, "1",newline);
			break;
		case IDC_BUTTON2:
			PrintNum(hDlg, IDC_EDIT1, "2", newline);
			break; 
		case IDC_BUTTON3:
			PrintNum(hDlg, IDC_EDIT1, "3", newline);
			break;
		case IDC_BUTTON4:
			PrintNum(hDlg, IDC_EDIT1, "4", newline);
			break;
		case IDC_BUTTON5:
			PrintNum(hDlg, IDC_EDIT1, "5", newline);
			break;
		case IDC_BUTTON6:
			PrintNum(hDlg, IDC_EDIT1, "6", newline);
			break;
		case IDC_BUTTON7:
			PrintNum(hDlg, IDC_EDIT1, "7", newline);
			break;
		case IDC_BUTTON8:
			PrintNum(hDlg, IDC_EDIT1, "8", newline);
			break;
		case IDC_BUTTON9:
			PrintNum(hDlg, IDC_EDIT1, "9", newline);
			break;
		case IDC_BUTTONZ:
			PrintNum(hDlg, IDC_EDIT1, "0", newline);
			break; 
		case IDC_BUTTONP:
			PrintNum(hDlg, IDC_EDIT1, ".", newline);
				break;
		case IDC_BUTTON10:
			rep = 0;
			value1 = SetVal1(hDlg, IDC_EDIT1);
			No_operat = 1;
			break;   
		case IDC_BUTTON11:
			rep = 0;
			value1 = SetVal1(hDlg, IDC_EDIT1);
			No_operat = 2;
			break;
		case IDC_BUTTON12:
			rep = 0;
			value1 = SetVal1(hDlg, IDC_EDIT1);
			No_operat = 3;
			break;
		case IDC_BUTTON13:
			rep = 0;
			value1 = SetVal1(hDlg, IDC_EDIT1);
			No_operat = 4;
			break;
		case IDC_BUTTONE:
			value2 = SetVal1(hDlg, IDC_EDIT1);
			if (!No_operat) break;
			
			newline = 1;
			if (No_operat == 1)
			{
				if (rep==1) swap(value2, value3);
				value1 += value2;
				rep = 1;
			}
				
			else if (No_operat == 2)
			{
				if (rep == 2) swap(value2, value3);
				value1 -= value2;
				rep = 2;
			}
			else if (No_operat == 3)
			{
				if (rep == 3) swap(value2, value3);
				value1 *= value2;
				rep = 3;
			}
			else if (No_operat == 4)
			{
				if (rep == 4) swap(value2, value3);
				value1 /= value2;
				rep = 4;
			}
			value3 = value2;
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON14: //ce
			value1 = 0;
			strcpy_s(mas1, "");
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON15: // <---
			GetDlgItemText(hDlg, IDC_EDIT1, mas2, 100);
			strncpy_s(mas1, mas2, strlen(mas2) - 1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON16:// sqrt
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			value1 = sqrt(value1);
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON17:  //sin
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			value1 = Calcsin(&value1); 
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON18: //ln
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			value1 = Calcln(&value1);
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON19://+/-
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			value1 = 0-value1;
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON20:// cos
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			value1 = Calccos(&value1);
			sprintf_s(mas1, "%f", value1);
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDC_BUTTON21:// Number of dividers (arithmetic function)  
			value1 = SetVal1(hDlg, IDC_EDIT1);
			newline = 1;
			temp = Calcnumdiv(&value1);
			SetDlgItemInt(hDlg, IDC_EDIT1, temp,false);
			break;
		case IDC_BUTTON22: //c
			No_operat = 0;
			strcpy_s(mas1, "");
			SetDlgItemText(hDlg, IDC_EDIT1, mas1);
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
