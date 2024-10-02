#ifndef TEST_SUI_NFTS_SDK_H
#define TEST_SUI_NFTS_SDK_H

#include "tests/test_macros.h"
#include "tests/test_tools.h"

#include "modules/sui_sdk/sui_sdk.h"

using namespace godot;
namespace TestSuiWalletSDK
{
  TEST_CASE("Mint & Transfer NFT")
  {
    SuiSDK suiSDK;
    TypedArray<WalletWrapper> wallets = suiSDK.getWallets();
    while (wallets.size() <= 1)
    {
      suiSDK.generateWallet("ed25519", "word12");
      wallets = suiSDK.getWallets();
    }
    CHECK(wallets.size() > 1);

    Ref<WalletWrapper> walletSender = wallets[0];
    Ref<WalletWrapper> walletReceipt = wallets[0];

    String package_id = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3";
    String object_type = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3::nft::NFT";
    String sender_address = walletSender->get_address();
    String recipient_address = walletReceipt->get_address();
    String name = "Unit test mint nft";
    String description = "This is a unit test mint nft";
    String uri = "";

    String messageMint = suiSDK.mintNft(package_id, sender_address, name, description, uri);
    CHECK(messageMint == "Mint NFT to sender success");

    TypedArray<WalletObjectWrapper> walletNFTObjects = suiSDK.getWalletObjects(sender_address, object_type);
    CHECK(walletNFTObjects.size() > 0);

    Ref<WalletObjectWrapper> nft = walletNFTObjects[0];
    String nft_id = nft->get_object_id();

    String messageTransfer = suiSDK.transferNft(package_id, sender_address, nft_id, recipient_address);
    CHECK(messageTransfer == "Transfer NFT success");
  }

}

#endif