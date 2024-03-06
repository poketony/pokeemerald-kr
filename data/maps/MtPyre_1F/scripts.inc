MtPyre_1F_MapScripts:: @ 8230F3E
	.byte 0

MtPyre_1F_EventScript_CleanseTagWoman:: @ 8230F3F
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_CLEANSE_TAG, MtPyre_1F_EventScript_ReceivedCleanseTag
	msgbox MtPyre_1F_Text_TakeThisForYourOwnGood, MSGBOX_DEFAULT
	giveitem ITEM_CLEANSE_TAG
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_CLEANSE_TAG
	release
	end

MtPyre_1F_EventScript_ReceivedCleanseTag:: @ 8230F6E
	msgbox MtPyre_1F_Text_ExplainCleanseTag, MSGBOX_DEFAULT
	release
	end

MtPyre_1F_EventScript_PokefanF:: @ 8230F78
	msgbox MtPyre_1F_Text_ComeToPayRespects, MSGBOX_NPC
	end

MtPyre_1F_EventScript_Man:: @ 8230F81
	msgbox MtPyre_1F_Text_RestingPlaceOfZigzagoon, MSGBOX_NPC
	end

MtPyre_1F_Text_TakeThisForYourOwnGood: @ 8230F8A
	.string "이 송화산에는\n"
	.string "다양한 존재가 떠돌고 있지...\p"
	.string "그래서 무슨 일이 일어날지 모른다네\n"
	.string "만약을 위해 이걸 가지고 가게$"
	@ この おくりびやま にはｎ
	@ いろんな ものが さまよっておる……ｐ
	@ なにが おきるか わからんｎ
	@ ねんのため これを もっていきなされ

MtPyre_1F_Text_ExplainCleanseTag: @ 8231005
	.string "순결의부적을\n"
	.string "포켓몬에게 지니게 하게\p"
	.string "그럼 야생 포켓몬이\n"
	.string "별로 안 튀어나오게 될 게야$"
	@ きよめのおふだ をなｎ
	@ ポケモンに もたせて おくｐ
	@ すると やせいの ポケモンがｎ
	@ あんまり とびだして こなくなるぞよ

MtPyre_1F_Text_ComeToPayRespects: @ 823104F
	.string "너도 떠나보낸 포켓몬을 보러 왔니?\n"
	.string "포켓몬을 생각하는 마음이 깊구나$"
	@ あなたも おはか まいりに きたの?ｎ
	@ ずいぶんと ポケモン おもい なのね

MtPyre_1F_Text_RestingPlaceOfZigzagoon: @ 82310BA
	.string "여기엔 내가 소중히 키우던\n"
	.string "지그제구리가 편히 잠들어 있다...$"
	@ ここには ぼくが たいせつに していたｎ
	@ ジグザグマが やすらかに ねむってる……

