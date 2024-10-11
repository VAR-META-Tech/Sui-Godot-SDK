#ifndef SUI_CLIENT_CPP_H
#define SUI_CLIENT_CPP_H
#include "../header/sui_lib.h"
#include "core/object/class_db.h"

extern "C"
{

	class SuiClient
	{
	public:
		void freeStrings(CStringArray array);
		void freeErrorString(const char *error);

		// SuiClient functions
		String apiVersion();
		int checkApiVersion();
		int buildDevNetwork();
		int buildTestNetwork();
		int buildMainNetNetwork();
	};
}

#endif // SUI_BALANCE_H
