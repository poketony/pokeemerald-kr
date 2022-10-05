MysteryEventScript_SurfPichu:: @ 8674D3D
	setvaddress MysteryEventScript_SurfPichu
	vgoto_if_unset FLAG_MYSTERY_EVENT_DONE, SurfPichu_GiveIfPossible
	returnram

SurfPichu_GiveIfPossible: @ 8674D4C
	specialvar VAR_EVENT_PICHU_SLOT, CalculatePlayerPartyCount
	compare VAR_EVENT_PICHU_SLOT, PARTY_SIZE
	vgoto_if_eq SurfPichu_FullParty
	setflag FLAG_MYSTERY_EVENT_DONE
	vcall SurfPichu_GiveEgg
	lock
	faceplayer
	vmessage sText_MysteryGiftEgg
	waitmessage
	waitbuttonpress
	playfanfare MUS_OBTAIN_ITEM
	waitfanfare
	release
	end

SurfPichu_FullParty: @ 8674D73
	lock
	faceplayer
	vmessage sText_FullParty
	waitmessage
	waitbuttonpress
	release
	end

SurfPichu_GiveEgg: @ 8674D7E
	giveegg SPECIES_PICHU
	setmonobedient VAR_EVENT_PICHU_SLOT
	setmonmetlocation VAR_EVENT_PICHU_SLOT, METLOC_FATEFUL_ENCOUNTER
	compare VAR_EVENT_PICHU_SLOT, 1
	vgoto_if_eq SurfPichu_Slot1
	compare VAR_EVENT_PICHU_SLOT, 2
	vgoto_if_eq SurfPichu_Slot2
	compare VAR_EVENT_PICHU_SLOT, 3
	vgoto_if_eq SurfPichu_Slot3
	compare VAR_EVENT_PICHU_SLOT, 4
	vgoto_if_eq SurfPichu_Slot4
	compare VAR_EVENT_PICHU_SLOT, 5
	vgoto_if_eq SurfPichu_Slot5
	return

SurfPichu_Slot1: @ 8674DC0
	setmonmove 1, 2, MOVE_SURF
	return

SurfPichu_Slot2:: @ 8674DC6
	setmonmove 2, 2, MOVE_SURF
	return

SurfPichu_Slot3: @ 8674DCC
	setmonmove 3, 2, MOVE_SURF
	return

SurfPichu_Slot4: @ 8674DD2
	setmonmove 4, 2, MOVE_SURF
	return

SurfPichu_Slot5: @ 8674DD8
	setmonmove 5, 2, MOVE_SURF
	return

sText_MysteryGiftEgg:
	.string "이상한 소포를 이용해\n"
	.string "주셔서 감사합니다!\p"
	.string "받으세요 포켓몬센터에서\n"
	.string "이 포켓몬의 알을\l"
	.string "선물합니다!\p"
	.string "소중하게\n"
	.string "키워주세요!$"
	// ふしぎなおくりもの を ごりようｎ
	// いただき ありがとう ございます!ｐ
	// どうぞ ポケモンセンタ- からｎ
	// この ポケモンの たまごをｌ
	// プレゼント いたします!ｐ
	// だいじに そだててｎ
	// ください!

sText_FullParty:
	.string "이런 지닌 포켓몬이\n"
	.string "가득한 모양이군요\p"
	.string "포켓몬을 PC에 맡기고 나서\n"
	.string "다시 와주십시오$"
	// おや てもちがｎ
	// いっぱいの ようですねｐ
	// ポケモンを パソコンに あずけてからｎ
	// もういちど おこしください
