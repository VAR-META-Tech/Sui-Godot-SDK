#include "sui_sdk.h"
#include "src/sui_balance.cpp"
#include "src/sui_client.cpp"
#include "src/sui_multisig.cpp"
#include "src/sui_nfts.cpp"
#include "src/sui_transaction.cpp"
#include "src/sui_wallet.cpp"

using namespace godot;

SuiSDK::SuiSDK()
{
}

String SuiSDK::test()
{
  return "Test ne`";
}

void SuiSDK::_bind_methods()
{
  // ClassDB::bind_static_method(D_METHOD("getWallets"), &SuiSDK::getWallets);

  ClassDB::bind_method(D_METHOD("test"), &SuiSDK::test);
  // ClassDB::bind_method(D_METHOD("set_amplitude", "p_amplitude"), &GDExample::set_amplitude);
  // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "amplitude"), "set_amplitude", "get_amplitude");
}