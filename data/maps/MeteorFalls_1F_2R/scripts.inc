MeteorFalls_1F_2R_MapScripts:: @ 822C4DD
	.byte 0

MeteorFalls_1F_2R_EventScript_Nicolas:: @ 822C4DE
	trainerbattle_single TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasIntro, MeteorFalls_1F_2R_Text_NicolasDefeat, MeteorFalls_1F_2R_EventScript_RegisterNicolas
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MeteorFalls_1F_2R_EventScript_RematchNicolas
	msgbox MeteorFalls_1F_2R_Text_NicolasPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterNicolas:: @ 822C50A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox MeteorFalls_1F_2R_Text_NicolasRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_NICOLAS_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchNicolas:: @ 822C529
	trainerbattle_rematch TRAINER_NICOLAS_1, MeteorFalls_1F_2R_Text_NicolasRematchIntro, MeteorFalls_1F_2R_Text_NicolasRematchDefeat
	msgbox MeteorFalls_1F_2R_Text_NicolasPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_John:: @ 822C540
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnIntro, MeteorFalls_1F_2R_Text_JohnDefeat, MeteorFalls_1F_2R_Text_JohnNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJohn
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MeteorFalls_1F_2R_EventScript_RematchJohn
	msgbox MeteorFalls_1F_2R_Text_JohnPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJohn:: @ 822C570
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJohn:: @ 822C589
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JohnRematchIntro, MeteorFalls_1F_2R_Text_JohnRematchDefeat, MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JohnPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_EventScript_Jay:: @ 822C5A4
	trainerbattle_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayIntro, MeteorFalls_1F_2R_Text_JayDefeat, MeteorFalls_1F_2R_Text_JayNotEnoughMons, MeteorFalls_1F_2R_EventScript_RegisterJay
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq MeteorFalls_1F_2R_EventScript_RematchJay
	msgbox MeteorFalls_1F_2R_Text_JayPostBattle, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_2R_EventScript_RegisterJay:: @ 822C5D4
	msgbox MeteorFalls_1F_2R_Text_JohnRegister, MSGBOX_DEFAULT  @ John speaks for both during register
	register_matchcall TRAINER_JOHN_AND_JAY_1
	release
	end

MeteorFalls_1F_2R_EventScript_RematchJay:: @ 822C5ED
	trainerbattle_rematch_double TRAINER_JOHN_AND_JAY_1, MeteorFalls_1F_2R_Text_JayRematchIntro, MeteorFalls_1F_2R_Text_JayRematchDefeat, MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons
	msgbox MeteorFalls_1F_2R_Text_JayPostRematch, MSGBOX_AUTOCLOSE
	end

MeteorFalls_1F_2R_Text_NicolasIntro: @ 822C608
	.string "여기는 우리들\n"
	.string "드래곤 조련사들이 수행하는 곳!\p"
	.string "챔피언도 찾아오는 곳이라고 하면\n"
	.string "그 대단함을 알 수 있겠지!?$"
	@ ここは オレたちｎ
	@ ドラゴンつかいの しゅぎょうの ばしょ!ｐ
	@ チャンピオンも くる ばしょ といったらｎ
	@ その すごさ わかるだろうか!?

MeteorFalls_1F_2R_Text_NicolasDefeat: @ 822C678
	.string "큭!\n"
	.string "이 정도로 강할 줄은...!$"
	@ くっ!ｎ
	@ これほど つよいとは……!

MeteorFalls_1F_2R_Text_NicolasPostBattle: @ 822C6A3
	.string "아직 길은 멀고 험하다\p"
	.string "나와 내 포켓몬이\n"
	.string "최고가 될 날은 언제일지...$"
	@ まだまだ みちは ながく けわしいｐ
	@ オレと オレの ポケモンがｎ
	@ いちばんに なれるのは いつだろう……

MeteorFalls_1F_2R_Text_NicolasRegister: @ 822C6F6
	.string "네 강함을 좀 더 알고 싶다\n"
	.string "포켓내비에 등록해 줘!$"
	@ きみの つよさを もっと しりたいｎ
	@ ポケナビに とうろく させてくれ!

MeteorFalls_1F_2R_Text_NicolasRematchIntro: @ 822C73F
	.string "그 후로 최고를 목표로\n"
	.string "자신과 포켓몬을 상당히 단련시켰다...\p"
	.string "얼마나 강해졌는지\n"
	.string "널 상대로 확인해보도록 하지!$"
	@ あれから いちばん めざしてｎ
	@ かなり じぶんたちを きたえた……ｐ
	@ どれほど つよくなったかｎ
	@ きみで たしかめさせて もらおうッ!

MeteorFalls_1F_2R_Text_NicolasRematchDefeat: @ 822C7AD
	.string "큭!\n"
	.string "이 정도로 강할 줄은...!$"
	@ くっ!ｎ
	@ これほど つよいとは……!

MeteorFalls_1F_2R_Text_NicolasPostRematch: @ 822C7D8
	.string "여전히 포켓몬을 단련시키고 있군\p"
	.string "네게 그 강함이 있는 이상\n"
	.string "나도 강해지겠다!$"
	@ あいかわらず ポケモンを きたえてるなｐ
	@ きみが その つよさで あるかぎりｎ
	@ オレも つよくなれるよ!

MeteorFalls_1F_2R_Text_JohnIntro: @ 822C843
	.string "현이: 우리는 항상 둘이서\n"
	.string "포켓몬 승부를 하고 있으니\l"
	.string "승부에는 자신이 있다네$"
	@ ゲン『わしらは いつも ふうふでｎ
	@ ポケモンを しておるからのうｌ
	@ しょうぶにも じしんが あるんじゃよ

MeteorFalls_1F_2R_Text_JohnDefeat: @ 822C89C
	.string "현이: 이런이런\n"
	.string "져버렸군 할멈$"
	@ ゲン『おやおやｎ
	@ まけたよ ばあさん

MeteorFalls_1F_2R_Text_JohnPostBattle: @ 822C8C1
	.string "현이: 결혼하고 50년...\n"
	.string "그러고 보니 한 번도 할멈을\l"
	.string "포켓몬 승부로 이긴 적이 없구려$"
	@ ゲン『けっこんして 50ねん……ｎ
	@ そういや いちども ばあさんにｌ
	@ ポケモンしょうぶで かってないのう

MeteorFalls_1F_2R_Text_JohnNotEnoughMons: @ 822C92B
	.string "현이: 이런이런\n"
	.string "혈기가 왕성한 트레이너구먼!\p"
	.string "우리와 승부하려면\n"
	.string "포켓몬을 더 데려오게나$"
	@ ゲン『おやおやｎ
	@ わかい トレ-ナ- じゃな!ｐ
	@ わしらと しょうぶ してくれるのならｎ
	@ ポケモンを もっと つれてきなされ

MeteorFalls_1F_2R_Text_JohnRegister: @ 822C99C
	.string "현이: 혈기 왕성한 트레이너분...\n"
	.string "다시 기회가 생기면\l"
	.string "우리와 배틀해주지 않겠나$"
	@ ゲン『わかい トレ-ナ-さん……ｎ
	@ また きかいが あればｌ
	@ わしらと たたかって くれんかのう

MeteorFalls_1F_2R_Text_JayIntro: @ 822C9E6
	.string "초: 결혼하고 나서 50년...\n"
	.string "우리 부부의 금슬은\l"
	.string "그 무엇으로도 깰 수 없지요$"
	@ ハツ『けっこんして 50ねん……ｎ
	@ わたしら ふうふの きずなはｌ
	@ どんな ものでも きれませんよ

MeteorFalls_1F_2R_Text_JayDefeat: @ 822CA44
	.string "초: 이런이런\n"
	.string "져버렸어요 영감$"
	@ ハツ『おやおやｎ
	@ まけましたよ じいさん

MeteorFalls_1F_2R_Text_JayPostBattle: @ 822CA70
	.string "초: 결혼하고 나서 50년...\n"
	.string "부부싸움을 할 때마다\l"
	.string "포켓몬 승부를 했었지요$"
	@ ハツ『けっこんして 50ねん……ｎ
	@ ふうふげんかに なるたびｌ
	@ ポケモンしょうぶを していましたねえ

MeteorFalls_1F_2R_Text_JayNotEnoughMons: @ 822CACD
	.string "초: 이런이런\n"
	.string "혈기가 왕성한 트레이너님이군요\p"
	.string "우리와 승부하려면\n"
	.string "포켓몬을 더 데려오시지요$"
	@ ハツ『おやおやｎ
	@ わかい トレ-ナ-さん ですねえｐ
	@ わしらと しょうぶ してくれるのならｎ
	@ ポケモンを もっと つれておいで

MeteorFalls_1F_2R_Text_JohnRematchIntro: @ 822CB47
	.string "현이: 우리는 항상 둘이서\n"
	.string "포켓몬 승부를 즐기고 있으니\l"
	.string "승부에는 자신이 있다네$"
	@ ゲン『わしらは いつも ふうふでｎ
	@ ポケモンを たのしんでおる からのうｌ
	@ しょうぶにも じしんが あるんじゃよ

MeteorFalls_1F_2R_Text_JohnRematchDefeat: @ 822CBA0
	.string "현이: 이런이런\n"
	.string "져버렸군 할멈$"
	@ ゲン『おやおやｎ
	@ まけたよ ばあさん

MeteorFalls_1F_2R_Text_JohnPostRematch: @ 822CBC5
	.string "현이: 결혼하고 나서 50년...\n"
	.string "그러고 보니 매일매일\l"
	.string "할멈과 승부를 했었구려$"
	@ ゲン『けっこんして 50ねん……ｎ
	@ そういや まいにち まいにちｌ
	@ ばあさんと しょうぶ していたのう

MeteorFalls_1F_2R_Text_JohnRematchNotEnoughMons: @ 822CC27
	.string "현이: 허허허\n"
	.string "혈기가 왕성한 트레이너로군!\p"
	.string "우리와 승부하려면\n"
	.string "포켓몬을 더 데려오게나$"
	@ ゲン『おやおやｎ
	@ わかい トレ-ナ- じゃな!ｐ
	@ わしらと しょうぶ してくれるのならｎ
	@ ポケモンを もっと つれてきなされ

MeteorFalls_1F_2R_Text_JayRematchIntro: @ 822CC98
	.string "초: 결혼하고 나서 50년...\n"
	.string "서로의 버팀목이었던\l"
	.string "우리 부부는 정말 강하지요$"
	@ ハツ『けっこんして 50ねん……ｎ
	@ おたがいを ささえあってきたｌ
	@ わたしら ふうふは つよいですよ

MeteorFalls_1F_2R_Text_JayRematchDefeat: @ 822CD08
	.string "초: 에구머니나\n"
	.string "져버렸어요 영감$"
	@ ハツ『おやおやｎ
	@ まけましたよ じいさん

MeteorFalls_1F_2R_Text_JayPostRematch: @ 822CD34
	.string "초: 결혼하고 나서 50년...\n"
	.string "여러 가지 일이 있었지요\p"
	.string "앞으로도 영감과 함께\n"
	.string "행복하게 지낼 수 있으면 좋겠네요$"
	@ ハツ『けっこんして 50ねん……ｎ
	@ いろんなことが ありましたねえｐ
	@ これからも じいさんと いっしょにｎ
	@ たのしいことが つづくと いいですわねえ

MeteorFalls_1F_2R_Text_JayRematchNotEnoughMons: @ 822CDAB
	.string "초: 이런이런\n"
	.string "혈기가 왕성한 트레이너님이군요\p"
	.string "우리와 승부하려면\n"
	.string "포켓몬을 더 데려오시지요$"
	@ ハツ『おやおやｎ
	@ わかい トレ-ナ-さん ですねえｐ
	@ わしらと しょうぶ してくれるのならｎ
	@ ポケモンを もっと つれておいで

