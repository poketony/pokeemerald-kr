AbandonedShip_Rooms2_1F_MapScripts::
	.byte 0

AbandonedShip_Rooms2_1F_EventScript_Dan::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanIntro, AbandonedShip_Rooms2_1F_Text_DanDefeat, AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterDan
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_Rooms2_1F_EventScript_DanRematch
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterDan::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT 
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_DanRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_DanRematchIntro, AbandonedShip_Rooms2_1F_Text_DanRematchDefeat, AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_DanPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Kira::
	trainerbattle_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraIntro, AbandonedShip_Rooms2_1F_Text_KiraDefeat, AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons, AbandonedShip_Rooms2_1F_EventScript_RegisterKira
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq AbandonedShip_Rooms2_1F_EventScript_KiraRematch
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostBattle, MSGBOX_DEFAULT
	release
	end

AbandonedShip_Rooms2_1F_EventScript_RegisterKira::
	msgbox AbandonedShip_Rooms2_1F_Text_KiraRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_KIRA_AND_DAN_1
	release
	end

AbandonedShip_Rooms2_1F_EventScript_KiraRematch::
	trainerbattle_rematch_double TRAINER_KIRA_AND_DAN_1, AbandonedShip_Rooms2_1F_Text_KiraRematchIntro, AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat, AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons
	msgbox AbandonedShip_Rooms2_1F_Text_KiraPostRematch, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Jani::
	trainerbattle_single TRAINER_JANI, AbandonedShip_Rooms2_1F_Text_JaniIntro, AbandonedShip_Rooms2_1F_Text_JaniDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_JaniPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_EventScript_Garrison::
	trainerbattle_single TRAINER_GARRISON, AbandonedShip_Rooms2_1F_Text_GarrisonIntro, AbandonedShip_Rooms2_1F_Text_GarrisonDefeat
	msgbox AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Rooms2_1F_Text_DanIntro:
	.string "중문: 보물을 찾고 있었더니\n"
	.string "트레이너를 발견!$"
	// フミ『おたから さがしていたらｎ
	// トレ-ナ- はっけん!

AbandonedShip_Rooms2_1F_Text_DanDefeat:
	.string "중문: 우리 둘의 힘으로도\n"
	.string "이길 수 없었나...$"
	// フミ『ぼくたち ふたりの ちからでもｎ
	// かてなかったのか……

AbandonedShip_Rooms2_1F_Text_DanPostBattle:
	.string "중문: 보물을 못 찾겠네...\n"
	.string "벌써 누가 가져간 거 아닐까?$"
	// フミ『おたから みつからないんだよね……ｎ
	// もう だれかが もっていったのかな?

AbandonedShip_Rooms2_1F_Text_DanNotEnoughMons:
	.string "중문: 포켓몬 2마리가 없구나\n"
	.string "그래선 우리를 이길 수 없어!$"
	// フミ『ポケモン 2ひき いないんだねｎ
	// それだと ぼくたちには かてないよ!

AbandonedShip_Rooms2_1F_Text_KiraIntro:
	.string "소영: 어머? 보물을 찾고 있었는데\n"
	.string "트레이너를 발견했네!$"
	// ナツ『あら? おたから さがしていたのにｎ
	// トレ-ナ- はっけん しちゃった!

AbandonedShip_Rooms2_1F_Text_KiraDefeat:
	.string "소영: 강하구나!$"
	// ナツ『つよいんだ!

AbandonedShip_Rooms2_1F_Text_KiraPostBattle:
	.string "소영: 보물은 어디 있을까?\n"
	.string "찾으면 뭘 살지 정하고 있어!$"
	// ナツ『おたから どこかな?ｎ
	// みつかったら なに かおうか きめてるのよ!

AbandonedShip_Rooms2_1F_Text_KiraNotEnoughMons:
	.string "소영: 어머 포켓몬 2마리가 아니구나?\n"
	.string "그럼 승부는 다음에 해야겠네!$"
	// ナツ『あら ポケモン 2ひき いないの?ｎ
	// じゃあ しょうぶは おあずけね!

AbandonedShip_Rooms2_1F_Text_KiraRegister:
	.string "소영: 정말 완전 짜증나!\n"
	.string "너 등록해 버릴 거야!$"
	// ナツ『もう くやしいな!ｎ
	// あなたなんて とうろく しちゃうんだから!

AbandonedShip_Rooms2_1F_Text_DanRematchIntro:
	.string "중문: 계속 보물을 찾다 보니\n"
	.string "포켓몬도 강해졌단 말이지-!\p"
	.string "잠깐 상대해줘$"
	// フミ『ずっと おたから さがしていてｎ
	// ポケモンも つよく なったんだよね-!ｌ
	// ちょっと あいて してみてよ

AbandonedShip_Rooms2_1F_Text_DanRematchDefeat:
	.string "중문: 변함없이 강하구나!$"
	// フミ『あいかわらず つよいな!

AbandonedShip_Rooms2_1F_Text_DanPostRematch:
	.string "중문: 보물도 못 찾겠고\n"
	.string "포켓몬 승부도 졌으니 집 가고 싶다\p"
	.string "하지만 그런 말을 하면\n"
	.string "여자친구가 화를 내겠지...$"
	// フミ『おたからは みつからないしｎ
	// ポケモンは まけるし いえに かえりたいよｐ
	// でも そんなこと いうとｎ
	// かのじょ おこりだすからな……

AbandonedShip_Rooms2_1F_Text_DanRematchNotEnoughMons:
	.string "중문: 포켓몬 2마리가 없구나\n"
	.string "그러면 우리를 이길 수 없어!$"
	// フミ『ポケモン 2ひき いないんだねｎ
	// それだと ぼくたちには かてないよ!

AbandonedShip_Rooms2_1F_Text_KiraRematchIntro:
	.string "소영: 어머? 또 만났네!\n"
	.string "우리처럼 포기하지 않고\l"
	.string "보물을 찾고 있나보구나!\p"
	.string "승부해서 진 쪽이\n"
	.string "포기하는 걸로 하지 않을래?$"
	// ナツ『あら? また であったわね!ｎ
	// あたしたちと いっしょで あきらめずにｌ
	// おたから さがしているのね!ｐ
	// しょうぶして まけた ほうはｎ
	// あきらめることに しない?

AbandonedShip_Rooms2_1F_Text_KiraRematchDefeat:
	.string "소영: 또 져버렸어...$"
	// ナツ『また まけちゃった……

AbandonedShip_Rooms2_1F_Text_KiraPostRematch:
	.string "소영: 더욱 포켓몬을 키워서\n"
	.string "보물을 찾을 때까지 안 돌아갈 거야!$"
	// ナツ『もっと ポケモン そだててｎ
	// おたから みつけるまで かえらないわよ!

AbandonedShip_Rooms2_1F_Text_KiraRematchNotEnoughMons:
	.string "소영: 어머 포켓몬 2마리가 아니구나?\n"
	.string "그럼 승부는 다음에 해야겠네!$"
	// ナツ『あら ポケモン 2ひき いないの?ｎ
	// じゃあ しょうぶは おあずけね!

AbandonedShip_Rooms2_1F_Text_JaniIntro:
	.string "수영은 못하지만\n"
	.string "포켓몬 승부는 잘한다고!$"
	// およぐの ヘタだけどｎ
	// しょうぶは つよいも-ん

AbandonedShip_Rooms2_1F_Text_JaniDefeat:
	.string "어라 이것도 못하네$"
	// あれ だめだったかあ

AbandonedShip_Rooms2_1F_Text_JaniPostBattle:
	.string "배 안을 맨발로 돌아다니면\n"
	.string "조금 기분이 나쁘단 말이지$"
	// ふねの なかを はだしで あるくとｎ
	// ちょっと きもちわるいなあ

AbandonedShip_Rooms2_1F_Text_GarrisonIntro:
	.string "강함과 상냥함도\n"
	.string "트레이너의 보물이다!$"
	// つよさも やさしさもｎ
	// これ トレ-ナ-の たから!

AbandonedShip_Rooms2_1F_Text_GarrisonDefeat:
	.string "오오 넌 듣고\n"
	.string "반짝 깨달았구나$"
	// おお あなたにはｎ
	// キラリと ひかるものが あるな

AbandonedShip_Rooms2_1F_Text_GarrisonPostBattle:
	.string "배 어딘가의 방에\n"
	.string "반짝거리는 물건이 있었는데...$"
	// ふねの どこかの へやにｎ
	// キラリと ひかるものが あったんだが……
