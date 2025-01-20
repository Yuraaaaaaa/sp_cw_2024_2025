#define _CRT_SECURE_NO_WARNINGS
/************************************************************
* N.Kozak // Lviv'2024-2025 // cw_sp2__2024_2025            *
*                         file: preparer.hxx                *
*                                                  (draft!) *
*************************************************************/

#include "../../../src/include/preparer/preparer.h"

#include "../../../src/include/def.h"
#include "../../../src/include/config.h"
#include "../../../src/include/lexica/lexica.h"
#include "../../../src/include/syntax/syntax.h"
#include "../../../src/include/semantix/semantix.h"
#include "../../../src/include/generator/generator.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int precedenceLevel(char* lexemStr) {
	if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_NOT][0], MAX_LEXEM_SIZE)) {		
		return 6;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_AND][0], MAX_LEXEM_SIZE)) {		
		return 5;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_MUL][0], MAX_LEXEM_SIZE)) {	
		return 5;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_DIV][0], MAX_LEXEM_SIZE)) {		
		return 5;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_MOD][0], MAX_LEXEM_SIZE)) {	
		return 5;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_OR][0], MAX_LEXEM_SIZE)) {	
		return 4;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_ADD][0], MAX_LEXEM_SIZE)) {
		return 4;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_SUB][0], MAX_LEXEM_SIZE)) {
		return 4;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_EQUAL][0], MAX_LEXEM_SIZE)) {
		return 3;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_NOT_EQUAL][0], MAX_LEXEM_SIZE)) {
		return 3;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_LESS_OR_EQUAL][0], MAX_LEXEM_SIZE)) {
		return 3;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_GREATER_OR_EQUAL][0], MAX_LEXEM_SIZE)) {
		return 3;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_RLBIND][0], MAX_LEXEM_SIZE)) {
		return 2;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)) {
		return 1;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_OUTPUT][0], MAX_LEXEM_SIZE)) {
		return 1;
	}

	return 0;

}

bool isLeftAssociative(char* lexemStr) {
	if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_AND][0], MAX_LEXEM_SIZE)) {	
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_MUL][0], MAX_LEXEM_SIZE)) {	
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_DIV][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_MOD][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_OR][0], MAX_LEXEM_SIZE)) {	
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_ADD][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_SUB][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_EQUAL][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_NOT_EQUAL][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_LESS_OR_EQUAL][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_GREATER_OR_EQUAL][0], MAX_LEXEM_SIZE)) {
		return true;
	}

	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_RLBIND][0], MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_NOT][0], MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)) {
		return false;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_OUTPUT][0], MAX_LEXEM_SIZE)) {
		return false;
	}

	return false;
}

bool isSplittingOperator(char* lexemStr) {
	if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)) {
		return true;
	}
	else if (!strncmp(lexemStr, tokenStruct[MULTI_TOKEN_OUTPUT][0], MAX_LEXEM_SIZE)) {
		return true;
	}

	return false;
}

void makePrepare4IdentifierOrValue(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) { // 
	if ((*lastLexemInfoInTable)->tokenType == IDENTIFIER_LEXEME_TYPE || (*lastLexemInfoInTable)->tokenType == VALUE_LEXEME_TYPE) {
		int prevNonOpenParenthesesIndex = -1;
		for (; !strncmp((*lastLexemInfoInTable)[prevNonOpenParenthesesIndex].lexemStr, "(", MAX_LEXEM_SIZE); --prevNonOpenParenthesesIndex);
		if (!strncmp((*lastLexemInfoInTable)[1].lexemStr, tokenStruct[MULTI_TOKEN_RLBIND][0], MAX_LEXEM_SIZE)
			||
			//!strncmp((*lastLexemInfoInTable)[-1].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)
			//||
			//!strncmp((*lastLexemInfoInTable)[-2].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)
			//||
			!strncmp((*lastLexemInfoInTable)[prevNonOpenParenthesesIndex].lexemStr, tokenStruct[MULTI_TOKEN_INPUT][0], MAX_LEXEM_SIZE)
			) {
			bool findComplete = false;
			for (unsigned long long int index = 0; identifierIdsTable[index][0] != '\0'; ++index) {
				if (!strncmp((*lastLexemInfoInTable)->lexemStr, identifierIdsTable[index], MAX_LEXEM_SIZE)) {
					findComplete = true;
					(*lastTempLexemInfoInTable)->ifvalue = /*dataOffset + */VALUE_SIZE * /*(unsigned long long int)*/index;
					_itoa((*lastTempLexemInfoInTable)->ifvalue, (*lastTempLexemInfoInTable)->lexemStr, 10);
					((*lastTempLexemInfoInTable)++)->tokenType = VALUE_LEXEME_TYPE; // ADDRESS_LEXEME_TYPE
					++* lastLexemInfoInTable;
				}
			}
			if (!findComplete) {
				printf("\r\nError!\r\n");
				exit(0);
			}
		}
		else {
			*(*lastTempLexemInfoInTable)++ = *(*lastLexemInfoInTable)++;
		}
	}
}

void makePrepare4Operators(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if (precedenceLevel((*lastLexemInfoInTable)->lexemStr)) {
		while (lexemInfoTransformationTempStackSize > 0) {
			struct LexemInfo/*&*/ currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
			if (precedenceLevel(currLexemInfo.lexemStr) && (
				(isLeftAssociative((*lastLexemInfoInTable)->lexemStr) && (precedenceLevel((*lastLexemInfoInTable)->lexemStr) <= precedenceLevel(currLexemInfo.lexemStr)))
				||
				(!isLeftAssociative((*lastLexemInfoInTable)->lexemStr) && (precedenceLevel((*lastLexemInfoInTable)->lexemStr) < precedenceLevel(currLexemInfo.lexemStr)))
				)) {

				**lastTempLexemInfoInTable = currLexemInfo; ++* lastTempLexemInfoInTable;
				--lexemInfoTransformationTempStackSize;
			}
			else {
				break;
			}
		}

		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = *((*lastLexemInfoInTable)++);
	}
}

void makePrepare4LeftParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if ((*lastLexemInfoInTable)->lexemStr[0] == '(') {
		lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize++] = *((*lastLexemInfoInTable)++);
	}
}

void makePrepare4RightParenthesis(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	if ((*lastLexemInfoInTable)->lexemStr[0] == ')') {
		bool findLeftParenthesis = false;
		while (lexemInfoTransformationTempStackSize > 0) {
			struct LexemInfo/*&*/ currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
			if (currLexemInfo.lexemStr[0] == '(') {
				findLeftParenthesis = true;
				break;
			}
			else {
				**lastTempLexemInfoInTable = currLexemInfo; ++* lastTempLexemInfoInTable;
				lexemInfoTransformationTempStackSize--;
			}
		}
		if (!findLeftParenthesis) {
			printf("Warning: parentheses mismatched\n");

			**lastTempLexemInfoInTable = **lastLexemInfoInTable; ++* lastTempLexemInfoInTable;
		}
		else {
			--lexemInfoTransformationTempStackSize;
		}

		++* lastLexemInfoInTable;
	}
}

unsigned int makePrepareEnder(struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	unsigned int addedLexemCount = (unsigned int)lexemInfoTransformationTempStackSize;
	while (lexemInfoTransformationTempStackSize > 0) {
		struct LexemInfo/*&*/ currLexemInfo = lexemInfoTransformationTempStack[lexemInfoTransformationTempStackSize - 1];
		if (currLexemInfo.lexemStr[0] == '(' || currLexemInfo.lexemStr[0] == ')') {
			printf("Error: parentheses mismatched\n");
			exit(0);
		}

		**lastTempLexemInfoInTable = currLexemInfo, ++(*lastTempLexemInfoInTable); // *(*lastTempLexemInfoInTable)++ = currLexemInfo;
		--lexemInfoTransformationTempStackSize;
	}

	(*lastTempLexemInfoInTable)->lexemStr[0] = '\0';
	return addedLexemCount;
}

long long int getPrevNonParenthesesIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex) {
	if (!currIndex) {
		return currIndex;
	}

	long long int index = currIndex - 1;
	for (; index != ~0 && (
		lexemInfoInTable[index].lexemStr[0] == '('
		|| lexemInfoInTable[index].lexemStr[0] == ')'
		);
		--index);

	return index;
}

long long int getEndOfNewPrevExpressioIndex(struct LexemInfo* lexemInfoInTable, unsigned long long currIndex) {
	if (!currIndex) { //  || lexemInfoInTable[currIndex - 1].lexemStr[0] != '('
		return currIndex;
	}

	long long int index = currIndex - 1;
	for (; index != ~0 && lexemInfoInTable[index].lexemStr[0] == '(';
		--index);

	return index;
}

unsigned long long int getNextEndOfExpressionIndex(struct LexemInfo* lexemInfoInTable, unsigned long long prevEndOfExpressionIndex) {
	bool isPreviousExpressionComplete = false;

	for (unsigned long long int index = prevEndOfExpressionIndex + 2; lexemInfoInTable[index].lexemStr[0] != '\0'; ++index) {

		if (!strncmp(lexemInfoInTable[index].lexemStr, "(", MAX_LEXEM_SIZE) || !strncmp(lexemInfoInTable[index].lexemStr, ")", MAX_LEXEM_SIZE)) {
			continue;
		}

		long long int prevNonParenthesesIndex = getPrevNonParenthesesIndex(lexemInfoInTable, index);

		if (lexemInfoInTable[index].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[index].tokenType == VALUE_LEXEME_TYPE) {
			if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (precedenceLevel(lexemInfoInTable[index].lexemStr) && isLeftAssociative(lexemInfoInTable[index].lexemStr)) {
			if (precedenceLevel(lexemInfoInTable[prevNonParenthesesIndex].lexemStr)) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (isSplittingOperator(lexemInfoInTable[index].lexemStr)) {
			if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE) {
				return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);
			}
		}
		else if (lexemInfoInTable[index].tokenType != IDENTIFIER_LEXEME_TYPE && lexemInfoInTable[index].tokenType != VALUE_LEXEME_TYPE && !precedenceLevel(lexemInfoInTable[index].lexemStr)) {
			 if (lexemInfoInTable[prevNonParenthesesIndex].tokenType == IDENTIFIER_LEXEME_TYPE || lexemInfoInTable[prevNonParenthesesIndex].tokenType == VALUE_LEXEME_TYPE || precedenceLevel(lexemInfoInTable[prevNonParenthesesIndex].lexemStr)) {
				     return getEndOfNewPrevExpressioIndex(lexemInfoInTable, index);			
			 }
		}
	}

	return ~0;
}

void makePrepare(struct LexemInfo* lexemInfoInTable, struct LexemInfo** lastLexemInfoInTable, struct LexemInfo** lastTempLexemInfoInTable) {
	unsigned long long int nullStatementIndex = 0;
	unsigned long long int passMakePrepareElementCount = getDataSectionLastLexemIndex(*lastLexemInfoInTable, &grammar);
	if (passMakePrepareElementCount++ == ~0) {
		printf("Error: bad section!\r\n");
		exit(0);
	}

//	*lastLexemInfoInTable += lastDataSectionLexemIndex;
//	while (lastDataSectionLexemIndex--) {
//	
//	}
//
//	for (; false && (*lastLexemInfoInTable)->lexemStr[0] != '\0'; *(*lastTempLexemInfoInTable)++ = *(*lastLexemInfoInTable)++) {
//		if (passMakePrepareElementCount) {
//			--passMakePrepareElementCount;
//			++lexemInfoInTable;
//			continue;
//		}
//		else {
//			break;
//		}
//	}

	lexemInfoTransformationTempStackSize = 0;
	for (; (*lastLexemInfoInTable)->lexemStr[0] != '\0'; *(*lastTempLexemInfoInTable)++ = *(*lastLexemInfoInTable)++) {
		if (passMakePrepareElementCount) {
			--passMakePrepareElementCount;
			++lexemInfoInTable;
			continue;
		}

		for (struct LexemInfo* lastLexemInfoInTable_ = NULL; lastLexemInfoInTable_ != *lastLexemInfoInTable;) {

			lastLexemInfoInTable_ = *lastLexemInfoInTable;
			makePrepare4IdentifierOrValue(lastLexemInfoInTable, lastTempLexemInfoInTable);
			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4Operators(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4LeftParenthesis(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ == *lastLexemInfoInTable)
				makePrepare4RightParenthesis(lastLexemInfoInTable, lastTempLexemInfoInTable);

			if (lastLexemInfoInTable_ != *lastLexemInfoInTable
				&& (!nullStatementIndex || (lexemInfoInTable + nullStatementIndex == lastLexemInfoInTable_))) {
				if (nullStatementIndex != ~0) {
					if (nullStatementIndex) {
//						printf("Added null statement after %lld(lexem index)\r\n", nullStatementIndex);
						makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);
						(void)createMultiToken(lastTempLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
					}

					nullStatementIndex = getNextEndOfExpressionIndex(lexemInfoInTable, nullStatementIndex);
				}
			}

		}

		makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);

		if ((!nullStatementIndex || (lexemInfoInTable + nullStatementIndex == *lastLexemInfoInTable))) {
			if (nullStatementIndex != ~0) {
				if (nullStatementIndex) {
//					printf("Added null statement after %lld(lexem index)\r\n", nullStatementIndex);
					makePrepareEnder(lastLexemInfoInTable, lastTempLexemInfoInTable);
					(void)createMultiToken(lastTempLexemInfoInTable, MULTI_TOKEN_NULL_STATEMENT);
				}

				nullStatementIndex = getNextEndOfExpressionIndex(lexemInfoInTable, nullStatementIndex);
			}
		}

	}
}