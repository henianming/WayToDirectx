#ifndef COMMON_CODE_H
#define COMMON_CODE_H

#include <Windows.h>

#define SAFEDELETE(a) \
do{ \
	if (a) { \
		delete (a); \
	} \
}while(0) \

#define SAFEDELETENULL(a) \
do{ \
	if (a) { \
		delete (a); \
		(a) = NULL; \
	} \
}while(0) \

#define UNUSED(a) ((void)(a))

#define RETURN_IF_FAILED(A) \
do { \
	if (!A) { \
		return FALSE; \
	} \
} while(0) \

#endif //COMMON_CODE_H
