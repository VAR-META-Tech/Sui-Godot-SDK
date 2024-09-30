#ifndef TEST_SUI_SDK_BALANCE
#define TEST_SUI_SDK_BALANCE

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiBalanceSDK
{
	String wallet = "0x0d000320903ccdb00281bc30a568af9b546ec4ef8d748f352f8c31ad08442fdb";

	TEST_CASE("Get balance sync")
	{
		SuiSDK suiSdk;
		Ref<BalanceWrapper> balance = suiSdk.getBalanceSync(wallet);
		CHECK(balance->get_total_balance() != "");
	}

	TEST_CASE("Get balances")
	{
		SuiSDK suiSdk;
		TypedArray<BalanceWrapper> balances = suiSdk.getBalances(wallet);
		CHECK(balances.size() != (const int)0);
	}

	TEST_CASE("Get All balance sync")
	{
		SuiSDK suiSdk;
		TypedArray<BalanceWrapper> balances = suiSdk.getAllBalancesSync(wallet);
		CHECK(balances.size() != (const int)0);
	}

	TEST_CASE("Get coin sync")
	{
		SuiSDK suiSdk;
		TypedArray<CoinWrapper> coins = suiSdk.getCoinsSync(wallet);
		CHECK(coins.size() != (const int)0);
	}

	TEST_CASE("Get total supply sync")
	{
		SuiSDK suiSdk;
		String totalSupply = suiSdk.getTotalSupplySync();
		CHECK(totalSupply != "");
	}
} // namespace TestSuiBalanceSDK

#endif