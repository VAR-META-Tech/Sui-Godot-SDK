/* register_types.cpp */

#include "register_types.h"
void initialize_sui_sdk_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

void uninitialize_sui_sdk_module(ModuleInitializationLevel p_level) {
	// Nothing to do here in this example.
}