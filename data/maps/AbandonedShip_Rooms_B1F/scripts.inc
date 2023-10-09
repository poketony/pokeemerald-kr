AbandonedShip_Rooms_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, AbandonedShip_Rooms_B1F_OnResume
	.byte 0

AbandonedShip_Rooms_B1F_OnResume:
	setdivewarp MAP_ABANDONED_SHIP_UNDERWATER2, 255, 17, 4
	end

AbandonedShip_Rooms_B1F_EventScript_FatMan::
	msgbox AbandonedShip_Rooms_B1F_Text_GettingQueasy, MSGBOX_NPC
	end

AbandonedShip_Rooms_B1F_Text_GettingQueasy:
	.string "우웁...\p"
	.string "어째선지 배 안에 있는 것만으로도\n"
	.string "멀미를 해버려...\p"
	.string "배는 조금도 안 움직이는데...$"
	// うぅ……ｐ
	// なんだか ふねの なかに いるだけでｎ
	// よってきちゃった……ｐ
	// ふねは ちっとも うごいてないのに……
