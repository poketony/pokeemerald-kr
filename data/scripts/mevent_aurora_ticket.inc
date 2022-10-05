MysteryEventScript_AuroraTicket:: @ 867533C
	setvaddress MysteryEventScript_AuroraTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_AURORA_TICKET, AuroraTicket_Obtained
	vgoto_if_set FLAG_BATTLED_DEOXYS, AuroraTicket_Obtained
	checkitem ITEM_AURORA_TICKET, 1
	compare VAR_RESULT, TRUE
	vgoto_if_eq AuroraTicket_Obtained
	vmessage sText_AuroraTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_AURORA_TICKET, 1
	compare VAR_RESULT, FALSE
	vgoto_if_eq AuroraTicket_NoBagSpace
	giveitem ITEM_AURORA_TICKET
	setflag FLAG_ENABLE_SHIP_BIRTH_ISLAND
	setflag FLAG_RECEIVED_AURORA_TICKET
	vmessage sText_AuroraTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_NoBagSpace: @ 8675397
	vmessage sText_AuroraTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

AuroraTicket_Obtained: @ 86753A0
	vmessage sText_AuroraTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_AuroraTicketForYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다!\l"
	.string "{PLAYER}님이시군요\p"
	.string "손님 앞으로\n"
	.string "이 티켓이\l"
	.string "도착했습니다$"
	// ふしぎなおくりもの を ごりようｎ
	// いただき ありがとう ございます!ｌ
	// §あさま ですねｐ
	// あなたさま あてにｎ
	// この かいずがｌ
	// おくられて きました

sText_AuroraTicketUseAtPort:
	.string "해안시티의 선착장에서\n"
	.string "쓸 수 있는 모양이군요\p"
	.string "한번 이용해 보시는 게\n"
	.string "어떻겠습니까?$"
	// ミナモシティの ふなつきば でｎ
	// つかえる ようですねｐ
	// ぜひ ごりよう してみてはｎ
	// いかがでしょうか?

sText_AuroraTicketThankYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다$"
	// ふしぎなおくりもの を ごりようｎ
	// いただき ありがとう ございました

sText_AuroraTicketBagFull:
	.string "하지만 {PLAYER}님!\n"
	.string "중요한 물건이 가득하군요\p"
	.string "PC에 맡기고 나서\n"
	.string "다시 와주십시오$"
	// しかし §あさま!ｎ
	// たいせつなものが いっぱい ですｐ
	// パソコンに あずけてからｎ
	// また きてください
