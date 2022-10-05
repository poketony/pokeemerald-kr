MysteryEventScript_OldSeaMap:: @ 86757F4
	setvaddress MysteryEventScript_OldSeaMap
	lock
	faceplayer
	vgoto_if_set FLAG_RECEIVED_OLD_SEA_MAP, OldSeaMap_Obtained
	vgoto_if_set FLAG_CAUGHT_MEW, OldSeaMap_Obtained
	checkitem ITEM_OLD_SEA_MAP, 1
	compare VAR_RESULT, TRUE
	vgoto_if_eq OldSeaMap_Obtained
	vmessage sText_MysteryGiftOldSeaMapForYou
	waitmessage
	waitbuttonpress
	checkitemspace ITEM_OLD_SEA_MAP, 1
	compare VAR_RESULT, FALSE
	vgoto_if_eq OldSeaMap_NoBagSpace
	giveitem ITEM_OLD_SEA_MAP
	setflag FLAG_ENABLE_SHIP_FARAWAY_ISLAND
	setflag FLAG_RECEIVED_OLD_SEA_MAP
	vmessage sText_MysteryGiftOldSeaMapUseAtPort
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_NoBagSpace: @ 867584F
	vmessage sText_MysteryGiftOldSeaMapBagFull
	waitmessage
	waitbuttonpress
	release
	end

OldSeaMap_Obtained: @ 8675858
	vmessage sText_MysteryGiftOldSeaMapThankYou
	waitmessage
	waitbuttonpress
	release
	end

sText_MysteryGiftOldSeaMapForYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다!\l"
	.string "{PLAYER}님이시군요\p"
	.string "손님 앞으로\n"
	.string "이 해도가\l"
	.string "도착했습니다$"

sText_MysteryGiftOldSeaMapUseAtPort:
	.string "해안시티의 선착장에서\n"
	.string "쓸 수 있는 모양이군요\p"
	.string "한번 이용해 보시는 게\n"
	.string "어떻겠습니까?$"

sText_MysteryGiftOldSeaMapThankYou:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다$"

sText_MysteryGiftOldSeaMapBagFull:
	.string "하지만 {PLAYER}님!\n"
	.string "중요한 물건이 가득하군요\p"
	.string "PC에 맡기고 나서\n"
	.string "다시 와주십시오$"
