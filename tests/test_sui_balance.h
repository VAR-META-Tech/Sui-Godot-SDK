#ifndef TEST_SUI_SDK_BALANCE
#include <stddef.h>
#include "tests/test_tools.h"
#include "thirdparty/doctest/doctest.h"

#include "modules/sui_sdk/sui_sdk.h"

namespace TestSuiBalanceSDK {

// TEST_CASE("Get balance sync") {
// 	SuiSDK suiSdk;
// 	SuiSDK::Balance balance = suiSdk.getBalanceSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(balance.total_balance > (long unsigned int*) 0);
// }

// TEST_CASE("Get balances") {
// 	SuiSDK suiSdk;
// 	SuiSDK::BalanceArray balances = suiSdk.getBalances("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(balances.balances !=NULL);
// }

// TEST_CASE("Get Aal balance sync"){
// 	SuiSDK suiSdk;
// 	SuiSDK::BalanceArray allBalances = suiSdk.getAllBalancesSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(allBalances.balances !=NULL);
// }

// TEST_CASE("Get coin sync"){
// 	SuiSDK suiSdk;
// 	SuiSDK::CCoinArray coins = suiSdk.getCoinsSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(coins.coins !=NULL);
// }


// TEST_CASE("Get total supply sync"){
// 	SuiSDK suiSdk;
// 	uint64_t totalSupply = suiSdk.getTotalSupplySync();
// 	CHECK(totalSupply >= (uint64_t) 0 );
// }

// TEST_CASE("free balance"){
// 	SuiSDK suiSdk;
// 	SuiSDK::Balance balance = suiSdk.getBalanceSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(balance.total_balance > (uint64_t*) 0);
// 	suiSdk.freeBalance(balance); 
// 	CHECK(balance != NULL);
// }


// TEST_CASE("free balance array"){
// 	SuiSDK suiSdk;
// 	SuiSDK::BalanceArray balances = suiSdk.getBalances("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(balances.balances !=NULL);
	
// 	suiSdk.freeBalanceArray(balances); 
// 	CHECK(balances.balances != NULL);
// }


// TEST_CASE("free coins array"){
// 	SuiSDK suiSdk;
// 	SuiSDK::CCoinArray coins = suiSdk.getCoinsSync("0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb");
// 	CHECK(coins.coins !=NULL);
	
// 	suiSdk.freeCoinArray(coins); 
// 	CHECK(coins.coins != NULL);
// }

} //namespace TestSuiBalanceSDK

#endif