#ifndef SUI_CLIENT_H
#define SUI_CLIENT_H

#include <inttypes.h>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <string>

extern "C" {

class SuiClient {
public:
	struct CStringArray {
		const char **data;
		int len;
	};

	struct ResultCStringArray {
		CStringArray strings;
		const char *error;
	};
	static void free_strings(CStringArray array);
	static void free_error_string(const char *error);

	static char *api_version();
	static int check_api_version(void);
	static ResultCStringArray available_rpc_methods();
	static ResultCStringArray available_subscriptions();

	static int buildDevnet(void);
	static int buildTestnet(void);
};
}
// extern "C"

#endif // SUI_CLIENT_H
