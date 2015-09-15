.386
    .model flat, stdcall    ;    language type=stdcall - передача параметров - справа налево
    ;option casemap :none
    
include kernel32.inc    	; ExitProcess
include user32.inc      	; MessageBox

includelib kernel32.lib
includelib user32.lib
    
    .data
hello_title     db  "First win32 GUI program", 0
hello_message   db  "Hello world!", 0

    .code
start:
    push    0h     		; MB_OK is defined in windows.inc
    push    offset hello_title
    push    offset hello_message
    push    0
    call    MessageBox
    
    push    0
    call    ExitProcess
    ;invoke  ExitProcess, 0
    
end start

