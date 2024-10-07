#include "sui_client.h"

/**
 * Main function
 */

String SuiClient::apiVersion()
{
	const char *version = api_version();
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
	return build_devnet();
}

int SuiClient::buildTestNetwork(void)
{
	return build_testnet();
}

int SuiClient::buildMainNetNetwork(void)
{
	return build_mainnet();
}