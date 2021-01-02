.set LOCALID_WALLYS_DAD, 1

PetalburgCity_WallysHouse_MapScripts:: @ 8204229
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp: @ 8204234
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther:: @ 820423E
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame: @ 8204247
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHM03Surf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHM03Surf:: @ 8204251
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM03
	setflag FLAG_RECEIVED_HM03
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad:: @ 8204278
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_WallysHouse_EventScript_ReceievedHM03Surf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHM03Surf:: @ 82042A2
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad:: @ 82042AC
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally:: @ 82042B6
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom:: @ 82042C0
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_WallysHouse_EventScript_ReceivedHM03Surf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHM03Surf:: @ 82042D5
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally: @ 82042DF
	.string "너는...\n"
	.string "아- {PLAYER}{K_I} 맞지?\p"
	.string "아깐 민진이와 같이 놀아줘서\n"
	.string "고맙구나...\p"
	.string "그 애는 태어났을 때부터\n"
	.string "몸이 그다지 좋지 않거든\p"
	.string "그래서 잔디마을에 있는 친척 집에서\n"
	.string "잠시 동안 신세 좀 지라고 했단다\p"
	.string "거긴 여기보다 훨씬\n"
	.string "공기가 깨끗한 곳이니깐!\p"
	.string "...그래서 민진이 보러 온 거지?\p"
	.string "미안한데\n"
	.string "민진이라면 벌써 출발했단다\p"
	.string "지금이면 어디쯤 갔으려나...$"

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing: @ 820444D
	.string "민진은 잘 있으려나...$"

PetalburgCity_WallysHouse_Text_PleaseExcuseUs: @ 820446E
	.string "안녕 {PLAYER}{K_AYA}!\p"
	.string "우리 민진이가 잔디마을에 갔을\n"
	.string "때보다 훨씬 건강해져서 말이야\p"
	.string "너한테 신세 졌구나!\p"
	.string "그날 네가 포켓몬 잡는 걸\n"
	.string "도와준 덕분에 민진이가\l"
	.string "이렇게 건강해질 수 있었단다\l"
	.string "정말 고맙구나\p"
	.string "우리 민진이한테 너 같은\n"
	.string "상냥한 친구가 있어서\l"
	.string "다행이라고 생각한단다!\p"
	.string "...아 그래!\p"
	.string "보답이라고 하긴 좀 그렇다만\n"
	.string "이걸 너에게 주마$"

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces: @ 820461A
	.string "파도타기를 쓸 수 있게 되면\n"
	.string "포켓몬들과 함께\l"
	.string "바다를 건널 수도 있단다$"

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon: @ 8204661
	.string "민진이가\n" 
	.string "곧 돌아온다고 했단다\p"
	.string "빨리 돌아온다면 좋겠구나$"

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity: @ 8204698
	.string "에엥!? 그랜드시티에서\n"
	.string "민진이를 만났다고...?\p"
	.string "에이 {PLAYER}\p"
	.string "그 애가 아무리 건강해졌다고 해도\n"
	.string "그렇게 먼 곳까지\l"
	.string "혼자 갈 수 있을 리가 없잖니...$"

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy: @ 8204732
	.string "민진이가 “포켓몬 잡았어!”라며\n"
	.string "정말 기쁜듯이 얘기했단다\p"
	.string "그 애가 그렇게 기뻐하는 모습\n"
	.string "오랜만에 봐$"

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling: @ 82047A7
	.string "우리 남편한테는 비밀인데...\p"
	.string "민진이가 아무에게도 말하지 않고\n"
	.string "잔디마을에서 없어졌대...\p"
	.string "민진이는 몸이 약하지만\n"
	.string "어느샌가 갑자기 활기차졌더구나\p"
	.string "그래도 민진이가 반드시 집으로\n"
	.string "돌아올 거라고 난 믿고 있단다!$"

