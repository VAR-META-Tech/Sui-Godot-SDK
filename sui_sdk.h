#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "src/sui_balance.h"
#include "src/sui_client.h"
#include "src/sui_multisig.h"
#include "src/sui_nfts.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

#include <godot_cpp/classes/node.hpp>

namespace godot
{

	class SuiSDK : public SuiBalance, public SuiWallet, public SuiMultisig, public SuiNfts, public SuiClient, public SuiTransaction, public Node
	{
		GDCLASS(SuiSDK, Node);

	protected:
		static void _bind_methods();

	public:
		String test();
		SuiSDK();
	};
}

#endif // GODOT_SUI_SDK_H