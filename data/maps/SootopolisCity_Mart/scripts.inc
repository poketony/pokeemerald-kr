SootopolisCity_Mart_MapScripts:: @ 8226794
	.byte 0

SootopolisCity_Mart_EventScript_Clerk:: @ 8226795
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart SootopolisCity_Mart_Pokemart
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_Pokemart: @ 82267AC
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_REVIVE
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_X_ATTACK
	.2byte ITEM_X_DEFEND
	.2byte ITEM_SHADOW_MAIL
	.2byte ITEM_NONE
	release
	end

SootopolisCity_Mart_EventScript_FatMan:: @ 82267C2
	lock
	faceplayer
	compare VAR_SKY_PILLAR_STATE, 2
	goto_if_ge SootopolisCity_Mart_EventScript_FatManNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_Mart_EventScript_FatManNoLegendaries
	msgbox SootopolisCity_Mart_Text_TooScaryOutside, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_FatManNoLegendaries:: @ 82267E2
	msgbox SootopolisCity_Mart_Text_PPUpIsGreat, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_Gentleman:: @ 82267EC
	lock
	faceplayer
	compare VAR_SKY_PILLAR_STATE, 2
	goto_if_ge SootopolisCity_Mart_EventScript_GentlemanNoLegendaries
	goto_if_unset FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN, SootopolisCity_Mart_EventScript_GentlemanNoLegendaries
	msgbox SootopolisCity_Mart_Text_DidSomethingAwaken, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_EventScript_GentlemanNoLegendaries:: @ 822680C
	msgbox SootopolisCity_Mart_Text_FullRestoreItemOfDreams, MSGBOX_DEFAULT
	release
	end

SootopolisCity_Mart_Text_PPUpIsGreat: @ 8226816
	.string "포인트업은 굉장해!\p"
	.string "왜냐면 포켓몬의\n"
	.string "파워포인트를 늘려주거든!$"
	@ ポイントアップは すごいぞ!ｐ
	@ なんたって ポケモンのｎ
	@ パワ-ポイントを ふやせるからな!

SootopolisCity_Mart_Text_TooScaryOutside: @ 822685D
	.string "대체 무슨 일이 일어나는 거지!?\p"
	.string "엄청 신경 쓰이지만\n"
	.string "무서워서 밖으로 나갈 수가 없어!$"
	@ いったい なにが おこってるんだ!?ｐ
	@ ものすごく きになる けどｎ
	@ こわくて そとに でられないよ!

SootopolisCity_Mart_Text_FullRestoreItemOfDreams: @ 82268AF
	.string "회복약이라고 알고 있나요?\p"
	.string "포켓몬의 체력이 완쾌!\n"
	.string "상태 이상도 모두 회복!\l"
	.string "정말 꿈만 같은 도구랍니다$"
	@ かいふくのくすり ごぞんじ ですか?ｐ
	@ ポケモンの たいりょく ぜんかい!ｎ
	@ じょうたい いじょうも すべて かいふく!ｌ
	@ まさに ゆめのような どうぐ なのです

SootopolisCity_Mart_Text_DidSomethingAwaken: @ 8226928
	.string "이 날씨...\n"
	.string "무언가가 눈을 뜬 건가...?$"
	@ この てんき……ｎ
	@ なにかが めざめたのか……?

