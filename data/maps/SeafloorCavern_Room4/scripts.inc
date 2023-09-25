SeafloorCavern_Room4_MapScripts:: @ 8234C9B
	.byte 0

SeafloorCavern_Room4_EventScript_Grunt3:: @ 8234C9C
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_3, SeafloorCavern_Room4_Text_Grunt3Intro, SeafloorCavern_Room4_Text_Grunt3Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt3PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_EventScript_Grunt4:: @ 8234CB3
	trainerbattle_single TRAINER_GRUNT_SEAFLOOR_CAVERN_4, SeafloorCavern_Room4_Text_Grunt4Intro, SeafloorCavern_Room4_Text_Grunt4Defeat
	msgbox SeafloorCavern_Room4_Text_Grunt4PostBattle, MSGBOX_AUTOCLOSE
	end

SeafloorCavern_Room4_Text_Grunt3Intro: @ 8234CCA
	.string "누구지 너는?\n"
	.string "어디로 들어온 거지?$"

SeafloorCavern_Room4_Text_Grunt3Defeat: @ 8234CF3
	.string "졌다...!$"

SeafloorCavern_Room4_Text_Grunt3PostBattle: @ 8234CFC
	.string "어떡하지? 출구를 찾을 수가 없어\p"
	.string "절대 무서운 게 아니야!\n"
	.string "착각하지 말라고!$"

SeafloorCavern_Room4_Text_Grunt4Intro: @ 8234D3A
	.string "너 누구?\n"
	.string "어디 가는 거야!?$"
	// あなた だれ?ｎ
	// どこへ いこうってのよ!?

SeafloorCavern_Room4_Text_Grunt4Defeat: @ 8234D68
	.string "이길 수 없었어...!$"
	// かてなかった……!

SeafloorCavern_Room4_Text_Grunt4PostBattle: @ 8234D79
	.string "파트너가 잠수정에\n"
	.string "지도를 놔두고 왔대!\p"
	.string "정말 도움이 안된다니까!$"
	// このひとったら せんすいていにｎ
	// ちずを わすれて きちゃったの!ｐ
	// まったく たよりに なんないんだから!

