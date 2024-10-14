#ifndef GODOT_SUI_BUILDER_H
#define GODOT_SUI_BUILDER_H

#include "../header/sui_lib.h"
#include "core/object/class_db.h"
#include "core/object/object.h"
#include "core/object/ref_counted.h"
#include "core/variant/typed_array.h"

class SuiArguments : public RefCounted
{
  GDCLASS(SuiArguments, RefCounted);

public:
  CArguments *arguments;

  SuiArguments() { arguments = create_arguments(); }
  ~SuiArguments() { destroy_arguments(arguments); }
};

class SuiProgrammableTransactionBuilder : public RefCounted
{
  GDCLASS(SuiProgrammableTransactionBuilder, RefCounted);

public:
  CProgrammableTransactionBuilder *builder;

  SuiProgrammableTransactionBuilder() { builder = create_builder(); }
  ~SuiProgrammableTransactionBuilder() { destroy_builder(builder); }
};

class SuiTypeTags : public RefCounted
{
  GDCLASS(SuiTypeTags, RefCounted);

public:
  CTypeTags *type_tags;
  SuiTypeTags() { type_tags = create_type_tags(); }
  ~SuiTypeTags() { destroy_type_tags(type_tags); }
};

class SuiBSCBasic : public RefCounted
{
  GDCLASS(SuiBSCBasic, RefCounted);

protected:
  static void _bind_methods();

public:
  CPure *pure;
  SuiBSCBasic() {};
  void BSCBasic(String type, String data) { pure = bsc_basic(type.utf8().get_data(), data.utf8().get_data()); }
};

class SuiBuilder
{

public:
  void makePure(SuiProgrammableTransactionBuilder *builder, SuiArguments *arguments, SuiBSCBasic *pure);
  void addSplitCoinsCommand(SuiProgrammableTransactionBuilder *builder, SuiArguments *coin, SuiArguments *amount);
  void addTransferObjectCommand(SuiProgrammableTransactionBuilder *builder, SuiArguments *arguments, SuiArguments *recipient);
  void addMoveCallCommand(SuiProgrammableTransactionBuilder *builder, String package, String module, String function, SuiTypeTags *type_arguments, SuiArguments *arguments);
  String executeTransaction(SuiProgrammableTransactionBuilder *builder, String senderAddress, uint64_t gasLimit);
  void addTypeTag(SuiTypeTags *type_tags, String tag);

  void addArgumentGasCoin(SuiArguments *arguments)
  {
    add_argument_gas_coin(arguments->arguments);
  };

  void addArgumentResult(SuiArguments *arguments, uint16_t value)
  {
    add_argument_result(arguments->arguments, value);
  };

  void addArgumentInput(SuiArguments *arguments, uint16_t value)
  {
    add_argument_input(arguments->arguments, value);
  }

  void addArgumentNestedResult(SuiArguments *arguments, uint16_t value1, uint16_t value2)
  {
    add_argument_nested_result(arguments->arguments, value1, value2);
  }

  void addMergeCoinsCommand(SuiProgrammableTransactionBuilder *builder,
                            SuiArguments *coin,
                            SuiArguments *agreements)
  {
    add_merge_coins_command(builder->builder,
                            coin->arguments,
                            agreements->arguments);
  }

  char *executeTransactionAllowSponser(SuiProgrammableTransactionBuilder *builder,
                                       String sender,
                                       uint64_t gas_budget,
                                       String sponser)
  {
    execute_transaction_allow_sponser(builder->builder,
                                      sender.utf8().get_data(),
                                      gas_budget,
                                      sponser.utf8().get_data());
  }
};

#endif
