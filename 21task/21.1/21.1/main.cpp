#undef UNICODE
#include<iostream>

using namespace std;

int main()
{
	char _str[1000], res[100];
	int  _strl = -1, n;
	cout << "Enter string:";
	cin.getline(_str, 1000);
		_asm
	{
	   cld            ;// counting _strl - length of _str
	   lea edi, [_str]
	   mov ecx,-1
	   mov al,0
	   repne scasb
	   sub _strl,ecx
	   mov ecx, _strl
	   dec _strl
	   jz _end
	   cmp _strl,1
	   je _end
	   lea esi, [_str]
	   xor ebx,ebx
	   xor edx,edx
   lpext:
	   inc edx
	   mov ecx, 1;//loading the next element 
	   repne lodsb   
	   mov ecx,ebx
	   inc ecx
	   lea edi, [res] ; //if element have been marked as repeated
	   repne scasb
	   cmp ecx,0
	   jne _jpr
	   lea edi, [_str + edx] ;// looking for  element to be equal 
	   mov ecx, _strl
	   repne scasb
	   cmp ecx,0
	   jne _jp
   _jpr:
	   dec _strl
	   mov ecx,_strl
	   loop lpext

	   mov n,ebx

	   jmp _end
   _jp:             ;//if there is new repeating element
	   mov  res[ebx], al;// it goes to res[n]
		inc ebx
		jmp _jpr
	_end:
	}
	   for (int i = 0; i < n;i++)
	     cout << char(res[i]) << endl;
	return 0;
}