#ifndef TEST_SUI_TRANSACTION_SDK_H
#define TEST_SUI_TRANSACTION_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"
#include "thirdparty/doctest/doctest.h"

#include "modules/sui_sdk/sui_sdk.h"

namespace TestSuiTransactionSDK {

// TEST_CASE("Sign Transaction") {
// 	SuiSDK suiSDK;
// 	const char *sender = "0x66e350a92a4ddf98906f4ae1a208a23e40047105f470c780d2d6bec139031f75";
// 	const char *recipient = "0xfee0108a2467a551f50f3f7c2dc77128406ae314ef4515030dc62accb0c15bcc";
// 	unsigned long long amount = 1000000000;

// 	char *result = suiSDK.signTransaction(sender, recipient, amount);
// 	CHECK(result != NULL);
// }

} //namespace TestSuiTransactionSDK

#endif