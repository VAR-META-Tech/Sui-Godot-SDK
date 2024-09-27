extends TabBar

var sdk = SuiSDK.new()

func makeHeaderTree (tree: Tree):
	tree.hide_root = true
	tree.set_column_title(0, 'No')
	tree.set_column_title(1, 'Address')
	tree.set_column_title(2, 'Public key')
	tree.set_column_title(3, 'Private key')
	tree.set_column_title(4, 'Scheme key')
	tree.set_column_custom_minimum_width(0, 0)
	tree.set_column_custom_minimum_width(1, 400)
	tree.set_column_custom_minimum_width(2, 300)
	tree.set_column_custom_minimum_width(3, 200)
	tree.set_column_custom_minimum_width(4, 50)

func genRowTree(row, index, wallet):
	var buttonCopy: Texture2D = load("res://icons/copy.svg")
	row.set_text(0, str(index + 1))
	row.set_text(1, wallet.get_address())
	row.set_text(2, wallet.get_public_base64_key())
	row.set_text(3, wallet.get_private_key())
	row.set_text(4, wallet.get_key_scheme())
	row.add_button(1, buttonCopy, index, false, "Copy")
	row.add_button(2, buttonCopy, index, false, "Copy")
	row.add_button(3, buttonCopy, index, false, "Copy")

func loadWallets():
	var wallets = sdk.getWallets()
	print(wallets.size())
	var tree: Tree = get_node("VBoxContainer/listWalletsTree")
	tree.clear()
	var root = tree.create_item()
	
	makeHeaderTree(tree)

	for index in wallets.size():
		var wallet = wallets[index]
		var row = tree.create_item(root)
		genRowTree(row, index, wallet)

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	loadWallets()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_tree_button_clicked(item: TreeItem, column: int, id: int, mouse_button_index: int) -> void:
	var label = item.get_text(column)
	DisplayServer.clipboard_set(label)

func _on_create_wallet_pressed() -> void:
	get_tree().change_scene_to_file("res://root_wallet_create.tscn")

func _on_line_edit_text_changed(new_text: String) -> void:
	if new_text.length() == 66:
		var tree: Tree = get_node("VBoxContainer/listWalletsTree")
		tree.clear()

		var root = tree.create_item()
		var row = tree.create_item(root)
		var wallet = getDetailWallet(new_text)
		genRowTree(row, 0, wallet)
		return
	elif new_text.length() == 0:
		loadWallets()
		return

func getDetailWallet(walletAddress):
	var wallet = sdk.getWalletFromAddress(walletAddress)
	return wallet

func _on_button_pressed() -> void:
	var wallet = sdk.generateAndAddKey()
	loadWallets()


func _on_button_2_pressed() -> void:
	get_tree().change_scene_to_file("res://root_wallet_import.tscn")
