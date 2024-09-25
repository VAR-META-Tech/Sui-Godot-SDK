#ifndef GODOT_SUI_SDK_H
#define GODOT_SUI_SDK_H

#include "core/object/class_db.h"
#include "core/object/object.h"
#include "src/sui_balance.h"
#include "src/sui_client.h"
#include "src/sui_multisig.h"
#include "src/sui_nfts.h"
#include "src/sui_transaction.h"
#include "src/sui_wallet.h"

namespace godot
{

	class SuiSDK : public SuiBalance, public SuiWallet, public SuiMultisig, public SuiNfts, public SuiClient, public SuiTransaction, public Object
	{
		GDCLASS(SuiSDK, Object);

	protected:
		static void _bind_methods();

	public:
		/**
		 * Balance
		 */
		TypedArray<BalanceWrapper> getBalances(String address) { return SuiBalance::getBalances(address); };
		TypedArray<BalanceWrapper> getAllBalancesSync(String address) { return SuiBalance::getAllBalancesSync(address); };
		Ref<BalanceWrapper> getBalanceSync(String address) { return SuiBalance::getBalanceSync(address); };
		String getTotalSupplySync() { return SuiBalance::getTotalSupplySync(); };
		TypedArray<CoinWrapper> getCoinsSync(String address) { return SuiBalance::getCoinsSync(address); };

		/**
		 * Client
		 */
		String apiVersion() { return SuiClient::apiVersion(); };
		int checkApiVersion() { return SuiClient::checkApiVersion(); };

		/**
		 * Multisig
		 */
		Ref<MulSigWrapper> getOrCreateMultisig(TypedArray<String> addresses, TypedArray<uint8_t> weights, uint16_t threshold)
		{
			return SuiMultisig::getOrCreateMultisig(addresses, weights, threshold);
		};
		TypedArray<uint8_t> createTransaction(String from_address, String to_address, uint64_t amount)
		{
			return SuiMultisig::createTransaction(from_address, to_address, amount);
		};

		/**
		 * NFTs
		 */
		TypedArray<WalletObjectWrapper> getWalletObjects(String address, String object_type) { return SuiNfts::getWalletObjects(address, object_type); };
		String mintNft(
				String package_id,
				String sender_address,
				String name,
				String description,
				String uri) { return SuiNfts::mintNft(package_id, sender_address, name, description, uri); };
		String transferNft(
				String package_id,
				String sender_address,
				String nft_id,
				String recipient_address) { return SuiNfts::transferNft(package_id, sender_address, nft_id, recipient_address); };

		/**
		 * Transaction
		 */
		String signTransaction(String sender, String recipient, unsigned long long int amount) { return SuiTransaction::signTransaction(sender, recipient, amount); };
		String programmableTransactionAllowSponser(String sender_address, String recipient_address, unsigned long long int amount, String sponser_address) { return SuiTransaction::programmableTransactionAllowSponser(sender_address, recipient_address, amount, sponser_address); };
		String requestTokensFromFaucet(String address_str) { return SuiTransaction::requestTokensFromFaucet(address_str); };

		/**
		 * Wallet
		 */
		TypedArray<WalletWrapper> getWallets() { return SuiWallet::getWallets(); };
		Ref<WalletWrapper> generateWallet(String key_scheme, String word_length) { return SuiWallet::generateWallet(key_scheme, word_length); };
		Ref<WalletWrapper> generateAndAddKey() { return SuiWallet::generateAndAddKey(); };
		Ref<WalletWrapper> getWalletFromAddress(String address) { return SuiWallet::getWalletFromAddress(address); };
		void importFromPrivateKey(String key_base64) { SuiWallet::importFromPrivateKey(key_base64); };
		String importFromMnemonic(String mnemonic) { return SuiWallet::importFromMnemonic(mnemonic); };

		SuiSDK();
	};

} // namespace godot

#endif // GODOT_SUI_SDK_H