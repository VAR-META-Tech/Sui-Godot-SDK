#include "sui_utility.h"

void SuiUtility::connectLocalnet()
{
  connect_localnet_c();
}

void SuiUtility::connectDevnet()
{
  connect_devnet_c();
}

void SuiUtility::connectTestnet()
{
  connect_testnet_c();
}

TypedArray<String> SuiUtility::availableSubscription()
{
  ResultCStringArray result = available_subscriptions();
  TypedArray<String> resultArray;

  for (size_t i = 0; i < result.strings.len; i++)
  {
    resultArray.append(result.strings.data[i]);
  }

  return resultArray;
}

TypedArray<String> SuiUtility::availableRPCMethods()
{
  ResultCStringArray result = available_rpc_methods();
  TypedArray<String> resultArray;

  for (size_t i = 0; i < result.strings.len; i++)
  {
    resultArray.append(result.strings.data[i]);
  }

  return resultArray;
}