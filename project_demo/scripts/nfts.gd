extends TabBar

var sdk = SuiSDK.new()
var wallets = []
const NFT_PACKAGE_ID = "0xe82276e2634220259709b827bf84828940cad87cdf061d396e6a569b9b4d9321";
const NFT_OBJECT_TYPE = "0xe82276e2634220259709b827bf84828940cad87cdf061d396e6a569b9b4d9321::nft::NFT";

func _ready():
	self.load_wallets()

func  load_wallets():
	wallets = sdk.getWallets()
	var box= get_node("VBoxContainer/h_box_address/address_box")
	box.clear()
	for i in wallets.size():
		var wallet = wallets[i]
		box.add_item(wallet.get_address(),i)
		
func _on_btn_send_pressed() -> void:
	var nft = get_node("VBoxContainer/h_box_transfer/nft_id").text
	var recipient = get_node("address").text
	var uri = get_node("VBoxContainer/h_box_mint/nft_uri").text
	if recipient == ""  or nft == "":
		get_node("VBoxContainer/result").text = "enter nft and recipient info"
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("VBoxContainer/result").text = "Please enter your address"
	else:
		var result = sdk.transferNft(NFT_PACKAGE_ID,get_node("VBoxContainer/h_box_address/address_box").get_item_text(address),nft,recipient)
		get_node("VBoxContainer/result").text = result

func _http_request_completed(result: int, response_code: int, headers: PackedStringArray, body: PackedByteArray, image: Image):
	var headersString: String = " ".join(headers)
	if "png" in headersString:
		image.load_png_from_buffer(body)
	elif "image/jpeg" in headersString || "image/jpg" in headersString:
		image.load_jpg_from_buffer(body)

func _on_btn_load_pressed() -> void:
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("VBoxContainer/result").text = "Please enter your address"
	else:
		var sender = get_node("VBoxContainer/h_box_address/address_box").get_item_text(address)
		var nftsList = get_node("VBoxContainer/ScrollContainer/nftsList")
		for nft in nftsList.get_children():
			nftsList.remove_child(nft)

		var nfts = sdk.getWalletObjects(sender, NFT_OBJECT_TYPE)
		print(nfts.size())

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
			image.resize(130, 130)
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


func _on_btn_mint_pressed() -> void:
	var name = get_node("VBoxContainer/h_box_mint/nft_name").text
	var desc = get_node("VBoxContainer/h_box_mint/nft_description").text
	var uri = get_node("VBoxContainer/h_box_mint/nft_uri").text
	if name == ""  or desc == "" or uri == "":
		get_node("VBoxContainer/result").text = "Please enter nft info"
	var address = get_node("VBoxContainer/h_box_address/address_box").get_selected_id()
	if address == -1:
		get_node("VBoxContainer/result").text = "Please enter your address"
	else:
		var result = sdk.mintNft(NFT_PACKAGE_ID,get_node("VBoxContainer/h_box_address/address_box").get_item_text(address),name,desc,uri)
		get_node("VBoxContainer/result").text = result
