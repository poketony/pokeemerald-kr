AbandonedShip_Corridors_1F_MapScripts::
	.byte 0

AbandonedShip_Corridors_1F_EventScript_Youngster::
	msgbox AbandonedShip_Corridors_1F_Text_IsntItFunHere, MSGBOX_NPC
	end

AbandonedShip_Corridors_1F_EventScript_Charlie::
	trainerbattle_single TRAINER_CHARLIE, AbandonedShip_Corridors_1F_Text_CharlieIntro, AbandonedShip_Corridors_1F_Text_CharlieDefeat
	msgbox AbandonedShip_Corridors_1F_Text_CharliePostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_1F_Text_CharlieIntro:
	.string "배 안에서도\n"
	.string "튜브를 끼는 게 이상해?$"
	// ねの なかでもｎ
	// うきわ もっていたら おかしい?

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "우와아 강하다-!$"
	// うわぁ つよ-い!

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "튜브를 끼고 있으면\n"
	.string "몬스터볼을 던지기 어려워$"
	// うきわを もったままだとｎ
	// モンスタ-ボ-ル なげにくいよ

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "여긴 참 재미있네!\n"
	.string "여기 있는 것만으로도 두근거려!$"
	// ここって おもしろいね!ｎ
	// いるだけで ワクワク してくるよ!
