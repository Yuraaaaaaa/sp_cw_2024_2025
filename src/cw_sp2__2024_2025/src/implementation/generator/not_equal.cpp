#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: not_equal.cpp               *
*                                                  (draft!) *
*************************************************************/

#include "../../include/def.h"
#include "../../include/generator/generator.h"
#include "../../include/lexica/lexica.h"
#include "stdio.h"

unsigned char* makeIsNotEqualCode(struct LexemInfo** lastLexemInfoInTable, unsigned char* currBytePtr, unsigned char generatorMode) {
	unsigned char multitokenSize = detectMultiToken(*lastLexemInfoInTable, MULTI_TOKEN_NOT_EQUAL);
	if (multitokenSize) {
#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("\r\n");
		printf("    ;\"%s\"\r\n", tokenStruct[MULTI_TOKEN_NOT_EQUAL][0]);
#endif

		const unsigned char code__mov_eax_stackTopByECX[]   = { 0x8B, 0x01 };
		const unsigned char code__sub_ecx_4[]               = { 0x83, 0xE9, 0x04 };
		const unsigned char code__cmp_stackTopByECX_eax[]   = { 0x39, 0x01 };
		const unsigned char code__setne_al[]                = { 0x0F, 0x95, 0xC0 };
		const unsigned char code__and_eax_1[]               = { 0x83, 0xE0, 0x01 };
		const unsigned char code__mov_stackTopByECX_eax[]   = { 0x89, 0x01 };

		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_eax_stackTopByECX, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__sub_ecx_4, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__cmp_stackTopByECX_eax, 2);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__setne_al, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__and_eax_1, 3);
		currBytePtr = outBytes2Code(currBytePtr, (unsigned char*)code__mov_stackTopByECX_eax, 2);

#ifdef DEBUG_MODE_BY_ASSEMBLY
		printf("    mov eax, dword ptr[ecx]\r\n");
		printf("    sub ecx, 4\r\n");
		printf("    cmp dword ptr[ecx], eax\r\n");
		printf("    setne al\r\n");
		printf("    and eax, 1\r\n");
		printf("    mov dword ptr[ecx], eax\r\n");
#endif

		return *lastLexemInfoInTable += multitokenSize, currBytePtr;
	}

	return currBytePtr;
}