.set LOCALID_WOMAN_1, 19
.set LOCALID_MAN_1, 20

LilycoveCity_MapScripts:: @ 81E2B3C
	map_script MAP_SCRIPT_ON_TRANSITION, LilycoveCity_OnTransition
	map_script MAP_SCRIPT_ON_LOAD, LilycoveCity_OnLoad
	.byte 0

LilycoveCity_OnTransition: @ 81E2B47
	setflag FLAG_VISITED_LILYCOVE_CITY
	setvar VAR_CONTEST_HALL_STATE, 0
	setflag FLAG_HIDE_LILYCOVE_CONTEST_HALL_REPORTER
	call_if_set FLAG_SYS_WEATHER_CTRL, Common_EventScript_SetAbnormalWeather
	call Common_EventScript_SetupRivalGfxId
	end

LilycoveCity_OnLoad: @ 81E2B61
	call_if_unset FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_SetWailmerMetatiles
	end

LilycoveCity_EventScript_SetWailmerMetatiles:: @ 81E2B6B
	setmetatile 76, 12, METATILE_Lilycove_Wailmer0, 1
	setmetatile 77, 12, METATILE_Lilycove_Wailmer1, 1
	setmetatile 76, 13, METATILE_Lilycove_Wailmer2, 1
	setmetatile 77, 13, METATILE_Lilycove_Wailmer3, 1
	setmetatile 76, 14, METATILE_Lilycove_Wailmer0_Alt, 1
	setmetatile 77, 14, METATILE_Lilycove_Wailmer1_Alt, 1
	setmetatile 76, 15, METATILE_Lilycove_Wailmer2, 1
	setmetatile 77, 15, METATILE_Lilycove_Wailmer3, 1
	setmetatile 77, 16, METATILE_Lilycove_Wailmer0_Alt, 1
	setmetatile 78, 16, METATILE_Lilycove_Wailmer1_Alt, 1
	setmetatile 77, 17, METATILE_Lilycove_Wailmer2, 1
	setmetatile 78, 17, METATILE_Lilycove_Wailmer3, 1
	return

LilycoveCity_EventScript_BerryGentleman:: @ 81E2BD8
	lock
	faceplayer
	dotimebasedevents
	goto_if_set FLAG_DAILY_LILYCOVE_RECEIVED_BERRY, LilycoveCity_EventScript_ReceivedBerry
	msgbox LilycoveCity_Text_BerrySuitsYou, MSGBOX_DEFAULT
	random 10
	addvar VAR_RESULT, FIRST_BERRY_INDEX
	giveitem VAR_RESULT
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_DAILY_LILYCOVE_RECEIVED_BERRY
	msgbox LilycoveCity_Text_BecauseYoureTrainer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ReceivedBerry:: @ 81E2C18
	msgbox LilycoveCity_Text_PokeblocksSuitPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man3:: @ 81E2C22
	msgbox LilycoveCity_Text_ContestHallInTown, MSGBOX_NPC
	end

LilycoveCity_EventScript_Girl:: @ 81E2C2B
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_GirlAquaGone
	msgbox LilycoveCity_Text_StrangeCaveInCove, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_GirlAquaGone:: @ 81E2C40
	msgbox LilycoveCity_Text_GoingToMoveDeleterForHMs, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_RichBoy:: @ 81E2C4A
	msgbox LilycoveCity_Text_ImFromKanto, MSGBOX_NPC
	end

LilycoveCity_EventScript_Sailor2:: @ 81E2C53
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Sailor2AquaGone
	msgbox LilycoveCity_Text_TeamAquaBeenTrainingWailmer, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor2AquaGone:: @ 81E2C68
	msgbox LilycoveCity_Text_SomeonePuntedTeamAquaOut, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2:: @ 81E2C72
	lock
	faceplayer
	goto_if_set FLAG_TEAM_AQUA_ESCAPED_IN_SUBMARINE, LilycoveCity_EventScript_Woman2AquaGone
	msgbox LilycoveCity_Text_SomeoneStoleMyPokemon, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Woman2AquaGone:: @ 81E2C87
	msgbox LilycoveCity_Text_MissingPokemonCameBack, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Man2:: @ 81E2C91
	msgbox LilycoveCity_Text_ImArtDealer, MSGBOX_NPC
	end

LilycoveCity_EventScript_ExpertM1:: @ 81E2C9A
	msgbox LilycoveCity_Text_SeaRemainsForeverYoung, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertF:: @ 81E2CA3
	msgbox LilycoveCity_Text_SixtyYearsAgoHusbandProposed, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ExpertM2:: @ 81E2CAC
	lock
	faceplayer
	goto_if_set FLAG_BADGE07_GET, LilycoveCity_EventScript_ExpertM2AquaGone
	msgbox LilycoveCity_Text_TeamAquaRenovatedCavern, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_ExpertM2AquaGone:: @ 81E2CC1
	msgbox LilycoveCity_Text_TeamAquaLotGoneForGood, MSGBOX_DEFAULT
	release
	end

LilycoveCity_EventScript_Sailor1:: @ 81E2CCB
	msgbox LilycoveCity_Text_HeardTowerCalledSkyPillar, MSGBOX_NPC
	end

LilycoveCity_EventScript_FatMan:: @ 81E2CD4
	msgbox LilycoveCity_Text_SawTallTowerOnRoute131, MSGBOX_NPC
	end

LilycoveCity_EventScript_Man1:: @ 81E2CDD
	lockall
	msgbox LilycoveCity_Text_JustArrivedAndSawRarePokemon, MSGBOX_NPC
	applymovement LOCALID_MAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_Woman1:: @ 81E2CEE
	lockall
	msgbox LilycoveCity_Text_HoneymoonVowToSeeRarePokemon, MSGBOX_NPC
	applymovement LOCALID_WOMAN_1, Common_Movement_FaceOriginalDirection
	end

LilycoveCity_EventScript_CitySign:: @ 81E2CFF
	msgbox LilycoveCity_Text_CitySign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_ContestHallSign:: @ 81E2D08
	msgbox LilycoveCity_Text_ContestHallSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MotelSign:: @ 81E2D11
	msgbox LilycoveCity_Text_MotelSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MuseumSign:: @ 81E2D1A
	lockall
	specialvar VAR_0x8004, CountPlayerContestPaintings
	switch VAR_0x8004
	case 0, LilycoveCity_EventScript_MuseumSignNoPaintings
	msgbox LilycoveCity_Text_MuseumSignPlayersExhibit, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_MuseumSignNoPaintings:: @ 81E2D3A
	msgbox LilycoveCity_Text_MuseumSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSign:: @ 81E2D44
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_HarborSignFerryReady
	msgbox LilycoveCity_Text_HarborSignUnderConstruction, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_HarborSignFerryReady:: @ 81E2D58
	msgbox LilycoveCity_Text_HarborSign, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_TrainerFanClubSign:: @ 81E2D62
	msgbox LilycoveCity_Text_TrainerFanClubSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_DepartmentStoreSign:: @ 81E2D6B
	msgbox LilycoveCity_Text_DepartmentStoreSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_MoveDeletersHouseSign:: @ 81E2D74
	msgbox LilycoveCity_Text_MoveDeletersHouseSign, MSGBOX_SIGN
	end

LilycoveCity_EventScript_WailmerTrainerGrunt:: @ 81E2D7D
	lockall
	goto_if_set FLAG_MET_WAILMER_TRAINER, LilycoveCity_EventScript_MetWailmerTrainer
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FacePlayer
	waitmovement 0
	msgbox LilycoveCity_Text_GetLostMessingUpTraining, MSGBOX_DEFAULT
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_MET_WAILMER_TRAINER
	releaseall
	end

LilycoveCity_EventScript_MetWailmerTrainer:: @ 81E2DB0
	msgbox LilycoveCity_Text_WailmerLeapOutOfWater, MSGBOX_DEFAULT
	releaseall
	end

LilycoveCity_EventScript_AquaGrunt1:: @ 81E2DBA
	msgbox LilycoveCity_Text_MovedLootIntoHideoutToday, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt2:: @ 81E2DC3
	msgbox LilycoveCity_Text_ChanceToDoBigThings, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt3:: @ 81E2DCC
	msgbox LilycoveCity_Text_DontGoNearCaveInCove, MSGBOX_NPC
	end

LilycoveCity_EventScript_AquaGrunt4:: @ 81E2DD5
	msgbox LilycoveCity_Text_IfWorldBecomesOurs, MSGBOX_NPC
	end

LilycoveCity_EventScript_Rival:: @ 81E2DDE
	lock
	faceplayer
	checkplayergender
	compare VAR_RESULT, MALE
	goto_if_eq LilycoveCity_EventScript_May
	compare VAR_RESULT, FEMALE
	goto_if_eq LilycoveCity_EventScript_Brendan
	end

LilycoveCity_EventScript_May:: @ 81E2DF8
	playbgm MUS_ENCOUNTER_MAY, 1
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_MayAskToBattle
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_EventScript_DeclineMayBattle
	msgbox LilycoveCity_Text_MayWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleMayTreecko
	case 1, LilycoveCity_EventScript_BattleMayTorchic
	case 2, LilycoveCity_EventScript_BattleMayMudkip
	end

LilycoveCity_EventScript_MayAskToBattleAgain:: @ 81E2E48
	msgbox LilycoveCity_Text_MayBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_MayAskToBattle:: @ 81E2E51
	msgbox LilycoveCity_Text_MayShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineMayBattle:: @ 81E2E5A
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_MayNotRaisingPokemon, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_Brendan:: @ 81E2E6B
	playbgm MUS_ENCOUNTER_BRENDAN, 1
	call_if_set FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattleAgain
	call_if_unset FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE, LilycoveCity_EventScript_BrendanAskToBattle
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_EventScript_DeclineBrendanBattle
	msgbox LilycoveCity_Text_BrendanWontBeBeaten, MSGBOX_DEFAULT
	switch VAR_STARTER_MON
	case 0, LilycoveCity_EventScript_BattleBrendanTreecko
	case 1, LilycoveCity_EventScript_BattleBrendanTorchic
	case 2, LilycoveCity_EventScript_BattleBrendanMudkip
	end

LilycoveCity_EventScript_BrendanAskToBattleAgain:: @ 81E2EBB
	msgbox LilycoveCity_Text_BrendanBattleMe, MSGBOX_YESNO
	return

LilycoveCity_EventScript_BrendanAskToBattle:: @ 81E2EC4
	msgbox LilycoveCity_Text_BrendanShoppingLetsBattle, MSGBOX_YESNO
	return

LilycoveCity_EventScript_DeclineBrendanBattle:: @ 81E2ECD
	setflag FLAG_DECLINED_RIVAL_BATTLE_LILYCOVE
	msgbox LilycoveCity_Text_BrendanNoConfidence, MSGBOX_DEFAULT
	savebgm MUS_DUMMY
	fadedefaultbgm
	release
	end

LilycoveCity_EventScript_BattleMayTreecko:: @ 81E2EDE
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TREECKO, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayTorchic:: @ 81E2EEE
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_TORCHIC, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleMayMudkip:: @ 81E2EFE
	trainerbattle_no_intro TRAINER_MAY_LILYCOVE_MUDKIP, LilycoveCity_Text_MayDefeat
	goto LilycoveCity_EventScript_DefeatedMay
	end

LilycoveCity_EventScript_BattleBrendanTreecko:: @ 81E2F0E
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TREECKO, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanTorchic:: @ 81E2F1E
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_TORCHIC, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_BattleBrendanMudkip:: @ 81E2F2E
	trainerbattle_no_intro TRAINER_BRENDAN_LILYCOVE_MUDKIP, LilycoveCity_Text_BrendanDefeat
	goto LilycoveCity_EventScript_DefeatedBrendan
	end

LilycoveCity_EventScript_DefeatedMay:: @ 81E2F3E
	msgbox LilycoveCity_Text_MayGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_EventScript_MayCollectBadges
	compare VAR_RESULT, TRUE
	call_if_eq LilycoveCity_EventScript_MayPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_MAYS_HOUSE_2F_PICHU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_CheckFinalBadge:: @ 81E2F76
	goto_if_set FLAG_BADGE08_GET, LilycoveCity_EventScript_HasFinalBadge
	return

LilycoveCity_EventScript_HasFinalBadge:: @ 81E2F80
	setvar VAR_RESULT, TRUE
	return

LilycoveCity_EventScript_MayCollectBadges:: @ 81E2F86
	msgbox LilycoveCity_Text_MayYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayPokemonLeague:: @ 81E2F8F
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_MayBattleFrontier
	msgbox LilycoveCity_Text_MayYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_MayBattleFrontier:: @ 81E2FA1
	msgbox LilycoveCity_Text_MayYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DefeatedBrendan:: @ 81E2FAA
	msgbox LilycoveCity_Text_BrendanGoingBackToLittleroot, MSGBOX_DEFAULT
	setvar VAR_RESULT, FALSE
	call_if_set FLAG_BADGE06_GET, LilycoveCity_EventScript_CheckFinalBadge
	compare VAR_RESULT, FALSE
	call_if_eq LilycoveCity_EventScript_BrendanCollectBadges
	compare VAR_RESULT, TRUE
	call_if_eq LilycoveCity_EventScript_BrendanPokemonLeague
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_RIVAL_BEDROOM
	clearflag FLAG_HIDE_LITTLEROOT_TOWN_BRENDANS_HOUSE_2F_SWABLU_DOLL
	goto LilycoveCity_EventScript_RivalFlyAway
	end

LilycoveCity_EventScript_BrendanCollectBadges:: @ 81E2FE2
	msgbox LilycoveCity_Text_BrendanYouGoingToCollectBadges, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanPokemonLeague:: @ 81E2FEB
	goto_if_set FLAG_SYS_GAME_CLEAR, LilycoveCity_EventScript_BrendanBattleFrontier
	msgbox LilycoveCity_Text_BrendanYouGoingToPokemonLeague, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_BrendanBattleFrontier:: @ 81E2FFD
	msgbox LilycoveCity_Text_BrendanYouGoingToBattleFrontier, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_RivalFlyAway:: @ 81E3006
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	delay 50
	setfieldeffectargument 0, 1
	dofieldeffect FLDEFF_NPCFLY_OUT
	delay 15
	removeobject VAR_LAST_TALKED
	waitfieldeffect FLDEFF_NPCFLY_OUT
	savebgm MUS_DUMMY
	fadedefaultbgm
	setflag FLAG_MET_RIVAL_LILYCOVE
	release
	end

LilycoveCity_EventScript_SchoolKidM:: @ 81E302D
	lock
	faceplayer
	msgbox LilycoveCity_Text_DoYouKnowAboutBerryBlender, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq LilycoveCity_EventScript_KnowAboutBerryBlender
	compare VAR_RESULT, NO
	call_if_eq LilycoveCity_EventScript_DontKnowAboutBerryBlender
	release
	end

LilycoveCity_EventScript_KnowAboutBerryBlender:: @ 81E304F
	msgbox LilycoveCity_Text_FasterSpinBetterPokeblocks, MSGBOX_DEFAULT
	return

LilycoveCity_EventScript_DontKnowAboutBerryBlender:: @ 81E3058
	msgbox LilycoveCity_Text_ExplainBerryBlender, MSGBOX_DEFAULT
	return

LilycoveCity_Text_MayShoppingLetsBattle: @ 81E3061
	.string "봄이: 어라!?\n"
	.string "{PLAYER}도 쇼핑하러 왔어?\p"
	.string "난 봉제인형이랑 포스터\n"
	.string "잔뜩 사버렸어!\p"
	.string "물론 포켓몬도 잔뜩 잡았고\n"
	.string "제대로 키우고 있다고!\p"
	.string "나로서는 {PLAYER}{K_IGA}\n"
	.string "포켓몬을 제대로 키우고 있는지 걱정되네\p"
	.string "승부해 줄 테니까\n"
	.string "{PLAYER}의 포켓몬도 보여줘!$"
	// ハルカ『あら!?ｎ
	// §あ§おも おかいもの?ｐ
	// あたし ぬいぐるみとか ポスタ-ｎ
	// いっぱい かっちゃった!ｐ
	// もちろん ポケモン いっぱい つかまえたしｎ
	// ちゃんと そだてて いるんだから!ｐ
	// あたし としては §あ§おがｎ
	// ポケモン そだててるか しんぱい だなｐ
	// しょうぶ してあげるからｎ
	// §あ§おの ポケモン みせてよ!

LilycoveCity_Text_MayNotRaisingPokemon: @ 81E318D
	.string "봄이: 에- 어째서?\n"
	.string "{PLAYER} 포켓몬 안 키운 거야?\p"
	.string "그러면 트레이너로서\n"
	.string "아직 멀었네!$"
	// ハルカ『え- なんで?ｎ
	// §あ§お ポケモン そだててないの?ｐ
	// それじゃあ トレ-ナ-としてｎ
	// まだまだ ね!

LilycoveCity_Text_MayBattleMe: @ 81E31F5
	.string "봄이: 승부해 줄 테니까\n"
	.string "{PLAYER}의 포켓몬도 보여 줘!$"
	// ハルカ『しょうぶ してあげるからｎ
	// §あ§おの ポケモン みせてよ!

LilycoveCity_Text_MayWontBeBeaten: @ 81E3234
	.string "봄이: 내가 키운 포켓몬이\n"
	.string "{PLAYER}의 포켓몬에게\l"
	.string "질 리가 없지!$"
	// ハルカ『あたしの そだてた ポケモンがｎ
	// §あ§おの ポケモンにｌ
	// まけるわけ ないんだから!

LilycoveCity_Text_MayDefeat: @ 81E3275
	.string "...... ...... ...... ......\p"
	.string "103번 도로에서\n"
	.string "{PLAYER}{K_WAGWA} 승부했던 일이\l"
	.string "떠올랐어!\p"
	.string "그 승부 덕분에\n"
	.string "{PLAYER}{K_IGA}\l"
	.string "이만큼 강해진 거야!$"
	// …… …… ……ｐ
	// 103ばん どうろでｎ
	// §あ§おと しょうぶ したことｌ
	// おもいだしちゃった!ｐ
	// あの しょうぶが あったからｎ
	// §あ§お ここまでｌ
	// つよく なったんだね!

LilycoveCity_Text_MayGoingBackToLittleroot: @ 81E32FB
	.string "봄이: 나 슬슬\n"
	.string "미로마을로 돌아가려고\p"
	.string "다양한 포켓몬을 잡아서\n"
	.string "도감도 꽤 모았으니까\l"
	.string "아빠한테 보여 줄 거야!$"
	// ハルカ『あたし そろそろｎ
	// ミシロタウンに かえる つもりなのｐ
	// いろいろ ポケモン つかまえてｎ
	// ずかんも けっこう できてきたからｌ
	// おとうさんに みせるんだ!

LilycoveCity_Text_MayYouGoingToCollectBadges: @ 81E3398
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "이곳저곳의 체육관 배지를 모아서\n"
	.string "포켓몬리그에 도전할 거야?\p"
	.string "그럼 나는 {PLAYER}{K_IGA}\n"
	.string "배지 모으고 있는 사이에\l"
	.string "포켓몬 도감을 완성시켜 놔야지!\p"
	.string "그럼 안녕!$"
	// §あ§おは どうするの?ｐ
	// あちこちの ジムバッジを あつめてｎ
	// ポケモンリ-グ ちょうせん するの?ｐ
	// じゃあ あたし §あ§おがｎ
	// バッジを あつめている あいだにｌ
	// ポケモンずかんを かんせい させちゃお!ｐ
	// じゃね!

LilycoveCity_Text_MayYouGoingToPokemonLeague: @ 81E346D
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "포켓몬리그에 도전할 거야?\p"
	.string "아니면 포켓몬 도감\n"
	.string "완성시킬 거야?\p"
	.string "포켓몬 승부로는 졌지만\n"
	.string "도감은 내가\l"
	.string "먼저 완성시킬 거야!\p"
	.string "그럼 안녕!$"
	// §あ§おは どうするの?ｐ
	// ポケモンリ-グ ちょうせん するの?ｐ
	// それとも ポケモンずかんｌ
	// かんせい させるの?ｐ
	// ポケモンしょうぶ じゃ まけちゃったけどｎ
	// ずかんは あたしの ほうがｌ
	// さきに かんせい させるんだから!ｐ
	// じゃね!

LilycoveCity_Text_MayYouGoingToBattleFrontier: @ 81E353A
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "배틀프런티어에 도전할 거야?\n"
	.string "아니면 포켓몬 도감 완성시킬 거야?\p"
	.string "포켓몬 승부로는 졌지만\n"
	.string "도감은 내가\l"
	.string "먼저 완성시킬 거야!\p"
	.string "그럼 안녕!$"
	// {PLAYER}{KUN}は どうするの?ｐ
	// バトルフロンティアに ちょうせん する?ｎ
	// それとも ずかんを かんせい させる?ｐ
	// ポケモンしょうぶ じゃ まけちゃったけどｎ
	// ずかんは あたしの ほうがｌ
	// さきに かんせい させるんだから!ｐ
	// じゃね!

LilycoveCity_Text_BrendanShoppingLetsBattle: @ 81E3608
	.string "휘웅: 뭐야 {PLAYER}{K_I}구나\p"
	.string "난 아빠에게 부탁받은\n"
	.string "심부름을 하고 있었어\l"
	.string "딱히 봉제인형 같은 건 안 샀다고\p"
	.string "그것보다 오랜만에 만났으니까\p"
	.string "누가 포켓몬을\n"
	.string "더 잘 키워 왔는지\l"
	.string "승부해 볼래?$"
	// ユウキ『なんだ §あかｐ
	// オレ とうさんに たのまれたｎ
	// かいものを してたんだｌ
	// べつに ぬいぐるみ なんか かってないよｐ
	// それよりも ひさしぶりに あったんだｐ
	// どっちが うまくｎ
	// ポケモン そだてているかｌ
	// しょうぶ してやろうか?

LilycoveCity_Text_BrendanNoConfidence: @ 81E36BF
	.string "휘웅: 뭐야\n"
	.string "자신이 없구나$"
	// ユウキ『なんだよｎ
	// じしんが ないのかよ

LilycoveCity_Text_BrendanBattleMe: @ 81E36FA
	.string "휘웅: 누가 포켓몬을\n"
	.string "더 잘 키워 왔는지\l"
	.string "승부해 볼래?$"
	// ユウキ『どっちが うまくｎ
	// ポケモン そだてているかｌ
	// しょうぶ してやろうか?

LilycoveCity_Text_BrendanWontBeBeaten: @ 81E373C
	.string "휘웅: 뭐 내가\n"
	.string "{PLAYER}한테 질 리는 없지만 말야$"
	// ユウキ『まあ オレがｎ
	// §あに まけるわけ ないんだけど

LilycoveCity_Text_BrendanDefeat: @ 81E3777
	.string "흐으음...\n"
	.string "제법 잘 키우고 있구나\p"
	.string "조금 분하네\n"
	.string "트레이너로서는 내가\l"
	.string "선배였는데 말이지...$"
	// ふうん……ｎ
	// かなり そだててるんだなｐ
	// ちょっと くやしいなｎ
	// トレ-ナ-としては オレの ほうがｌ
	// センパイ だったのに……

LilycoveCity_Text_BrendanGoingBackToLittleroot: @ 81E37D7
	.string "휘웅: 나...\n"
	.string "미로마을로 돌아가려고\p"
	.string "아빠 도와주려고 만들고 있는\n"
	.string "포켓몬 도감도 꽤 완성돼서\l"
	.string "아빠한테 한번 보여 줘야 되거든$"
	// ユウキ『オレ……ｎ
	// ミシロタウンに もどるつもり なんだｐ
	// とうさんの てつだいで つくっているｎ
	// ポケモンずかんも けっこう できてきたしｌ
	// いちど とうさんに みせておかないと

LilycoveCity_Text_BrendanYouGoingToCollectBadges: @ 81E3876
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "역시 모든 체육관 배지를 모아서\n"
	.string "포켓몬리그에 도전할 거야?\p"
	.string "나도 그렇게 할까\p"
	.string "뭐든 상관없나\n"
	.string "어쨌든 힘내!$"
	// §あは どうする?ｐ
	// やっぱり ぜんぶの ジムバッジ あつめてｎ
	// ポケモンリ-グ ちょうせん するのか?ｐ
	// オレも そうしようかなｐ
	// まあ いいやｎ
	// とにかく がんばれよ!

LilycoveCity_Text_BrendanYouGoingToPokemonLeague: @ 81E390C
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "그 정도로 강하니까\n"
	.string "포켓몬리그에 도전할 거야?\p"
	.string "나도 좀 더\n"
	.string "포켓몬을 키우면 {PLAYER}보다도\l"
	.string "강해질 수 있긴 하겠다\p"
	.string "뭐든 상관없나\n"
	.string "어쨌든 힘내!$"
	// §あは どうする?ｐ
	// そんなに つよいんだからｎ
	// ポケモンリ-グに ちょうせん するのか?ｐ
	// オレだって もうちょっとｎ
	// ポケモン そだてれば §あよりもｌ
	// つよくなれる はずだからなｐ
	// まあ いいやｎ
	// とにかく がんばれよ!

LilycoveCity_Text_BrendanYouGoingToBattleFrontier: @ 81E39E3
	.string "{PLAYER}{K_EUNNEUN} 어떡할 거야?\p"
	.string "배틀프런티어에 도전할 거야?\n"
	.string "아니면 도감을 완성시킬 거야?\p"
	.string "나도 좀 더\n"
	.string "포켓몬을 키우면 {PLAYER}보다도\l"
	.string "강해질 수 있을 테니까\l"
	.string "배틀프런티어에 가볼까?\p"
	.string "뭐든 상관없나\n"
	.string "어쨌든 힘내!$"
	// §あは どうする?ｐ
	// バトルフロンティアに ちょうせん する?ｎ
	// それとも ずかんを かんせい させる?ｐ
	// そんなに つよいんだからｎ
	// バトルフロンティアに ちょうせん するか?ｐ
	// オレだって もうちょっとｎ
	// ポケモン そだてれば §あよりもｌ
	// つよくなれる はずだからなｌ
	// バトルフロンティアに いってみようかな?ｐ
	// まあ いいやｎ
	// とにかく がんばれよ!

LilycoveCity_Text_MovedLootIntoHideoutToday: @ 81E3B2C
	.string "후후후...\p"
	.string "오늘도 빼앗은 물건을\n"
	.string "아지트로 옮겼다...\p"
	.string "뭐 뭐야 넌!\n"
	.string "바 방금 건 혼잣말이야!$"
	// ふふふ……ｐ
	// きょうも うばった ブツをｎ
	// アジトに はこびこんだぞ……ｐ
	// なっ なんだ おまえ!ｎ
	// いっ いまのは ひとりごと だぞ!

LilycoveCity_Text_ChanceToDoBigThings: @ 81E3B95
	.string "리더께서 무슨 생각을 하시는지\n"
	.string "조무래기인 나는 모르겠지만\p"
	.string "아쿠아단에 있으면\n"
	.string "엄청난 일을 할 수 있을 거 같아!\p"
	.string "뭐 뭐야 넌!\n"
	.string "지 지금 건 혼잣말이야!$"
	// リ-ダ-が なに かんがえてるのかｎ
	// したっぱの オレには わからんがｐ
	// アクアだんに いるとｎ
	// すごいこと できそうだぜ!ｐ
	// なっ なんだ おまえ!ｎ
	// いっ いまのは ひとりごと だぞ!

LilycoveCity_Text_DontGoNearCaveInCove: @ 81E3C46
	.string "잠깐 너!\p"
	.string "저기 구석진 곳에 있는\n"
	.string "동굴에는 접근하지 마!\p"
	.string "왜냐고? 이유는 뭐든 상관없잖아!\n"
	.string "어른이 하는 말을 들어!!$"
	// おい おまえ!ｐ
	// いりえに あるｎ
	// どうくつには ちかづくなよ!ｐ
	// なぜって? りゆうは どうでも いいんだ!ｎ
	// おとなの いうこと きけよな!!
	
LilycoveCity_Text_IfWorldBecomesOurs: @ 81E3CBE
	.string "이 넓은 세상의 모든 것이\n"
	.string "우리 아쿠아단의 것이 되면\l"
	.string "포켓몬들도 행복해질 거야!$"
	// この ひろい せかい すべてがｎ
	// おれら アクアだんの ものに なったらｌ
	// ポケモンも しあわせに なれるはずだ!

LilycoveCity_Text_WailmerLeapOutOfWater: @ 81E3D1F
	.string "자! 고래왕자!\n"
	.string "거기 수면에서 점프하는 거야!$"
	// それっ! ホエルコ!ｎ
	// そこで すいめんから ジャンプするのだ!

LilycoveCity_Text_GetLostMessingUpTraining: @ 81E3D4A
	.string "...응? 뭐야 넌?\p"
	.string "트레이닝에 방해되니까\n"
	.string "저리로 가 줘!$"
	// ……ん? なんだ おまえは?ｐ
	// トレ-ニングの じゃまに なるからｎ
	// あっちに いっててくれ!

LilycoveCity_Text_ContestHallInTown: @ 81E3D9E
	.string "이 마을에 포켓몬 콘테스트\n"
	.string "회장이 있는 거구나!\p"
	.string "그렇다는 건 잘 키운 포켓몬이\n"
	.string "잔뜩 모여 있는 거구나!\p"
	.string "이 몸의 심장도 두근두근거리는구나!$"
	// この まちに ポケモンコンテストのｎ
	// かいじょうが あるんだな!ｐ
	// ということは よく そだった ポケモンがｎ
	// いっぱい あつまって いるんだな!ｐ
	// わしの ハ-トは わくわく なんだな!

LilycoveCity_Text_StrangeCaveInCove: @ 81E3E3C
	.string "마을 변두리에 있는 구석진 곳에\n"
	.string "이상한 동굴 있는 거 봤어?$"
	// まちの はずれの いりえにｎ
	// おかしな どうくつが あるの みた?

LilycoveCity_Text_GoingToMoveDeleterForHMs: @ 81E3E7D
	.string "나 포켓몬\n"
	.string "콘테스트를 위해서 새로운 기술을\l"
	.string "배우게 할 거야!\p"
	.string "그래서 기술잊기 할아버지한테 부탁해서\n"
	.string "비전기술을 잊게 할 거야!$"
	// あたしの ポケモンｎ
	// コンテストの ために あたらしい わざをｌ
	// おぼえさせる つもりなの!ｐ
	// だからね わざわすれ じいさんに たのんでｎ
	// ひでんわざを わすれさせて もらうのよ!

LilycoveCity_Text_ImFromKanto: @ 81E3F05
	.string "저는 관동에서 왔습니다!\p"
	.string "호연지방은 물과 초목이\n"
	.string "넘쳐흐르는 곳이네요!\p"
	.string "...응? 그렇다는 건?\p"
	.string "이 땅에서만 서식하는\n"
	.string "희귀한 포켓몬이 있을 수도?$"
	// ぼくは カント-から きました!ｐ
	// ホウエン ちほうは みずと みどりにｎ
	// あふれた うつくしい ところ ですね!ｐ
	// ……ん? ということは?ｐ
	// この とち だけに せいそくするｎ
	// めずらしい ポケモンが いるのかも?

LilycoveCity_Text_TeamAquaBeenTrainingWailmer: @ 81E3FAB
	.string "아쿠아단 녀석들이\n"
	.string "구석진 곳에서 고래왕자를\l"
	.string "트레이닝시키고 있더라고!\p"
	.string "이대로는 우리 선원들이\n"
	.string "바다에 나갈 수가 없어!$"
	// アクアだんの れんちゅうがｎ
	// いりえで ホエルコをｌ
	// トレ-ニング してるんだよ!ｐ
	// おいらたち ふなのりｎ
	// このままじゃ うみに でられないよ!

LilycoveCity_Text_SomeonePuntedTeamAquaOut: @ 81E4020
	.string "너 그거 알아?\p"
	.string "누군가가 아쿠아단을\n"
	.string "혼쭐을 내줬다고 하더라고!\p"
	.string "덕분에 고래왕자가 없어져서\n"
	.string "바다로 나갈 수 있게 됐어!$"
	// あんた しってるかい?ｐ
	// だれかが アクアだんをｎ
	// けちらしてくれた らしいんだ!ｐ
	// おかげで ホエルコ いなくなってｎ
	// うみに でられるように なったよ!

LilycoveCity_Text_SomeoneStoleMyPokemon: @ 81E40AD
	.string "해변의 숙소에서 파도 소리를\n"
	.string "들으면서 여유롭게 낮잠\l"
	.string "...을 자고 있었더니\p"
	.string "내 포켓몬을 도둑맞았어!\p"
	.string "범인은 누구지!?\n"
	.string "아쿠아단? 아쿠아단이야!?$"
	// うみべの やどで なみの おとをｎ
	// ききながら のんびり おひるねｌ
	// ……を していたらｐ
	// わたしの ポケモン とられちゃった!ｐ
	// はんにんは だれ-!?ｎ
	// アクアだん? アクアだん なの-!?

LilycoveCity_Text_MissingPokemonCameBack: @ 81E4145
	.string "없어진 내 포켓몬이\n"
	.string "어느샌가 돌아와 있었어!$"
	// いなくなってた わたしの ポケモンｎ
	// いつのまにか かえってきたの!

LilycoveCity_Text_ImArtDealer: @ 81E417B
	.string "전 화상입니다!\p"
	.string "아니 이름이 화상이라는 게 아니라\n"
	.string "가치 있는 그림을 사고팔고 하는\l"
	.string "직업의 이름이에요!\p"
	.string "이 마을의 미술관에 정말 멋진\n"
	.string "명화가 있다고 들었는데...$"
	// わたしは ガショウ です!ｐ
	// いや そういう なまえ なのではなくｎ
	// かちのある えを かったり うったりするｌ
	// しょくぎょうの なまえ なんです!ｐ
	// このまちの びじゅつかんに すばらしいｎ
	// めいが が あると きいたの ですが……

LilycoveCity_Text_SeaRemainsForeverYoung: @ 81E420B
	.string "우리가 쭈글쭈글해져도\n"
	.string "이 바다는 늘 싱그럽고\l"
	.string "생명의 반짝임으로 가득하구려\p"
	.string "으하하 으하하하하...$"
	// わしらが しわくちゃに なってもｎ
	// このうみは いつまでも わかわかしくｌ
	// いのちの かがやきに あふれとるｐ
	// ふほほ ふほほほほ……

LilycoveCity_Text_SixtyYearsAgoHusbandProposed: @ 81E4283
	.string "60년 전에 여기서 할아범이\n"
	.string "나한테 프러포즈했을 때부터\l"
	.string "이 바다는 변함없이 아름다워요\p"
	.string "오호호 오호호호호...$"
	// 60ねんまえ ここで おじいしゃんがｎ
	// わしに プロポ-ズ してくれた ときからｌ
	// このうみは うつくしいまま ですのじゃｐ
	// むふふ むふふふふ……

LilycoveCity_Text_TeamAquaRenovatedCavern: @ 81E42FC
	.string "여기 구석진 곳에 이상한\n"
	.string "동굴의 입구가 있지?\p"
	.string "예전에는 천연동굴이었는데\n"
	.string "아쿠아단이라는 녀석들이\l"
	.string "저렇게 개조해 버렸지 뭔가!\p"
	.string "“자연을 사랑하는 아쿠아단!”\n"
	.string "...이라고 하지만\p"
	.string "말과 행동이 다르지 않은가!$"
	// この いりえの ところに おかしなｎ
	// どうくつの いりぐちが ある じゃろう?ｐ
	// いぜんは てんねんの どうくつ だったがｎ
	// アクアだん とかいう れんちゅうがｌ
	// かいぞうして あんなふうに したんじゃ!ｐ
	// 「しぜんを あいする アクアだん!」ｎ
	// ……と いっておるがｐ
	// いうことと やることが ちがっとる!

LilycoveCity_Text_TeamAquaLotGoneForGood: @ 81E43FF
	.string "구석진 곳에 있는 동굴...\n"
	.string "어느샌가 텅 비어 버렸다네\p"
	.string "아쿠아단 녀석들\n"
	.string "어딘가로 가버린 것 같구먼$"
	// いりえに あった どうくつ……ｎ
	// いつのまにやら カラッポに なっておるｐ
	// アクアだんの れんちゅうｎ
	// どこかへ いって しまったらしい のう

LilycoveCity_Text_CitySign: @ 81E448B
	.string "여기는 해안시티\n"
	.string "육지가 끝나고 바다가 시작되는 곳$"
	// ここは ミナモ シティｎ
	// りくちの さいはて うみの はじまり

LilycoveCity_Text_ContestHallSign: @ 81E44C3
	.string "포켓몬 콘테스트 회장\n"
	.string "모여라! 포켓몬 트레이너$"
	// ポケモンコンテスト かいじょうｎ
	// あつまれ! ポケモン トレ-ナ-

LilycoveCity_Text_MotelSign: @ 81E44FC
	.string "“안해민박”\n"
	.string "해안의 안해로 기억해 주세요$"
	// 「みんしゅく モナミ」ｎ
	// ミナモのモナミ と おぼえて ください

LilycoveCity_Text_MuseumSign: @ 81E4534
	.string "“해안 미술관”\n"
	.string "포켓몬 명화전 개최 중!$"
	// 「ミナモ びじゅつかん」ｎ
	// ポケモン めいがてん かいさい ちゅう!

LilycoveCity_Text_MuseumSignPlayersExhibit: @ 81E4571
	.string "“해안 미술관”\p"
	.string "{PLAYER}의 포켓몬 컬렉션\n"
	.string "개최 중!$"
	// 「ミナモ びじゅつかん」ｐ
	// §あの ポケモン コレクションｎ
	// かいさい ちゅう!

LilycoveCity_Text_HarborSignUnderConstruction: @ 81E45A7
	.string "“해안시티 배 타는 곳”\p"
	.string "연락선 타이드립호는\n"
	.string "현재 잿빛도시에서 건조 중!\p"
	.string "조금만 더 기다려주세요!$"
	// 「ミナモ シティ ふねのりば」ｐ
	// れんらくせん タイドリップごう はｎ
	// カイナシティにて けんぞう ちゅう!ｐ
	// もう しばらく おまちください!

LilycoveCity_Text_HarborSign: @ 81E4624
	.string "“해안시티 배 타는 곳”\p"
	.string "연락선 타이드립호로\n"
	.string "배 여행을 만끽해 주세요!$"
	// 「ミナモ シティ ふねのりば」ｐ
	// れんらくせん タイドリップごうでｎ
	// ふねの たびを おたのしみ ください!

LilycoveCity_Text_TrainerFanClubSign: @ 81E466E
	.string "“포켓몬 트레이너 팬클럽”\p"
	.string "간판에는 여러 트레이너들의\n"
	.string "이름이 낙서처럼 써져 있다...$"
	// 「ポケモン トレ-ナ- ファンクラブ」ｐ
	// かんばんに いろんな トレ-ナ-のｎ
	// なまえが らくがき されている……

LilycoveCity_Text_DepartmentStoreSign: @ 81E46BE
	.string "“해안백화점”\p"
	.string "굿즈 한가득! 설렘 한가득!\n"
	.string "무언가를 발견할 수 있는 멋진 장소$"
	// 「ミナモ デパ-ト」ｐ
	// グッズ いっぱい! ドキドキ いっぱい!ｎ
	// なにかが みつかる すてきな ところ

LilycoveCity_Text_MoveDeletersHouseSign: @ 81E473D
	.string "“기술잊기 할아버지의 집”\n"
	.string "포켓몬 기술을 잊게 합니다$"
	// 「わざわすれ じいさんの いえ」ｎ
	// ポケモンの わざ わすれさせます

LilycoveCity_Text_DoYouKnowAboutBerryBlender: @ 81E4774
	.string "나무열매블렌더라고 하는\n"
	.string "머신을 알고 있어?$"
	// きのみブレンダ- っていうｎ
	// マシンを しってるかい?

LilycoveCity_Text_FasterSpinBetterPokeblocks: @ 81E47A1
	.string "다 같이 고속으로 마구 돌리는 거야\p"
	.string "엄-청 돌리면\n"
	.string "엄-청 좋은 포켓몬스넥이 나오나 봐!$"
	// みんなで こうそくで まわし まくるんだｐ
	// すっげ- はやいとｎ
	// すっげ- いいポロックが できるらしいぜ!

LilycoveCity_Text_ExplainBerryBlender: @ 81E4824
	.string "포켓몬스넥이라는 과자를 만들 수 있대\p"
	.string "좋은 포켓몬스넥을 먹으면 포켓몬의\n"
	.string "컨디션도 쑥쑥 업해!$"
	// ポロックっていう おかしが できるんだぜｐ
	// いいポロックを つくると ポケモンのｎ
	// コンディションも ぐ-んと アップさ!

LilycoveCity_Text_HeardTowerCalledSkyPillar: @ 81E48A5
	.string "있잖아 어딘가 수로에\n"
	.string "하늘기둥이라고 하는 탑이\l"
	.string "있는 것 같아$"
	// あのな どこかの すいどうにｎ
	// そらのはしら とかいう とうがｌ
	// たってる らしいぜ

LilycoveCity_Text_SawTallTowerOnRoute131: @ 81E4902
	.string "나 말야 131번 수로 근처에서\n"
	.string "엄청 큰 탑을 봤는데\l"
	.string "설마 그거...?$"
	// オレな 131ばん すいどうの あたりでｎ
	// たか-い とうを みたんだけどｌ
	// もしかして それって……?

LilycoveCity_Text_JustArrivedAndSawRarePokemon: @ 81E494D
	.string "우리는 신혼여행으로\n"
	.string "이 마을에 온 지 얼마 안됐는데\p"
	.string "드래곤타입 포켓몬이\n"
	.string "하늘을 날고 있는 걸 봤어!\p"
	.string "호연지방에는\n"
	.string "그런 멋있는 포켓몬이\l"
	.string "서식하고 있는 거야?$"
	// ぼくら しんこん りょこうでｎ
	// このまちに きたばかり なんだけどｐ
	// ドラゴンタイプの ポケモンがｎ
	// そらを とんで いくのを みたんだよ!ｐ
	// ホウエン ちほうにはｎ
	// あんな かっこいい ポケモンがｌ
	// せいそく してるのかい?

LilycoveCity_Text_HoneymoonVowToSeeRarePokemon: @ 81E49F4
	.string "우리의 신혼여행은\n"
	.string "각지의 희귀한 포켓몬을\l"
	.string "가능한 많이 보는 거예요\p"
	.string "이 마을에 도착했더니\n"
	.string "갑자기 희귀한 포켓몬이 보여서\l"
	.string "엄청 행복했어요!$"
	// わたしたちの しんこん りょこうはｎ
	// かくちの めずらしい ポケモンをｌ
	// できるだけ たくさん みること なんですｐ
	// この まちに とうちゃく したらｎ
	// いきなり めずらしい ポケモンが みられてｌ
	// とても ハッピ- だわ!
