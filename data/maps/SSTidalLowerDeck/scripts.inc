SSTidalLowerDeck_MapScripts:: @ 823C818
	.byte 0

SSTidalLowerDeck_EventScript_Phillip:: @ 823C819
	trainerbattle_single TRAINER_PHILLIP, SSTidalLowerDeck_Text_PhillipIntro, SSTidalLowerDeck_Text_PhillipDefeat
	msgbox SSTidalLowerDeck_Text_PhillipPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_EventScript_Leonard:: @ 823C830
	trainerbattle_single TRAINER_LEONARD, SSTidalLowerDeck_Text_LeonardIntro, SSTidalLowerDeck_Text_LeonardDefeat
	msgbox SSTidalLowerDeck_Text_LeonardPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalLowerDeck_Text_PhillipIntro: @ 823C847
	.string "이렇게 넓은 곳을\n"
	.string "언제 다 청소하지?! 이제 질렸어!\l"
	.string "잠깐 승부나 하자고!$"

SSTidalLowerDeck_Text_PhillipDefeat: @ 823C8A0
	.string "아우야! 져버렸다!$"

SSTidalLowerDeck_Text_PhillipPostBattle: @ 823C8B4
	.string "우리들은 청소브라더스!\p"
	.string "형은 세제를 마구 뿌리고-\n"
	.string "동생은 빡빡 닦는다-$"

SSTidalLowerDeck_Text_LeonardIntro: @ 823C917
	.string "이렇게 넓으니까\n"
	.string "뱃바닥에서 포켓몬 승부를 해도\l"
	.string "괜찮겠지?$"

SSTidalLowerDeck_Text_LeonardDefeat: @ 823C97D
	.string "형님! 져버렸습니다!$"

SSTidalLowerDeck_Text_LeonardPostBattle: @ 823C98E
	.string "우리들은 청소브라더스!\p"
	.string "형은 세제를 마구 뿌리고-\n"
	.string "동생은 빡빡 닦는다-$"

