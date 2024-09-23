#ifndef SUI_CLIENT_CPP_H
#define SUI_CLIENT_CPP_H
#include "../header/sui_lib.h"


extern "C" {

class SuiClient {
public:

	void freeStrings(CStringArray array);
	void freeErrorString(const char *error);

	// SuiClient functions
	char *apiVersion();
	int checkApiVersion(void);
	ResultCStringArray availableRpcMethods();
	ResultCStringArray availableSubscriptions();

	int buildDevNetwork(void);
	int buildTestNetwork(void);
};
}

#endif // SUI_BALANCE_H
