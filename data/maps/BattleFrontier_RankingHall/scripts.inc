BattleFrontier_RankingHall_MapScripts:: @ 825E4A9
	.byte 0

BattleFrontier_RankingHall_EventScript_TowerSinglesRecords:: @ 825E4AA
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_TOWER_SINGLES
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_TowerDoublesRecords:: @ 825E4B6
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_TOWER_DOUBLES
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_TowerMultisRecords:: @ 825E4C2
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_TOWER_MULTIS
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_TowerLinkRecords:: @ 825E4CE
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_TOWER_LINK
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_ArenaRecords:: @ 825E4DA
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_ARENA
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_PalaceRecords:: @ 825E4E6
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_PALACE
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_FactoryRecords:: @ 825E4F2
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_FACTORY
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_DomeRecords:: @ 825E4FE
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_DOME
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_PikeRecords:: @ 825E50A
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_PIKE
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_PyramidRecords:: @ 825E516
	lockall
	setvar VAR_0x8005, RANKING_HALL_BATTLE_PYRAMID
	goto BattleFrontier_RankingHall_EventScript_ShowRecords
	end

BattleFrontier_RankingHall_EventScript_ShowRecords:: @ 825E522
	special ShowRankingHallRecordsWindow
	waitbuttonpress
	special ScrollRankingHallRecordsWindow
	waitbuttonpress
	special RemoveRecordsWindow
	releaseall
	end

BattleFrontier_RankingHall_EventScript_Attendant:: @ 825E52F
	msgbox BattleFrontier_RankingHall_Text_ExplainRankingHall, MSGBOX_NPC
	end

BattleFrontier_RankingHall_EventScript_DomePikeFactoryRecordsSign:: @ 825E538
	msgbox BattleFrontier_RankingHall_Text_DomePikeFactoryRecords, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_PalaceArenaPyramidRecordsSIgn:: @ 825E541
	msgbox BattleFrontier_RankingHall_Text_PalaceArenaPyramidRecords, MSGBOX_SIGN
	end

BattleFrontier_RankingHall_EventScript_NinjaBoy:: @ 825E54A
	lock
	faceplayer
	msgbox BattleFrontier_RankingHall_Text_IsYourNameOnThisList, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BattleFrontier_RankingHall_EventScript_NinjaBoyNameOnList
	msgbox BattleFrontier_RankingHall_Text_WorkHarderIfYouSawFriendsName, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_NinjaBoyNameOnList:: @ 825E569
	msgbox BattleFrontier_RankingHall_Text_WowThatsSuper, MSGBOX_DEFAULT
	release
	end

BattleFrontier_RankingHall_EventScript_Boy:: @ 825E573
	msgbox BattleFrontier_RankingHall_Text_MyNamesNotUpThere, MSGBOX_NPC
	end

BattleFrontier_RankingHall_Text_ExplainRankingHall: @ 825E57C
	.string "여기는 랭킹홀\p"
	.string "배틀프런티어에 도전한\n"
	.string "트레이너들의 위대한 기록을\l"
	.string "기리는 장소입니다$"
	// ここは ランキングホ-ルｐ
	// バトルフロンティアに ちょうせん したｎ
	// トレ-ナ-たちの いだいな きろくをｌ
	// たたえる ばしょ です

BattleFrontier_RankingHall_Text_DomePikeFactoryRecords: @ 825E5F9
	.string "배틀돔 배틀튜브\n"
	.string "배틀팩토리의 기록은 이쪽$"
	// バトルド-ム バトルチュ-ブｎ
	// バトルファクトリ- の きろくは こちら

BattleFrontier_RankingHall_Text_PalaceArenaPyramidRecords: @ 825E62E
	.string "배틀팰리스 배틀아레나\n"
	.string "배틀피라미드의 기록은 이쪽$"
	// バトルパレス バトルアリ-ナｎ
	// バトルピラミッド の きろくは こちら

BattleFrontier_RankingHall_Text_IsYourNameOnThisList: @ 825E666
	.string "저기 네 이름\n"
	.string "여기에 적혀 있어?$"
	// ねえ きみの なまえｎ
	// ここに のってるの?

BattleFrontier_RankingHall_Text_WowThatsSuper: @ 825E685
	.string "헤- 굉장하다!\n"
	.string "나도 열심히 해야지!$"
	// へ- すごいね!ｎ
	// ぼくも がんばらなきゃ!

BattleFrontier_RankingHall_Text_WorkHarderIfYouSawFriendsName: @ 825E6B6
	.string "그렇구나...\p"
	.string "하지만 친구의 이름을 여기서 보면\n"
	.string "더 열심히 하고 싶어지지!$"
	// そうなんだ…ｐ
	// でも ともだちの なまえを ここで みるとｎ
	// がんばろうって きもちに なるよね!

BattleFrontier_RankingHall_Text_MyNamesNotUpThere: @ 825E715
	.string "음 내 이름\n"
	.string "적혀 있지 않네...\p"
	.string "아직 어디에도 도전하지 않았으니까\n"
	.string "당연한 건가...$"
	// う-ん ぼくの なまえｎ
	// のって ないなあ……ｐ
	// まだ どこにも ちょうせん してないからｎ
	// あたりまえか……

