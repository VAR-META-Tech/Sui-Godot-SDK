#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "src/sui_balance.h"
#include "src/sui_client.h"
#include "src/sui_multisig.h"
#include "src/sui_nfts.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

namespace godot {

class SuiSDK : public SuiBalance, public SuiWallet, public SuiMultisig, public SuiNfts, public SuiClient, public SuiTransaction, public Object {
	GDCLASS(SuiSDK, Object);

protected:
	static void _bind_methods();

public:
	String test();
	void import();
	SuiSDK();
};
} //namespace godot

#endif // GODOT_SUI_SDK_H