.set LOCALID_STEVEN, 1
.set LOCALID_BELDUM_BALL, 2

MossdeepCity_StevensHouse_MapScripts:: @ 8222784
	map_script MAP_SCRIPT_ON_LOAD, MossdeepCity_StevensHouse_OnLoad
	map_script MAP_SCRIPT_ON_TRANSITION, MossdeepCity_StevensHouse_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, MossdeepCity_StevensHouse_OnFrame
	.byte 0

MossdeepCity_StevensHouse_OnLoad: @ 8222794
	call_if_unset FLAG_SYS_GAME_CLEAR, MossdeepCity_StevensHouse_EventScript_HideStevensNote
	end

MossdeepCity_StevensHouse_EventScript_HideStevensNote:: @ 822279E
	setmetatile 6, 4, METATILE_GenericBuilding_TableEdge, 1
	return

MossdeepCity_StevensHouse_OnTransition: @ 82227A8
	compare VAR_STEVENS_HOUSE_STATE, 2
	call_if_eq MossdeepCity_StevensHouse_EventScript_SetStevenPos
	end

MossdeepCity_StevensHouse_EventScript_SetStevenPos:: @ 82227B4
	setobjectxyperm LOCALID_STEVEN, 6, 5
	setobjectmovementtype LOCALID_STEVEN, MOVEMENT_TYPE_FACE_UP
	return

MossdeepCity_StevensHouse_OnFrame: @ 82227C0
	map_script_2 VAR_STEVENS_HOUSE_STATE, 1, MossdeepCity_StevensHouse_EventScript_StevenGivesDive
	.2byte 0

MossdeepCity_StevensHouse_EventScript_StevenGivesDive:: @ 82227CA
	lockall
	applymovement LOCALID_STEVEN, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_STEVEN, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_STEVEN, Common_Movement_Delay48
	waitmovement 0
	applymovement LOCALID_STEVEN, MossdeepCity_StevensHouse_Movement_StevenApproachPlayer
	waitmovement 0
	msgbox MossdeepCity_StevensHouse_Text_YouveEarnedHMDive, MSGBOX_DEFAULT
	giveitem ITEM_HM08
	setflag FLAG_RECEIVED_HM08
	setflag FLAG_OMIT_DIVE_FROM_STEVEN_LETTER
	msgbox MossdeepCity_StevensHouse_Text_ExplainDive, MSGBOX_DEFAULT
	closemessage
	delay 20
	applymovement LOCALID_STEVEN, MossdeepCity_StevensHouse_Movement_StevenReturn
	waitmovement 0
	setflag FLAG_HIDE_MOSSDEEP_CITY_SCOTT
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ENTRANCE_AQUA_GRUNT
	setvar VAR_STEVENS_HOUSE_STATE, 2
	releaseall
	end

MossdeepCity_StevensHouse_Movement_StevenApproachPlayer: @ 8222833
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_in_place_fastest_down
	step_end

MossdeepCity_StevensHouse_Movement_StevenReturn: @ 822283B
	walk_up
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MossdeepCity_StevensHouse_EventScript_BeldumPokeball:: @ 8222841
	lockall
	msgbox MossdeepCity_StevensHouse_Text_TakeBallContainingBeldum, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_StevensHouse_EventScript_LeaveBeldum
	goto MossdeepCity_StevensHouse_EventScript_GiveBeldum
	end

MossdeepCity_StevensHouse_EventScript_LeaveBeldum:: @ 822285B
	msgbox MossdeepCity_StevensHouse_Text_LeftPokeBallWhereItWas, MSGBOX_DEFAULT
	releaseall
	end

MossdeepCity_StevensHouse_EventScript_GiveBeldum:: @ 8222865
	setvar VAR_TEMP_1, SPECIES_BELDUM
	givemon SPECIES_BELDUM, 5, ITEM_NONE
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_StevensHouse_EventScript_SendBeldumParty
	compare VAR_RESULT, 1
	goto_if_eq MossdeepCity_StevensHouse_EventScript_SendBeldumPC
	goto Common_EventScript_NoMoreRoomForPokemon
	end

MossdeepCity_StevensHouse_EventScript_SendBeldumParty:: @ 8222895
	call MossdeepCity_StevensHouse_EventScript_ReceivedBeldumFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_StevensHouse_EventScript_ReceivedBeldum
	call Common_EventScript_GetGiftMonPartySlot
	call Common_EventScript_NameReceivedPartyMon
	goto MossdeepCity_StevensHouse_EventScript_ReceivedBeldum
	end

MossdeepCity_StevensHouse_EventScript_SendBeldumPC:: @ 82228BD
	call MossdeepCity_StevensHouse_EventScript_ReceivedBeldumFanfare
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq MossdeepCity_StevensHouse_EventScript_BeldumTransferredToPC
	call Common_EventScript_NameReceivedBoxMon
	goto MossdeepCity_StevensHouse_EventScript_BeldumTransferredToPC
	end

MossdeepCity_StevensHouse_EventScript_BeldumTransferredToPC:: @ 82228E0
	call Common_EventScript_TransferredToPC
	goto MossdeepCity_StevensHouse_EventScript_ReceivedBeldum
	end

MossdeepCity_StevensHouse_EventScript_ReceivedBeldumFanfare:: @ 82228EB
	bufferspeciesname 1, SPECIES_BELDUM
	removeobject LOCALID_BELDUM_BALL
	playfanfare MUS_OBTAIN_ITEM
	message MossdeepCity_StevensHouse_Text_ObtainedBeldum
	waitmessage
	waitfanfare
	bufferspeciesname 0, SPECIES_BELDUM
	return

MossdeepCity_StevensHouse_EventScript_ReceivedBeldum:: @ 8222901
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_BELDUM_POKEBALL
	setflag FLAG_RECEIVED_BELDUM
	releaseall
	end

MossdeepCity_StevensHouse_EventScript_RockDisplay:: @ 8222909
	msgbox MossdeepCity_StevensHouse_Text_CollectionOfRareRocks, MSGBOX_SIGN
	end

MossdeepCity_StevensHouse_EventScript_Steven:: @ 8222912
	msgbox MossdeepCity_StevensHouse_Text_UnderwateCavernBetweenMossdeepSootopolis, MSGBOX_NPC
	end

MossdeepCity_StevensHouse_EventScript_Letter:: @ 822291B
	lockall
	msgbox MossdeepCity_StevensHouse_Text_LetterFromSteven, MSGBOX_DEFAULT
	releaseall
	end

@ Unused, leftover from RS
MossdeepCity_StevensHouse_EventScript_DiveItemBall:: @ 8222926
	finditem ITEM_HM08
	setflag FLAG_RECEIVED_HM08
	end

MossdeepCity_StevensHouse_Text_YouveEarnedHMDive: @ 8222936
	.string "성호: {PLAYER}...\p"
	.string "보는 대로 아무것도 없지만\n"
	.string "여기가 내 집이야\p"
	.string "...맞다 아까는 고마웠어\n"
	.string "이건 내가 주는 감사의 마음\l"
	.string "비전머신 다이빙이야\p"
	.string "사양 말고 받아줘$"
	@ ダイゴ『§あ§お……ｐ
	@ みてのとおり なにも ないけどｎ
	@ ここが ボクの いえなんだｐ
	@ ……そうだ さっきは ありがとうｎ
	@ これは ボクからの おれいの きもちｌ
	@ ひでんマシンの ダイビングだｐ
	@ えんりょ しないで もっていきなよ

MossdeepCity_StevensHouse_Text_ExplainDive: @ 8222A0E
	.string "성호: 파도타기를 하고 있으면\n"
	.string "물의 색이 진한 곳이 있어\p"
	.string "거기서 다이빙을 사용하면\n"
	.string "바다 깊은 곳으로 잠수할 수 있지\p"
	.string "다시 올라오고 싶을 때는\n"
	.string "다시 한 번 다이빙을 쓰면 돼\p"
	.string "장소에 따라\n"
	.string "올라올 수 없는 경우도 있지만$"
	@ ダイゴ『なみのりを しているとｎ
	@ みずの いろが こい ばしょが あるｐ
	@ そこで ダイビングを つかうとｎ
	@ うみの そこに もぐれるからｐ
	@ うかびたい ときはｎ
	@ もういちど ダイビングを つかうんだｐ
	@ ばしょに よってはｎ
	@ うかべない ばあいも あるけど

MossdeepCity_StevensHouse_Text_UnderwateCavernBetweenMossdeepSootopolis: @ 8222B11
	.string "성호: 이끼시티와 루네시티 사이에는\n"
	.string "해저동굴이 있는 것 같아\p"
	.string "왜 그... 해양관장이\n"
	.string "발견한 그거 있잖아$"
	@ ダイゴ『トクサネと ルネの あいだにはｎ
	@ かいていどうくつが あるらしいｐ
	@ ほら たしか…… クスノキかんちょうがｎ
	@ はっけんした という あれだよ

MossdeepCity_StevensHouse_Text_TakeBallContainingBeldum: @ 8222B9E
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "몬스터볼을 조사했다!\p"
	.string "안에는 포켓몬\n"
	.string "메탕이 들어 있다!\p"
	.string "몬스터볼을 가지고 가겠습니까?$"
	@ §あはｎ
	@ モンスタ-ボ-ルを しらべた!ｐ
	@ なかには ポケモンのｎ
	@ ダンバルが はいっている!ｐ
	@ モンスタ-ボ-ルを もって いきますか?

MossdeepCity_StevensHouse_Text_ObtainedBeldum: @ 8222BED
	.string "{PLAYER}{K_EUNNEUN}\n"
	.string "메탕을 손에 넣었다!$"
	@ §あはｎ
	@ ダンバルを てにいれた!

@ Unused
MossdeepCity_StevensHouse_Text_NoSpaceForAnotherMon: @ 8222C03
	.string "이 이상 포켓몬을 지닐 수 없다!$"
	@ これいじょう ポケモンを もてない!

MossdeepCity_StevensHouse_Text_LeftPokeBallWhereItWas: @ 8222C2A
	.string "{PLAYER}{K_EUNNEUN} 몬스터볼을\n"
	.string "그대로 놔두었다$"
	@ あは モンスタ-ボ-ルをｎ
	@ そのままに しておいた

MossdeepCity_StevensHouse_Text_LetterFromSteven: @ 8222C4E
	.string "편지가 있다!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "{PLAYER}에게\p"
	.string "난 생각할 게 좀 있어서\n"
	.string "잠시 수행을 계속할 거야\l"
	.string "당분간은 집에 돌아갈 생각이 없어\p"
	.string "그래서 부탁 하나 할게\p"
	.string "책상 위에 있는\n"
	.string "몬스터볼을 받아줬으면 해\p"
	.string "안에는 메탕이라고 하는\n"
	.string "내가 좋아하는 포켓몬이 들어있으니까\p"
	.string "잘 부탁해\p"
	.string "그럼 또 어딘가에서 만나자!\n"
	.string "                           나성호가$"
	@ てがみが ある!ｐ
	@ …… …… ……ｎ
	@ …… …… ……ｐ
	@ §あ§おへｐ
	@ ボクは おもうことが あってｎ
	@ しばらく しゅぎょうを つづけるｌ
	@ とうぶん いえに かえらないｐ
	@ そこで おねがいだｐ
	@ つくえの うえにあるｎ
	@ モンスタ-ボ-ルを うけとって ほしいｐ
	@ なかに いるのは ダンバルといってｎ
	@ ボクの おきにいりの ポケモンだからｐ
	@ よろしく たのむよｐ
	@ では また いつか あおう!ｎ
	@       ツワブキ ダイゴより

MossdeepCity_StevensHouse_Text_CollectionOfRareRocks: @ 8222D97
	.string "성호가 모은\n"
	.string "희귀한 돌이 장식되어 있다!$"
	@ ダイゴの あつめたｎ
	@ めずらしい いしが かざってある!

