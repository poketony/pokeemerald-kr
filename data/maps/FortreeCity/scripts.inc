FortreeCity_MapScripts:: @ 81E25A4
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, FortreeCity_OnResume
	.byte 0

FortreeCity_OnTransition: @ 81E25AF
	setflag FLAG_VISITED_FORTREE_CITY
	end

FortreeCity_OnResume: @ 81E25B3
	setstepcallback STEP_CB_FORTREE_BRIDGE
	end

FortreeCity_EventScript_Man:: @ 81E25B6
	msgbox FortreeCity_Text_SawGiganticPokemonInSky, MSGBOX_NPC
	end

FortreeCity_EventScript_Woman:: @ 81E25BF
	lock
	faceplayer
	goto_if_set FLAG_KECLEON_FLED_FORTREE, FortreeCity_EventScript_WomanGymAccessible
	msgbox FortreeCity_Text_SomethingBlockingGym, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_WomanGymAccessible:: @ 81E25D4
	msgbox FortreeCity_Text_ThisTimeIllBeatWinona, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_Girl:: @ 81E25DE
	msgbox FortreeCity_Text_TreesGrowByDrinkingRainwater, MSGBOX_NPC
	end

FortreeCity_EventScript_OldMan:: @ 81E25E7
	msgbox FortreeCity_Text_EveryoneHealthyAndLively, MSGBOX_NPC
	end

FortreeCity_EventScript_Boy:: @ 81E25F0
	msgbox FortreeCity_Text_BugPokemonComeThroughWindow, MSGBOX_NPC
	end

FortreeCity_EventScript_GameboyKid:: @ 81E25F9
	msgbox FortreeCity_Text_PokemonThatEvolveWhenTraded, MSGBOX_NPC
	end

FortreeCity_EventScript_CitySign:: @ 81E2602
	msgbox FortreeCity_Text_CitySign, MSGBOX_SIGN
	end

FortreeCity_EventScript_GymSign:: @ 81E260B
	msgbox FortreeCity_Text_GymSign, MSGBOX_SIGN
	end

FortreeCity_EventScript_Kecleon:: @ 81E2614
	lock
	faceplayer
	checkitem ITEM_DEVON_SCOPE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq FortreeCity_EventScript_AskUseDevonScope
	msgbox FortreeCity_Text_SomethingUnseeable, MSGBOX_DEFAULT
	release
	end

FortreeCity_EventScript_AskUseDevonScope:: @ 81E2630
	msgbox FortreeCity_Text_UnseeableUseDevonScope, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq FortreeCity_EventScript_UseDevonScope
	release
	end

FortreeCity_EventScript_UseDevonScope:: @ 81E2645
	msgbox FortreeCity_Text_UsedDevonScopePokemonFled, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Movement_KecleonAppears
	waitmovement 0
	waitse
	playmoncry SPECIES_KECLEON, 2
	delay 40
	waitmoncry
	applymovement VAR_LAST_TALKED, FortreeCity_Movement_KecleonFlee
	waitmovement 0
	removeobject VAR_LAST_TALKED
	setflag FLAG_KECLEON_FLED_FORTREE
	release
	end

FortreeCity_Movement_KecleonFlee: @ 81E2674
	walk_right
	step_end

FortreeCity_Text_SawGiganticPokemonInSky: @ 81E2676
	.string "아무도 믿어주질 않는데\n"
	.string "거대한 포켓몬이 몸을 비튼 채\l"
	.string "하늘을 날고 있는 걸 봤어...\p"
	.string "그 녀석은 131번수로 쪽으로\n"
	.string "날아갔지...\p"
	.string "...그런데\n"
	.string "왠지 너 탄내가 나\p"
	.string "화산에라도 갔다 왔어?$"
	// だれも しんじて くれないけどｎ
	// おおきな ポケモンが からだを くねらせｌ
	// そらを とんでいるのを みたんだ……ｐ
	// そいつは 131ばん すいどうの ほうへｎ
	// とんでいったよ……ｐ
	// ……ところでｎ
	// なんか きみ コゲくさいねｐ
	// かざんに でも いってきた?

FortreeCity_Text_SomethingBlockingGym: @ 81E2738
	.string "포켓몬체육관에 가고 싶은데\n"
	.string "뭔가가 길을 막고 있어!\p"
	.string "모처럼 120번도로에서\n"
	.string "포켓몬을 키우고 왔는데!$"

FortreeCity_Text_ThisTimeIllBeatWinona: @ 81E27B6
	.string "내가 자랑하는 포켓몬으로\n"
	.string "이번에야말로 은송님에게 이겨보겠어!$"

FortreeCity_Text_TreesGrowByDrinkingRainwater: @ 81E27FE
	.string "비가 땅에 스며들고\n"
	.string "그 물을 빨아들여 나무가 자란다...\p"
	.string "물과 땅 양쪽이 있으니까\n"
	.string "이 검방울시티도 있는 거야$"

FortreeCity_Text_EveryoneHealthyAndLively: @ 81E2880
	.string "이 마을은 나무 위에\n"
	.string "집을 짓고 살고 있다네...\p"
	.string "그 때문인지 모두 건강하고\n"
	.string "활기가 넘치지\p"
	.string "나도 이 마을에 오고 나서\n"
	.string "30년 정도 젊어진 느낌이라네$"

FortreeCity_Text_BugPokemonComeThroughWindow: @ 81E292E
	.string "나무 위에서 산다는 건 좋지만\p"
	.string "가끔 창문 밖에서\n"
	.string "벌레포켓몬이 들어오기도 해서\l"
	.string "깜짝 놀랄 때가 있어$"

FortreeCity_Text_PokemonThatEvolveWhenTraded: @ 81E299D
	.string "통신케이블을 지나는 것으로\n"
	.string "진화하는 포켓몬도 있어$"

FortreeCity_Text_SomethingUnseeable: @ 81E29E5
	.string "보이지 않는 무언가가 있는 것 같다$"

FortreeCity_Text_UnseeableUseDevonScope: @ 81E2A08
	.string "보이지 않는 무언가가 있는 것 같다\p"
	.string "데봉스코프를 사용하겠습니까?$"

FortreeCity_Text_UsedDevonScopePokemonFled: @ 81E2A48
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "데봉스코프를 사용했다!\p"
	.string "투명했던\n"
	.string "포켓몬의 모습이 훤히 보이게 됐다!\p"
	.string "포켓몬은\n"
	.string "놀라서 도망쳤다!$"

FortreeCity_Text_CitySign: @ 81E2AAC
	.string "여기는 검방울시티\n"
	.string "나무 위에서 자연과 어우러지는 마을$"

FortreeCity_Text_GymSign: @ 81E2AE6
	.string "검방울시티 포켓몬체육관\n"
	.string "관장 은송\l"
	.string "세상에 날갯짓하는 새 조련사$"

