extends Node

var address = ""
var sdk = SuiSDK.new()
func _on_btn_get_balances_pressed() -> void:
	if address == "":
		get_node("result").text = "Plase input your address"
	if address != "":
		var balances = sdk.getAllBalancesSync(address)
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n"
		
		self.get_node("result").text=res


func _on_txt_address_text_changed() -> void:
	var txt_address = get_node("txt_address")
	address = txt_address.text


func _on_btn_get_all_balances_sync_pressed() -> void:
	if address == "":
		get_node("result").text = "Plase input your address"
	if address != "":
		var sdk = SuiSDK.new()
		var balances = sdk.getAllBalancesSync(address)
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n"
		
		self.get_node("result").text=res


func _on_btn_get_balance_sync_pressed() -> void:
	if address == "":
		get_node("result").text = "Plase input your address"
	if address != "":
		var balance = sdk.getBalanceSync(address)
		var res=""
		res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
		res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
		res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n"
		
		self.get_node("result").text=res


func _on_btn_get_total_supply_sync_pressed() -> void:
	var totalSupply = sdk.getTotalSupplySync(address)
	self.get_node("result").text="Total supply: " + str(totalSupply)


func _on_btn_get_coins_sync_pressed() -> void:
	if address == "":
		get_node("result").text = "Plase input your address"
	if address != "":
		var coins = sdk.getCoinsSync(address)
		var res=""
		for coin in coins:
			res = res+ "Balance: " + str(coin.get_balance()) + "\n"
			res = res+ "Coin type: " + str( coin.get_coin_type()) + "\n"
			res = res+ "Coin object id: " + str(coin.get_coin_object_id()) + "\n"
			res = res+ "Digest: " + str(coin.get_digest()) + "\n"
			res = res+ "Version: " + str(coin.get_version()) + "\n"
			res = res+ "Previous transaction: " + str(coin.get_previous_transaction()) + "\n"
		
		self.get_node("result").text=res

func printAddress(wallet):
	print(wallet.get_address())
	print(wallet.get_mnemonic())
	print(wallet.get_public_base64_key())
	print(wallet.get_private_key())
	print(wallet.get_key_scheme())

func onGetWallets():
	#var sdk = SuiSDK.new()
	var wallets = sdk.getWallets()
	
	for wallet in wallets:
		printAddress(wallet)

func onGenerateWallet():
	#var sdk = SuiSDK.new()
	var wallet = sdk.generateWallet("ed25519", "word12")
	printAddress(wallet)

func onGenAndAddKey():
	var wallet = sdk.generateAndAddKey()
	printAddress(wallet)

func onGetWalletFromAddress():
	var address = '0xfee0108a2467a551f50f3f7c2dc77128406ae314ef4515030dc62accb0c15bcc'
	var wallet =  sdk.getWalletFromAddress(address)
	if wallet == null: print('Wallet not found')
	else: printAddress(wallet)

func onImportFromPrivateKey():
	var privateKey = 'ALxpSoPbaEhbXXwsUrpC+icfmeArLR+fm65u8j1O9i2q'
	sdk.importFromPrivateKey(privateKey)
	print('ImportFromPrivateKey OK')

func onImportFromMnemonic():
	var mnemonic = 'finish appear ghost horn text train network flag evoke symbol lesson cycle'
	var address = sdk.importFromMnemonic(mnemonic)
	print(address)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_button_get_wallets_pressed() -> void:
	onGetWallets()
	pass # Replace with function body.

func _on_button_gen_wallet_pressed() -> void:
	onGenerateWallet()
	pass # Replace with function body.

func _on_button_generate_and_add_key_pressed() -> void:
	onGenAndAddKey()
	pass # Replace with function body.

func _on_button_get_wallet_from_address_pressed() -> void:
	onGetWalletFromAddress()
	pass # Replace with function body.


func _on_button_import_from_private_key_pressed() -> void:
	onImportFromPrivateKey()
	pass # Replace with function body.


func _on_button_import_from_mnemonic_pressed() -> void:
	onImportFromMnemonic()
	pass # Replace with function body.


func _on_button_scene_version_pressed() -> void:
	get_tree().change_scene_to_file("res://version.tscn")
	pass # Replace with function body.
