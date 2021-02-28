SootopolisCity_Gym_B1F_MapScripts:: @ 8225C8A
	.byte 0

SootopolisCity_Gym_B1F_EventScript_Andrea:: @ 8225C8B
	trainerbattle_single TRAINER_ANDREA, SootopolisCity_Gym_B1F_Text_AndreaIntro, SootopolisCity_Gym_B1F_Text_AndreaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AndreaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Crissy:: @ 8225CA2
	trainerbattle_single TRAINER_CRISSY, SootopolisCity_Gym_B1F_Text_CrissyIntro, SootopolisCity_Gym_B1F_Text_CrissyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_CrissyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Brianna:: @ 8225CB9
	trainerbattle_single TRAINER_BRIANNA, SootopolisCity_Gym_B1F_Text_BriannaIntro, SootopolisCity_Gym_B1F_Text_BriannaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BriannaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Connie:: @ 8225CD0
	trainerbattle_single TRAINER_CONNIE, SootopolisCity_Gym_B1F_Text_ConnieIntro, SootopolisCity_Gym_B1F_Text_ConnieDefeat
	msgbox SootopolisCity_Gym_B1F_Text_ConniePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bridget:: @ 8225CE7
	trainerbattle_single TRAINER_BRIDGET, SootopolisCity_Gym_B1F_Text_BridgetIntro, SootopolisCity_Gym_B1F_Text_BridgetDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BridgetPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Olivia:: @ 8225CFE
	trainerbattle_single TRAINER_OLIVIA, SootopolisCity_Gym_B1F_Text_OliviaIntro, SootopolisCity_Gym_B1F_Text_OliviaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_OliviaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Tiffany:: @ 8225D15
	trainerbattle_single TRAINER_TIFFANY, SootopolisCity_Gym_B1F_Text_TiffanyIntro, SootopolisCity_Gym_B1F_Text_TiffanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_TiffanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Bethany:: @ 8225D2C
	trainerbattle_single TRAINER_BETHANY, SootopolisCity_Gym_B1F_Text_BethanyIntro, SootopolisCity_Gym_B1F_Text_BethanyDefeat
	msgbox SootopolisCity_Gym_B1F_Text_BethanyPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Annika:: @ 8225D43
	trainerbattle_single TRAINER_ANNIKA, SootopolisCity_Gym_B1F_Text_AnnikaIntro, SootopolisCity_Gym_B1F_Text_AnnikaDefeat
	msgbox SootopolisCity_Gym_B1F_Text_AnnikaPostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_EventScript_Daphne:: @ 8225D5A
	trainerbattle_single TRAINER_DAPHNE, SootopolisCity_Gym_B1F_Text_DaphneIntro, SootopolisCity_Gym_B1F_Text_DaphneDefeat
	msgbox SootopolisCity_Gym_B1F_Text_DaphnePostBattle, MSGBOX_AUTOCLOSE
	end

SootopolisCity_Gym_B1F_Text_AndreaIntro: @ 8225D71
	.string "체육관 관장 아단님께 배운\n"
	.string "화려한 테크닉을 보여줄게!$"
	// ジムリ-ダ- アダンさまに おしえてもらったｎ
	// かれいな テクニックを みせたげる!

SootopolisCity_Gym_B1F_Text_AndreaDefeat: @ 8225DB6
	.string "아단님 죄송해요...$"
	// アダンさま ごめんね……

SootopolisCity_Gym_B1F_Text_AndreaPostBattle: @ 8225DCF
	.string "모든 바닥에 금이 가게 하면\n"
	.string "뭔가가 일어나$"
	// すべての ゆかに ヒビを いれるとｎ
	// なにかが おこるわよ

SootopolisCity_Gym_B1F_Text_CrissyIntro: @ 8225E04
	.string "모처럼 여기까지 왔는데\n"
	.string "나한테 질 거니까\l"
	.string "아단님과 만나지도 못하겠네!$"
	// せっかく ここまで これたのにｎ
	// あたしに まけるからｌ
	// アダンさまに あえないわね!

SootopolisCity_Gym_B1F_Text_CrissyDefeat: @ 8225E60
	.string "강하잖아!!\n"
	.string "귀여워 보여서 속았어$"
	// つよい じゃない!!ｎ
	// かわいい みために だまされたわ

SootopolisCity_Gym_B1F_Text_CrissyPostBattle: @ 8225E90
	.string "너라면 아단님과 싸워도\n"
	.string "한 방에 나가떨어지진 않을 거야$"
	// あなたなら アダンさまと たたかってもｎ
	// いちげきで やられなくて すむかもね

SootopolisCity_Gym_B1F_Text_DaphneIntro: @ 8225ED6
	.string "아단님의 싸우는 모습...\p"
	.string "그 아름다움에 마음을 빼앗겨\n"
	.string "나도 포켓몬을 키우게 됐어$"
	// アダンさまの たたかう すがた……ｐ
	// その うつくしさに こころ うばわれｎ
	// わたくしも ポケモンを はじめましてよ

SootopolisCity_Gym_B1F_Text_DaphneDefeat: @ 8225F35
	.string "싸우는 모습의\n"
	.string "아름다움마저 져버렸어...$"
	// たたかう すがたのｎ
	// うつくしさで まけましたわ……

SootopolisCity_Gym_B1F_Text_DaphnePostBattle: @ 8225F67
	.string "네 싸우는 방식도\n"
	.string "대단했어\p"
	.string "아아...!\n"
	.string "포켓몬과 만나서 다행이야$"
	// あなたさまの たたかう すがたもｎ
	// すばらしくってよｐ
	// ああっ……!ｎ
	// ポケモンに であえて よかったですわ

SootopolisCity_Gym_B1F_Text_ConnieIntro: @ 8225FBE
	.string "내가 승부의 가혹함을\n"
	.string "여러 가지 알려줄게$"
	// おねえさんが しょうぶの きびしさｎ
	// いろいろと おしえて あげちゃおっかな

SootopolisCity_Gym_B1F_Text_ConnieDefeat: @ 8225FEB
	.string "뭐야\n"
	.string "강하네$"
	// なんだｎ
	// つよいんだ

SootopolisCity_Gym_B1F_Text_ConniePostBattle: @ 8225FFE
	.string "좋은 걸 알려줄게\p"
	.string "아단님을 만나고 싶다면\n"
	.string "모든 바닥을 한 번씩만\l"
	.string "밟고 가면 돼$"
	// いいこと おしえて あげるねｐ
	// アダンさまに あいたいのならｎ
	// すべての ゆかを 1かいずつｌ
	// あるいて いけば いいの

SootopolisCity_Gym_B1F_Text_BridgetIntro: @ 8226061
	.string "호연지방에서 가장\n"
	.string "레벨이 높은 포켓몬체육관...\p"
	.string "바로 여기 루네체육관이야!$"
	// ホウエンちほうで いちばんｎ
	// レベルの たかい ポケモンジム……ｐ
	// それが ここ ルネジムよ!

SootopolisCity_Gym_B1F_Text_BridgetDefeat: @ 82260B6
	.string "얼마나 레벨이 높은 거야...$"
	// なんて レベルの たかい……

SootopolisCity_Gym_B1F_Text_BridgetPostBattle: @ 82260D1
	.string "레벨이 높은 체육관에 있다는 것에\n"
	.string "만족하지 않고\l"
	.string "다른 수행을 하러 가는 편이\l"
	.string "강해질 수 있기도 하고 즐거워$"
	// レベルの たかい ジムに いることにｎ
	// まんぞく しないでｌ
	// ほかにも しゅぎょうに いくほうがｌ
	// つよくなれそうだし なにより たのしそうね

SootopolisCity_Gym_B1F_Text_OliviaIntro: @ 8226164
	.string "아단님과 함께\n"
	.string "포켓몬을 단련하고 있어\p"
	.string "간단히 이기진 못할 거야$"
	// アダンさまと いっしょにｎ
	// ポケモンを きたえて いるのｐ
	// かんたんに たおせると おもわないでね

SootopolisCity_Gym_B1F_Text_OliviaDefeat: @ 82261A7
	.string "졌다...$"
	// たおされちゃった……

SootopolisCity_Gym_B1F_Text_OliviaPostBattle: @ 82261B5
	.string "당신 장래성이 있는 것 같은데\n"
	.string "같이 여기서 포켓몬 단련할래?$"
	// あなた みどころ あると おもうのｎ
	// いっしょに ここで ポケモン きたえない?

SootopolisCity_Gym_B1F_Text_TiffanyIntro: @ 82261F7
	.string "얼음 위의 한붓그리기\p"
	.string "그게 가능한 트레이너는\n"
	.string "엘레강트하고 아름다워!$"
	// こおりの うえでの ひとふでがきｐ
	// それが できる トレ-ナ-はｎ
	// エレガントに うつくしいのよ!

SootopolisCity_Gym_B1F_Text_TiffanyDefeat: @ 8226274
	.string "잠깐-?!$"
	// ちょっと-!?

SootopolisCity_Gym_B1F_Text_TiffanyPostBattle: @ 8226286
	.string "당연한 거지만\n"
	.string "포켓몬의 강함은\l"
	.string "나이와 관계가 없어$"
	// あたりまえ だけどｎ
	// ポケモンの つよさにｌ
	// おとなも こどもも かんけい ないよ

SootopolisCity_Gym_B1F_Text_BethanyIntro: @ 82262F3
	.string "포켓몬과 함께 있으면\n"
	.string "시간이 눈 깜짝할 사이에 지나가!$"
	// ポケモンと いっしょに いるとｎ
	// じかんが あっ というまに すぎるのよ!

SootopolisCity_Gym_B1F_Text_BethanyDefeat: @ 822633B
	.string "깜짝!$"
	// あっ!

SootopolisCity_Gym_B1F_Text_BethanyPostBattle: @ 8226341
	.string "져버린 승부도\n"
	.string "눈 깜짝할 사이에 잊고 싶어...$"
	// まけた しょうぶもｎ
	// あっ というまに わすれたい……

SootopolisCity_Gym_B1F_Text_AnnikaIntro: @ 8226388
	.string "엄청 희귀한 포켓몬과\n"
	.string "싸우게 해줄게-!$"
	// すっごく めずらしい ポケモンちゃんでｎ
	// たたかって あげても いいわよ-!

SootopolisCity_Gym_B1F_Text_AnnikaDefeat: @ 82263BD
	.string "잠깐!\n"
	.string "내 포켓몬 제대로 보고 있지?$"
	// ちょっと!ｎ
	// ポケモンちゃんも ちゃんと みてくれた?

SootopolisCity_Gym_B1F_Text_AnnikaPostBattle: @ 82263F4
	.string "내가 이 체육관에 있는 건\n"
	.string "아단님이 내 포켓몬을\l"
	.string "칭찬해 주셨기 때문이야\p"
	.string "아-아 남편을 만나기 전에\n"
	.string "아단님을 만났더라면 지금쯤...$"
	// わたしが このジムに いるのはｎ
	// アダンさんが わたしの ポケモンちゃんをｌ
	// ほめて くれたから なのよぉｐ
	// あ-あ ダンナに であうまえにｎ
	// アダンさんに であっていれば いまごろは…

SootopolisCity_Gym_B1F_Text_BriannaIntro: @ 822646E
	.string "우후후...\n"
	.string "그 필사적인 얼굴이 멋져$"
	// うふふ……ｎ
	// その ひっしな おかおが ステキよ

SootopolisCity_Gym_B1F_Text_BriannaDefeat: @ 8226495
	.string "어라\n"
	.string "너무 적당히 한 것 같네...$"
	// あらｎ
	// てかげん しすぎて しまいましたわ……

SootopolisCity_Gym_B1F_Text_BriannaPostBattle: @ 82264BC
	.string "너는 아단님에게\n"
	.string "손끝 하나 못 댈 거야 우후후...$"
	// あなたでは アダンさまにはｎ
	// きっと はが たちませんわよ うふふ……

