#ifndef COMMON_CODE_H
#define COMMON_CODE_H

#include <windows.h>

#define RETURN_IF_FAILED(A) \
do { \
	if (!A) { \
		return FALSE; \
	} \
} while(0) \

#endif //COMMON_CODE_H
