MtPyre_3F_MapScripts:: @ 8231752
	.byte 0

MtPyre_3F_EventScript_William:: @ 8231753
	trainerbattle_single TRAINER_WILLIAM, MtPyre_3F_Text_WilliamIntro, MtPyre_3F_Text_WilliamDefeat
	msgbox MtPyre_3F_Text_WilliamPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Kayla:: @ 823176A
	trainerbattle_single TRAINER_KAYLA, MtPyre_3F_Text_KaylaIntro MtPyre_3F_Text_KaylaDefeat
	msgbox MtPyre_3F_Text_KaylaPostBattle, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_EventScript_Gabrielle:: @ 8231781
	trainerbattle_single TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleIntro, MtPyre_3F_Text_GabrielleDefeat, MtPyre_3F_EventScript_RegisterGabrielle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MtPyre_3F_EventScript_RematchGabrielle
	msgbox MtPyre_3F_Text_GabriellePostBattle, MSGBOX_DEFAULT
	release
	end

MtPyre_3F_EventScript_RegisterGabrielle:: @ 82317AD
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MtPyre_3F_Text_GabrielleRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_GABRIELLE_1
	release
	end

MtPyre_3F_EventScript_RematchGabrielle:: @ 82317CC
	trainerbattle_rematch TRAINER_GABRIELLE_1, MtPyre_3F_Text_GabrielleRematchIntro, MtPyre_3F_Text_GabrielleRematchDefeat
	msgbox MtPyre_3F_Text_GabriellePostRematch, MSGBOX_AUTOCLOSE
	end

MtPyre_3F_Text_WilliamIntro: @ 82317E3
	.string "영험하고 신통한 산의 힘으로\n"
	.string "사이코 파워가 업한 나를\l"
	.string "어린애인 네가 이길 수 있을까!?$"
	// れいげん あらたかな やまの ちからでｎ
	// サイコパワ-の アップした わたしにｌ
	// こどもの おまえが かてるかな!?

MtPyre_3F_Text_WilliamDefeat: @ 8231853
	.string "업... 업...$"
	// アップ アップ……

MtPyre_3F_Text_WilliamPostBattle: @ 8231869
	.string "나의 사이코 파워는 분명히\n"
	.string "강해졌을 텐데...$"
	// わたしの サイコパワ-は かくじつにｎ
	// つよく なっている はずなのに……

MtPyre_3F_Text_KaylaIntro: @ 82318A1
	.string "오호호호홋!\p"
	.string "여기는 너 같은 어린애가\n"
	.string "올 곳이 아니란다!$"
	// おほほほほっ!ｐ
	// ここは あなたの ような こどもがｎ
	// くる ばしょ では ないのよっ!

MtPyre_3F_Text_KaylaDefeat: @ 82318DD
	.string "깨끗이 졌어...!$"
	// あっさり まけたわっ……!

MtPyre_3F_Text_KaylaPostBattle: @ 82318F2
	.string "아직 수행이 부족하구나...\n"
	.string "정상을 노리겠어...!\p"
	.string "파이팅! 나!$"
	// まだまだ しゅぎょうが たりないのね……ｎ
	// さんちょうを めざすわよ……!ｐ
	// ファイト! わたし!

MtPyre_3F_Text_GabrielleIntro: @ 8231952
	.string "넌 어째서 여기에...?$"
	// あなたは なぜ ここへ……?

MtPyre_3F_Text_GabrielleDefeat: @ 823196A
	.string "대단해!\n"
	.string "너는 멋진 트레이너님이구나$"
	// すごいわ!ｎ
	// あなたは すてきな トレ-ナ-さんね

MtPyre_3F_Text_GabriellePostBattle: @ 823199B
	.string "이제는 세상에 없는 포켓몬\n"
	.string "아직 같이 있는 포켓몬\p"
	.string "그리고\n"
	.string "앞으로 만날 포켓몬...\p"
	.string "모두 소중한 포켓몬들이야\n"
	.string "부디 그걸 기억해 줘$"
	// いまはもう いない ポケモンｎ
	// いま いっしょに いる ポケモンｐ
	// それにｎ
	// これから であう ポケモン……ｐ
	// すべて たいせつな ポケモン なのよｎ
	// おぼえて おいて くださいね

MtPyre_3F_Text_GabrielleRegister: @ 8231A49
	.string "네 포켓몬이 자라는 걸\n"
	.string "보고 싶어...\l"
	.string "자 포켓내비를 줘봐$"
	// あなたの ポケモンが そだったらｎ
	// みてみたいわ……ｌ
	// さあ ポケナビを だして

MtPyre_3F_Text_GabrielleRematchIntro: @ 8231AAB
	.string "어라 너는...\n"
	.string "키운 포켓몬 보여 주러 왔어?$"
	// あら あなたは……ｎ
	// そだてた ポケモン みせてくれるの?

MtPyre_3F_Text_GabrielleRematchDefeat: @ 8231AE6
	.string "정말 대단해!\n"
	.string "넌 멋진 사람이구나$"
	// ほんとうに すごいわ!ｎ
	// あなたは すてきね

MtPyre_3F_Text_GabriellePostRematch: @ 8231B0D
	.string "이제는 세상에 없는 포켓몬\n"
	.string "아직 같이 있는 포켓몬\p"
	.string "그리고\n"
	.string "앞으로 만날 포켓몬...\p"
	.string "모두 소중한 포켓몬들이야\n"
	.string "기억하고 있었구나$"
	// いまはもう いない ポケモンｎ
	// いま いっしょに いる ポケモンｐ
	// それにｎ
	// これから であう ポケモン……ｐ
	// すべて たいせつな ポケモン なのよｎ
	// おぼえて くれて いたのね

