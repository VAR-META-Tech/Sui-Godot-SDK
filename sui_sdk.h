#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "src/sui_balance.h"
#include "src/sui_client.h"
#include "src/sui_multisig.h"
#include "src/sui_nfts.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

class SuiSDK : public SuiBalance, public SuiWallet, public SuiMultisig, public SuiNfts, public SuiClient, public SuiTransaction {
public:
	SuiSDK();
};

#endif // GODOT_SUI_SDK_H