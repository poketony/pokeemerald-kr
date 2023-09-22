.set LOCALID_WINGULL, 3

FortreeCity_House4_MapScripts:: @ 8217C80
	.byte 0

FortreeCity_House4_EventScript_Woman:: @ 8217C81
	msgbox FortreeCity_House4_Text_BringsWorldCloserTogether, MSGBOX_NPC
	end

FortreeCity_House4_EventScript_Boy:: @ 8217C8A
	lockall
	goto_if_set FLAG_RECEIVED_MENTAL_HERB, FortreeCity_House4_EventScript_ReceivedMentalHerb
	goto_if_set FLAG_WINGULL_DELIVERED_MAIL, FortreeCity_House4_EventScript_WingullReturned
	goto_if_set FLAG_WINGULL_SENT_ON_ERRAND, FortreeCity_House4_EventScript_WingullOnErrand
	msgbox FortreeCity_House4_Text_GoBirdPokemon, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_WINGULL_SENT_ON_ERRAND
	clearflag FLAG_HIDE_MOSSDEEP_CITY_HOUSE_2_WINGULL
	applymovement LOCALID_WINGULL, FortreeCity_House4_Movement_WingullExit
	waitmovement 0
	removeobject LOCALID_WINGULL
	releaseall
	end

FortreeCity_House4_EventScript_WingullOnErrand:: @ 8217CC4
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_AskedWingullToRunErrand, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_EventScript_WingullReturned:: @ 8217CD8
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb, MSGBOX_DEFAULT
	giveitem ITEM_MENTAL_HERB
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_MENTAL_HERB
	releaseall
	end

FortreeCity_House4_EventScript_ReceivedMentalHerb:: @ 8217D06
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox FortreeCity_House4_Text_FriendsFarAwayThanksToWingull, MSGBOX_DEFAULT
	releaseall
	end

FortreeCity_House4_Movement_WingullExit: @ 8217D1A
	walk_fast_down
	walk_fast_down
	walk_fast_right
	walk_in_place_fastest_down
	delay_8
	step_end

FortreeCity_House4_EventScript_Wingull:: @ 8217D20
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox FortreeCity_House4_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FortreeCity_House4_Text_BringsWorldCloserTogether: @ 8217D33
	.string "포켓몬과 함께 있으면\n"
	.string "친한 친구들이 점점 늘어나...\p"
	.string "이렇게 전 세계는\n"
	.string "하나로 뭉쳐지는 거구나!\l"
	.string "너무 멋진 거 같아!$"

FortreeCity_House4_Text_GoBirdPokemon: @ 8217DB9
	.string "자!\n"
	.string "갔다 와! 새포켓몬$"

FortreeCity_House4_Text_AskedWingullToRunErrand: @ 8217DD2
	.string "헤헷 갈모매한테\n"
	.string "심부름 좀 시켰어$"

FortreeCity_House4_Text_WelcomeWingullTakeMentalHerb: @ 8217E05
	.string "좋아!\n"
	.string "수고했어 갈모매!\p"
	.string "응?\n"
	.string "뭘 들고 있는 거야?\p"
	.string "멘탈허브네...\n"
	.string "오면서 주워 왔구나?\p"
	.string "그치만 난 트레이너가 아니니까\n"
	.string "필요 없어\l"
	.string "이거 너한테 줄게!$"

FortreeCity_House4_Text_FriendsFarAwayThanksToWingull: @ 8217EA8
	.string "갈모매 덕분에\n"
	.string "멀리 있는 친구랑도\l"
	.string "친하게 지낼 수 있어!$"

FortreeCity_House4_Text_Wingull: @ 8217EE0
	.string "갈모매: 삐뾰-!$"

