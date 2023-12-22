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
	.string "선원은 배에 탈 때\n"
	.string "반드시 포켓몬을 데리고 가지!\l"
	.string "잠깐 승부해 줘야겠어!$"
	// ふなのりは ふねに のるときｎ
	// かならず ポケモンを もっている!ｌ
	// ちょいと しょうぶ してくれ!

AbandonedShip_Corridors_B1F_Text_DuncanDefeat:
	.string "이거 곤란한걸$"
	// こりゃ まいった

AbandonedShip_Corridors_B1F_Text_DuncanPostBattle:
	.string "뱃바닥이 물속으로\n"
	.string "가라앉아 버렸어\p"
	.string "포켓몬이 물속에 잠수하는 기술을\n"
	.string "쓴다면 앞으로 나아갈 수 있을 텐데...$"
	// ふなぞこが みずの なかにｎ
	// しずんで いるんだよｐ
	// ポケモンが みずに もぐれる わざをｎ
	// つかえたら さきに すすめるんだがな……

AbandonedShip_Corridors_B1F_Text_YayItsAShip:
	.string "와-!\n"
	.string "배다-!$"
	// わ-い!ｎ
	// ふね だぞ-!

AbandonedShip_Corridors_B1F_Text_DoorIsLocked:
	.string "문이 잠겨 있다\p"
	.string "문에는 창고라고 쓰여 있다$"
	// カギが かかっているｐ
	// とびらには そうこ と かかれている

AbandonedShip_Corridors_B1F_Text_InsertedStorageKey:
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "창고열쇠를 썼다!\p"
	.string "꽂은 열쇠는 빠지지 않게 되었지만\n"
	.string "문은 열렸다!$"
	// §あはｎ
	// そうこのカギを つかった!ｐ
	// さしこんだ カギは ぬけなくなったがｎ
	// とびらは ひらいた!

AbandonedShip_Text_TheDoorIsOpen:
	.string "문은 열려 있다!$"
	// とびらは あいている!
