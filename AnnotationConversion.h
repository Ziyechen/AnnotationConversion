#ifndef __ANNOTATIONCONVERSION_H__
#define __ANNOTATIONCONVERSION_H__

#include <stdio.h>
#include <assert.h>
#include <errno.h>

typedef enum State
{
	C_BEGIN,
	C_END
}State;

void AnnotationConversion(const char *FreadFile, const char *FwriteFile); //注释转换

#endif //__ANNOTATIONCONVERSION_H__
