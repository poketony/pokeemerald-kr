ShoalCave_LowTideLowerRoom_MapScripts:: @ 8237156
	map_script MAP_SCRIPT_ON_LOAD, ShoalCave_LowTideLowerRoom_OnLoad
	.byte 0

ShoalCave_LowTideLowerRoom_OnLoad: @ 823715C
	call ShoalCave_LowTideLowerRoom_EventScript_SetShoalItemMetatiles
	end

ShoalCave_LowTideLowerRoom_EventScript_SetShoalItemMetatiles:: @ 8237162
	goto_if_set FLAG_RECEIVED_SHOAL_SALT_4, ShoalCave_LowTideLowerRoom_EventScript_SetShoalItemMetatilesEnd
	setmetatile 18, 2, METATILE_Cave_ShoalCave_DirtPile_Large, 1
	return

ShoalCave_LowTideLowerRoom_EventScript_SetShoalItemMetatilesEnd:: @ 8237175
	return

ShoalCave_LowTideLowerRoom_EventScript_ShoalSalt4:: @ 8237176
	lockall
	goto_if_set FLAG_RECEIVED_SHOAL_SALT_4, ShoalCave_LowTideLowerRoom_EventScript_ReceivedShoalSalt
	giveitem ITEM_SHOAL_SALT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setmetatile 18, 2, METATILE_Cave_ShoalCave_DirtPile_Small, 0
	special DrawWholeMapView
	setflag FLAG_RECEIVED_SHOAL_SALT_4
	releaseall
	end

ShoalCave_LowTideLowerRoom_EventScript_ReceivedShoalSalt:: @ 82371A8
	msgbox ShoalCave_Text_WasShoalSaltNowNothing, MSGBOX_DEFAULT
	releaseall
	end

ShoalCave_LowTideLowerRoom_EventScript_BlackBelt:: @ 82371B2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_FOCUS_BAND, ShoalCave_LowTideLowerRoom_EventScript_ReceivedFocusBand
	msgbox ShoalCave_LowTideLowerRoom_Text_CanOvercomeColdWithFocus, MSGBOX_DEFAULT
	giveitem ITEM_FOCUS_BAND
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_FOCUS_BAND
	release
	end

ShoalCave_LowTideLowerRoom_EventScript_ReceivedFocusBand:: @ 82371E1
	msgbox ShoalCave_LowTideLowerRoom_Text_EverythingStartsWithFocus, MSGBOX_DEFAULT
	release
	end

ShoalCave_LowTideLowerRoom_Text_CanOvercomeColdWithFocus: @ 82371EB
	.string "이 주변은 몸이 차가워져서\n"
	.string "수행하는 것도 잘 안 돼...\p"
	.string "하지만 기합이 있으면 괜찮아!\p"
	.string "너도 이 기합의머리띠로\n"
	.string "추위를 견디는 거야!$"
	@ このあたりは からだが ひえきってｎ
	@ しゅぎょう するのも ままならぬ……ｐ
	@ だが きあいが あれば だいじょうぶッ!ｐ
	@ おぬしも この きあいのハチマキでｎ
	@ さむさに たえてみせるのだッ!

ShoalCave_LowTideLowerRoom_Text_EverythingStartsWithFocus: @ 823728D
	.string "뭐든지 기합이다-앗!!$"
	@ なにごとも きあい なのだ-ッ!!

