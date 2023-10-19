MtPyre_6F_MapScripts:: @ 8231D3A
	.byte 0

MtPyre_6F_EventScript_Valerie:: @ 8231D3B
	trainerbattle_single TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieIntro, MtPyre_6F_Text_ValerieDefeat, MtPyre_6F_EventScript_RegisterValerie
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtPyre_6F_EventScript_RematchValerie
	msgbox MtPyre_6F_Text_ValeriePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_6F_EventScript_RegisterValerie:: @ 8231D67
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_6F_Text_ValerieRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_VALERIE_1
	release
	end

MtPyre_6F_EventScript_RematchValerie:: @ 8231D86
	trainerbattle_rematch TRAINER_VALERIE_1, MtPyre_6F_Text_ValerieRematchIntro, MtPyre_6F_Text_ValerieRematchDefeat
	msgbox MtPyre_6F_Text_ValeriePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_EventScript_Cedric:: @ 8231D9D
	trainerbattle_single TRAINER_CEDRIC, MtPyre_6F_Text_CedricIntro, MtPyre_6F_Text_CedricDefeat
	msgbox MtPyre_6F_Text_CedricPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_6F_Text_ValerieIntro: @ 8231DB4
	.string "여기에 있으면...\n"
	.string "무언가의 힘이 흘러 들어와...$"
	// ここに いると……ｎ
	// なにかの ちからが はいってくるの……

MtPyre_6F_Text_ValerieDefeat: @ 8231DE2
	.string "힘이 빠져나간다...$"
	// ちからが ぬけていく……

MtPyre_6F_Text_ValeriePostBattle: @ 8231DFC
	.string "여기에 잠들어 있는 포켓몬들의\n"
	.string "힘이 흘러 들어오는 걸까...?$"
	// ここに ねむっている ポケモンたちのｎ
	// ちからが はいって くるのかもよ……?

MtPyre_6F_Text_ValerieRegister: @ 8231E43
	.string "후후후후 승부에선 졌지만\n"
	.string "나... 이런 것도 할 수 있어...\p"
	.string "너의 포켓내비에 전혀\n"
	.string "손을 대지 않아도... 에-잇...!$"
	// ふふふふ しょうぶには まけたけどｎ
	// わたし…… こんな ことが できるの……ｐ
	// あなたの ポケナビに いっさい てをｎ
	// ふれなくても…… きえ-いっ……!

MtPyre_6F_Text_ValerieRematchIntro: @ 8231EB3
	.string "너의 뒤에...\n"
	.string "뭐가 있는 거지...?$"
	// あなたの うしろ……ｎ
	// なにが いるの……?

MtPyre_6F_Text_ValerieRematchDefeat: @ 8231ECB
	.string "뭔가가 사라졌어...$"
	// なにかが きえたわ……

MtPyre_6F_Text_ValeriePostRematch: @ 8231EE1
	.string "여기에 잠들어 있는 포켓몬들...\n"
	.string "가끔 함께 놀고 있는 것 같아...$"
	// ここに ねむっている ポケモンたち……ｎ
	// ときどき あそんでいる みたいなの……

MtPyre_6F_Text_CedricIntro: @ 8231F11
	.string "너 길을 잃어버렸니?\n"
	.string "내가 있으니까 안심해!$"
	// きみ まいごなのか?ｎ
	// おれが きた からには あんしんだ!

MtPyre_6F_Text_CedricDefeat: @ 8231F4A
	.string "길을 잃어버린 게 아닌가?$"
	// まいご じゃ なかったか?

MtPyre_6F_Text_CedricPostBattle: @ 8231F5C
	.string "길을 잃은 트레이너는 겁먹었으니까\n"
	.string "이기기 쉽단 말이지\p"
	.string "비겁하니까 이제 그만둘게...$"
	// まいごの トレ-ナ-は あわてて いるからｎ
	// かてる きが するんだよなｐ
	// ずるいから もう やめとくよ……

