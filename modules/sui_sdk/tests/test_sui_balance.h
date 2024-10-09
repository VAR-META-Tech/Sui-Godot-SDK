#ifndef TEST_SUI_SDK_BALANCE
#define TEST_SUI_SDK_BALANCE

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiBalanceSDK
{
	SuiSDK suiSDK;

	TEST_CASE("Get balance sync")
	{
		Ref<WalletWrapper> wallet;
		TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
		if (wallets.size() == 0)
		{
			wallet = suiSDK.generateWallet("ed25519", "word12");
		}
		else
		{
			wallet = wallets[0];
		}

		Ref<BalanceWrapper> balance = suiSDK.getBalanceSync(wallet->address);
		CHECK(balance->total_balance == "0");
	}

	TEST_CASE("Get balances")
	{
		Ref<WalletWrapper> wallet;
		TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
		if (wallets.size() == 0)
		{
			wallet = suiSDK.generateWallet("ed25519", "word12");
		}
		else
		{
			wallet = wallets[0];
		}
		TypedArray<BalanceWrapper> balances = suiSDK.getBalances(wallet->address);
		int emptySize = 0;
		CHECK(balances.size() == emptySize);
	}

	TEST_CASE("Get All balance sync")
	{
		Ref<WalletWrapper> wallet;
		TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
		if (wallets.size() == 0)
		{
			wallet = suiSDK.generateWallet("ed25519", "word12");
		}
		else
		{
			wallet = wallets[0];
		}
		TypedArray<BalanceWrapper> balances = suiSDK.getAllBalancesSync(wallet->address);
		int emptySize = 0;
		CHECK(balances.size() != emptySize);
	}

	TEST_CASE("Get coin sync")
	{
		Ref<WalletWrapper> wallet;
		TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
		if (wallets.size() == 0)
		{
			wallet = suiSDK.generateWallet("ed25519", "word12");
		}
		else
		{
			wallet = wallets[0];
		}
		TypedArray<CoinWrapper> coins = suiSDK.getCoinsSync(wallet->address);
		CHECK(coins.size() != (const int)0);
	}

	TEST_CASE("Get total supply sync")
	{
		String totalSupply = suiSDK.getTotalSupplySync();
		CHECK(totalSupply != "0");
	}
} // namespace TestSuiBalanceSDK

#endif