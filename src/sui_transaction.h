#ifndef GODOT_SUI_TRANSACTION_H
#define GODOT_SUI_TRANSACTION_H

#include "../header/sui_lib.h"

class SuiTransaction {
protected:
	// static void _bind_methods();

public:
	char *signTransaction(const char *sender, const char *recipient, unsigned long long amount);
};

#endif
