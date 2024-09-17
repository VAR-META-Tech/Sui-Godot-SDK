#include "sui_client.h"
#include "header/sui_lib.h"

char *SuiClient::apiVersion() {
	return api_version();
};

int SuiClient::checkApiVersion(void arg) {
	return check_api_version(arg);
}

void SuiClient::freeErrorString(const char *error) {
	return free_error_string(error);
}
void SuiClient::freeStrings(SuiClient::CStringArray array) {
	return free_strings(array);
}

SuiClient::ResultCStringArray SuiClient::availableRpcMethods() {
	return available_rpc_methods();
}

SuiClient::ResultCStringArray SuiClient::availableSubscriptions() {
	return available_subscriptions();
}

int SuiClient::buildDevnet(void) {
	return build_devnet();
}
int SuiClient::buildTestnet(void) {
	return build_testnet();
}