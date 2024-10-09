extends TabBar

var wallets = []
var suiSDK = SuiSDK.new()
var objectType = "0xe82276e2634220259709b827bf84828940cad87cdf061d396e6a569b9b4d9321::nft::NFT"

func _http_request_completed(result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray, image: Image):
	var headersString: String = " ".join(headers)
	print(headersString)
	if "png" in headersString:
		image.load_png_from_buffer(body)
	elif "image/jpeg" in headersString || "image/jpg" in headersString:
		image.load_jpg_from_buffer(body)

func handleCopyNftId(nftId: String):
	DisplayServer.clipboard_set(nftId)
	Global.showToast("Copied")

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
			var nftId: String = nftContent.id.id
			var vBox = VBoxContainer.new()
			var hBox = HBoxContainer.new()
			var image = Image.new()

			var httpRequest = HTTPRequest.new()
			self.add_child(httpRequest)

			var idLabel: Label = Label.new()
			var idTextLabel: Label = Label.new()
			idLabel.text = "ID: #"
			idTextLabel.text = nftId.substr(0, 6) + "..." + nftId.substr(nftId.length() - 6, nftId.length())

			var buttonCopy: Texture2D = load("res://icons/copy.svg")
			var boxId = HBoxContainer.new()
			var buttonCopyId = TextureButton.new()
			buttonCopyId.texture_normal = buttonCopy
			buttonCopyId.connect("pressed", func(): handleCopyNftId(nftId))
			boxId.add_child(idLabel)
			boxId.add_child(idTextLabel)
			boxId.add_child(buttonCopyId)
			boxId.add_theme_constant_override("separation", 0)

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
			vBox.add_child(boxId)
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
	Global.changeScene(Global.SCREEN.ROOT_NFT_MINT)


func _on_action_2_pressed() -> void:
	Global.changeScene(Global.SCREEN.ROOT_NFT_TRANSFER)
