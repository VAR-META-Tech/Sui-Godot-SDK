#include "sui_client.h"
#include "header/sui_lib.h"

char *SuiClient::apiVersion() {
	return api_version();
};

int SuiClient::checkApiVersion(void) {
	return check_api_version();
}

void SuiClient::freeErrorString(const char *error) {
	return free_error_string(error);
}
void SuiClient::freeStrings(CStringArray array) {
	return free_strings(array);
}

ResultCStringArray SuiClient::availableRpcMethods() {
	return available_rpc_methods();
}

ResultCStringArray SuiClient::availableSubscriptions() {
	return available_subscriptions();
}

int SuiClient::buildDevNetwork(void) {
	return buildDevnet();
}
int SuiClient::buildTestNetwork(void) {
	return buildTestnet();
}