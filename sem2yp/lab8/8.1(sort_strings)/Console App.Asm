.586
.model flat, stdcall                    
option casemap :none

include windows.inc     ; always first

include masm32.inc
include gdi32.inc
include user32.inc
include kernel32.inc

includelib masm32.lib
includelib gdi32.lib
includelib user32.lib
includelib kernel32.lib

.data
    szHelloWorld        db   "Press ENTER to continue...", 13, 10, 0
    buf                 db  300 dup(' ')
    Space DB " ",0
M DD 2
N DD 2
MN DD ?
STREND  DB      13,10,0            
NAMETEMP DB     20 DUP(' '),0
ENDADDR DD     ?
MESSG1  DB      "Enter one by one:",13,10,0
MESSG2  DB      "Number of rows?",13,10,0
MESSG3  DB      "Number of cols?",13,10,0
NAMECTR DB      0
NAMETAB DB      30 DUP(20 DUP(' ')) ;Таблица имен
NAMESAV DB      20 DUP(?), 13, 10, 0
SWAPPED DB      0
.code

MainProc	proc
       
        CLD
        Invoke StdOut,addr MESSG2
        Invoke StdIn,addr buf,300
        Invoke atol,addr buf
        mov M,EAX
        Invoke StdOut,addr MESSG3
        Invoke StdIn,addr buf,300
        Invoke atol,addr buf
        mov N,EAX
        LEA     EDI,NAMETAB
        XOR EDX,EDX
        MUL M
        CMP EAX,0
        JE _END
        MOV MN,EAX
        Invoke StdOut,addr MESSG1
        MOV ECX,MN
        
A20LOOP:
        PUSH ECX
        PUSH EDI
        Invoke StdIn,ADDR NAMESAV,20
        Invoke StripLF, ADDR NAMESAV
        POP EDI
        MOV ECX,10
        LEA ESI, NAMESAV
        REP MOVSW
        POP ECX
        INC NAMECTR
        LOOP A20LOOP
A30:                            
        CMP     NAMECTR,1      ;Введено менее 2 имен?
        JBE     A40             ; да - выйти
        CALL    G10SORT         ;Сортировать имена
A40: 
       Invoke StdOut,ADDR STREND
       LEA ESI,NAMETAB
       MOV ECX,M
A45LOOP:
        PUSH ECX
        MOV ECX,N
A50LOOP: 
       LEA EDI,NAMETEMP
       PUSH ECX
       MOV ECX,10
       REP MOVSW
       PUSH ESI
       Invoke StdOut,ADDR NAMETEMP
       Invoke StdOut,ADDR Space
       POP ESI
       POP ECX
       LOOP A50LOOP
      
       Invoke StdOut,ADDR STREND
       POP ECX
       LOOP A45LOOP
A60:
_END:         
            invoke  StdOut, addr szHelloWorld
            invoke  StdIn, addr buf, 300
            invoke  ExitProcess, 0
MainProc    endp

;               Сортировка имен в таблице:
;               -------------------------
G10SORT PROC
        SUB     EDI,40           ;Установить адреса останова
        MOV     ENDADDR,EDI
G20:
        MOV     SWAPPED,0      ;Установить начало
        LEA     ESI,NAMETAB      ; таблицы
G30:
        MOV     ECX,20           ;Длина сравнения
        MOV     EDI,ESI
        ADD     EDI,20           ;Следующее имя для сравнения
        MOV     EAX,EDI
        MOV     EBX,ESI
        REPE CMPSB              ;Сравнить имя со следующим
        JBE     G40             ; нет перестановки
        CALL    H10XCHG         ; перестановка
G40:
        MOV     ESI,EAX
        CMP     ESI,ENDADDR      ;Конец таблицы?
        JBE     G30             ; нет - продолжить
        CMP     SWAPPED,0      ;Есть перестановки?
        JNZ     G20             ; да - продолжить,
        RET                     ; нет - конец сортировки
G10SORT ENDP
;               Перестановка элементов таблицы:
;               ------------------------------
H10XCHG PROC
        MOV     ECX,10
        LEA     EDI,NAMESAV
        MOV     ESI,EBX
        REP MOVSW               ;Сохранить меньший элемент

        MOV     ECX,10
        MOV     EDI,EBX
        REP MOVSW               ;Переслать больший элемент
                                ; на место меньшего
        MOV     ECX,10
        LEA     ESI,NAMESAV 
        REP MOVSW               ;Переслать сохраненный
                                ; элемент на место большего
        MOV     SWAPPED,1      ;Признак перестановки
        RET
H10XCHG ENDP
end MainProc
