extends TabBar

var sdk = SuiSDK.new()
var wallets = []

func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)
		
func _on_btn_get_balances_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Plase input your address"
	else:
		var balances = sdk.getAllBalancesSync(get_node("address_box").get_item_text(address))
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n\n"
		
		self.get_node("result").text=res


func _on_btn_get_all_balances_sync_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Plase input your address"
	else:
		var sdk = SuiSDK.new()
		var balances = sdk.getAllBalancesSync(get_node("address_box").get_item_text(address))
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n\n"
		
		self.get_node("result").text=res


func _on_btn_get_balance_sync_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Plase input your address"
	else:
		var balance = sdk.getBalanceSync(get_node("address_box").get_item_text(address))
		var res=""
		res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
		res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
		res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n\n"
		
		self.get_node("result").text=res


func _on_btn_get_total_supply_sync_pressed() -> void:
	var totalSupply = sdk.getTotalSupplySync()
	self.get_node("result").text="Total supply: " + str(totalSupply)


func _on_btn_get_coins_sync_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Plase input your address"
	else:
		var coins = sdk.getCoinsSync(get_node("address_box").get_item_text(address))
		var res=""
		for coin in coins:
			res = res+ "Balance: " + str(coin.get_balance()) + "\n"
			res = res+ "Coin type: " + str( coin.get_coin_type()) + "\n"
			res = res+ "Coin object id: " + str(coin.get_coin_object_id()) + "\n"
			res = res+ "Digest: " + str(coin.get_digest()) + "\n"
			res = res+ "Version: " + str(coin.get_version()) + "\n"
			res = res+ "Previous transaction: " + str(coin.get_previous_transaction()) + "\n\n"
		
		self.get_node("result").text=res
