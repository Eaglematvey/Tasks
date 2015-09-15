#include<iostream>

long long arrmult[10000];

int main()
{
	long long temp = 0;
	int nplm = 0,
		nm = 0,
		n, m;
	int arr1[1000], arr2[1000], arrsum[1000];
	std::cout << "Enter n:" << std::endl;
	std::cin >> n;
	std::cout << "Enter m:" << std::endl;
	std::cin >> m;
	std::cout << "Enter arr1:" << std::endl;
	for (int i = 0; i < n; i++)
		std::cin >> arr1[i];
	std::cout << "Enter arr2:" << std::endl;
	for (int i = 0; i < m; i++)
		std::cin >> arr2[i];
	_asm{
		mov ecx, n
		cmp ecx, m
		jg ngreaterm
		mov ecx,m
	ngreaterm:
		cmp ecx,0
		jle endprog
	
		xor esi,esi
	lp1sum :
		mov arrsum[esi*4],0
		cmp esi, n
		jge jmp1
		mov eax, arr1[esi * 4]
		add arrsum[esi * 4], eax
	jmp1:
		cmp esi, m
		jge jmp2
		mov eax, arr2[esi * 4]
		add arrsum[esi * 4], eax
	jmp2:
		inc esi
		cmp esi,ecx
		jl lp1sum

		mov nplm,esi
		xor esi, esi
		xor edi,edi
		cmp n,0
		jle endprog
		cmp m,0
		jle endprog
	lp1mul :
	lp2mul :
	   mov eax, arr1[esi * 4]
	   cdq
	   imul arr2[edi * 4]
	   mov ebx,esi
	   add ebx,edi
	   add dword ptr arrmult[ebx * 8],eax
	   adc dword ptr arrmult[ebx*8 + 4],edx
		inc edi
		cmp edi,m
		jl lp2mul

		xor edi,edi
		inc esi
		cmp esi, n
		jl lp1mul
		
		mov nm,ebx
	endprog:
	}
	std::cout << "Sum:" << std::endl;
	    for (int i = 0; i < nplm; i++)
	        std::cout << arrsum[i] << std::endl;
	std::cout << "Mult:" << std::endl;
	for (int i = 0; i <= nm; i++)
		std::cout << arrmult[i] << std::endl;
	return 0;
}