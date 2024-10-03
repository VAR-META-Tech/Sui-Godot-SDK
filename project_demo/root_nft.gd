extends TabBar

var wallets = []
var suiSDK = SuiSDK.new()
var objectType = "0x48a557eb090729457000b7303796c4447abea2362b009988b3ab7445b60ed6a3::nft::NFT"

func _http_request_completed(result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray, image: Image):
	var headersString: String = " ".join(headers)
	if "png" in headersString:
		image.load_png_from_buffer(body)
	elif "image/jpeg" in headersString || "image/jpg" in headersString:
		image.load_jpg_from_buffer(body)

func getListNfts():
	if Global.currentWallet != "":
		var nftsList = get_node("VBoxContainer/ScrollContainer/nftsList")
		for nft in nftsList.get_children():
			nftsList.remove_child(nft)

		var nfts = suiSDK.getWalletObjects(Global.currentWallet, objectType)

		for nft in nfts:
			var nftContent = JSON.parse_string(nft.get_content())
			print(nftContent)
			var nftURI = nftContent.url
			var vBox = VBoxContainer.new()
			var hBox = HBoxContainer.new()
			var image = Image.new()

			var httpRequest = HTTPRequest.new()
			self.add_child(httpRequest)

			var nameLabel: Label = Label.new()
			var descriptionLabel: Label = Label.new()
			var uriLabel: Label = Label.new()

			nameLabel.text = nftContent.name
			nameLabel.max_lines_visible = 2
			descriptionLabel.text = nftContent.description
			descriptionLabel.max_lines_visible = 2
			descriptionLabel.autowrap_mode = TextServer.AUTOWRAP_WORD_SMART
			uriLabel.text = nftContent.url

			await httpRequest.request_completed.connect(self._http_request_completed.bind(image))
			httpRequest.request(nftURI)
			await httpRequest.request_completed
			image.resize(200, 200)
			var textureImage = ImageTexture.create_from_image(image)
			var texture = TextureRect.new()
			
			texture.texture = textureImage
			vBox.add_child(texture)
			vBox.add_child(nameLabel)
			vBox.add_child(descriptionLabel)
			hBox.add_child(vBox)
			hBox.add_theme_constant_override('h_separation', 20)
			hBox.add_theme_constant_override('v_separation', 20)
			#vBox.add_child(uriLabel)
			nftsList.add_child(hBox)

func getWallets():
	wallets = suiSDK.getWallets()
	
	return wallets
	
func addWalletsToPopup():
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer2/walletsOption")
	walletsOption.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		walletsOption.add_item(wallet.get_address(), i)
	walletsOption.select(-1)

func setCurrentWallet(address):
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer2/walletsOption")
	var walletIndex = -1
	for id in wallets.size():
		if wallets[id].get_address() == address:
			walletIndex = id
	walletsOption.select(walletIndex)

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	getWallets()
	addWalletsToPopup()
	getListNfts()


# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(_delta: float) -> void:
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer2/walletsOption")
	if Global.currentWallet != "" && walletsOption.text != Global.currentWallet:
		setCurrentWallet(Global.currentWallet)


func _on_wallets_option_item_selected(index: int) -> void:
	var walletsOption: OptionButton = get_node("VBoxContainer/VBoxContainer2/walletsOption")
	var walletAddress = walletsOption.text
	Global.currentWallet = walletAddress
	getListNfts()


func _on_action_1_pressed() -> void:
	get_tree().change_scene_to_file("res://root_nft_mint.tscn")


func _on_action_2_pressed() -> void:
	get_tree().change_scene_to_file("res://root_nft_transfer.tscn")
