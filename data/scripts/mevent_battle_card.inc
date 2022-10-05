MysteryEventScript_BattleCard:: @ 867513C
	setvaddress MysteryEventScript_BattleCard
	vgoto_if_set FLAG_MYSTERY_EVENT_DONE, MysteryEventScript_BattleCardInfo
	setorcopyvar VAR_RESULT, GET_CARD_BATTLES_WON
	specialvar VAR_0x8008, GetMysteryEventCardVal
	compare VAR_0x8008, REQUIRED_CARD_BATTLES
	vgoto_if_ne MysteryEventScript_BattleCardInfo
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard_WonPrize
	waitmessage
	waitbuttonpress
	giveitem ITEM_POTION
	release
	setflag FLAG_MYSTERY_EVENT_DONE
	end

MysteryEventScript_BattleCardInfo: @ 8675179
	lock
	faceplayer
	vmessage sText_MysteryGiftBattleCountCard
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftBattleCountCard:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다\p"
	.string "손님이 가지고 계신\n"
	.string "대전 카운트 카드는\p"
	.string "같은 카드를 가지고 있는\n"
	.string "트레이너와 대전하는 것으로\l"
	.string "전적을 기록할 수 있습니다\p"
	.string "꼭 같은 카드를 가진\n"
	.string "트레이너와 대전해 주세요\p"
	.string "또한 뉴스를 통해서\n"
	.string "랭킹을 볼 수 있으니\l"
	.string "꼭 이용해 주세요!$"
	// ふしぎなおくりもの を ごりようｎ
	// いただき ありがとう ございますｐ
	// あなたの もっているｎ
	// たいせん カウント カ-ド はｐ
	// おなじ カ-ドを もっているｎ
	// トレ-ナ-と たいせん することでｌ
	// せいせきが きろくされて いきますｐ
	// ぜひ おなじ カ-ドをもつｎ
	// トレ-ナ-と たいせん してくださいｐ
	// また ニュ-スを よみこむことでｎ
	// ランキングを みれますのでｌ
	// ぜひ ごりよう ください!

sText_MysteryGiftBattleCountCard_WonPrize:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다\p"
	.string "축하합니다!\p"
	.string "지금 대전에서 3승을 거둔\n"
	.string "트레이너에게는 선물을\l"
	.string "드리고 있습니다!\p"
	.string "앞으로도 팍팍\n"
	.string "대전을 즐겨 주세요!$"
	// ふしぎなおくりもの を ごりようｎ
	// いただき ありがとう ございますｐ
	// おめでとう ございます!ｐ
	// ただいま たいせんで 3しょうしたｎ
	// トレ-ナ-には プレゼントをｌ
	// さしあげて います!ｐ
	// これからも どんどんｎ
	// たいせんを たのしんで ください!
