.set LOCALID_SUDOWOODO, 14

BattleFrontier_OutsideEast_MapScripts:: @ 8242C04
	map_script MAP_SCRIPT_ON_RESUME, BattleFrontier_OutsideEast_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, BattleFrontier_OutsideEast_OnTransition
	.byte 0

BattleFrontier_OutsideEast_OnResume: @ 8242C0F
	call_if_set FLAG_SYS_CTRL_OBJ_DELETE, BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_TryRemoveSudowoodo:: @ 8242C19
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_CAUGHT
	goto_if_ne Common_EventScript_NopReturn
	removeobject VAR_LAST_TALKED
	return

BattleFrontier_OutsideEast_OnTransition: @ 8242C2D
	setvar VAR_BRAVO_TRAINER_BATTLE_TOWER_ON, 0
	setflag FLAG_HIDE_BATTLE_TOWER_REPORTER
	call_if_unset FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_ShowSudowoodo
	end

BattleFrontier_OutsideEast_EventScript_ShowSudowoodo:: @ 8242C3F
	clearflag FLAG_HIDE_BATTLE_FRONTIER_SUDOWOODO
	return

BattleFrontier_OutsideEast_EventScript_BattleTowerSign:: @ 8242C43
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePalaceSign:: @ 8242C4C
	msgbox BattleFrontier_OutsideEast_Text_BattlePalaceSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattleArenaSign:: @ 8242C55
	msgbox BattleFrontier_OutsideEast_Text_BattleArenaSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_BattlePyramidSign:: @ 8242C5E
	msgbox BattleFrontier_OutsideEast_Text_BattlePyramidSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_NinjaBoy:: @ 8242C67
	msgbox BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man1:: @ 8242C70
	msgbox BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Hiker:: @ 8242C79
	msgbox BattleFrontier_OutsideEast_Text_PyramidTooHarsh, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_HexManiac:: @ 8242C82
	msgbox BattleFrontier_OutsideEast_Text_ThriveInDarkness, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt1:: @ 8242C8B
	msgbox BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Cook:: @ 8242C94
	lock
	msgbox BattleFrontier_OutsideEast_Text_BelieveInYouBuddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Zigzagoon:: @ 8242C9F
	lock
	faceplayer
	waitse
	playmoncry SPECIES_ZIGZAGOON, 0
	msgbox BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant, MSGBOX_DEFAULT
	waitmoncry
	release
	end

BattleFrontier_OutsideEast_EventScript_RichBoy:: @ 8242CB2
	msgbox BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_ExpertF:: @ 8242CBB
	msgbox BattleFrontier_OutsideEast_Text_OnceBeatGymLeader, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_TriathleteF:: @ 8242CC4
	msgbox BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Twin:: @ 8242CCD
	msgbox BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man2:: @ 8242CD6
	lock
	msgbox BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_TriathleteM:: @ 8242CE1
	msgbox BattleFrontier_OutsideEast_Text_DidScottBringYouHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Sudowoodo:: @ 8242CEA
	lock
	faceplayer
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	release
	end

BattleFrontier_OutsideEast_EventScript_WaterSudowoodo:: @ 8242CFC
	lock
	faceplayer
	special DoWateringBerryTreeAnim
	waitstate
	waitse
	playse SE_SUDOWOODO_SHAKE
	applymovement LOCALID_SUDOWOODO, BattleFrontier_OutsideEast_Movement_SudowoodoShake
	waitmovement 0
	msgbox gText_Sudowoodo_Attacked, MSGBOX_DEFAULT
	closemessage
	waitse
	playmoncry SPECIES_SUDOWOODO, 2
	delay 40
	waitmoncry
	setvar VAR_LAST_TALKED, LOCALID_SUDOWOODO
	setwildbattle SPECIES_SUDOWOODO, 40, ITEM_NONE
	setflag FLAG_SYS_CTRL_OBJ_DELETE
	dowildbattle
	clearflag FLAG_SYS_CTRL_OBJ_DELETE
	specialvar VAR_RESULT, GetBattleOutcome
	compare VAR_RESULT, B_OUTCOME_WON
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	compare VAR_RESULT, B_OUTCOME_RAN
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	compare VAR_RESULT, B_OUTCOME_PLAYER_TELEPORTED
	goto_if_eq BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo
	setflag FLAG_DEFEATED_SUDOWOODO
	release
	end

BattleFrontier_OutsideEast_EventScript_DefeatedSudowoodo:: @ 8242D60
	setflag FLAG_DEFEATED_SUDOWOODO
	goto Common_EventScript_RemoveStaticPokemon
	end

BattleFrontier_OutsideEast_Movement_SudowoodoShake: @ 8242D69
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	delay_8
	face_right
	delay_8
	face_down
	delay_8
	face_left
	delay_8
	face_down
	step_end

BattleFrontier_OutsideEast_EventScript_Maniac1:: @ 8242D79
	msgbox BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Girl:: @ 8242D82
	msgbox BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_PsychicM:: @ 8242D8B
	msgbox BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Man3:: @ 8242D94
	msgbox BattleFrontier_OutsideEast_Text_GotWipedOut, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman1:: @ 8242D9D
	msgbox BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Woman2:: @ 8242DA6
	msgbox BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_BlackBelt2:: @ 8242DAF
	msgbox BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_Maniac2:: @ 8242DB8
	lock
	msgbox BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Woman3:: @ 8242DC3
	lock
	msgbox BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_RankingHallSign:: @ 8242DCE
	msgbox BattleFrontier_OutsideEast_Text_RankingHallSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_ExchangeCornerSign:: @ 8242DD7
	msgbox BattleFrontier_OutsideEast_Text_ExchangeCornerSign, MSGBOX_SIGN
	end

BattleFrontier_OutsideEast_EventScript_Gentleman:: @ 8242DE0
	msgbox BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_EventScript_OldWoman:: @ 8242DE9
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_SUDOWOODO, BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone
	msgbox BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_OldWomanSudowoodoGone:: @ 8242DFE
	msgbox BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere, MSGBOX_DEFAULT
	release
	end

BattleFrontier_OutsideEast_EventScript_Camper:: @ 8242E08
	msgbox BattleFrontier_OutsideEast_Text_StickyMonWithLongTail, MSGBOX_NPC
	end

BattleFrontier_OutsideEast_Text_BattleTowerSign: @ 8242E11
	.string "여기는 배틀타워!\n"
	.string "이겨나가라! 최강의 트레이너!$"
	// ここは バトルタワ-!ｎ
	// かちぬけ! さいきょう トレ-ナ-!

BattleFrontier_OutsideEast_Text_BattlePalaceSign: @ 8242E58
	.string "여기는 배틀팰리스!\n"
	.string "지켜봐라! 포켓몬 배틀!$"
	// ここは バトルパレス!ｎ
	// みまもれ! ポケモンバトル!

BattleFrontier_OutsideEast_Text_BattleArenaSign: @ 8242E96
	.string "여기는 배틀아레나!\n"
	.string "모아라! 최강 팀!$"
	// ここは バトルアリ-ナ!ｎ
	// つどえ! さいきょう チ-ム!

BattleFrontier_OutsideEast_Text_BattlePyramidSign: @ 8242ECF
	.string "여기는 배틀피라미드!\n"
	.string "나아가라! 배틀어드벤처!$"
	// ここは バトルピラミッド!ｎ
	// すすめ! バトルアドベンチャ-!

BattleFrontier_OutsideEast_Text_RankingHallSign: @ 8242F0D
	.string "배틀프런티어 랭킹홀\n"
	.string "새겨라! 최고의 기록!$"
	// バトルフロンティア ランキングホ-ルｎ
	// きざめ! さいこうの きろく!

BattleFrontier_OutsideEast_Text_ExchangeCornerSign: @ 8242F4A
	.string "배틀포인트 교환서비스 코너\n"
	.string "교환하라! 너의 배틀포인트!$"
	// バトルポイント ひきかえサ-ビス コ-ナ-ｎ
	// ひきかえろ! キミの バトルポイント!

BattleFrontier_OutsideEast_Text_BattleTowerFeelsSpecial: @ 8242F8C
	.string "우와-! 크다!\p"
	.string "역시 배틀타워는\n"
	.string "특별하다는 느낌이 들어$"
	// うっひゃ- でかい!ｐ
	// やはり バトルタワ-はｎ
	// とくべつ って かんじが するな

BattleFrontier_OutsideEast_Text_ConquerLeagueAndFrontier: @ 8242FDC
	.string "내 야망은\n"
	.string "배틀프런티어 그리고 포켓몬리그\l"
	.string "모든 것의 정점에 서는 거야!\p"
	.string "그리고 만약 그게 이뤄진다면!\p"
	.string "여 옆집의 미미씨에게\n"
	.string "친구다 되어달라고 할 거야!$"
	// わたしの やぼうはｎ
	// バトルフロンティア そして ポケモンリ-グｌ
	// すべての ちょうてんに たつ ことだ!ｐ
	// そして もし それが かなったら!ｐ
	// とっ となりの いえの ミミちゃんにｎ
	// おともだちに なって くださいって いうぞ!

BattleFrontier_OutsideEast_Text_PyramidTooHarsh: @ 824308C
	.string "배틀피라미드는 너무 어려워서\n"
	.string "도저히 정상까지 갈 수가 없어!\p"
	.string "어쩔 수 없지 차라리\n"
	.string "바깥쪽을 기어서 올라갈까$"
	// バトルピラミッドは むずかし すぎてｎ
	// どうしても ちょうじょうに まで いけん!ｐ
	// しかたが ないから いっそのことｎ
	// そとがわを のぼって やろうかしら

BattleFrontier_OutsideEast_Text_ThriveInDarkness: @ 8243106
	.string "나는 어둠 속이 좋아...\n"
	.string "그래... 내게 어울리는 건...\l"
	.string "역시 이 배틀피라미드...\p"
	.string "있잖아... 너도 어둠 속을\n"
	.string "열심히 헤매지 않을래...?$"
	// くらやみが だいすきな わたし……ｎ
	// そう…… わたしに ふさわしい のは……ｌ
	// やはり この バトルピラミッド……ｐ
	// ネ…… あなたも くらやみの なかをｎ
	// ひっしに さまよって みない……?

BattleFrontier_OutsideEast_Text_PutTogetherUltimateTeam: @ 82431A5
	.string "일주일 동안 자지 않고 생각한\n"
	.string "나의 최강 팀...\p"
	.string "질 것 같지가 않아!\n"
	.string "좋-아 아레나로 가자-!$"
	// いっしゅうかん ねないで かんがえたｎ
	// オレの さいきょう チ-ム……ｌ
	// まけるきが しねえぜ!ｐ
	// ぃよ-し アリ-ナに なぐりこみだ-!

BattleFrontier_OutsideEast_Text_DidScottBringYouHere: @ 8243230
	.string "당신도 금작화씨가\n"
	.string "데려온 거야?\l"
	.string "그 사람 뭐하는 사람일까\p"
	.string "강한 트레이너를 보는 눈은\n"
	.string "확실하다고 하지만...\l"
	.string "스스로 배틀하는 모습은\l"
	.string "한 번도 본 적이 없단 말이지$"
	// あんたも エニシダさんにｎ
	// つれて こられたの?ｌ
	// あのひと なんなんだろうねｐ
	// つよい トレ-ナ-を みぬく めはｎ
	// たしからしい けど……ｌ
	// ほんにんが たたかって いる ところはｌ
	// いちども みたことが ないんだよなあ

BattleFrontier_OutsideEast_Text_BelieveInYouBuddy: @ 82432DD
	.string "지그야! 믿고 있어!\p"
	.string "이기면 지그가 좋아하는 간식\n"
	.string "얼-마든지 만들어 줄 테니까!$"
	// ジグちゃん! しんじてるからね!ｐ
	// かったら ジグちゃんの すきな おやつｎ
	// な-んでも つくって あげるからね!

BattleFrontier_OutsideEast_Text_ZigzagoonLooksVacant: @ 824334B
	.string "지그제구리는 멍하니 있다...$"
	// ジグザグマは ぼんやり してる……

BattleFrontier_OutsideEast_Text_PeopleCallMeBusybody: @ 8243363
	.string "나 나는 참견쟁이다!\n"
	.string "거기 너! 모자가 어긋나 있다고!\l"
	.string "어이쿠 바닥에 쓰레기가 있군!\l"
	.string "이런! 곧 밥 먹을 시간이다!\p"
	.string "... ...배틀팰리스에서\n"
	.string "승부를 그저 지켜보는 걸\l"
	.string "내가 할 수 있을까...?$"
	// お おれは でしゃばり だ!ｎ
	// オイあんた! ぼうしが ずれてるぜ!ｌ
	// おっと じめんに ゴミが おちてる!ｌ
	// ああっと! もうすぐ ごはんだぜ!ｐ
	// …… ……バトルパレスでｎ
	// しょうぶを ただ みまもる だけなんてｌ
	// おれに できるだろ-か……?

BattleFrontier_OutsideEast_Text_OnceBeatGymLeader: @ 8243425
	.string "이래 보여도 왕년엔\n"
	.string "체육관 관장에게 이긴 적이 있단다\p"
	.string "이제 다시 왕년을 살아봐야겠어$"
	// こう みえても むかしはｎ
	// ジムリ-ダ-に かった ことも あるのよｐ
	// もう ひとはな さかせて みようかしらねぇ

BattleFrontier_OutsideEast_Text_FastOnBikeAndBattles: @ 82434A0
	.string "자전거도 잘 타지만\n"
	.string "포켓몬도 자신 있어!\p"
	.string "눈 깜짝할 사이에 이겨버릴 거야!$"
	// じてんしゃも はやいけどｎ
	// ポケモン だって じしんあるわ!ｌ
	// めにも とまらぬ はやさで かっちゃうわよ!

BattleFrontier_OutsideEast_Text_BetterThanDaddyAtPokemon: @ 8243504
	.string "내가 아빠보다\n"
	.string "포켓몬이 더 강해!$"
	// わたしのほうがねえ- パパよりｎ
	// ポケモン つよいんだよ!

BattleFrontier_OutsideEast_Text_GoRackUpSomeWinsForDaddy: @ 8243529
	.string "딸!\n"
	.string "힘내서 이기고 오렴!\l"
	.string "너는 엄마를 닮아서 강하니까!$"
	// むすめよ!ｎ
	// がんばって かちぬいて こい!ｌ
	// おまえは ママ そっくり だから つよいぞ!

BattleFrontier_OutsideEast_Text_HeardPrettyGirlAtBattleArena: @ 8243598
	.string "배틀아레나에 엄청나게\n"
	.string "예쁜 애가 있다고 들어서\l"
	.string "여기까지 힘내서 왔는데-에!\p"
	.string "땀 냄새나고 숨막히는\n"
	.string "격투가밖에 없었어!$"
	// バトルアリ-ナに めちゃくちゃｎ
	// ぷりてぃ-な こが いるって きいたからｌ
	// ここまで がんばって きたのに-っ!ｐ
	// あせくさ-くて あつくるし-いｎ
	// かくとうか ばっかり だったよ!

BattleFrontier_OutsideEast_Text_SometimesImportantOldManInThere: @ 8243668
	.string "두근거리네- 이 건물에\n"
	.string "엄청 강해 보이는 포켓몬을 데리고\l"
	.string "엄청 대단해 보이지만\l"
	.string "꽤 상냥해 보이는\l"
	.string "할아버지가 들어갔어!$"
	// ときどきね- ここの たてものにｎ
	// すっごく つよそ-な ポケモン つれてｌ
	// すっごく えらそ- だけどｌ
	// けっこ- やさしそ-なｌ
	// じ-ちゃんが はいってくのよ!

BattleFrontier_OutsideEast_Text_LegendOfBattlePyramid: @ 82436F2
	.string "넌 알고 있어!?\n"
	.string "배틀피라미드의 전설을!!\p"
	.string "넘치는 용기를 가진 트레이너\n"
	.string "금자탑의 정상을 향할 때\l"
	.string "사나이 중의 사나이가 나타난다\p"
	.string "...어때? 모르겠지-!\n"
	.string "그럴 게 이거 방금 내가\l"
	.string "생각해 낸 거니까!\p"
	.string "뭐? 무슨 의미냐고?\n"
	.string "크크!! 그건 알려줄 수 없지!$"
	// きみは しって いるか!?ｎ
	// バトルピラミッドの でんせつを!!ｐ
	// みなぎる ゆうきを もつ トレ-ナ-ｎ
	// きんじとうの いただきを めざすときｌ
	// おとこの なかの おとこ あらわれるｐ
	// ……どうだ? しらないだろ-!ｎ
	// だって これ さっき おれがｌ
	// かんがえたんだ もんな!ｐ
	// なに? どういう いみ かって?ｎ
	// チッチッ!! それは おしえられないな!

BattleFrontier_OutsideEast_Text_GotWipedOut: @ 8243809
	.string "젠장!\p"
	.string "지금까지 누구에게 한 번도\n"
	.string "진 적이 없는 내가\l"
	.string "손도 발도 못 쓰고\l"
	.string "게다가 재능이 없다고!?\p"
	.string "젠장! 젠장! 젠장!$"
	// くそ-っ!ｐ
	// いままで だれにも いちどもｎ
	// まけたこと なかった この ぼくがｌ
	// ても あしも でない うえにｌ
	// さいのうが ない だと!?ｐ
	// くそ-っ! くそ-っ! くそ-っ!

BattleFrontier_OutsideEast_Text_ToughTrainerInBattleTower: @ 8243895
	.string "이 사람 배틀타워에\n"
	.string "도전하고 있을 때\l"
	.string "엄청나게 강한 트레이너하고\l"
	.string "배틀했었나 봐요...\p"
	.string "당신도 배틀타워에\n"
	.string "도전할 때는 조심하세요$"
	// このひと バトルタワ-にｎ
	// ちょうせん している ときにｌ
	// おそろしく つよい トレ-ナ-とｌ
	// たたかった みたい なの……ｐ
	// あなたも バトルタワ-にｎ
	// ちょうせんする ときは ちゅういして……

BattleFrontier_OutsideEast_Text_EnoughBattlePointsForDoll: @ 8243943
	.string "자! 배틀포인트도 모았고!\n"
	.string "또 거대한 봉제인형이라도\l"
	.string "모으러 가볼까!$"
	// さて! バトルポイントも たまったし!ｎ
	// また おおきな ぬいぐるみ でもｌ
	// もらいに いこ-っと!

BattleFrontier_OutsideEast_Text_LikeToHaveNameRecordedHere: @ 82439A0
	.string "우하하하-앗!\n"
	.string "여기가 랭킹홀이군요-!\p"
	.string "저도 여기에 이름을 남길 만한\n"
	.string "최고의 슈퍼 챔피언이\l"
	.string "빨리 되고 싶네요!$"
	// おほほほ-いっ!ｎ
	// ここが ランキングホ-ル っスね-!ｐ
	// わしも ここに なを のこす ようなｎ
	// えいこうの ス-パ- チャンプにｌ
	// はやく なりたい っスよ!

BattleFrontier_OutsideEast_Text_CanDoAnythingWithYou: @ 8243A2B
	.string "네가 옆에 있어준다면\n"
	.string "난 뭐든지 할 수 있어...$"
	// もし きみが そばに いてくれたらｎ
	// ぼくは なんだって できるのさ……

BattleFrontier_OutsideEast_Text_PowerOfOurLoveWillOvercome: @ 8243A53
	.string "아앙 역시 달링은 멋 지 다 니 까!\p"
	.string "...... ...아-!\n"
	.string "정말-! 나 이제 못 참겠어!!\p"
	.string "지금 당장 둘이서 멀티배틀룸으로\n"
	.string "돌격하자고-!!\p"
	.string "배틀살롱에 같이 선다면\n"
	.string "둘의 러브파워로\l"
	.string "이놈이든 저놈이든 한 방이야!\l"
	.string "빨리 가자- 달링!!$"
	// ぁあん やっぱ ダ-リンは ス テ キ!ｐ
	// …… ……あ-!ｎ
	// も-! わたし たまんないっ!!ｐ
	// いますぐ ふたりで マルチ バトルル-ムにｎ
	// とつげき しましょうよ-っ!!ｐ
	// バトルサロンで いっしょに なったらｎ
	// ふたりの ラブパワ-でｌ
	// どいつも こいつも ギタギタよ!ｌ
	// ねぇ- ダ-リン!!

BattleFrontier_OutsideEast_Text_FrontierNotExclusivelyForToughTrainers: @ 8243B68
	.string "배틀프런티어에는\n"
	.string "강한 트레이너뿐만이 아니라\l"
	.string "별난 힘을 가진 사람들도\l"
	.string "초대받은 거 같아...\p"
	.string "...금작화라고 하는 남자...\p"
	.string "실은 뭔가 큰 목적이\n"
	.string "있어서 여기를 만든 걸지도 몰라$"
	// バトルフロンティアにはｎ
	// つよい トレ-ナ-だけでは なくｌ
	// かわった ちからを もった ひとたちもｌ
	// まねかれて いるな……ｐ
	// ……エニシダと いう おとこ……ｐ
	// じつは なにか おおきな もくてきがｎ
	// あって ここを つくったのかも しれないぞ

BattleFrontier_OutsideEast_Text_OddTreeHereSeemsToWiggle: @ 8243C2C
	.string "저기 당신은\n"
	.string "눈이 좋은 편인가요?\p"
	.string "저는 이 앞의 나무가 가끔씩\n"
	.string "떨고 있는 것처럼 보이거든요...$"
	// もしもし あんたさんはｎ
	// めは いいほう ですかい?ｐ
	// あたしには このさきの きが ときどきｎ
	// ぷるぷる してる ように みえるんですわ…

BattleFrontier_OutsideEast_Text_OnceAnOddTreePastHere: @ 8243CA3
	.string "저기 당신은\n"
	.string "기억력이 좋은 편인가요?\p"
	.string "저는 이 앞의 이상한 나무를\n"
	.string "본 적이 있는 것 같아서요...$"
	// もしもし あんたさんはｎ
	// ものおぼえは いいほう ですかい?ｐ
	// あたしには このさきに へんな きがｎ
	// あった ような きが するんですわ…

BattleFrontier_OutsideEast_Text_StickyMonWithLongTail: @ 8243D0B
	.string "저저저 저 봤어요!!\p"
	.string "이 앞의 바위에서 꼬리가 길고\n"
	.string "뭔가 끈적끈적한 포켓몬이\l"
	.string "저를 가만히 엿보고 있었어요!\p"
	.string "분명 무서운 포켓몬일 거예요!!$"
	// ぼぼぼ ぼく みちゃったんだっ!!ｐ
	// このさきの いわ から しっぽが ながくってｎ
	// なんか ベタベタした ポケモンがｌ
	// ぼくの こと じ-っと のぞいてたんだっ!ｐ
	// きっと こわい ポケモン だよ-っ!!
