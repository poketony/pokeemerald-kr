Route111_Text_MakingRoomUseTMToMakeYourOwn: @ 82762C9
	.string "엣 뭘 하고 있냐고?\p"
	.string "포켓몬의 기술을 써서\n"
	.string "여기에 나만의 방을\l"
	.string "만들려고 생각 중이야!\p"
	.string "그래 이 기술머신을 줄 테니까\n"
	.string "너도 만들어 볼래?$"
	@ えっ なにを してるかって?ｐ
	@ ポケモンの わざを つかってｎ
	@ ここに ぼくだけの へやをｌ
	@ つくろうと おもってね!ｐ
	@ そうだっ この わざマシンを あげるからｎ
	@ きみも つくって みるかい?

Route111_Text_ExplainSecretPower: @ 827636E
	.string "덩굴이 떨어질 것 같은 나무를 향해서\n"
	.string "비밀의힘을 써 봐!\l"
	.string "덩굴이 떨어져서 나무 위에 들어갈 수 있어!\p"
	.string "그러면 위에 넓은 방이 있어서\n"
	.string "나는 거기에 좋아하는 물건을 놓지!\l"
	.string "자신만의 비밀의 방...\l"
	.string "그래 비밀기지야!\l"
	.string "너도 만들면 좋을걸-\p"
	.string "아 참 비밀기지를 만들 수 있는 곳은\n"
	.string "나무 위뿐만이 아니야!\p"
	.string "작게 움푹 패인 벽 같은 곳에도\n"
	.string "비밀의힘을 써보도록 해!\p"
	.string "나는 다른 장소를 찾아보도록 할게\n"
	.string "그럼 이만!$"
	@ ツルが おちそうな きにむかってｎ
	@ ひみつのちからを つかってごらん!ｌ
	@ ツルが おちてきて きのうえに のぼれるよ!ｐ
	@ それでね うえには ひろいへやが あるからｎ
	@ ぼくは そこに すきなものを おくんだ!ｌ
	@ じぶんだけの ひみつのへや…ｌ
	@ そう ひみつきちさ!ｌ
	@ きみも つくると いいよ-ｐ
	@ そうそう ひみつきちを つくれる ばしょはｎ
	@ きのうえ だけじゃ ないよ!ｐ
	@ ちいさな くぼみがある かべなんかにもｎ
	@ ひみつのちからを つかって みるといいよ!ｐ
	@ ぼくも ほかの ばしょを さがして みるねｎ
	@ それじゃ!

Route111_Text_DontWantThis: @ 827655C
	.string "그래 필요 없구나...\n"
	.string "가지고 싶어진다면 다시 말 걸어줘!$"
	@ そう いらないんだ…ｎ
	@ ほしくなったら また こえかけてね!

Route111_Text_DontHaveAnyRoom: @ 827659D
	.string "어라?\n"
	.string "그 이상은 지닐 수 없는 것 같아\p"
	.string "다음에 가지러 와줘!$"
	@ あれ?ｎ
	@ それいじょうは もてない みたいだよｐ
	@ また こんど とりに きてね!

Route111_EventScript_SecretPowerMan:: @ 82765FF
	lock
	faceplayer
	msgbox Route111_Text_MakingRoomUseTMToMakeYourOwn, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route111_EventScript_GiveSecretPower
	msgbox Route111_Text_DontWantThis, MSGBOX_DEFAULT
	release
	end

Route111_EventScript_GiveSecretPower:: @ 827661E
	giveitem ITEM_TM43
	compare VAR_RESULT, FALSE
	goto_if_eq Route111_EventScript_NoRoomForSecretPower
	msgbox Route111_Text_ExplainSecretPower, MSGBOX_DEFAULT
	closemessage
	setflag FLAG_RECEIVED_SECRET_POWER
	clearflag FLAG_HIDE_SLATEPORT_CITY_TM_SALESMAN
	compare VAR_FACING, DIR_WEST
	call_if_eq Route111_EventScript_SecretPowerManExit
	compare VAR_FACING, DIR_EAST
	call_if_eq Route111_EventScript_SecretPowerManExit
	compare VAR_FACING, DIR_NORTH
	call_if_eq Route111_EventScript_SecretPowerManExitNorth
	removeobject VAR_LAST_TALKED
	release
	end

Route111_EventScript_SecretPowerManExit:: @ 827666A
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExit
	waitmovement 0
	return

Route111_EventScript_SecretPowerManExitNorth:: @ 8276675
	applymovement VAR_LAST_TALKED, Route111_Movement_SecretPowerManExitNorth
	waitmovement 0
	return

Route111_EventScript_NoRoomForSecretPower:: @ 8276680
	msgbox Route111_Text_DontHaveAnyRoom, MSGBOX_DEFAULT
	release
	end

Route111_Movement_SecretPowerManExit: @ 827668A
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end

Route111_Movement_SecretPowerManExitNorth: @ 8276696
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	step_end
