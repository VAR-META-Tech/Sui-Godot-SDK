#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "src/sui_balance.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

class SuiSDK : public SuiBalance, public SuiWallet, public SuiTransaction {
public:
	SuiSDK();
};

#endif // GODOT_SUI_SDK_H