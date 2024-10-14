#include "sui_builder.h"

void SuiBuilder::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("makePure", "builder", "arguments"), &SuiBuilder::makePure);
}