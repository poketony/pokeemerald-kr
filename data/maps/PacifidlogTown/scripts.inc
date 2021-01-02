PacifidlogTown_MapScripts:: @ 81EBAB1
	map_script MAP_SCRIPT_ON_TRANSITION, PacifidlogTown_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, PacifidlogTown_OnResume
	.byte 0

PacifidlogTown_OnTransition: @ 81EBABC
	setflag FLAG_VISITED_PACIFIDLOG_TOWN
	end

PacifidlogTown_OnResume: @ 81EBAC0
	setstepcallback STEP_CB_PACIFIDLOG_BRIDGE
	end

PacifidlogTown_EventScript_NinjaBoy:: @ 81EBAC3
	msgbox PacifidlogTown_Text_NeatHousesOnWater, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Girl:: @ 81EBACC
	msgbox PacifidlogTown_Text_FastRunningCurrent, MSGBOX_NPC
	end

PacifidlogTown_EventScript_Fisherman:: @ 81EBAD5
	msgbox PacifidlogTown_Text_SkyPillarTooScary, MSGBOX_NPC
	end

PacifidlogTown_EventScript_TownSign:: @ 81EBADE
	msgbox PacifidlogTown_Text_TownSign, MSGBOX_SIGN
	end

PacifidlogTown_Text_FastRunningCurrent: @ 81EBAE7
	.string "황금마을에서 잿빛도시까지는\n"
	.string "해류의 흐름이 굉장히 격해서\p"
	.string "섣불리 파도타기를 하면\n"
	.string "생각지도 못한 방향으로\l"
	.string "떠내려가 버려$"

PacifidlogTown_Text_NeatHousesOnWater: @ 81EBB6C
	.string "어때?! 어때?! 굉장하지?!\n"
	.string "물 위에 집이 있어!\p"
	.string "난 여기서 태어났지롱!$"

PacifidlogTown_Text_SkyPillarTooScary: @ 81EBBAC
	.string "하늘기둥?\p"
	.string "...아아 그 앞에 세워져 있는\n"
	.string "높-은 탑을 말하는 거구나\p"
	.string "그런 높은 곳\n"
	.string "무서워서 올라갈 수나 있으려나-\p"
	.string "수면에 닿을락 말락한 생활이\n"
	.string "나한테 맞거든$"
	// そらのはしら?ｐ
	// ……ああ このさきに たっているｎ
	// たか--い とうの ことだねｐ
	// あんな たかい ところｎ
	// おっかなくて のぼれないな-ｐ
	// ぼくは やっぱり キナギでのｎ
	// すいめん スレスレな せいかつがｌ
	// はだに あうんだよねえ-

PacifidlogTown_Text_TownSign: @ 81EBC7A
	.string "여기는 황금마을\n"
	.string "해님이 물가를 비춰주는 마을$"

