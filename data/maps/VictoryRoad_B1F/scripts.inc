VictoryRoad_B1F_MapScripts:: @ 82364E4
	.byte 0

VictoryRoad_B1F_EventScript_Samuel:: @ 82364E5
	trainerbattle_single TRAINER_SAMUEL, VictoryRoad_B1F_Text_SamuelIntro, VictoryRoad_B1F_Text_SamuelDefeat
	msgbox VictoryRoad_B1F_Text_SamuelPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Shannon:: @ 82364FC
	trainerbattle_single TRAINER_SHANNON, VictoryRoad_B1F_Text_ShannonIntro, VictoryRoad_B1F_Text_ShannonDefeat
	msgbox VictoryRoad_B1F_Text_ShannonPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Michelle:: @ 8236513
	trainerbattle_single TRAINER_MICHELLE, VictoryRoad_B1F_Text_MichelleIntro, VictoryRoad_B1F_Text_MichelleDefeat
	msgbox VictoryRoad_B1F_Text_MichellePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Mitchell:: @ 823652A
	trainerbattle_single TRAINER_MITCHELL, VictoryRoad_B1F_Text_MitchellIntro, VictoryRoad_B1F_Text_MitchellDefeat
	msgbox VictoryRoad_B1F_Text_MitchellPostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_EventScript_Halle:: @ 8236541
	trainerbattle_single TRAINER_HALLE, VictoryRoad_B1F_Text_HalleIntro, VictoryRoad_B1F_Text_HalleDefeat
	msgbox VictoryRoad_B1F_Text_HallePostBattle, MSGBOX_AUTOCLOSE
	end

VictoryRoad_B1F_Text_SamuelIntro: @ 8236558
	.string "포켓몬리그에\n"
	.string "가까워지고 있다고 생각하니\l"
	.string "왠지 가슴이 두근거리기 시작했어...$"

VictoryRoad_B1F_Text_SamuelDefeat: @ 82365AD
	.string "아무것도 할 수 없었어...$"

VictoryRoad_B1F_Text_SamuelPostBattle: @ 82365C4
	.string "포켓몬리그가 멀어졌어...\n"
	.string "완전 김빠진다...$"

VictoryRoad_B1F_Text_ShannonIntro: @ 82365FD
	.string "포켓몬리그를 이겨나가기 위해서는\n"
	.string "포켓몬을 향한 신뢰가 필요해$"

VictoryRoad_B1F_Text_ShannonDefeat: @ 823664D
	.string "아주 돈독한 신뢰 관계구나!$"

VictoryRoad_B1F_Text_ShannonPostBattle: @ 8236678
	.string "언제나 함께 있는 걸로\n"
	.string "포켓몬과 트레이너 사이에\l"
	.string "신뢰 관계가 형성되는 거야$"

VictoryRoad_B1F_Text_MichelleIntro: @ 82366C2
	.string "여기는 골인 지점이 아니야\n"
	.string "포켓몬리그로 가는 중간 지점이지!$"

VictoryRoad_B1F_Text_MichelleDefeat: @ 823670B
	.string "그래! 바로 그거야!$"

VictoryRoad_B1F_Text_MichellePostBattle: @ 823671B
	.string "너라면 분명히 괜찮을 거야!\n"
	.string "포켓몬도 의욕이 넘치니까!$"

VictoryRoad_B1F_Text_MitchellIntro: @ 8236757
	.string "제 포켓몬은 굉장하다고요!$"
	// わたしの ポケモンは すばらしいですよ!

VictoryRoad_B1F_Text_MitchellDefeat: @ 8236780
	.string "당신 같은 사람\n"
	.string "처음이에요$"
	// あなた みたいな かたｎ
	// はじめて です

VictoryRoad_B1F_Text_MitchellPostBattle: @ 82367A7
	.string "당신과 당신의 포켓몬이\n"
	.string "같이 있는 것만으로도\l"
	.string "굉장한 파워가 느껴져요$"
	// あなたと あなたの ポケモンがｎ
	// いっしょに いるだけでｌ
	// すごい パワ-を かんじます

VictoryRoad_B1F_Text_HalleIntro: @ 82367FD
	.string "오케이 그렇게 보채지 말라고!\n"
	.string "릴랙스하고 상대해 줄 테니까!$"
	// オ-ケイ そんなに かまえないで!ｎ
	// リラックス して いきましょ!

VictoryRoad_B1F_Text_HalleDefeat: @ 823683B
	.string "원더풀!$"
	// ワンダフル!

VictoryRoad_B1F_Text_HallePostBattle: @ 823684C
	.string "챔피언로드라지만\n"
	.string "지금까지와 별다른 건 없어\l"
	.string "남은 길을 인조이하라고!$"
	// チャンピオンロ-ド だってｎ
	// いままでの みちのりと かわらないわｌ
	// のこりも エンジョイしてね

