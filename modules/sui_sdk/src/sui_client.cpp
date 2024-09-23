#include "sui_client.h"

String SuiClient::apiVersion()
{
	char *version = api_version();
	return version;
};

int SuiClient::checkApiVersion()
{
	return check_api_version();
}

void SuiClient::freeErrorString(const char *error)
{
	return free_error_string(error);
}
void SuiClient::freeStrings(CStringArray array)
{
	return free_strings(array);
}

int SuiClient::buildDevNetwork(void)
{
	return buildDevnet();
}
int SuiClient::buildTestNetwork(void)
{
	return buildTestnet();
}