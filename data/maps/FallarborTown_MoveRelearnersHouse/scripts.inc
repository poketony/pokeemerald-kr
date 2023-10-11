.set LOCALID_MOVE_RELEARNER, 1

FallarborTown_MoveRelearnersHouse_MapScripts:: @ 8201382
	.byte 0

FallarborTown_MoveRelearnersHouse_EventScript_MoveRelearner:: @ 8201383
	lockall
	applymovement LOCALID_MOVE_RELEARNER, Common_Movement_FacePlayer
	waitmovement 0
	goto_if_set FLAG_TEMP_1, FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	msgbox FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor, MSGBOX_DEFAULT
	setflag FLAG_TEMP_1
	goto FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_AskTeachMove:: @ 82013A8
	checkitem ITEM_HEART_SCALE, 1
	compare VAR_RESULT, FALSE
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	msgbox FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove, MSGBOX_YESNO
	switch VAR_RESULT
	case NO, FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon:: @ 82013D6
	msgbox FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon, MSGBOX_DEFAULT
	special ChooseMonForMoveRelearner
	waitstate
	compare VAR_0x8004, 255
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	special IsSelectedMonEgg
	compare VAR_RESULT, TRUE
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg
	compare VAR_0x8005, 0
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove
	end

FallarborTown_MoveRelearnersHouse_EventScript_ChooseMove:: @ 820140C
	msgbox FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove, MSGBOX_DEFAULT
	special TeachMoveRelearnerMove
	waitstate
	compare VAR_0x8004, 0
	goto_if_eq FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	msgbox FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale, MSGBOX_DEFAULT
	removeitem ITEM_HEART_SCALE
	goto FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale
	end

FallarborTown_MoveRelearnersHouse_EventScript_NoMoveToTeachMon:: @ 8201436
	msgbox FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_CantTeachEgg:: @ 8201444
	msgbox FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg, MSGBOX_DEFAULT
	goto FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon
	end

FallarborTown_MoveRelearnersHouse_EventScript_ComeBackWithHeartScale:: @ 8201452
	msgbox FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale, MSGBOX_DEFAULT
	releaseall
	end

FallarborTown_MoveRelearnersHouse_Text_ImTheMoveTutor: @ 820145C
	.string "난 포켓몬 기술마니아\p"
	.string "포켓몬이 성장해서 배우는\n"
	.string "기술을 모두 알고 있어서\l"
	.string "포켓몬에게 가르쳐줄 수 있어!\p"
	.string "지금 내가 모으고 있는\n"
	.string "하트비늘을 주면\l"
	.string "알고 있는 기술을 가르쳐줄게!$"
	// ぼく ポケモン わざマニアｐ
	// ポケモンが せいちょうして おぼえていくｎ
	//わざを すべて しっていてｌ
	// ポケモンに おしえることが できるんだ!ｐ
	// ぼくが いま あつめているｎ
	// ハ-トのウロコを くれたらｌ
	// しってる わざを おしえてあげるよ!

FallarborTown_MoveRelearnersHouse_Text_ThatsAHeartScaleWantMeToTeachMove: @ 8201541
	.string "오오!\n"
	.string "그건 바로 하트비늘!\p"
	.string "기술을 떠올리게 할 거야?$"
	// おおっ!ｎ
	// それは まさしく ハ-トのウロコ!ｐ
	// わざを おぼえさせたいんだね?

FallarborTown_MoveRelearnersHouse_Text_TutorWhichMon: @ 82015A5
	.string "어느 포켓몬에게 할 거야?$"
	// どの ポケモンに するんだい?

FallarborTown_MoveRelearnersHouse_Text_TeachWhichMove: @ 82015C3
	.string "어느 기술을 배우게 할 거야?$"
	// どの わざに するんだい?

FallarborTown_MoveRelearnersHouse_Text_DontHaveMoveToTeachPokemon: @ 82015DE
	.string "미안해...\p"
	.string "내가 그 포켓몬에게\n"
	.string "가르쳐줄 수 있는 기술은 없나 봐$"
	// ごめんね……ｐ
	// ぼくが その ポケモンにｎ
	// おしえられる わざは ないみたいだよ

FallarborTown_MoveRelearnersHouse_Text_HandedOverHeartScale: @ 8201627
	.string "{PLAYER}{K_EUNNEUN} 보답으로\n"
	.string "하트비늘을 1장 주었다!$"
	// §あは おれいにｎ
	// ハ-トのウロコを 1まい あげた!

FallarborTown_MoveRelearnersHouse_Text_ComeBackWithHeartScale: @ 8201653
	.string "떠올리게 하고 싶은 기술이 있으면\n"
	.string "하트비늘을 가지고 오렴!$"
	// おぼえさせたい わざが あったらｎ
	// ハ-トのウロコを もってきてね!

FallarborTown_MoveRelearnersHouse_Text_CantTeachEgg: @ 8201697
	.string "엥?\n"
	.string "알에게 가르쳐줄 기술은 없어$"
	// えっ?ｎ
	// タマゴに おしえられる わざは ないよ

