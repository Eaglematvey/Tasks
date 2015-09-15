.386
.model flat, stdcall  ;32 bit memory model
option casemap :none  ;case sensitive

include proj2.2.inc

.code

start:

	invoke GetModuleHandle,NULL
	mov		hInstance,eax

    invoke InitCommonControls
	invoke DialogBoxParam,hInstance,IDD_DIALOG1,NULL,addr DlgProc,NULL
	invoke ExitProcess,0

;########################################################################

DlgProc proc hWin:HWND,uMsg:UINT,wParam:WPARAM,lParam:LPARAM

	mov		eax,uMsg
	.if eax==WM_INITDIALOG
	    invoke  GetDlgItem, hWin, IDC_LST1
        mov     hList, eax
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem1
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem2
        invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szStringItem3
        invoke  GetDlgItem, hWin, IDC_EDT1
        mov     hEdit, eax 


	.elseif eax==WM_COMMAND
	        mov     eax, wParam
            mov     bx, ax	; LOWORD(wParam) - control identifier
            shr       eax, 16	; HIWORD(wParam) -  notification code 
	    .if (bx==IDC_LST1) && (ax==LBN_SELCHANGE)
   	            invoke  SendMessage, hList, LB_GETCURSEL, 0, 0
   	            mov     nIndex,eax
   	            
                invoke  SendMessage, hList, LB_GETTEXT, nIndex, addr szBuffer
                 INVOKE    MessageBox, NULL, addr szBuffer, addr szBuffer, MB_OK 
   	            invoke  SendMessage, hEdit, WM_SETTEXT, 0, addr szBuffer
    	        pop     eax	   
    	 .endif 
    	.if(bx==IDC_BTN1)
    	       invoke GetDlgItemText,hWin,IDC_EDT1,addr szBuffer,50
    	      ; invoke GetWindowText,hEdit,addr szBuf,50
    	       INVOKE    MessageBox, NULL, addr szBuffer, addr szBuffer, MB_OK 
    	       invoke SetDlgItemText,hWin,IDC_LST1,addr szBuffer
    	       ;invoke SendMessage,hList,LB_ADDSTRING, 0,offset szBuf  
    	     	        
        .endif

    
	.elseif eax==WM_CLOSE
		invoke EndDialog,hWin,0
	.else
		mov		eax,FALSE
		ret
	.endif
	mov		eax,TRUE
	ret

DlgProc endp

end start
;MessageBox(HWND,lpChar,LpChar,UINT) MB_OK
;invoke MessageBox,addr szBuf, addr szBuf, MB_OK
;оконна€ процедура(HWND hWin,UINT uMsg, WPARAM wParam,

;.elseif eax==IDC_BTN1
    ;      invoke GetWindowText,hEdit,szBuffer,50
     ;     invoke  GetDlgItem, hWin, IDC_LST1
      ;  mov     hList, eax
       ; invoke  SendMessage, hList, LB_ADDSTRING, 0, offset szBuffer
       ; invoke  GetDlgItem, hWin, IDC_EDT1
       ; mov     hEdit, eax 
          
          
          
 ;LBN_SELCHANGE LB_ADDSTRING
 ; ўелчок по Button
 
 ;if(LOWORD(wParam)== IDC_BTN1)
 ;1)HWND GetDlgItem(HWND lDlg,UInT IDC
 ; GetWindowText(HWND,
 ;SendMessage(HWND ?hList?,uMsg,адрес буф wParam, длина буф lParam
 ; WM_GETTEXT
 ;2)GetDlgItem
 ;mov hEdit,eax
 ; invoke SendMessage,hEdit,WM_GETTEXT,300,addr szBuf
;3)GetDlgItemText
;?4)SendDlgItemMessage
;LB_GETCURSEL получить элемент списка
; -1 нету
;LB_DELETESTRING

;FileDialog
;1определить заполнить  структуру
;< ,  ,   , , ,>
;2вызвать
;3 выйти из диалога?


;скрыть командную кнопку
;1;n  dd  5
;2;WM_INITDIALOG 
;HWND CreateWindow(
;3;lParam - handle командной кнопки от которой пришло сообщение
;ShowWindow SW_HIDE

;strLen masm32
;lb_getcount
;lb_gettext
;lb_gettextlen
;dilogbox
