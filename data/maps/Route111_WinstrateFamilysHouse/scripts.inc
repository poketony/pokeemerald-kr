.set LOCALID_VIVI, 1
.set LOCALID_VICTOR, 2
.set LOCALID_VICTORIA, 3
.set LOCALID_VICKY, 4

Route111_WinstrateFamilysHouse_MapScripts:: @ 822A48C
	.byte 0

Route111_WinstrateFamilysHouse_EventScript_Victor:: @ 822A48D
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTOR
	msgbox Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Victoria:: @ 822A4A2
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICTORIA
	goto_if_set FLAG_RECEIVED_MACHO_BRACE, Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace
	msgbox Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace, MSGBOX_DEFAULT
	giveitem ITEM_MACHO_BRACE
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MACHO_BRACE
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_ReceivedMachoBrace:: @ 822A4DA
	msgbox Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vivi:: @ 822A4E8
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VIVI
	msgbox Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_Vicky:: @ 822A4FD
	lock
	faceplayer
	setvar VAR_0x8008, LOCALID_VICKY
	goto_if_set FLAG_TEMP_4, Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrong, MSGBOX_DEFAULT
	setflag FLAG_TEMP_4
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_AlreadySpokenTo:: @ 822A51E
	msgbox Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort, MSGBOX_DEFAULT
	goto Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection
	end

Route111_WinstrateFamilysHouse_EventScript_FaceOriginalDirection:: @ 822A52C
	closemessage
	applymovement VAR_0x8008, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

Route111_WinstrateFamilysHouse_Text_MySonIsStrongerThanYou: @ 822A539
	.string "너 정도로 포켓몬을 능숙하게\n"
	.string "다루는 트레이너는 처음이군!\p"
	.string "하지만 너보다\n"
	.string "우리 아들이 더 강하다!\p"
	.string "뭐니 뭐니 해도 포켓몬리그에\n"
	.string "도전하러 갔을 정도니 말이다!$"

Route111_WinstrateFamilysHouse_Text_LikeYouToHaveMachoBrace: @ 822A5F4
	.string "우리 가족 모두는\n"
	.string "교정깁스로 포켓몬을\l"
	.string "단련시키고 있어요!\p"
	.string "우리 가족 모두에게 이긴\n"
	.string "당신에겐 필요 없을지도 모르지만\l"
	.string "꼭 받아주셨으면 해요!$"

Route111_WinstrateFamilysHouse_Text_PassionateAboutBattles: @ 822A6B4
	.string "우리는 포켓몬 승부에\n"
	.string "정열을 쏟아붓고 있어요!$"

Route111_WinstrateFamilysHouse_Text_StrongerFamilyMembers: @ 822A6F7
	.string "아빠보다 엄마가 강하고\p"
	.string "엄마보다 내가 강하고\p"
	.string "나보다 할머니가 강하지\p"
	.string "하지만 할머니보다 강한 건\n"
	.string "우리 오빠야!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrong: @ 822A780
	.string "네가 아무리 강해도\n"
	.string "우리 손자를 만나면\l"
	.string "패배의 눈물을 흘리게 될 게다...\p"
	.string "우리 가족이 알고 있는\n"
	.string "그 어떤 트레이너보다\l"
	.string "강했으니까 말이다!\p"
	.string "손주 녀석도 지금쯤\n"
	.string "포켓몬리그 챔피언에\l"
	.string "도전하고 있겠구먼\p"
	.string "아니면 내 손주답게\n"
	.string "벌써 챔피언이\l"
	.string "돼 있을지도 모르지... 이히히!$"

Route111_WinstrateFamilysHouse_Text_GrandsonStrongShort: @ 822A89B
	.string "손주 녀석도 지금쯤\n"
	.string "포켓몬리그 챔피언에\l"
	.string "도전하고 있겠구먼\p"
	.string "아니면 내 손주답게\n"
	.string "벌써 챔피언이\l"
	.string "돼 있을지도 모르지... 이히히!$"

