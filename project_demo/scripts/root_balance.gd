extends TabBar

var suiSDK = SuiSDK.new()
var wallets = []

@onready var walletsOption: OptionButton = $VBoxContainer/VBoxContainer/walletsOption
@onready var balanceText: Label = $VBoxContainer/balance
@onready var coinList: VBoxContainer = $VBoxContainer/coinList
@onready var totalSuplyLableValue: Label = $VBoxContainer/HBoxContainer/suiTotalSuply

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
	wallets = suiSDK.getWallets()

func addWalletsToPopup():
	walletsOption.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		walletsOption.add_item(wallet.get_address(), i)
	walletsOption.select(-1)
	
func getBalance(address):
	var balance = suiSDK.getBalanceSync(address)
	balanceText.text = str(float(balance.get_total_balance()) / 10**9) + " SUI"

func getCoins(address):
	for n in coinList.get_children():
		coinList.remove_child(n)
		n.queue_free()

	var coins = suiSDK.getCoinsSync(address)
	for coin in coins:
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
	totalSuplyLableValue.text = str(number_format(float(totalSuply)/10**9))

func setCurrentWallet(address):
	var walletIndex = -1
	for id in wallets.size():
		if wallets[id].get_address() == address:
			walletIndex = id
	walletsOption.select(walletIndex)

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	getWallets()
	addWalletsToPopup()
	getTotalSuply()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if Global.currentWallet != "" && walletsOption.text != Global.currentWallet:
		setCurrentWallet(Global.currentWallet)
		getBalance(Global.currentWallet)
		getCoins(Global.currentWallet)

func _on_wallets_option_item_selected(index: int) -> void:
	var walletAddress = walletsOption.text
	Global.currentWallet = walletAddress
	getBalance(Global.currentWallet)
	getCoins(Global.currentWallet)

func _on_action_1_pressed() -> void:
	var message = suiSDK.requestTokensFromFaucet(Global.currentWallet)
	getBalance(Global.currentWallet)
	getCoins(Global.currentWallet)
	Global.showToast(message)


func _on_action_2_pressed() -> void:
	Global.changeScene(Global.SCREEN.ROOT_BALACNE_SEND)
