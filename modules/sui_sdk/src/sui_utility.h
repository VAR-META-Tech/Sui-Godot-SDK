#ifndef GODOT_SUI_UTILITY_H
#define GODOT_SUI_UTILITY_H

#include "../header/sui_lib.h"
#include "core/variant/typed_array.h"

class SuiUtility
{
protected:
public:
  void connectLocalnet();
  void connectDevnet();
  void connectTestnet();
  TypedArray<String> availableSubscription();
  TypedArray<String> availableRPCMethods();
};

#endif
