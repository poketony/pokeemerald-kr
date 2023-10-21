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
	.string "포켓몬의 영혼이 부활하는 곳이라는\n"
	.string "소문이 있던데\l"
	.string "정말로 그런 일이 가능할까요?$"
	// どこかに めざめのほこら とよばれるｎ
	// どうくつが あるんですって!ｐ
	// ポケモンの たましいが よみがえる ところｎ
	// という うわさ だけどｌ
	// そんなこと ほんとうに あるのかしら?

Route119_House_Text_Wingull: @ 8270A17
	.string "갈모매: 삐효?$"
	// キャモメ『ぴひょ?

