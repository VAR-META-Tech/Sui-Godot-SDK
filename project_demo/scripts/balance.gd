extends TabBar

var sdk = SuiSDK.new()
var wallets = []

func make_header_tree (tree: Tree):
	tree.hide_root = true
	tree.columns = 4
	tree.set_column_title(0, 'No')
	tree.set_column_title(1, 'Balance')
	tree.set_column_title(2, 'Coin type')
	tree.set_column_title(3, 'Coin object count')
	tree.set_column_custom_minimum_width(0, 0)
	tree.set_column_custom_minimum_width(1, 400)
	tree.set_column_custom_minimum_width(2, 300)
	tree.set_column_custom_minimum_width(3, 200)

func gen_row_tree(row, index, balance:BalanceWrapper):
	var buttonCopy: Texture2D = load("res://icons/copy.svg")
	row.set_text(0, str(index + 1))
	row.set_text(1, balance.get_total_balance())
	row.set_text(2, balance.get_coin_type())
	row.set_text(3, str(balance.get_coin_object_count()))
	row.add_button(1, buttonCopy, index, false, "Copy")
	row.add_button(2, buttonCopy, index, false, "Copy")
	row.add_button(3, buttonCopy, index, false, "Copy")


func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("VBoxContainer/h_box_address/address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)
		
func _on_btn_get_balances_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please input your address"
	else:
		var addressText = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
		var balances = sdk.getAllBalancesSync(addressText)
		
		var tree: Tree = get_node("VBoxContainer/list_result_tree")
		tree.clear()
		var root = tree.create_item()
		make_header_tree(tree)
		for index in balances.size():
			var balance = balances[index]
			var row = tree.create_item(root)
			gen_row_tree(row,index,balance)


func _on_btn_get_all_balances_sync_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please input your address"
	else:
		var addressText = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
		var balances = sdk.getAllBalancesSync(addressText)
		var tree: Tree = get_node("VBoxContainer/list_result_tree")
		tree.clear()
		var root = tree.create_item()
		make_header_tree(tree)
		for index in balances.size():
			var balance = balances[index]
			var row = tree.create_item(root)
			gen_row_tree(row,index,balance)


func _on_btn_get_balance_sync_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please input your address"
	else:
		var addressText = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
		var balance = sdk.getBalanceSync(addressText)
		var tree: Tree = get_node("VBoxContainer/list_result_tree")
		tree.clear()
		var root = tree.create_item()
		make_header_tree(tree)

		var row = tree.create_item(root)
		gen_row_tree(row,0,balance)


func _on_btn_get_total_supply_sync_pressed() -> void:
	var totalSupply = sdk.getTotalSupplySync()
	var tree: Tree = get_node("VBoxContainer/list_result_tree")
	tree.clear()
	var root = tree.create_item()
	tree.hide_root = true
	tree.columns = 2
	tree.set_column_title(0, 'No')
	tree.set_column_title(1, 'Total Supply')
	tree.set_column_custom_minimum_width(0, 0)
	tree.set_column_custom_minimum_width(1, 800)
	var buttonCopy: Texture2D = load("res://icons/copy.svg")

	var row = tree.create_item(root)
	row.set_text(0, str(1))
	row.set_text(1, str(totalSupply))
	row.add_button(1, buttonCopy, 0, false, "Copy")


func _on_btn_get_coins_sync_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("result").text = "Please input your address"
	else:
		var addressText = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
		var coins = sdk.getCoinsSync(addressText)
		var tree: Tree = get_node("VBoxContainer/list_result_tree")
		tree.clear()
		tree.columns = 7
		var root = tree.create_item()
		tree.hide_root = true
		tree.set_column_title(0, 'No')
		tree.set_column_title(1, 'Balance')
		tree.set_column_title(2, 'Coin type')
		tree.set_column_title(3, 'Coin object id')
		tree.set_column_title(4, 'Digest')
		tree.set_column_title(5, 'Version')
		tree.set_column_title(6, 'Previous transaction')
		tree.set_column_custom_minimum_width(0, 0)
		tree.set_column_custom_minimum_width(1, 150)
		tree.set_column_custom_minimum_width(2, 150)
		tree.set_column_custom_minimum_width(3, 100)
		tree.set_column_custom_minimum_width(4, 200)
		tree.set_column_custom_minimum_width(5, 100)
		tree.set_column_custom_minimum_width(6, 300)
		var buttonCopy: Texture2D = load("res://icons/copy.svg")
		for index in coins.size():
			var coin = coins[index]
			var row = tree.create_item(root)
			row.set_text(0, str(index+1))
			row.set_text(1, str(coin.get_balance()))
			row.set_text(2, str(coin.get_coin_type()))
			row.set_text(3, str(coin.get_coin_object_id()))
			row.set_text(4, str(coin.get_digest()))
			row.set_text(5, str(coin.get_version()))
			row.set_text(6, str(coin.get_previous_transaction()))
			row.add_button(1, buttonCopy, index, false, "Copy")
			row.add_button(2, buttonCopy, index, false, "Copy")
			row.add_button(3, buttonCopy, index, false, "Copy")
			row.add_button(4, buttonCopy, index, false, "Copy")
			row.add_button(5, buttonCopy, index, false, "Copy")
			row.add_button(6, buttonCopy, index, false, "Copy")
