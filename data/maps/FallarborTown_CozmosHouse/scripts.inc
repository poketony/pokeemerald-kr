FallarborTown_CozmosHouse_MapScripts:: @ 8200F12
	.byte 0

FallarborTown_CozmosHouse_EventScript_ProfCozmo:: @ 8200F13
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM27, FallarborTown_CozmosHouse_EventScript_GaveMeteorite
	checkitem ITEM_METEORITE, 1
	compare VAR_RESULT, TRUE
	goto_if_eq FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_PlayerHasMeteorite:: @ 8200F38
	call_if_unset FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_NoticeMeteorite
	call_if_set FLAG_TEMP_2, FallarborTown_CozmosHouse_EventScript_AskForMeteorite
	compare VAR_RESULT, NO
	goto_if_eq FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite
	msgbox FallarborTown_CozmosHouse_Text_PleaseUseThisTM, MSGBOX_DEFAULT
	giveitem ITEM_TM27
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setvar VAR_0x8004, ITEM_METEORITE
	call Common_EventScript_PlayerHandedOverTheItem
	setflag FLAG_RECEIVED_TM27
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_NoticeMeteorite:: @ 8200F8B
	msgbox FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow, MSGBOX_DEFAULT
	msgbox FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_AskForMeteorite:: @ 8200F9C
	msgbox FallarborTown_CozmosHouse_Text_MayIHaveMeteorite, MSGBOX_YESNO
	return

FallarborTown_CozmosHouse_EventScript_DeclineGiveMeteorite:: @ 8200FA5
	setflag FLAG_TEMP_2
	msgbox FallarborTown_CozmosHouse_Text_CrushedWithDisappointment, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_GaveMeteorite:: @ 8200FB2
	msgbox FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmosWife:: @ 8200FBC
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM27, FallarborTown_CozmosHouse_EventScript_CozmoIsHappy
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_CozmosHouse_EventScript_CozmoIsSad
	msgbox FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsSad:: @ 8200FDA
	msgbox FallarborTown_CozmosHouse_Text_FeelSorryForCozmo, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_EventScript_CozmoIsHappy:: @ 8200FE4
	msgbox FallarborTown_CozmosHouse_Text_CozmoIsSoHappy, MSGBOX_DEFAULT
	release
	end

FallarborTown_CozmosHouse_Text_MeteoriteWillNeverBeMineNow: @ 8200FEE
	.string "공석박사: 아아...\n"
	.string "마그마단에게 속아서\l"
	.string "운석을 손에 넣을 수 있는 장소를\l"
	.string "알려주고 말았어...\p"
	.string "유성의 폭포의 운석은\n"
	.string "더 이상 내 것이 아니겠지...$"
	// ソライシ『ああ……ｎ
	// マグマだんに だまされたからと いってｌ
	// いんせきが てに はいる ばしょをｌ
	// おしえてしまったら だめ だなあ……ｐ
	// りゅうせいのたき の いんせきｎ
	// もう ぼくの モノには ならないよな……

FallarborTown_CozmosHouse_Text_IsThatMeteoriteMayIHaveIt: @ 82010A2
	.string "오오! 에에?\p"
	.string "그건...\p"
	.string "혹시 설마..\p"
	.string "마그마단이 유성의 폭포에서\n"
	.string "가져갔었던 운석인가요...!?\p"
	.string "괜찮다면 제게 넘겨주세요!\p"
	.string "공짜로 넘기라고 하진 않겠습니다\n"
	.string "답례로 이 기술머신을\l"
	.string "드릴 테니까...$"
	// おお! ええ?ｐ
	// それは……ｐ
	// もしかして もしかすると……ｐ
	// マグマだんが りゅうせいのたき からｎ
	// もっていった いんせき ですか……!?ｐ
	// よかったら ぼくに ください!ｐ
	// ただで とは いいませんｎ
	// かわりに この わざマシンをｌ
	// あげますから……

FallarborTown_CozmosHouse_Text_PleaseUseThisTM: @ 8201159
	.string "공석박사: 이 기술머신은\n"
	.string "제 고마움의 표시입니다\l"
	.string "꼭 써보세요!$"
	// ソライシ『この わざマシンはｎ
	// ぼくの きもちですｌ
	// ぜひ つかってください!

FallarborTown_CozmosHouse_Text_ReallyGoingToHelpMyResearch: @ 82011A5
	.string "공석박사: 이야- 정말로 기쁩니다\n"
	.string "이걸로 제 연구도 순조로워졌어요!$"
	// ソライシ『いや- すごく うれしいなｎ
	// これで ぼくの けんきゅうも はかどります!

FallarborTown_CozmosHouse_Text_CrushedWithDisappointment: @ 8201212
	.string "공석박사: 그럴 수가...\n"
	.string "완전 실망입니다...$"
	// ソライシ『そんな……ｎ
	// ものすごく がっかりだよ……$

FallarborTown_CozmosHouse_Text_MayIHaveMeteorite: @ 8201249
	.string "공석박사: 그 운석...\n"
	.string "괜찮다면 제게 넘겨주세요!\p"
	.string "공짜로 넘기라고 하진 않겠습니다\n"
	.string "답례로 이 기술머신을\l"
	.string "드릴 테니까...$"	
	// ソライシ『その いんせき……ｎ
	// よかったら ぼくに ください!ｐ
	// ただで とは いいませんｎ
	// かわりに この わざマシンをｌ
	// あげますから……

FallarborTown_CozmosHouse_Text_CozmoWentToMeteorFalls: @ 82012BC
	.string "공석박사님은\n"
	.string "마그마단 사람들과 같이\l"
	.string "114번 도로에 있는\l"
	.string "유성의 폭포에 가셨어요$"
	// ソライシはかせはｎ
	// マグマだんの ひとと いっしょにｌ
	// 114ばん どうろに あるｌ
	// りゅうせいのたきに いきましたよ

FallarborTown_CozmosHouse_Text_FeelSorryForCozmo: @ 8201310
	.string "공석박사님...\n"
	.string "저렇게 슬퍼하시다니 불쌍해!$"
	// ソライシはかせ……ｎ
	// あんなに おちこんで かわいそう!

FallarborTown_CozmosHouse_Text_CozmoIsSoHappy: @ 820134B
	.string "공석박사님...\n"
	.string "저렇게 기뻐하시다니 귀여워!$"
	// ソライシはかせ ったらｎ
	// あんなに よろこんで かわいい!

