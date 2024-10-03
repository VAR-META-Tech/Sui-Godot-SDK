extends TabBar

var sdk = SuiSDK.new()

func make_header_tree (tree: Tree):
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

func gen_row_tree(row, index, wallet):
	var buttonCopy: Texture2D = load("res://icons/copy.svg")
	row.set_text(0, str(index + 1))
	row.set_text(1, wallet.get_address())
	row.set_text(2, wallet.get_public_base64_key())
	row.set_text(3, wallet.get_private_key())
	row.set_text(4, wallet.get_key_scheme())
	row.add_button(1, buttonCopy, index, false, "Copy")
	row.add_button(2, buttonCopy, index, false, "Copy")
	row.add_button(3, buttonCopy, index, false, "Copy")

func load_wallets():
	var wallets = sdk.getWallets()
	print(wallets.size())
	var tree: Tree = get_node("VBoxContainer/listWalletsTree")
	tree.clear()
	var root = tree.create_item()
	
	make_header_tree(tree)

	for index in wallets.size():
		var wallet = wallets[index]
		var row = tree.create_item(root)
		gen_row_tree(row, index, wallet)

func _ready() -> void:
	load_wallets()

func _on_import_private_key_pressed() -> void:
	var privateKey = get_node("VBoxContainer/h_box_import/box_key").text
	if privateKey != "":
		sdk.importFromPrivateKey(privateKey)
		print('ImportFromPrivateKey OK')
		self.load_wallets()


func _on_import_mnemonic_pressed() -> void:
	var privateKey = get_node("VBoxContainer/h_box_import/box_key").text
	if privateKey != "":
		sdk.importFromMnemonic(privateKey)
		print('import mnemonic OK')
		self.load_wallets()


func _on_create_custom_pressed() -> void:
	var scheme = get_node("VBoxContainer/h_box_gen/scheme").get_selected_id()
	var word = get_node("VBoxContainer/h_box_gen/word").get_selected_id()
	if scheme == -1 or word == -1:
		return
	else:
		var schemeText= get_node("VBoxContainer/h_box_gen/scheme").get_item_text(scheme)
		var wordText = get_node("VBoxContainer/h_box_gen/word").get_item_text(word)
		var wallet = sdk.generateWallet(schemeText,wordText)
		var tree: Tree = get_node("VBoxContainer/listWalletsTree")
		tree.clear()
		var root = tree.create_item()
		tree.hide_root = true
		tree.set_column_title(0, 'No')
		tree.set_column_title(1, 'Address')
		tree.set_column_title(2, 'Mnemonic key')
		tree.set_column_title(3, 'Private key')
		tree.set_column_title(4, 'Scheme key')
		tree.set_column_custom_minimum_width(0, 0)
		tree.set_column_custom_minimum_width(1, 400)
		tree.set_column_custom_minimum_width(2, 300)
		tree.set_column_custom_minimum_width(3, 200)
		tree.set_column_custom_minimum_width(4, 50)
		var row = tree.create_item(root)
		var buttonCopy: Texture2D = load("res://icons/copy.svg")
		row.set_text(0, str(1))
		row.set_text(1, wallet.get_address())
		row.set_text(2, wallet.get_mnemonic())
		row.set_text(3, wallet.get_private_key())
		row.set_text(4, wallet.get_key_scheme())
		row.add_button(1, buttonCopy, 0, false, "Copy")
		row.add_button(2, buttonCopy, 0, false, "Copy")
		row.add_button(3, buttonCopy, 0, false, "Copy")


func _on_generate_pressed() -> void:
	var wallet = sdk.generateAndAddKey()
	var tree: Tree = get_node("VBoxContainer/listWalletsTree")
	tree.clear()
	var root = tree.create_item()
	
	make_header_tree(tree)

	var row = tree.create_item(root)
	gen_row_tree(row, 0, wallet)

func _on_load_pressed() -> void:
	load_wallets()

func _on_list_wallets_tree_button_clicked(item: TreeItem, column: int, id: int, mouse_button_index: int) -> void:
	var label = item.get_text(column)
	DisplayServer.clipboard_set(label)
