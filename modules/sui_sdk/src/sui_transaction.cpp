#include "sui_transaction.h"
#include <iostream>
#include <string.h>

/**
 * Main function
 */

String SuiTransaction::signTransaction(String sender, String recipient, unsigned long long int amount)
{
	return programmable_transaction(sender.utf8().get_data(), recipient.utf8().get_data(), amount);
}

String SuiTransaction::programmableTransactionAllowSponser(String sender_address, String recipient_address, unsigned long long int amount, String sponser_address)
{
	return programmable_transaction_allow_sponser(sender_address.utf8().get_data(), recipient_address.utf8().get_data(), amount, sponser_address.utf8().get_data());
}

String SuiTransaction::requestTokensFromFaucet(String address_str)
{
	return request_tokens_from_faucet(address_str.utf8().get_data());
}

String SuiTransaction::programmableTransactionBuilder(String sender, String recipientAddress, unsigned long long int amountArg)
{
	CProgrammableTransactionBuilder *builder = create_builder();
	CArguments *coin = create_arguments();
	add_argument_gas_coin(coin);
	CArguments *amount = create_arguments();
	make_pure(builder, amount, bsc_basic("u64", std::to_string(amountArg).c_str()));

	add_split_coins_command(builder, coin, amount);

	CArguments *agrument = create_arguments();
	add_argument_result(agrument, 0);
	CArguments *recipient = create_arguments();
	make_pure(builder, recipient, bsc_basic("address", recipientAddress.utf8().get_data()));
	add_transfer_object_command(builder, agrument, recipient);

	const char *result = execute_transaction(builder, sender.utf8().get_data(), 5000000);
	return result;
}