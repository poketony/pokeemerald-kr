RustboroCity_Gym_MapScripts:: @ 8212F30
	.byte 0

RustboroCity_Gym_EventScript_Roxanne:: @ 8212F31
	trainerbattle_single TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxanneIntro, RustboroCity_Gym_Text_RoxanneDefeat, RustboroCity_Gym_EventScript_RoxanneDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq RustboroCity_Gym_EventScript_RoxanneRematch
	goto_if_unset FLAG_RECEIVED_TM39, RustboroCity_Gym_EventScript_GiveRockTomb
	msgbox RustboroCity_Gym_Text_RoxannePostBattle, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneDefeated:: @ 8212F66
	message RustboroCity_Gym_Text_ReceivedStoneBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox RustboroCity_Gym_Text_StoneBadgeInfoTakeThis, MSGBOX_DEFAULT
	setflag FLAG_DEFEATED_RUSTBORO_GYM
	setflag FLAG_BADGE01_GET
	setvar VAR_RUSTBORO_CITY_STATE, 1
	addvar VAR_PETALBURG_GYM_STATE, 1
	setvar VAR_0x8008, 1
	call Common_EventScript_SetGymTrainers
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	goto RustboroCity_Gym_EventScript_GiveRockTomb
	end

RustboroCity_Gym_EventScript_GiveRockTomb:: @ 8212FA4
	giveitem ITEM_TM39
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM39
	msgbox RustboroCity_Gym_Text_ExplainRockTomb, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_RoxanneRematch:: @ 8212FC8
	trainerbattle_rematch_double TRAINER_ROXANNE_1, RustboroCity_Gym_Text_RoxannePreRematch, RustboroCity_Gym_Text_RoxanneRematchDefeat, RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons
	msgbox RustboroCity_Gym_Text_RoxannePostRematch, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Josh:: @ 8212FE3
	trainerbattle_single TRAINER_JOSH, RustboroCity_Gym_Text_JoshIntro, RustboroCity_Gym_Text_JoshDefeat
	msgbox RustboroCity_Gym_Text_JoshPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Tommy:: @ 8212FFA
	trainerbattle_single TRAINER_TOMMY, RustboroCity_Gym_Text_TommyIntro, RustboroCity_Gym_Text_TommyDefeat
	msgbox RustboroCity_Gym_Text_TommyPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_Marc:: @ 8213011
	trainerbattle_single TRAINER_MARC, RustboroCity_Gym_Text_MarcIntro, RustboroCity_Gym_Text_MarcDefeat
	msgbox RustboroCity_Gym_Text_MarcPostBattle, MSGBOX_AUTOCLOSE
	end

RustboroCity_Gym_EventScript_GymGuide:: @ 8213028
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_RUSTBORO_GYM, RustboroCity_Gym_EventScript_GymGuidePostVictory
	msgbox RustboroCity_Gym_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_GymGuidePostVictory:: @ 821303D
	msgbox RustboroCity_Gym_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

RustboroCity_Gym_EventScript_LeftGymStatue:: @ 8213047
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_RightGymStatue:: @ 8213057
	lockall
	goto_if_set FLAG_BADGE01_GET, RustboroCity_Gym_EventScript_GymStatueCertified
	goto RustboroCity_Gym_EventScript_GymStatue
	end

RustboroCity_Gym_EventScript_GymStatueCertified:: @ 8213067
	msgbox RustboroCity_Gym_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_GymStatue:: @ 8213071
	msgbox RustboroCity_Gym_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

RustboroCity_Gym_EventScript_RegisterRoxanne:: @ 821307B
	lockall
	pokenavcall RustboroCity_Gym_Text_RoxanneRegisterCall
	waitmessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox RustboroCity_Gym_Text_RegisteredRoxanne, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_ROXANNE_MATCH_CALL
	clearflag FLAG_ENABLE_ROXANNE_FIRST_CALL
	releaseall
	end

RustboroCity_Gym_Text_GymGuideAdvice: @ 821309D
	.string "잘 있었나!!\p"
	.string "갑작스럽지만 너!\n"
	.string "챔피언을 목표로 해보지 않을래?\p"
	.string "난 트레이너는 아니지만\n"
	.string "이기기 위한 확실한\l"
	.string "어드바이스를 할 수 있어!\p"
	.string "좋아 정했다! 같이\n"
	.string "포켓몬 챔피언을 목표로 하자\p"
	.string "트레이너의 목적이라고 하면\n"
	.string "체육관 배지를 모으는 거잖아\l"
	.string "그렇지만 체육관 관장은 강하다!\p"
	.string "그래서 내가 나올 차례라는 거지!\p"
	.string "너에게 확실한\n"
	.string "어드바이스를 해줄게!\p"
	.string "여기 체육관 관장 원규는\n"
	.string "바위타입의 포켓몬 사용자!\p"
	.string "바위타입은 단단하지만\n"
	.string "물타입이나 풀타입의\l"
	.string "공격에는 약해!\p"
	.string "체육관 관장을 이기면\n"
	.string "다시 나에게 말 걸어줘!\p"
	.string "그럼 힘내-!!$"

RustboroCity_Gym_Text_GymGuidePostVictory: @ 82132E2
	.string "우오오! 멋진 승리다!!\n"
	.string "내 응원이 좋았던 걸까!?\p"
	.string "좋아! 너의\n"
	.string "트레이너카드를 봐봐!\p"
	.string "아까 손에 넣은 스톤배지가\n"
	.string "잘 기록되어 있지\p"
	.string "즉...\p"
	.string "너는 챔피언으로 향한 계단을\n"
	.string "하나 올라간 거야!\p"
	.string "늠름해-!!$"

RustboroCity_Gym_Text_JoshIntro: @ 82133E9
	.string "체육관 소속 트레이너를\n"
	.string "우습게 보지 말라고!\l"
	.string "실력의 차이를 보여주겠어!$"

RustboroCity_Gym_Text_JoshDefeat: @ 821342D
	.string "실력이 너무 달라...!$"

RustboroCity_Gym_Text_JoshPostBattle: @ 8213447
	.string "바위타입의 진정한 무서움은\n"
	.string "이 정도가 아니라고!$"

RustboroCity_Gym_Text_TommyIntro: @ 8213486
	.string "날 이길 실력이 없으면\n"
	.string "원규님에겐 절대로 이길 수 없어!$"

RustboroCity_Gym_Text_TommyDefeat: @ 82134C6
	.string "엄청난 실력이다!$"

RustboroCity_Gym_Text_TommyPostBattle: @ 82134E6
	.string "원규님은 나보다\n"
	.string "몇 배는 더 강해!\p"
	.string "방심하지 않는 게 좋을 거야!$"

RustboroCity_Gym_Text_MarcIntro: @ 8213533
	.string "이런 마을에서도\n"
	.string "바위타입은 대활약한다고!$"
	// こんな まちなか でもｎ
	// いわタイプで おおあばれだ!

RustboroCity_Gym_Text_MarcDefeat: @ 8213589
	.string "오옷-!\n"
	.string "기세 좋은 도전자구만!$"
	// おお-っ!ｎ
	// いきの いい ちょうせんしゃ だな!

RustboroCity_Gym_Text_MarcPostBattle: @ 82135C0
	.string "젊은데도 바위타입을\n"
	.string "고르다니\l"
	.string "우리 체육관 관장은 감이 좋아!$"
	// わかくして いわタイプにｎ
	// めを つける なんてｌ
	// うちの ジムリ-ダ-は センスが いいぜ!

RustboroCity_Gym_Text_RoxanneIntro: @ 821362A
	.string "어머 안녕하세요\p"
	.string "전 금탄도시 포켓몬체육관\n"
	.string "체육관 관장 원규라고 합니다\p"
	.string "트레이너스쿨에서 배운 내용을\n"
	.string "승부에 살리고 싶어서\l"
	.string "체육관 관장이 되었습니다\p"
	.string "어떤 포켓몬으로\n"
	.string "어떻게 배틀할지\l"
	.string "저에게 알려주시겠어요?$"

RustboroCity_Gym_Text_RoxanneDefeat: @ 821370B
	.string "전 져버린 거군요...\p"
	.string "더 많은 것을\n"
	.string "공부할 필요가 있는 것 같아요...\p"
	.string "잘 알았습니다\p"
	.string "포켓몬리그의 규칙으로\n"
	.string "체육관 관장을 이긴 트레이너에게\l"
	.string "이것을 드리게 되어 있습니다\p"
	.string "어서 포켓몬리그 공인\n"
	.string "스톤배지를 받아 주세요$"

RustboroCity_Gym_Text_ReceivedStoneBadge: @ 82137EC
	.string "{PLAYER}{K_EUNNEUN} 원규에게\n"
	.string "스톤배지를 받았다!$"

RustboroCity_Gym_Text_StoneBadgeInfoTakeThis: @ 8213816
	.string "스톤배지를 가지고 있으면\n"
	.string "지닌 포켓몬의\l"
	.string "공격력이 올라가게 됩니다\p"
	.string "또한 비전기술인 풀베기를\n"
	.string "사용할 수 있게 됩니다\p"
	.string "마지막으로...\n"
	.string "이것도 받아 주세요$"

RustboroCity_Gym_Text_ExplainRockTomb: @ 82138B1
	.string "기술머신39의 안에는\n"
	.string "암석봉인이 들어 있습니다\p"
	.string "암석봉인은 상대를 향해\n"
	.string "바위를 떨어뜨려 데미지를 주고\p"
	.string "거기에 상대의 스피드까지\n"
	.string "떨어뜨리는 기술입니다\p"
	.string "기술머신을 사용하면\n"
	.string "포켓몬에게 한순간에\l"
	.string "기술을 배우게 할 수 있습니다\p"
	.string "다만 한 번 쓰면 없어져버리니\n"
	.string "쓸 때는 잘 생각하도록 하세요$"

RustboroCity_Gym_Text_RoxannePostBattle: @ 82139A7
	.string "그 정도로 강하다면\n"
	.string "다른 포켓몬체육관에도\l"
	.string "도전하는 건 어떠세요?\p"
	.string "많은 트레이너와 승부하는 것으로\n"
	.string "여러 가지를 배울 수 있을 거예요$"

RustboroCity_Gym_Text_GymStatue: @ 8213A21
	.string "금탄도시 포켓몬체육관$"

RustboroCity_Gym_Text_GymStatueCertified: @ 8213A3B
	.string "금탄도시 포켓몬체육관\p"
	.string "원규 인정 트레이너!\n"
	.string "{PLAYER}$"

RustboroCity_Gym_Text_RoxanneRegisterCall: @ 8213A76
	.string "...... ...... ......\n"
	.string "...... ...... ...... 삑!\p"
	.string "원규: 앗 {PLAYER}씨인가요?\n"
	.string "저 금탄도시의 원규예요!\p"
	.string "종길씨한테서 들었습니다\n"
	.string "당신 굉장한 기세로\l"
	.string "이겨나가고 있던데요!\p"
	.string "이쪽도 진 채로 있을 수 없죠\n"
	.string "다시 한 번 체육관을 정비하고\l"
	.string "언젠가 다시 도전을 받겠습니다!\p"
	.string "부디 그 날을\n"
	.string "기대해 주세요!\p"
	.string "...... ...... ......\n"
	.string "...... ...... ...... 딸깍-$"
	// …… …… ……ｎ
	// …… …… …… ピッ!ｐ
	// ツツジ『あっ §あさん ですか?ｎ
	// わたくし カナズミの ツツジです!ｐ
	// トウキさんから ききましたよぉｎ
	// あなた すごい いきおいでｌ
	// かちすすんで いるらしい ですね!ｐ
	// こちらも まけっぱなしでは いられませんｎ
	// もういちど ジムを きたえなおしてｌ
	// いつかまた ちょうせんを うけますよ!ｐ
	// そのひが くるのをｎ
	// どうぞ まっていて くださいね!ｐ
	// …… …… ……ｎ
	// …… …… …… ツ-

RustboroCity_Gym_Text_RegisteredRoxanne: @ 8213C01
	.string "체육관 관장 원규를\n"
	.string "포켓내비에 등록했다!$"

RustboroCity_Gym_Text_RoxannePreRematch: @ 8213C2F
	.string "원규: 다시 뵙게 되었군요\n"
	.string "체육관 관장 원규입니다\p"
	.string "그로부터 서로\n"
	.string "수많은 승부를 경험하고\p"
	.string "얼마나 강해졌는지...\n"
	.string "자 승부하도록 하죠!$"
	// ツツジ『また おめにかかれましたねｎ
	// ジムリ-ダ-の ツツジ ですｐ
	// あれから おたがいにｎ
	// いくつもの しょうぶを けいけんしｌ
	// どれほど つよく なれたのか……ｐ
	// さあ おてあわせ ねがいます!

RustboroCity_Gym_Text_RoxanneRematchDefeat: @ 8213CF9
	.string "으으으...\n"
	.string "또 저의 패배인가요....$"
	// くうぅ……ｎ
	// またしても わたくしの まけ……

RustboroCity_Gym_Text_RoxannePostRematch: @ 8213D12
	.string "원규: 아직 포켓몬 승부에는\n"
	.string "배울 것이 잔뜩 있군요\p"
	.string "저... 포켓몬 승부가\n"
	.string "더 좋아졌어요!$"
	// ツツジ『まだまだ ポケモン しょうぶはｎ
	// まなぶことが たくさん あるのですねｐ
	// わたくし…… ポケモン しょうぶがｎ
	// ますます すきに なりましたよ!

RustboroCity_Gym_Text_RoxanneRematchNeedTwoMons: @ 8213D93
	.string "원규: 다시 뵙게 되었군요\n"
	.string "체육관 관장 원규입니다\p"
	.string "그로부터 서로\n"
	.string "수많은 승부를 경험하고\l"
	.string "얼마나 강해졌는지...\p"
	.string "...어라? 싸울 수 있는 포켓몬이\n"
	.string "한 마리밖에 없군요\p"
	.string "부디 두 마리 이상\n"
	.string "포켓몬을 데리고 와주세요$"
	// ツツジ『また おめにかかれましたねｎ
	// ジムリ-ダ-の ツツジ ですｐ
	// あれから おたがいにｎ
	// いくつもの しょうぶを けいけんしｌ
	// どれほど つよく なれたのか……ｐ
	// ……あら? たたかえる ポケモンをｎ
	// 1ひきしか もっていませんねｐ
	// どうぞ 2ひき いじょうのｎ
	// ポケモンを もって きてください
