RustboroCity_Mart_MapScripts:: @ 8214F05
	.byte 0

RustboroCity_Mart_EventScript_Clerk:: @ 8214F06
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	goto_if_unset FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartBasic
	goto_if_set FLAG_MET_DEVON_EMPLOYEE, RustboroCity_Mart_EventScript_PokemartExpanded
	end

RustboroCity_Mart_EventScript_PokemartBasic:: @ 8214F21
	pokemart RustboroCity_Mart_Pokemart_Basic
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

RustboroCity_Mart_Pokemart_Basic: @ 8214F30
	.2byte ITEM_POKE_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_PokemartExpanded:: @ 8214F48
	pokemart RustboroCity_Mart_Pokemart_Expanded
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
RustboroCity_Mart_Pokemart_Expanded: @ 8214F58
	.2byte ITEM_POKE_BALL
	.2byte ITEM_TIMER_BALL
	.2byte ITEM_REPEAT_BALL
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_REPEL
	.2byte ITEM_X_SPEED
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_NONE
	release
	end

RustboroCity_Mart_EventScript_PokefanF:: @ 8214F74
	msgbox RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_Boy:: @ 8214F7D
	msgbox RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead, MSGBOX_NPC
	end

RustboroCity_Mart_EventScript_BugCatcher:: @ 8214F86
	msgbox RustboroCity_Mart_Text_GettingEscapeRopeJustInCase, MSGBOX_NPC
	end

RustboroCity_Mart_Text_BuyingHealsInCaseOfShroomish: @ 8214F8F
	.string "등화숲에서 버섯꼬가\n"
	.string "튀어나왔을 때를 대비해서\l"
	.string "마비치료제와 해독제를 사둘 거야!$"
	@ トウカのもりで キノココがｎ
	@ とびだして きたときの ためｌ
	@ まひなおしや どくけしを かっておくの!

RustboroCity_Mart_Text_ShouldBuySuperPotionsInstead: @ 8214FF1
	.string "포켓몬이 진화해서 체력이\n"
	.string "늘어났으니 상처약 말고\l"
	.string "좋은상처약을 사줘야 되나$"
	@ ポケモン しんかして たいりょくがｎ
	@ ふえたから キズぐすり じゃなくてｌ
	@ いいキズぐすりを かってあげようかな

RustboroCity_Mart_Text_GettingEscapeRopeJustInCase: @ 821505C
	.string "동굴에서 길을 잃었을 때를 대비해서\n"
	.string "동굴탈출로프를 사두려고 해!\p"
	.string "쓰면 눈 깜짝할 사이에\n"
	.string "입구로 돌아갈 수 있거든!$"
	@ どうくつで まよった ときのためｎ
	@ あなぬけのヒモを かっておこう っと!ｐ
	@ つかうと いっしゅんでｎ
	@ いりぐちに もどれるもんね!

