#ifndef SUI_BALANCE_CPP_H
#define SUI_BALANCE_CPP_H

#include <inttypes.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

extern "C" {

class SuiClient {
public:
	typedef struct
	{
		const char **data;
		int len;
	} CStringArray;

	// Struct to hold the result, either CStringArray or error message
	typedef struct
	{
		CStringArray strings;
		const char *error;
	} ResultCStringArray;

	void freeStrings(CStringArray array);
	void freeErrorString(const char *error);

	// SuiClient functions
	char *apiVersion();
	int checkApiVersion(void);
	ResultCStringArray availableRpcMethods();
	ResultCStringArray availableSubscriptions();

	int buildDevnet(void);
	int buildTestnet(void);
};
}

#endif // SUI_BALANCE_H
