#define _CRT_SECURE_NO_WARNINGS 1

#include "AnnotationConversion.h"

void Conversion(FILE *fIn, FILE *fOut)
{
	assert(fIn);
	assert(fOut);

	State tag = C_END;
	char fir, sec;
	while ((fir = fgetc(fIn)) != EOF)
	{
		switch (fir)
		{
		case '/':
			fputc('/', fOut);
			// 3.匹配问题
			if ((sec = fgetc(fIn)) == '*' && tag == C_END)
			{
				tag = C_BEGIN;
				fputc('/', fOut);
			}
			// 7.C++注释问题
			else if (sec == '/')
			{
				char next;
				fputc('/', fOut);
				do
				{
					next = fgetc(fIn);
					if (next != EOF)
					{
						fputc(next, fOut);
					}
				} while (next != '\n' && next != EOF);
			}
			else
			{
				fputc(sec, fOut);
			}
			break;
		case '*':
			if ((sec = fgetc(fIn)) == '/' && tag == C_BEGIN)
			{
				tag = C_END;
				// 2.换行问题
				char next = fgetc(fIn);
				if (next != '\n')
				{
					// 5.连续注释问题
					fputc('\n', fOut);
					if (next == '/')
					{
						fseek(fIn, -1, SEEK_CUR);
					}
					else
					{
						fputc(next, fOut);
					}
				}
				else
				{
					fputc('\n', fOut);
				}
			}
			// 6.连续的**/问题
			else if (sec == '*')
			{
				fputc('*', fOut);
				fseek(fIn, -1, SEEK_CUR);
			}
			else
			{
				fputc('*', fOut);
				fputc(sec, fOut);
			}
			break;
		// 4.多行注释问题
		case '\n':
			fputc('\n', fOut);
			if (tag == C_BEGIN)
			{
				fputc('/', fOut);
				fputc('/', fOut);
			}
			break;
		default:
			fputc(fir, fOut);
			break;
		}
	}

}

void AnnotationConversion(const char *readFile, const char *writeFile)
{
	assert(readFile);
	assert(writeFile);
	FILE *fIn, *fOut;
	fIn = fopen(readFile, "r");
	if (fIn == NULL)
	{
		printf("打开文件%s失败\nerrno: %d\n", readFile, errno);
		return;
	}
	fOut = fopen(writeFile, "w");
	if (fOut == NULL)
	{
		fclose(fIn);
		printf("打开文件%s失败\nerrno: %d\n", readFile, errno);
		return;
	}
	Conversion(fIn, fOut);
	fclose(fIn);
	fclose(fOut);
}
