MagmaHideout_2F_2R_MapScripts:: @ 8239E07
	.byte 0

MagmaHideout_2F_2R_EventScript_Grunt15:: @ 8239E08
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_15, MagmaHideout_2F_2R_Text_Grunt15Intro, MagmaHideout_2F_2R_Text_Grunt15Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt15PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt6:: @ 8239E1F
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_6, MagmaHideout_2F_2R_Text_Grunt6Intro, MagmaHideout_2F_2R_Text_Grunt6Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt6PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt7:: @ 8239E36
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_7, MagmaHideout_2F_2R_Text_Grunt7Intro, MagmaHideout_2F_2R_Text_Grunt7Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt7PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_EventScript_Grunt8:: @ 8239E4D
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_8, MagmaHideout_2F_2R_Text_Grunt8Intro, MagmaHideout_2F_2R_Text_Grunt8Defeat
	msgbox MagmaHideout_2F_2R_Text_Grunt8PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_2F_2R_Text_Grunt15Intro: @ 8239E64
	.string "너에게 원한은 없지만\n"
	.string "이것도 명령이라서 말야!$"
	// あなたに うらみは ないけどｎ
	// これも めいれい だからね!

MagmaHideout_2F_2R_Text_Grunt15Defeat: @ 8239EA5
	.string "나는 져버렸지만...$"
	// わたしは まけたけど……

MagmaHideout_2F_2R_Text_Grunt15PostBattle: @ 8239EBB
	.string "엄청난 걸 파내버렸어!\n"
	.string "쪽빛구슬도 손에 넣었지!\p"
	.string "남은 건 리더가...\n"
	.string "후후후... 우하하하하!$"
	// とんでもないものを ほりだした!ｎ
	// あいいろのたまも てにいれた!ｐ
	// あとは リ-ダ-が……ｎ
	// ふふふ…… ふはははは!

MagmaHideout_2F_2R_Text_Grunt6Intro: @ 8239F31
	.string "난 더위를 잘 타는데\n"
	.string "어쩌면 아쿠아단에 들어가는 편이\l"
	.string "더 나았으려나?$"
	// オレって あつがり なんだよｎ
	// もしかして アクアだんに はいったほうがｌ
	// よかったのかな?

MagmaHideout_2F_2R_Text_Grunt6Defeat: @ 8239F71
	.string "역시 나\n"
	.string "마그마단에는 어울리지 않을지도...$"
	// やっぱり オレｎ
	// マグマだんには むいてないかも……

MagmaHideout_2F_2R_Text_Grunt6PostBattle: @ 8239FA1
	.string "이런 곳에 있으면\n"
	.string "바다가 그리워지지 않아?$"
	// こんなところに いるとｎ
	// うみが こいしく なったり しないか?

MagmaHideout_2F_2R_Text_Grunt7Intro: @ 8239FDE
	.string "가끔씩 땅이 울리는 소리가 들려\p"
	.string "이건 혹시 화산의 진동인가?\n"
	.string "아니면 그란...\p"
	.string "어이쿠 아무것도 아냐!$"
	// ときどき じひびきが きこえるんだよｐ
	// それって かざんの しんどう かな?ｎ
	// それとも グラ……ｐ
	// おっとっと なんでもないよ!

MagmaHideout_2F_2R_Text_Grunt7Defeat: @ 823A050
	.string "으-음\n"
	.string "화산처럼 뜨겁구나 너는!$"
	// う-むｎ
	// かざんのように あついな きみは!

MagmaHideout_2F_2R_Text_Grunt7PostBattle: @ 823A07D
	.string "나는 어쩌다가 너한테 졌지만\n"
	.string "마그마단의 목적은\l"
	.string "곧 이루어질 거야!$"
	// オレは たまたま おまえに まけたがｎ
	// マグマだんの もくてきはｌ
	// まもなく たっせい されるのさ!

MagmaHideout_2F_2R_Text_Grunt8Intro: @ 823A0E4
	.string "마그마의증표를 잃어버렸다고\n"
	.string "난리를 치던 녀석이 있었는데\p"
	.string "...아! 설마\n"
	.string "그거 네가 주운 거야?$"
	// マグマのしるしを どこかに おとしたｎ
	// って おおさわぎ してるやつが いたけどｐ
	// ……あ! もしかしてｎ
	// それ ひろったの おまえ?

MagmaHideout_2F_2R_Text_Grunt8Defeat: @ 823A14C
	.string "으-음 엄청난 녀석이군...$"
	// う-ん なんて やつだ……

MagmaHideout_2F_2R_Text_Grunt8PostBattle: @ 823A16F
	.string "뭔가... 우리들의 계획이\n"
	.string "실패할지도 모른다는 예감이 들어$"
	// なんか…… オレたちの けいかくｎ
	// しっぱい するような きが してきたよ

