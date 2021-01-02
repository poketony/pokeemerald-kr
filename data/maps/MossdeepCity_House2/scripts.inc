.set LOCALID_WINGULL, 3

MossdeepCity_House2_MapScripts:: @ 82220DE
	.byte 0

MossdeepCity_House2_EventScript_Man:: @ 82220DF
	msgbox MossdeepCity_House2_Text_SisterMailsBoyfriendInFortree, MSGBOX_NPC
	end

MossdeepCity_House2_EventScript_Twin:: @ 82220E8
	msgbox MossdeepCity_House2_Text_PokemonCarriesMailBackAndForth, MSGBOX_NPC
	end

MossdeepCity_House2_EventScript_Wingull:: @ 82220F1
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox MossdeepCity_House2_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	closemessage
	setflag FLAG_WINGULL_DELIVERED_MAIL
	clearflag FLAG_HIDE_FORTREE_CITY_HOUSE_4_WINGULL
	compare VAR_FACING, DIR_NORTH
	call_if_eq MossdeepCity_House2_EventScript_WingullExitNorth
	compare VAR_FACING, DIR_WEST
	call_if_eq MossdeepCity_House2_EventScript_WingullExitWest
	removeobject LOCALID_WINGULL
	release
	end

MossdeepCity_House2_EventScript_WingullExitNorth:: @ 8222124
	applymovement LOCALID_WINGULL, MossdeepCity_House2_Movement_WingullExitNorth
	waitmovement 0
	return

MossdeepCity_House2_EventScript_WingullExitWest:: @ 822212F
	applymovement LOCALID_WINGULL, MossdeepCity_House2_Movement_WingullExitEast
	waitmovement 0
	return

MossdeepCity_House2_Movement_WingullExitNorth: @ 822213A
	walk_fast_right
	walk_fast_down
	walk_fast_down
	walk_fast_left
	walk_fast_down
	delay_8
	step_end

MossdeepCity_House2_Movement_WingullExitEast: @ 8222141
	walk_fast_down
	walk_fast_down
	walk_fast_down
	delay_8
	step_end

MossdeepCity_House2_Text_SisterMailsBoyfriendInFortree: @ 8222146
	.string "내 동생은 검방울시티에 사는\n"
	.string "남자 친구랑 펜팔하고 있는데\p"
	.string "진짜로 조금도 부럽지 않아!$"

MossdeepCity_House2_Text_PokemonCarriesMailBackAndForth: @ 82221A6
	.string "검방울시티에 사는 친구랑 못 만나도\n"
	.string "포켓몬이 편지를 전달해 줘\l"
	.string "그래서 아무리 떨어져 있어도\l"
	.string "외롭지 않아!$"

MossdeepCity_House2_Text_Wingull: @ 822222E
	.string "갈모매: 삐뾰-!$"

