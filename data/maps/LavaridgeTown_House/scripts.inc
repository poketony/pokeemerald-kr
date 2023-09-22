LavaridgeTown_House_MapScripts:: @ 81FF911
	.byte 0

LavaridgeTown_House_EventScript_OldMan:: @ 81FF912
	msgbox LavaridgeTown_House_Text_WifeWarmingEggInHotSprings, MSGBOX_NPC
	end

LavaridgeTown_House_EventScript_Zigzagoon:: @ 81FF91B
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox LavaridgeTown_House_Text_Zigzagoon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LavaridgeTown_House_Text_WifeWarmingEggInHotSprings: @ 81FF92E
	.string "온천에서 알을 따뜻하게 하고 있는\n"
	.string "할멈에게서 들었는데...\p"
	.string "키우미집에 포켓몬을\n"
	.string "두 마리 같이 맡겼더니 말이지\p"
	.string "이게 웬일!\n"
	.string "알이 발견됐다고 하더구나!!$"

LavaridgeTown_House_Text_Zigzagoon: @ 81FF9BB
	.string "지그제구리: 우샤-!$"

