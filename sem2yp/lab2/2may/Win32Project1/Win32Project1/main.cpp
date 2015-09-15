#undef UNICODE 
#include<windows.h>
#include "resource.h"
#include<vector>
#include<string>
#include <cstdlib>
#include <iomanip>
using namespace std;
INT_PTR CALLBACK DlgProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK DlgProc2(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

HINSTANCE hInstance;
int APIENTRY WinMain(HINSTANCE , HINSTANCE, LPTSTR , int )
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
	return 0;
}
char tmp[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};


INT_PTR CALLBACK DlgProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int myparam = 0, len;
	static char x2[33];
	static char chbuf[1000];
	static char x16[9];

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
		case IDC_BUTTON1:
			GetDlgItemText(hDlg, IDC_EDIT1, chbuf, 1000);
			_asm{
				   mov ebx, -1
					lea edi, chbuf
					mov ecx, -1
					mov al, 0
					repne scasb
					sub ebx, ecx
					dec ebx
					mov len,ebx
			}
			SetDlgItemInt(hDlg, IDC_EDIT3, len, false);
			break;
		case IDC_BUTTON2:
			myparam = GetDlgItemInt(hDlg, IDC_EDIT1,NULL,TRUE);
			_asm{
				mov ebx, myparam
				mov ecx,32
		   lp:
				shr ebx,1
				jc met1
				dec ecx
				mov dl, tmp[0]
				mov x2[ecx], dl
				inc ecx
			met2:
				loop lp
				jmp _end
			met1:
				dec ecx
				mov dl, tmp[1]
				mov x2[ecx], dl
				inc ecx
				jmp met2
			_end:
			}
			x2[32] = '\0';
			SetDlgItemText(hDlg, IDC_EDIT3, x2);
			break; 
		case IDC_BUTTON3:
			myparam = GetDlgItemInt(hDlg, IDC_EDIT1, NULL, TRUE);
			
			_asm{
				mov ecx, 8
				mov eax, myparam
				start:
				xor ebx, ebx
				shld ebx,eax,4
				rol eax, 4
				mov dl, tmp[ebx]
				mov ebx,8
				sub ebx,ecx
				mov x16[ebx],dl
				loop start
			}
			x16[8] = '\0';
			SetDlgItemText(hDlg, IDC_EDIT3, x16);
			break;
		case IDC_BUTTON4:
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG2), NULL, DlgProc2);
			break;
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

//string strarr[16];
char mas[10000];
INT_PTR CALLBACK DlgProc2(HWND hDlg2, UINT message, WPARAM wParam, LPARAM lParam)
{
	
	static int i = 1, j = 1, m = 0, temp = 0, numlen = 0;
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			_asm{
			mov i,1
		   
			xor ecx, ecx
		lpext:  
			mov j, 1
			lpin:
			 mov eax,i
			 mov ebx,j
			 xor edx,edx
			 mul ebx 
			 mov m,eax
		 met2 :
			 cmp m,0
			 jg met1

			 cmp numlen,1
			 je met3
		 met4:
			 cmp numlen,2
			 je met5
	    met6:
			 mov numlen,0
			mov mas[ecx], 32
			 inc ecx
			 inc j
			 cmp j,16
			 jl lpin
			 
		   mov mas[ecx], 13
		    inc ecx
		   mov mas[ecx],10
		   inc ecx
		   inc i
		   cmp i,16
		   jl lpext
			 
			 jmp _end
		 met1:
			 mov eax, m
			 xor edx, edx
			 mov ebx, 16
			 div ebx
			 mov m, eax
			 mov al, tmp[edx]
			 mov mas[ecx], al
			 inc ecx
			 inc numlen
			jmp met2
		met3:
			 dec ecx
			 mov  al, mas[ecx]
			 mov mas[ecx],32
		     inc ecx
			 mov mas[ecx], 32
			 inc ecx
			 mov mas[ecx],  al
			 inc ecx
			 jmp met4
		 met5:
			 dec ecx
			 mov al, mas[ecx]
			 dec ecx
			 mov bl, mas[ecx]
			 mov mas[ecx],al
			 inc ecx
			 mov mas[ecx],bl
			 inc ecx
			 jmp met6
		_end :
			 mov temp,ecx
			}
			mas[temp] = '\0';
			SetDlgItemText(hDlg2, IDC_EDIT1, mas);
			
			break;
		case IDCANCEL:
			EndDialog(hDlg2, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
