#include "sui_transaction.h"
#include <iostream>
#include <string.h>

/**
 * Main function
 */

String SuiTransaction::signTransaction(String sender, String recipient, uint64_t amount)
{
	return programmable_transaction(sender.utf8().get_data(), recipient.utf8().get_data(), amount);
}

String SuiTransaction::programmableTransactionAllowSponser(String sender_address, String recipient_address, uint64_t amount, String sponser_address)
{
	return programmable_transaction_allow_sponser(sender_address.utf8().get_data(), recipient_address.utf8().get_data(), amount, sponser_address.utf8().get_data());
}

String SuiTransaction::requestTokensFromFaucet(String address_str)
{
	return request_tokens_from_faucet(address_str.utf8().get_data());
}

String SuiTransaction::programmableTransactionBuilder(String sender, String recipientAddress, uint64_t amountArg)
{
	CProgrammableTransactionBuilder *builder = create_builder();
	CArguments *coin = create_arguments();
	add_argument_gas_coin(coin);
	CArguments *amount = create_arguments();
	make_pure(builder, amount, bsc_basic("u64", String::num_uint64(amountArg).utf8().get_data()));

	add_split_coins_command(builder, coin, amount);

	CArguments *argument = create_arguments();
	add_argument_result(argument, 0);
	CArguments *recipient = create_arguments();
	make_pure(builder, recipient, bsc_basic("address", recipientAddress.utf8().get_data()));
	add_transfer_object_command(builder, argument, recipient);

	const char *result = execute_transaction(builder, sender.utf8().get_data(), 5000000);
	return result;
}