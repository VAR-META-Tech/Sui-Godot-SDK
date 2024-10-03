extends TabBar

var address = ""
var sdk = SuiSDK.new()
var wallets = []

func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("VBoxContainer/h_box_address/address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)

func _on_btn_send_with_sponser_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	var recipient = get_node("VBoxContainer/h_box_recipient/txt_recipient_address").text
	var sponser_address = get_node("VBoxContainer/h_box_send_with_sponser/txt_sponser_address").text
	var amount = get_node("VBoxContainer/h_box_send/txt_amount").text
	
	if address == -1:
		get_node("result").text = "Please enter your address"
	var sender = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
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


func _on_btn_request_faucet_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var result = sdk.requestTokensFromFaucet(get_node("VBoxContainer/h_box_address/address_box").get_item_text(address))
		self.get_node("result").text = result


func _on_btn_send_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	var recipient = get_node("VBoxContainer/h_box_recipient/txt_recipient_address").text
	var amount = get_node("VBoxContainer/h_box_send/txt_amount").text
	
	if address == -1:
		get_node("result").text = "Please enter your address"
	var sender = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
	if recipient == "":
		get_node("result").text = "Please enter recipient address"
	if amount == "":
		get_node("result").text = "Please enter amount"
	if int(amount) == 0:
		get_node("result").text = "Please enter correct amount"
	else:
		var result = sdk.signTransaction(sender,recipient,int(amount))
		self.get_node("result").text=result

func _on_btn_get_coins_sync_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please enter your address"
	else:
		var balance = sdk.getBalanceSync(get_node("VBoxContainer/h_box_address/address_box").get_item_text(address))
		get_node("VBoxContainer/h_box_balance/total_balance").text=str(float(balance.get_total_balance())/10**9) + " SUI"
