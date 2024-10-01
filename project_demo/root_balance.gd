extends TabBar

var suiSDK = SuiSDK.new()
var walletAddress

func number_format(n):
	n = str(n)
	var size = n.length()
	var s = ""
	
	for i in range(size):
			if((size - i) % 3 == 0 and i > 0):
				s = str(s,",", n[i])
			else:
				s = str(s,n[i])
			
	return s

func getWallets():
	var wallets = suiSDK.getWallets()
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer/walletsOption")
	walletsOption.clear()

	for i in wallets.size():
		var wallet = wallets[i]
		walletsOption.add_item(wallet.get_address(), i)
	walletsOption.select(-1)
	
func getBalance(address):
	var balance = suiSDK.getBalanceSync(address)
	var balanceText: Label = get_node("VBoxContainer/balance")
	balanceText.text = str(number_format(float(balance.get_total_balance()) / 10**9)) + " SUI"

func getCoins(address):
	var coinList: VBoxContainer = get_node("VBoxContainer/coinList")
	for n in coinList.get_children():
		coinList.remove_child(n)
		n.queue_free()

	var coins = suiSDK.getCoinsSync(address)
	for coin in coins:
		print(coin)
		var coinH = HBoxContainer.new()
		var coinType = Label.new()
		var coinBalance = Label.new()
		coinType.text = coin.get_coin_type()
		coinBalance.text = str(float(coin.get_balance()) / 10**9)
		coinBalance.size_flags_horizontal = 3
		coinBalance.horizontal_alignment = HORIZONTAL_ALIGNMENT_RIGHT
	
		coinH.add_child(coinType)
		coinH.add_child(coinBalance)

		coinList.add_child(coinH)

func getTotalSuply():
	var totalSuply = suiSDK.getTotalSupplySync()
	var totalSuplyLableValue: Label = get_node("VBoxContainer/HBoxContainer/suiTotalSuply")
	totalSuplyLableValue.text = str(number_format(float(totalSuply)/10**9))

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	getWallets()
	getTotalSuply()
	pass # Replace with function body.


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass


func _on_wallets_option_item_selected(index: int) -> void:
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer/walletsOption")
	walletAddress = walletsOption.get_item_text(index)
	Global.setCurrentWallet(walletAddress)
	
	getBalance(walletAddress)
	getCoins(walletAddress)


func _on_action_1_pressed() -> void:
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer/walletsOption")
	var walletIndex = walletsOption.get_selected_id()
	var walletAddress = walletsOption.get_item_text(walletIndex)
	suiSDK.requestTokensFromFaucet(walletAddress)
	getBalance(walletAddress)
	getCoins(walletAddress)


func _on_action_2_pressed() -> void:
	get_tree().change_scene_to_file("res://root_balance_send.tscn")


func _on_action_3_pressed() -> void:
	get_tree().change_scene_to_file("res://root_balance_send.tscn")
