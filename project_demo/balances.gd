extends TabBar

var address = ""
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

func _on_btn_send_with_sponser_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	var recipient = get_node("txt_recipient_address").text
	var sponser_address = get_node("txt_recipient_address").text
	var amount = get_node("txt_amount").text
	
	if address == -1:
		get_node("result").text = "Please enter your address"
	var sender = get_node("address_box").get_item_text(address)
	if recipient == "":
		get_node("result").text = "Please enter recipient address"
	if sponser_address == "":
		get_node("result").text = "Please enter sponser address"
	if amount == "":
		get_node("result").text = "Please enter amount"
	if int(amount) == 0:
		get_node("result").text = "Please enter correct amount"
	else:
		var result = sdk.programmableTransactionAllowSponser(sender,recipient,int(amount),sponser_address)
		self.get_node("result").text=result


func _on_btn_load_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var balances = sdk.getBalances(get_node("address_box").get_item_text(address))
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n"
		self.get_node("result").text=res


func _on_btn_request_faucet_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var result = sdk.requestTokensFromFaucet(get_node("address_box").get_item_text(address))
		self.get_node("result").text = result


func _on_btn_send_pressed() -> void:
	var address = get_node("address_box").get_selected_id()
	var recipient = get_node("txt_recipient_address").text
	var amount = get_node("txt_amount").text
	
	if address == -1:
		get_node("result").text = "Please enter your address"
	var sender = get_node("address_box").get_item_text(address)
	if recipient == "":
		get_node("result").text = "Please enter recipient address"
	if amount == "":
		get_node("result").text = "Please enter amount"
	if int(amount) == 0:
		get_node("result").text = "Please enter correct amount"
	else:
		var result = sdk.signTransaction(sender,recipient,int(amount))
		self.get_node("result").text=result
