#include "sui_builder.h"

void SuiBuilder::makePure(SuiProgrammableTransactionBuilder *builder, SuiArguments *arguments, SuiBSCBasic *pure)
{
  make_pure(builder->builder, arguments->arguments, pure->pure);
}

void SuiBuilder::addSplitCoinsCommand(SuiProgrammableTransactionBuilder *builder, SuiArguments *coin, SuiArguments *amount)
{
  add_split_coins_command(builder->builder, coin->arguments, amount->arguments);
}
void SuiBuilder::addTransferObjectCommand(SuiProgrammableTransactionBuilder *builder, SuiArguments *arguments, SuiArguments *recipient)
{
  add_transfer_object_command(builder->builder, arguments->arguments, recipient->arguments);
}
void SuiBuilder::addMoveCallCommand(SuiProgrammableTransactionBuilder *builder, String package, String module, String function, SuiTypeTags *type_arguments, SuiArguments *arguments)
{
  add_move_call_command(builder->builder, package.utf8().get_data(), module.utf8().get_data(), function.utf8().get_data(), type_arguments->type_tags, arguments->arguments);
}

String SuiBuilder::executeTransaction(SuiProgrammableTransactionBuilder *builder, String senderAddress, uint64_t gasLimit)
{
  const char *result = execute_transaction(builder->builder, senderAddress.utf8().get_data(), gasLimit);
  return result;
}

void SuiBuilder::addTypeTag(SuiTypeTags *type_tags, String tag)
{
  add_type_tag(type_tags->type_tags, tag.utf8().get_data());
}

void SuiBSCBasic::_bind_methods()
{
  ClassDB::bind_method(D_METHOD("BSCBasic", "type", "data"), &SuiBSCBasic::BSCBasic);
}