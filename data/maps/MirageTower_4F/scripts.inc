.set LOCALID_ROOT_FOSSIL, 1
.set LOCALID_CLAW_FOSSIL, 2

MirageTower_4F_MapScripts:: @ 823AD47
	.byte 0

MirageTower_4F_EventScript_RootFossil:: @ 823AD48
	lock
	faceplayer
	msgbox MirageTower_4F_Text_TakeRootFossil, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MirageTower_4F_EventScript_LeaveRootFossil
	giveitem ITEM_ROOT_FOSSIL
	closemessage
	setflag FLAG_HIDE_MIRAGE_TOWER_ROOT_FOSSIL
	setflag FLAG_HIDE_MIRAGE_TOWER_CLAW_FOSSIL
	removeobject LOCALID_ROOT_FOSSIL
	delay 30
	setflag FLAG_CHOSE_ROOT_FOSSIL
	goto MirageTower_4F_EventScript_CollapseMirageTower
	end

MirageTower_4F_EventScript_LeaveRootFossil:: @ 823AD7F
	msgbox MirageTower_4F_Text_LeftRootFossilAlone, MSGBOX_DEFAULT
	release
	end

MirageTower_4F_EventScript_ClawFossil:: @ 823AD89
	lock
	faceplayer
	msgbox MirageTower_4F_Text_TakeClawFossil, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MirageTower_4F_EventScript_LeaveClawFossil
	giveitem ITEM_CLAW_FOSSIL
	closemessage
	setflag FLAG_HIDE_MIRAGE_TOWER_CLAW_FOSSIL
	setflag FLAG_HIDE_MIRAGE_TOWER_ROOT_FOSSIL
	removeobject LOCALID_CLAW_FOSSIL
	delay 30
	setflag FLAG_CHOSE_CLAW_FOSSIL
	goto MirageTower_4F_EventScript_CollapseMirageTower
	end

MirageTower_4F_EventScript_LeaveClawFossil:: @ 823ADC0
	msgbox MirageTower_4F_Text_LeaveClawFossilAlone, MSGBOX_DEFAULT
	release
	end

MirageTower_4F_EventScript_CollapseMirageTower:: @ 823ADCA
	setvar VAR_0x8004, 1   @ vertical pan
	setvar VAR_0x8005, 1   @ horizontal pan
	setvar VAR_0x8006, 32  @ num shakes
	setvar VAR_0x8007, 2   @ shake delay
	special ShakeCamera
	waitstate
	special DoMirageTowerCeilingCrumble
	waitstate
	setvar VAR_MIRAGE_TOWER_STATE, 1
	clearflag FLAG_LANDMARK_MIRAGE_TOWER
	warp MAP_ROUTE111, 255, 19, 59
	waitstate
	release
	end

MirageTower_4F_Text_TakeRootFossil: @ 823ADF9
	.string "뿌리화석을 발견했다!\p"
	.string "이 화석을 가져가면\n"
	.string "발밑이 무너져버릴 것 같다...\p"
	.string "뿌리화석을 가져가겠습니까?$"
	// ねっこのカセキを みつけた!ｐ
	// この カセキを とるとｎ
	// あしもとが くずれて しまいそうだ……ｐ
	// ねっこのカセキを とりますか?

MirageTower_4F_Text_LeftRootFossilAlone: @ 823AE79
	.string "{PLAYER}{K_EUNNEUN} 뿌리화석을\n"
	.string "그대로 놔뒀다$"
	// §あは ねっこのカセキをｎ
	// そのままに しておいた

MirageTower_4F_Text_TakeClawFossil: @ 823AE98
	.string "발톱화석을 발견했다!\p"
	.string "이 화석을 가져가면\n"
	.string "발밑이 무너져버릴 것 같다...\p"
	.string "발톱화석을 가져가겠습니까?$"
	// ツメのカセキを みつけた!ｐ
	// この カセキを とるとｎ
	// あしもとが くずれて しまいそうだ……ｐ
	// ツメのカセキを とりますか?

MirageTower_4F_Text_LeaveClawFossilAlone: @ 823AF18
	.string "{PLAYER}{K_EUNNEUN} 발톱화석을\n"
	.string "그대로 놔뒀다$"
	// §あは ツメのカセキをｎ
	// そのままに しておいた

