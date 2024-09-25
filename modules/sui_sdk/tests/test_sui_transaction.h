#ifndef TEST_SUI_TRANSACTION_SDK_H
#define TEST_SUI_TRANSACTION_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"
using namespace godot;
namespace TestSuiTransactionSDK
{

  TEST_CASE("Sign Transaction")
  {
    SuiSDK suiSDK;
    String sender = "0x3b681380d39b7109e029a4869cb53d42cc4ac9a92b5749ce65173bc3e8680c11";
    String recipient = "0x3f2c2374b9902cdd7423c24618c7993e516df6f3fc6034822e844f80cd79e49e";
    unsigned long long amount = 10000000;

    String result = suiSDK.signTransaction(sender, recipient, amount);
    CHECK(result == "Transaction completed successfully");
  }

} // namespace TestSuiTransactionSDK

#endif