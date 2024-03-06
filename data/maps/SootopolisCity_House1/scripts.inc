SootopolisCity_House1_MapScripts:: @ 822694C
	.byte 0

SootopolisCity_House1_EventScript_BrickBreakBlackBelt:: @ 822694D
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM31, SootopolisCity_House1_EventScript_ReceivedBrickBreak
	msgbox SootopolisCity_House1_Text_DevelopedThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM31
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM31
	msgbox SootopolisCity_House1_Text_ExplainBrickBreak, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House1_EventScript_ReceivedBrickBreak:: @ 8226984
	msgbox SootopolisCity_House1_Text_ExplainBrickBreak, MSGBOX_DEFAULT
	release
	end

SootopolisCity_House1_EventScript_Kecleon:: @ 822698E
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, 0
	msgbox SootopolisCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House1_Text_DevelopedThisTM: @ 82269A1
	.string "으음...\n"
	.string "루네시티에 틀어박혀 산 지 30년...\p"
	.string "내가 만든 필살 기술머신을!\n"
	.string "너에게 주마!$"
	@ うむう……ｎ
	@ ルネシティに こもること 30ねん……ｐ
	@ わしが あみだした ひっさつの わざマシン!ｎ
	@ おまえに ゆずろう!

SootopolisCity_House1_Text_ExplainBrickBreak: @ 8226A13
	.string "기술머신31은 깨트리다!\n"
	.string "설명하기조차 무서운 기술이지...$"
	@ わざマシン31は かわらわり!ｎ
	@ せつめい するのも おそろしい わざよ……

SootopolisCity_House1_Text_Kecleon: @ 8226A60
	.string "켈리몬: 푸- 푸햐아-$"
	@ カクレオン『ぷ- ぷひゃあ-

