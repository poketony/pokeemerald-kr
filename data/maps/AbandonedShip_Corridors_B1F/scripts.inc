AbandonedShip_Corridors_B1F_MapScripts::
	map_script MAP_SCRIPT_ON_RESUME, AbandonedShip_Corridors_B1F_OnResume
	map_script MAP_SCRIPT_ON_LOAD, AbandonedShip_Corridors_B1F_OnLoad
	.byte 0

AbandonedShip_Corridors_B1F_OnResume:
	setdivewarp MAP_ABANDONED_SHIP_UNDERWATER1, 255, 5, 4
	end

AbandonedShip_Corridors_B1F_OnLoad:
	call_if_unset FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_LockStorageRoom
	call_if_set FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom
	end

AbandonedShip_Corridors_B1F_EventScript_LockStorageRoom::
	setmetatile 11, 4, METATILE_InsideShip_IntactDoor_Bottom_Locked, 1
	return

AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom::
	setmetatile 11, 4, METATILE_InsideShip_IntactDoor_Bottom_Unlocked, 1
	return

AbandonedShip_Corridors_B1F_EventScript_TuberM::
	msgbox AbandonedShip_Corridors_B1F_Text_YayItsAShip, MSGBOX_NPC
	end

AbandonedShip_Corridors_B1F_EventScript_StorageRoomDoor::
	lockall
	goto_if_set FLAG_USED_STORAGE_KEY, AbandonedShip_Corridors_B1F_EventScript_DoorIsUnlocked
	checkitem ITEM_STORAGE_KEY, 1
	compare VAR_RESULT, FALSE
	goto_if_eq AbandonedShip_Corridors_B1F_EventScript_DoorIsLocked
	msgbox AbandonedShip_Corridors_B1F_Text_InsertedStorageKey, MSGBOX_DEFAULT
	playse SE_PIN
	removeitem ITEM_STORAGE_KEY
	setflag FLAG_USED_STORAGE_KEY
	call AbandonedShip_Corridors_B1F_EventScript_UnlockStorageRoom
	special DrawWholeMapView
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_DoorIsLocked::
	msgbox AbandonedShip_Corridors_B1F_Text_DoorIsLocked, MSGBOX_DEFAULT
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_DoorIsUnlocked::
	msgbox AbandonedShip_Text_TheDoorIsOpen, MSGBOX_DEFAULT
	releaseall
	end

AbandonedShip_Corridors_B1F_EventScript_Duncan::
	trainerbattle_single TRAINER_DUNCAN, AbandonedShip_Corridors_B1F_Text_DuncanIntro, AbandonedShip_Corridors_B1F_Text_DuncanDefeat
	msgbox AbandonedShip_Corridors_B1F_Text_DuncanPostBattle, MSGBOX_AUTOCLOSE
	end

AbandonedShip_Corridors_B1F_Text_DuncanIntro:
	.string "바다로 나갈 때\n"
	.string "우리 선원들은\l"
	.string "항상 포켓몬을 데리고 간다!\l"
	.string "잠깐 승부해줘야겠어!$"

AbandonedShip_Corridors_B1F_Text_DuncanDefeat:
	.string "이거 큰일인걸$"

AbandonedShip_Corridors_B1F_Text_DuncanPostBattle:
	.string "배가 물속으로\n"
	.string "가라앉아버렸어\p"
	.string "포켓몬이 물속에 잠수하는 기술을\n"
	.string "쓸 수 있다면\l"
	.string "일이 쉬워질 텐데...$"

AbandonedShip_Corridors_B1F_Text_YayItsAShip:
	.string "와-!\n"
	.string "배다-!$"

AbandonedShip_Corridors_B1F_Text_DoorIsLocked:
	.string "열쇠가 걸려 있다\p"
	.string "문에는 “창고”라고 쓰여 있다$"

AbandonedShip_Corridors_B1F_Text_InsertedStorageKey:
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "창고열쇠를 사용했다!\p"
	.string "넣은 열쇠는 뺄 수 없게 되었지만\n"
	.string "문은 열렸다!$"

AbandonedShip_Text_TheDoorIsOpen:
	.string "문이 열렸다!$"
