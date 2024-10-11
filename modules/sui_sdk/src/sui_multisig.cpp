#include "sui_multisig.h"

Ref<MulSigWrapper> _toMultiSigWrapper(const MultiSigStruct &multi_sig_struct)
{
	Ref<MulSigWrapper> wrapper = memnew(MulSigWrapper);
	wrapper->set_address(multi_sig_struct.address);
	wrapper->set_bytes(multi_sig_struct.bytes);

	return wrapper;
}

Ref<MulSigWrapper> _makeMultiSigStruct(CMultiSig multisig)
{
	MultiSigStruct multiSigStructItem;
	multiSigStructItem.address = multisig.address;
	multiSigStructItem.error = multisig.error;

	TypedArray<uint8_t> bytes;
	for (size_t i = 0; i < multisig.bytes.len; i++)
	{
		bytes.append(multisig.bytes.data[i]);
	}

	multiSigStructItem.bytes = bytes;

	return _toMultiSigWrapper(multiSigStructItem);
}

CStringArray _makeAddressArray(TypedArray<String> addresses)
{
	CStringArray addressesArray;
	int size = addresses.size();

	char **tempStrings = (char **)malloc(size * sizeof(char *));
	addressesArray.len = size;

	for (int i = 0; i < size; ++i)
	{
		CharString char_string = String(addresses[i]).utf8();
		char *str_copy = (char *)malloc(char_string.length() + 1);
		memcpy(str_copy, char_string.get_data(), char_string.length() + 1);
		tempStrings[i] = str_copy;
	}
	addressesArray.data = (const char *const *)tempStrings;

	return addressesArray;
};

CU8Array _makeWeightArray(TypedArray<uint8_t> weights)
{
	CU8Array weightsArray;
	weightsArray.len = weights.size();
	uint8_t *weightData = new uint8_t[weights.size()];
	for (size_t i = 0; i < weights.size(); i++)
	{
		weightData[i] = weights[i];
	}
	weightsArray.data = weightData;

	return weightsArray;
}

CU8Array _parseMultiSig(Ref<MulSigWrapper> multisigRef)
{
	CU8Array multiSigBytes;
	multiSigBytes.len = multisigRef->get_bytes().size();
	uint8_t *multiSigBytesData = new uint8_t[multisigRef->get_bytes().size()];
	for (size_t i = 0; i < multisigRef->get_bytes().size(); i++)
	{
		multiSigBytesData[i] = multisigRef->get_bytes()[i];
	}
	multiSigBytes.data = multiSigBytesData;

	return multiSigBytes;
}

CU8Array _parseTx(TypedArray<uint8_t> txRef)
{
	CU8Array tx;
	tx.len = txRef.size();
	uint8_t *txData = new uint8_t[txRef.size()];
	for (size_t i = 0; i < txRef.size(); i++)
	{
		txData[i] = txRef[i];
	}
	tx.data = txData;
	return tx;
};

/**
 * Main function
 */

Ref<MulSigWrapper> SuiMultisig::getOrCreateMultisig(TypedArray<String> addresses, TypedArray<uint8_t> weights, uint16_t threshold)
{
	CStringArray addressesArray = _makeAddressArray(addresses);
	CU8Array weightsArray = _makeWeightArray(weights);

	CMultiSig multiSig = get_or_create_multisig(addressesArray, weightsArray, threshold);
	return _makeMultiSigStruct(multiSig);
}

TypedArray<uint8_t> SuiMultisig::createTransaction(String from_address, String to_address, uint64_t amount)
{
	CU8Array tx = create_transaction(from_address.utf8(), to_address.utf8(), amount);
	TypedArray<uint8_t> txArray;
	for (size_t i = 0; i < tx.len; i++)
	{
		txArray.append(tx.data[i]);
	}

	return txArray;
}

String SuiMultisig::signAndExecuteTransaction(Ref<MulSigWrapper> multisigRef, TypedArray<uint8_t> txRef, TypedArray<String> addresses)
{
	CU8Array multiSigBytes = _parseMultiSig(multisigRef);
	CU8Array tx = _parseTx(txRef);
	CStringArray addressesArray = _makeAddressArray(addresses);

	return sign_and_execute_transaction_miltisig(multiSigBytes, tx, addressesArray);
}

void SuiMultisig::freeMultisig(CMultiSig multisig)
{
	free_multisig(multisig);
}
