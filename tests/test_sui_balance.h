#ifndef TEST_SUI_SDK_BALANCE
#include "tests/test_tools.h"
#include "thirdparty/doctest/doctest.h"

#include "modules/sui_sdk/sui_sdk.h"

namespace TestSuiBalanceSDK {

TEST_CASE("Get Balance") {
	SuiSDK suiBalance;
	SuiSDK::Balance balance = suiBalance.getBalanceSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
	CHECK(balance.total_balance > (uint64_t *)0);
}

} //namespace TestSuiBalanceSDK

#endif