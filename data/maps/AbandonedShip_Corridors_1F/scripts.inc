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
	.string "배 안에서\n"
	.string "튜브를 끼는 게 뭐가 그렇게 웃겨?$"

AbandonedShip_Corridors_1F_Text_CharlieDefeat:
	.string "압도당했어...$"

AbandonedShip_Corridors_1F_Text_CharliePostBattle:
	.string "튜브를 끼고 있으면\n"
	.string "몬스터볼을 던지기 어려워$"

AbandonedShip_Corridors_1F_Text_IsntItFunHere:
	.string "여긴 참 재미있네!\n"
	.string "여기 있는 것만으로도 두근거려!$"
