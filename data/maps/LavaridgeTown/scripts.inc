.set LOCALID_RIVAL_ON_BIKE, 7
.set LOCALID_RIVAL, 8

LavaridgeTown_MapScripts:: @ 81EA4D3
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, LavaridgeTown_OnFrame
	.byte 0

LavaridgeTown_OnTransition: @ 81EA4DE
	setflag FLAG_VISITED_LAVARIDGE_TOWN
	call_if_set FLAG_WHITEOUT_TO_LAVARIDGE, LavaridgeTown_EventScript_ClearLavaridgeWhiteOut
	call_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, LavaridgeTown_EventScript_ShowMtChimneyTrainers
	call Common_EventScript_SetupRivalGfxId
	call Common_EventScript_SetupRivalOnBikeGfxId
	compare VAR_LAVARIDGE_TOWN_STATE, 1
	call_if_eq LavaridgeTown_EventScript_CheckSetRivalPos
	compare VAR_LAVARIDGE_TOWN_STATE, 1
	call_if_eq LavaridgeTown_EventScript_HideMapNamePopup
	end

LavaridgeTown_EventScript_ClearLavaridgeWhiteOut:: @ 81EA514
	clearflag FLAG_WHITEOUT_TO_LAVARIDGE
	return

LavaridgeTown_EventScript_CheckSetRivalPos:: @ 81EA518
	getplayerxy VAR_0x8004, VAR_0x8005
	compare VAR_0x8004, 9
	goto_if_eq LavaridgeTown_EventScript_SetRivalPos
	return

LavaridgeTown_EventScript_SetRivalPos:: @ 81EA529
	setobjectxyperm LOCALID_RIVAL, 11, 9
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 9, 8
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_UP
	clearflag FLAG_HIDE_LAVARIDGE_TOWN_RIVAL
	return

LavaridgeTown_EventScript_ShowMtChimneyTrainers:: @ 81EA53F
	clearflag FLAG_HIDE_MT_CHIMNEY_TRAINERS
	return

LavaridgeTown_EventScript_HideMapNamePopup:: @ 81EA543
	setflag FLAG_HIDE_MAP_NAME_POPUP
	return

LavaridgeTown_OnFrame: @ 81EA547
	map_script_2 VAR_LAVARIDGE_TOWN_STATE, 1, LavaridgeTown_EventScript_RivalGiveGoGoggles
	.2byte 0

LavaridgeTown_EventScript_RivalGiveGoGoggles:: @ 81EA551
	lockall
	getplayerxy VAR_0x8008, VAR_0x8009
	compare VAR_0x8008, 9
	call_if_eq LavaridgeTown_EventScript_RivalNoticePlayer
	compare VAR_0x8008, 9
	call_if_ne LavaridgeTown_EventScript_RivalExitHerbShop
	delay 20
	checkplayergender
	compare VAR_RESULT, MALE
	call_if_eq LavaridgeTown_EventScript_PlayMayMusic
	compare VAR_RESULT, FEMALE
	call_if_eq LavaridgeTown_EventScript_PlayBrendanMusic
	compare VAR_0x8008, 9
	call_if_eq LavaridgeTown_EventScript_RivalApproachPlayer1
	compare VAR_0x8008, 9
	call_if_ne LavaridgeTown_EventScript_RivalApproachPlayer2
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LavaridgeTown_EventScript_MayGiveGoGoggles
	compare VAR_RESULT, FEMALE
	goto_if_eq LavaridgeTown_EventScript_BrendanGiveGoGoggles
	end

LavaridgeTown_EventScript_MayGiveGoGoggles:: @ 81EA5B5
	msgbox LavaridgeTown_Text_MayNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_MayExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_BrendanGiveGoGoggles:: @ 81EA5DA
	msgbox LavaridgeTown_Text_BrendanNiceBadgesTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_GO_GOGGLES
	setflag FLAG_RECEIVED_GO_GOGGLES
	msgbox LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad, MSGBOX_DEFAULT
	goto LavaridgeTown_EventScript_RivalExit
	end

LavaridgeTown_EventScript_RivalExit:: @ 81EA5FF
	closemessage
	removeobject LOCALID_RIVAL
	addobject LOCALID_RIVAL_ON_BIKE
	delay 30
	compare VAR_0x8008, 9
	call_if_eq LavaridgeTown_EventScript_RivalExit1
	compare VAR_0x8008, 9
	call_if_ne LavaridgeTown_EventScript_RivalExit2
	removeobject LOCALID_RIVAL_ON_BIKE
	setvar VAR_LAVARIDGE_TOWN_STATE, 2
	clearflag FLAG_HIDE_MAP_NAME_POPUP
	savebgm MUS_DUMMY
	fadedefaultbgm
	releaseall
	end

LavaridgeTown_EventScript_PlayMayMusic:: @ 81EA630
	playbgm MUS_ENCOUNTER_MAY, 1
	return

LavaridgeTown_EventScript_PlayBrendanMusic:: @ 81EA635
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	return

LavaridgeTown_EventScript_RivalNoticePlayer:: @ 81EA63A
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExitHerbShop:: @ 81EA65C
	opendoor 12, 15
	waitdooranim
	addobject LOCALID_RIVAL
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalExitHerbShop
	waitmovement 0
	closedoor 12, 15
	waitdooranim
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer1:: @ 81EA6A1
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalApproachPlayer2:: @ 81EA6AC
	applymovement LOCALID_RIVAL, LavaridgeTown_Movement_RivalApproachPlayer2
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit1:: @ 81EA6B7
	applymovement OBJ_EVENT_ID_PLAYER, LavaridgeTown_Movement_PlayerWatchRivalExit
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit1
	waitmovement 0
	return

LavaridgeTown_EventScript_RivalExit2:: @ 81EA6C9
	applymovement LOCALID_RIVAL_ON_BIKE, LavaridgeTown_Movement_RivalExit2
	waitmovement 0
	return

LavaridgeTown_Movement_RivalExit2: @ 81EA6D4
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_up
	step_end

LavaridgeTown_Movement_PlayerWatchRivalExit: @ 81EA6DF
	delay_16
	delay_8
	walk_in_place_fastest_right
	step_end

LavaridgeTown_Movement_RivalExit1: @ 81EA6E3
	walk_fast_down
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

LavaridgeTown_Movement_RivalApproachPlayer2: @ 81EA6ED
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

LavaridgeTown_Movement_RivalApproachPlayer1: @ 81EA6F4
	walk_left
	walk_left
	walk_up
	step_end

LavaridgeTown_Movement_RivalExitHerbShop: @ 81EA6F8
	walk_down
	step_end

LavaridgeTown_EventScript_HotSpringsTrigger:: @ 81EA6FA
	specialvar VAR_RESULT, GetPlayerFacingDirection
	compare VAR_RESULT, DIR_SOUTH
	goto_if_eq LavaridgeTown_EventScript_EnteredHotSprings
	end

LavaridgeTown_EventScript_EnteredHotSprings:: @ 81EA70B
	incrementgamestat GAME_STAT_ENTERED_HOT_SPRINGS
	end

LavaridgeTown_EventScript_ExpertM:: @ 81EA70E
	msgbox LavaridgeTown_Text_HotSpringsNeverRunDry, MSGBOX_NPC
	end

LavaridgeTown_EventScript_OldMan:: @ 81EA717
	msgbox LavaridgeTown_Text_PokemonNippedBackside, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_Twin:: @ 81EA720
	msgbox LavaridgeTown_Text_BatheInHotSpringsEveryDay, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman1:: @ 81EA729
	msgbox LavaridgeTown_Text_IfPokemonInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_HotSpringsOldWoman2:: @ 81EA732
	msgbox LavaridgeTown_Text_HotSpringsClaims, MSGBOX_NPC
	end

LavaridgeTown_EventScript_ExpertF:: @ 81EA73B
	msgbox LavaridgeTown_Text_OhYouLikeHotSprings, MSGBOX_NPC
	end

LavaridgeTown_EventScript_EggWoman:: @ 81EA744
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_LAVARIDGE_EGG, LavaridgeTown_EventScript_ReceivedEgg
	msgbox LavaridgeTown_Text_HaveEggWillYouTakeIt, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LavaridgeTown_EventScript_DeclineEgg
	getpartysize
	compare VAR_RESULT, PARTY_SIZE
	goto_if_eq LavaridgeTown_EventScript_NoRoomForEgg
	msgbox LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_LAVARIDGE_EGG
	playfanfare MUS_OBTAIN_ITEM
	message LavaridgeTown_Text_ReceivedTheEgg
	waitfanfare
	giveegg SPECIES_WYNAUT
	release
	end

LavaridgeTown_EventScript_ReceivedEgg:: @ 81EA787
	msgbox LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_NoRoomForEgg:: @ 81EA791
	msgbox LavaridgeTown_Text_NoRoomForThisEgg, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_DeclineEgg:: @ 81EA79B
	msgbox LavaridgeTown_Text_AsYouWishThen, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_EventScript_TownSign:: @ 81EA7A5
	msgbox LavaridgeTown_Text_TownSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_GymSign:: @ 81EA7AE
	msgbox LavaridgeTown_Text_GymSign, MSGBOX_SIGN
	end

LavaridgeTown_EventScript_HerbShopSign:: @ 81EA7B7
	msgbox LavaridgeTown_Text_HerbShopSign, MSGBOX_SIGN
	end

LavaridgeTown_Text_MayNiceBadgesTakeThis: @ 81EA7C0
	.string "봄이: {PLAYER}! 오랜만이야!\p"
	.string "어라? 내가 온천에\n"
	.string "들어간 사이에\l"
	.string "용암마을의 체육관 배지를\l"
	.string "손에 넣었구나!\p"
	.string "꽤 포켓몬을 모으고\n"
	.string "키우고 있구나!\p"
	.string "그럼 이걸 줘도\n"
	.string "괜찮겠네$"

LavaridgeTown_Text_MayExplainGoGogglesChallengeDad: @ 81EA897
	.string "봄이: 그 고고고글이 있으면\n"
	.string "111번 도로에 있는 사막에도\l"
	.string "갈 수 있게 돼!\p"
	.string "그건 그렇고 {PLAYER}\n"
	.string "포켓몬체육관에 도전이라니...\p"
	.string "나한테 지고 싶지 않아서\n"
	.string "열심히 하고 있구나!\p"
	.string "그럼 난 등화도시에서 {PLAYER}의\n"
	.string "아빠에게 도전해 볼까?\p"
	.string "{PLAYER} 그럼 다음에 보자!$"

LavaridgeTown_Text_BrendanNiceBadgesTakeThis: @ 81EA9A2
	.string "휘웅: {PLAYER} 오랜만이네\n"
	.string "상태는 어때?\p"
	.string "음...\n"
	.string "배지를 제법 모았구나\p"
	.string "그럼\n"
	.string "이걸 줄게$"

LavaridgeTown_Text_BrendanExplainGoGogglesChallengeDad: @ 81EAA2E
	.string "휘웅: 그걸 가지고 있으면\n"
	.string "111번 도로에 있는 사막에도\l"
	.string "들어갈 수 있어\p"
	.string "사막에서밖에 만날 수 없는\n"
	.string "포켓몬도 있을 테니까\l"
	.string "괜찮다면 가보지 그래...?\p"
	.string "나는...\n"
	.string "등화도시의 체육관 관장 종길님에게\l"
	.string "도전해 볼까...\p"
	.string "{PLAYER}의 아빠\n"
	.string "{PLAYER}{K_WAGWA} 달리 강해 보이니까\p"
	.string "그럼!$"

LavaridgeTown_Text_HaveEggWillYouTakeIt: @ 81EAB80
	.string "알을 부화시키려고\n"
	.string "모래찜질을 시켜서\l"
	.string "따뜻하게 해주고 있었는데\p"
	.string "그것만으로는\n"
	.string "안 되는 모양이더구먼...\p"
	.string "왠지 건강한 포켓몬이랑 같이\n"
	.string "데리고 걸어다니는 게\l"
	.string "좋다고 하던데...\p"
	.string "자네 트레이너지?\n"
	.string "게다가 건강한 포켓몬도\l"
	.string "데리고 있고\p"
	.string "어떤가?\n"
	.string "알을 부화시켜 보지 않겠나?$"

LavaridgeTown_Text_HopeYoullWalkPlentyWithEgg: @ 81EACC0
	.string "알이랑 같이\n"
	.string "많-이 걷고 오게나!$"

LavaridgeTown_Text_ReceivedTheEgg: @ 81EACF4
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "알을 받았다!$"

LavaridgeTown_Text_NoRoomForThisEgg: @ 81EAD09
	.string "어라? 포켓몬이 가득하구나\p"
	.string "알을 데리고 갈 수 있게 되면\n"
	.string "또 오거라$"

LavaridgeTown_Text_AsYouWishThen: @ 81EAD44
	.string "그런가...\p"
	.string "뭐 알을 부화시키고 싶어지면\n"
	.string "그때 또 와주거라$"

LavaridgeTown_Text_EverySoOftenEggFoundAtDayCare: @ 81EAD9E
	.string "포켓몬알은\n"
	.string "가끔 키우미집에서 발견된다...고\p"
	.string "하는 소문을 들은 적이 있구나$"

LavaridgeTown_Text_HotSpringsNeverRunDry: @ 81EAE03
	.string "퍼도 퍼도 따뜻한 물이 나와\n"
	.string "주전자도 아니면서 따뜻한 물이 나와\p"
	.string "...이거 참 신기하지 않나?\p"
	.string "화산이 가까이 있는 곳에서는\n"
	.string "용암의 열로 지하수가\l"
	.string "데워지게 되거든!$"

LavaridgeTown_Text_PokemonNippedBackside: @ 81EAEE1
	.string "이렇게 모래에 묻혀 있으면\n"
	.string "하아아...\p"
	.string "따뜻해서 좋은 기분...\p"
	.string "...음? 아얏!\p"
	.string "포켓몬한테 엉덩이를 물렸다!$"

LavaridgeTown_Text_OhYouLikeHotSprings: @ 81EAF4E
	.string "응? 너\n"
	.string "온천 좋아하나 보지?\p"
	.string "아직 젊은데 특이하구먼...$"

LavaridgeTown_Text_BatheInHotSpringsEveryDay: @ 81EAF9B
	.string "나 민지님 같은\n"
	.string "멋있고 강한 체육관 관장이\l"
	.string "되기 위해서\l"
	.string "매일 온천에 들어가고 있어!$"

LavaridgeTown_Text_IfPokemonInHotSprings: @ 81EB003
	.string "온천에 포켓몬을 넣으면\n"
	.string "전기온천이나 거품온천 또는\l"
	.string "용암온천이 돼서 엄청날 거 같아$"

LavaridgeTown_Text_HotSpringsClaims: @ 81EB092
	.string "이 온천은...\p"
	.string "신경통과 근육통 그리고\n"
	.string "연애운이랑 재물운에도\l"
	.string "효과적이라고 하더라고...$"

LavaridgeTown_Text_TownSign: @ 81EB12B
	.string "여기는 용암마을\p"
	.string "포켓몬센터와 온천이 좋은 곳$"

LavaridgeTown_Text_GymSign: @ 81EB178
	.string "용암마을 포켓몬체육관\n"
	.string "관장 민지\l"
	.string "화상 입을 정도로 열정적인 사람$"

LavaridgeTown_Text_HerbShopSign: @ 81EB1CB
	.string "“포켓몬 한방약국”\n"
	.string "몸에 좋은 약이 입에 쓰다!$"

