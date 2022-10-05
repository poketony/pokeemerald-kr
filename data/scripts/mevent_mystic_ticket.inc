MysteryEventScript_MysticTicket:: @ 867550B
	setvaddress MysteryEventScript_MysticTicket
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_MYSTIC_TICKET, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_LUGIA, MysticTicket_Obtained
	vgoto_if_set FLAG_CAUGHT_HO_OH, MysticTicket_Obtained
	checkitem ITEM_MYSTIC_TICKET, 1
	compare VAR_RESULT, TRUE
	vgoto_if_eq MysticTicket_Obtained
	vmessage sText_MysticTicketForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_MYSTIC_TICKET, 1
	compare VAR_RESULT, FALSE
	vgoto_if_eq MysticTicket_NoBagSpace
	giveitem ITEM_MYSTIC_TICKET
	setflag FLAG_ENABLE_SHIP_NAVEL_ROCK
	setflag FLAG_RECEIVED_MYSTIC_TICKET
	vmessage sText_MysticTicketUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_NoBagSpace: @ 867556F
	vmessage sText_MysticTicketBagFull
	waitmessage
	waitbuttonpress
	release
	end

MysticTicket_Obtained: @ 8675578
	vmessage sText_MysticTicketThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysticTicketForYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다!\l"
	.string "{PLAYER}님이시군요\p"
	.string "손님 앞으로\n"
	.string "이 티켓이\l"
	.string "도착했습니다$"

sText_MysticTicketUseAtPort:
	.string "해안시티의 선착장에서\n"
	.string "쓸 수 있는 모양이군요\p"
	.string "한번 이용해 보시는 게\n"
	.string "어떻겠습니까?$"

sText_MysticTicketThankYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다$"

sText_MysticTicketBagFull:
	.string "하지만 {PLAYER}님!\n"
	.string "중요한 물건이 가득하군요\p"
	.string "PC에 맡기고 나서\n"
	.string "다시 와주십시오$"
