VictoryRoad_B2F_MapScripts:: @ 82368D4
	.byte 0

VictoryRoad_B2F_EventScript_Vito:: @ 82368D5
	trainerbattle_single TRAINER_VITO, VictoryRoad_B2F_Text_VitoIntro, VictoryRoad_B2F_Text_VitoDefeat
	msgbox VictoryRoad_B2F_Text_VitoPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Owen:: @ 82368EC
	trainerbattle_single TRAINER_OWEN, VictoryRoad_B2F_Text_OwenIntro, VictoryRoad_B2F_Text_OwenDefeat
	msgbox VictoryRoad_B2F_Text_OwenPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Caroline:: @ 8236903
	trainerbattle_single TRAINER_CAROLINE, VictoryRoad_B2F_Text_CarolineIntro, VictoryRoad_B2F_Text_CarolineDefeat
	msgbox VictoryRoad_B2F_Text_CarolinePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Julie:: @ 823691A
	trainerbattle_single TRAINER_JULIE, VictoryRoad_B2F_Text_JulieIntro, VictoryRoad_B2F_Text_JulieDefeat
	msgbox VictoryRoad_B2F_Text_JuliePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Felix:: @ 8236931
	trainerbattle_single TRAINER_FELIX, VictoryRoad_B2F_Text_FelixIntro, VictoryRoad_B2F_Text_FelixDefeat
	msgbox VictoryRoad_B2F_Text_FelixPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_EventScript_Dianne:: @ 8236948
	trainerbattle_single TRAINER_DIANNE, VictoryRoad_B2F_Text_DianneIntro, VictoryRoad_B2F_Text_DianneDefeat
	msgbox VictoryRoad_B2F_Text_DiannePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B2F_Text_VitoIntro: @ 823695F
	.string "가족들끼리\n"
	.string "포켓몬 수행을 했었어!\l"
	.string "누구에게도 지지 않는다고!$"

VictoryRoad_B2F_Text_VitoDefeat: @ 82369B3
	.string "우리 가족보다 강하다고!?\n"
	.string "그런 게 가능한 건가!?$"

VictoryRoad_B2F_Text_VitoPostBattle: @ 82369DE
	.string "가족 중에서 제일 강했던 내가...\n"
	.string "지금까지 누구에게도\l"
	.string "지지 않았던 내가...\p"
	.string "하지만 이제 자신이 없어졌어\n"
	.string "집으로 돌아갈까...?$"

VictoryRoad_B2F_Text_OwenIntro: @ 8236A4C
	.string "강한 꼬맹이가 있다는 소문이 있더군!\n"
	.string "그게 바로 넌가?$"

VictoryRoad_B2F_Text_OwenDefeat: @ 8236A92
	.string "진짜로 강하군!$"

VictoryRoad_B2F_Text_OwenPostBattle: @ 8236AAE
	.string "내가 들은 소문에 의하면\n"
	.string "그 강한 꼬맹이는\l"
	.string "등화도시 출신이라고 하더군!$"

VictoryRoad_B2F_Text_CarolineIntro: @ 8236AF0
	.string "이제 슬슬 지치기 시작했겠지?$"

VictoryRoad_B2F_Text_CarolineDefeat: @ 8236B14
	.string "하나도 안 지쳐 있잖아!$"

VictoryRoad_B2F_Text_CarolinePostBattle: @ 8236B2F
	.string "이 챔피언로드도\n"
	.string "포켓몬리그도 아주 긴 여정이지!\l"
	.string "체력에 주의해!$"

VictoryRoad_B2F_Text_JulieIntro: @ 8236B88
	.string "체육관 배지를 많이 가지고 있다고\n"
	.string "방심하지 마 뛰는 사람 위에\l"
	.string "나는 사람이 있으니까!$"

VictoryRoad_B2F_Text_JulieDefeat: @ 8236C0A
	.string "바로 네가 나는 사람이었구나!$"

VictoryRoad_B2F_Text_JuliePostBattle: @ 8236C21
	.string "내가 모은 체육관 배지를 보면서\n"
	.string "지금까지 승부했던\l"
	.string "트레이너를 떠올려$"

VictoryRoad_B2F_Text_FelixIntro: @ 8236C67
	.string "여기까지 왔는데\n"
	.string "긴장해서 그런지 배가 아파요!$"
	// ここまで きてｎ
	// きんちょう して おなかが いたいんです!

VictoryRoad_B2F_Text_FelixDefeat: @ 8236CAB
	.string "아아\n"
	.string "...아파$"
	// ああｎ
	// ……いたい

VictoryRoad_B2F_Text_FelixPostBattle: @ 8236CBA
	.string "곧 포켓몬리그라고 생각하니\n"
	.string "긴장되기 시작했어요!\p"
	.string "괜찮은 척하는 것만으로도 지쳐요$"
	// もうすぐ ポケモンリ-グと おもうとｎ
	// きんちょう して きんちょう して!ｌ
	// みため ごまかすのが せいいっぱい です

VictoryRoad_B2F_Text_DianneIntro: @ 8236D27
	.string "엘리트 중의 엘리트가 모인\n"
	.string "이 동굴은 어때?$"
	// エリ-ト ちゅうの エリ-トが あつまるｎ
	// この どうくつは どうかしら?

VictoryRoad_B2F_Text_DianneDefeat: @ 8236D6E
	.string "아무렇지도 않잖아...!$"
	// ぜんぜん どうじて いないわ……!

VictoryRoad_B2F_Text_DiannePostBattle: @ 8236D8C
	.string "당신 배짱이 좋구나\n"
	.string "마음에 들었어 힘내!$"
	// あなた どきょうが あるのねｎ
	// きにいったわ がんばって!

