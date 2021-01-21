VerdanturfTown_WandasHouse_MapScripts:: @ 82028BE
	.byte 0

VerdanturfTown_WandasHouse_EventScript_Wally:: @ 82028BF
	lock
	faceplayer
	goto_if_set FLAG_WALLY_SPEECH, VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeech, MSGBOX_DEFAULT
	setflag FLAG_WALLY_SPEECH
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallyShortSpeech:: @ 82028D7
	msgbox VerdanturfTown_WandasHouse_Text_StrongerSpeechShort, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncle:: @ 82028E1
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff
	msgbox VerdanturfTown_WandasHouse_Text_WallysNextDoor, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleSlippedOff:: @ 82028FF
	msgbox VerdanturfTown_WandasHouse_Text_WallySlippedOff, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysUncleEverGrande:: @ 8202909
	msgbox VerdanturfTown_WandasHouse_Text_WallyGoneThatFar, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandasBoyfriend:: @ 8202913
	msgbox VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay, MSGBOX_NPC
	end

VerdanturfTown_WandasHouse_EventScript_Wanda:: @ 820291C
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WandaDontWorry
	goto_if_set FLAG_DEFEATED_WALLY_MAUVILLE, VerdanturfTown_WandasHouse_EventScript_MeetWanda
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_MeetWanda:: @ 820293A
	msgbox VerdanturfTown_WandasHouse_Text_MeetWanda, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WandaDontWorry:: @ 8202944
	msgbox VerdanturfTown_WandasHouse_Text_DontWorryAboutWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAunt:: @ 820294E
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened
	goto_if_set FLAG_RUSTURF_TUNNEL_OPENED, VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntTunnelOpen:: @ 8202975
	msgbox VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntAnythingHappened:: @ 820297F
	msgbox VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_EventScript_WallysAuntEverGrande:: @ 8202989
	msgbox VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_WandasHouse_Text_StrongerSpeech: @ 8202993
	.string "민진: {PLAYER}님에게는 졌지만\n"
	.string "더는 우울해하지 않을 거예요\p"
	.string "왜냐면 랄토스와 함께\n"
	.string "여기저기 체육관에 도전해서\l"
	.string "대단한 트레이너가 되겠다는\l"
	.string "목표가 생겼으니까요!\p"
	.string "언젠가 {PLAYER}님보다도\n"
	.string "강해져서 한번 더\l"
	.string "포켓몬 승부를 할 거니까요!$"

VerdanturfTown_WandasHouse_Text_StrongerSpeechShort: @ 8202ABE
	.string "민진: 언젠가 {PLAYER}님보다도\n"
	.string "강해져서 한번 더\l"
	.string "포켓몬 승부를 할 거니까요!$"

VerdanturfTown_WandasHouse_Text_WallysNextDoor: @ 8202B37
	.string "작은아버지: 오오! {PLAYER}{K_AYA}\n"
	.string "민진은 옆방에 있단다!\p"
	.string "그나저나 대단하구나!\p"
	.string "자연에 둘러싸인 환경 덕분에\n"
	.string "민진이 건강해지고 있어!\p"
	.string "...아니 어쩌면\n"
	.string "저 아이에게 희망을 주고 있는 건\p"
	.string "포켓몬일지도 모르겠군...$"

VerdanturfTown_WandasHouse_Text_WallySlippedOff: @ 8202C20
	.string "민진...\n"
	.string "어느샌가 사라져버렸어...$"

VerdanturfTown_WandasHouse_Text_WallyGoneThatFar: @ 8202C4E
	.string "작은아버지: 그렇구나...\n"
	.string "그 민진이\l"
	.string "혼자서 그렇게 멀리까지...\p"
	.string "역시 우리 형님의 아들이야!$"

VerdanturfTown_WandasHouse_Text_MeetWanda: @ 8202CCF
	.string "미진: 당신은...?\n"
	.string "...아 그렇구나!\p"
	.string "민진이 말했던\n"
	.string "{PLAYER}님이 당신이구나!\p"
	.string "나는 민진의 사촌이야!\p"
	.string "어때? 저 아이 이쪽으로 온 이후로\n"
	.string "충분히 건강해진 것 같지?$"

VerdanturfTown_WandasHouse_Text_DontWorryAboutWally: @ 8202D91
	.string "미진: 민진이라면 괜찮을 거야!\n"
	.string "걱정하지 마!\p"
	.string "왜냐면 내 사촌이잖아!\n"
	.string "게다가 무엇보다\l"
	.string "포켓몬이 같이 있는걸!$"

VerdanturfTown_WandasHouse_Text_CanSeeGirlfriendEveryDay: @ 8202E00
	.string "네 덕분에\n"
	.string "매일 그녀와 만날 수 있어\l"
	.string "난 해피해!$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendDriven: @ 8202E47
	.string "우리 딸 애인은\n"
	.string "꽤 정열적인 사람이라서\p"
	.string "딸아이를 만나기 위해\n"
	.string "무작정 터널을 파고 있다고 하더라!\p"
	.string "딸아이도 걱정되는지\n"
	.string "항상 터널에 가고 있어$"

VerdanturfTown_WandasHouse_Text_DaughtersBoyfriendWasDigging: @ 8202F19
	.string "이럴 수가!\n"
	.string "딸아이의 애인이라는 사람이\l"
	.string "맨손으로 터널을 팠대!\p"
	.string "이거 놀랄 일이야!$"

VerdanturfTown_WandasHouse_Text_IfAnythingHappenedToWally: @ 8202F73
	.string "민진에게 만약 무슨 일이 생긴다면\n"
	.string "난 등화도시에 있는 그의 부모를\l"
	.string "볼 면목이 없어...$"

VerdanturfTown_WandasHouse_Text_WallyWasInEverGrande: @ 8202FDB
	.string "민진이 그랜드시티로 갔다고!?\p"
	.string "등화도시에 있는 그의 부모도\n"
	.string "깜짝 놀라겠는걸$"

