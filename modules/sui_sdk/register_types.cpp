#include "register_types.h"
#include "core/object/class_db.h"
#include "sui_sdk.h"

using namespace godot;

void initialize_sui_sdk_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}

	ClassDB::register_class<SuiSDK>();
	ClassDB::register_class<WalletWrapper>();
	ClassDB::register_class<ImportResultWrapper>();
	ClassDB::register_class<BalanceWrapper>();
	ClassDB::register_class<CoinWrapper>();
	ClassDB::register_class<WalletObjectWrapper>();
	ClassDB::register_class<MulSigWrapper>();
	ClassDB::register_class<SuiArguments>();
	ClassDB::register_class<SuiBuilder>();
	ClassDB::register_class<SuiBSCBasic>();
	ClassDB::register_class<SuiProgrammableTransactionBuilder>();
	ClassDB::register_class<SuiTypeTags>();
}

void uninitialize_sui_sdk_module(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
	{
		return;
	}
}
