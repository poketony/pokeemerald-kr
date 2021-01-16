Route119_House_MapScripts:: @ 8270965
	.byte 0

Route119_House_EventScript_Woman:: @ 8270966
	msgbox Route119_House_Text_RumorAboutCaveOfOrigin, MSGBOX_NPC
	end

Route119_House_EventScript_Wingull:: @ 827096F
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox Route119_House_Text_Wingull, MSGBOX_DEFAULT
	waitmoncry
	release
	end

Route119_House_Text_RumorAboutCaveOfOrigin: @ 8270982
	.string "어딘가에 각성의 사당이라고 불리는\n"
	.string "동굴이 있다고 해요!\p"
	.string "포켓몬의 혼이 부활한다는\n"
	.string "소문이 있던데\l"
	.string "정말로 그런 게 가능할까요?$"

Route119_House_Text_Wingull: @ 8270A17
	.string "갈모매: 삐홍?$"

