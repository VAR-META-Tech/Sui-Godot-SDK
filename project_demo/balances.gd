extends TabBar

var address = ""
var sdk = SuiSDK.new()
		
func _on_btn_send_with_sponser_pressed() -> void:
	var sender = get_node("txt_address").text
	var recipient = get_node("txt_recipient_address").text
	var sponser_address = get_node("txt_recipient_address").text
	var amount = get_node("txt_amount").text
	if sender == "":
		get_node("result").text = "Plase input your address"
	if recipient == "":
		get_node("result").text = "Plase enter recipient address"
	if sponser_address == "":
		get_node("result").text = "Plase enter sponser address"
	if amount == "":
		get_node("result").text = "Plase enter amount"
	if int(amount) == 0:
		get_node("result").text = "Plase enter correct amount"
	else:
		var result = sdk.programmableTransactionAllowSponser(sender,recipient,int(amount),sponser_address)
		self.get_node("result").text=result


func _on_btn_load_pressed() -> void:
	if get_node("txt_address").text == "":
		get_node("result").text = "Plase enter your address"
	if get_node("txt_address").text != "":
		var balances = sdk.getBalances(get_node("txt_address").text)
		var res=""
		for balance in balances:
			res = res+ "Balance: " + str(balance.get_total_balance()) + "\n"
			res = res+ "Coin type: " + str( balance.get_coin_type()) + "\n"
			res = res+ "Coin object count: " + str(balance.get_coin_object_count()) + "\n"
		self.get_node("result").text=res


func _on_btn_request_faucet_pressed() -> void:
	if get_node("txt_address").text == "":
		get_node("result").text = "Plase enter your address"
	if get_node("txt_address").text != "":
		var result = sdk.requestTokensFromFaucet(get_node("txt_address").text)
		self.get_node("result").text=result


func _on_btn_send_pressed() -> void:
	var sender = get_node("txt_address").text
	var recipient = get_node("txt_recipient_address").text
	var amount = get_node("txt_amount").text
	if sender == "":
		get_node("result").text = "Plase input your address"
	if recipient == "":
		get_node("result").text = "Plase enter recipient address"
	if amount == "":
		get_node("result").text = "Plase enter amount"
	if int(amount) == 0:
		get_node("result").text = "Plase enter correct amount"
	else:
		var result = sdk.signTransaction(sender,recipient,int(amount))
		self.get_node("result").text=result
