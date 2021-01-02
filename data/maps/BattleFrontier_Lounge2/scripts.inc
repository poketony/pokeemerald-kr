BattleFrontier_Lounge2_MapScripts:: @ 8260642
	.byte 0

@ This NPC gives hints about a random facility or battle mode.
@ For battle modes he gives generic advice 
@ For facilities, depending on how far the player has progressed he will say either
@    The name of the Frontier Brain there
@    The type and description of the 3 pokemon they use in their silver battle
@    The type and description of the 3 pokemon they use in their gold battle
BattleFrontier_Lounge2_EventScript_FrontierManiac:: @ 8260643
	lock
	faceplayer
	goto_if_set FLAG_MET_BATTLE_FRONTIER_MANIAC, BattleFrontier_Lounge2_EventScript_AlreadyMetManiac
	setflag FLAG_MET_BATTLE_FRONTIER_MANIAC
	msgbox BattleFrontier_Lounge2_Text_FrontierManiacIntro, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_AlreadyMetManiac:: @ 826065F
	msgbox BattleFrontier_Lounge2_Text_SwingByForTheLatestWord, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge2_EventScript_GiveAdvice
	end

BattleFrontier_Lounge2_EventScript_GiveAdvice:: @ 826066D
	compare VAR_FRONTIER_MANIAC_FACILITY, 0
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferSingle
	compare VAR_FRONTIER_MANIAC_FACILITY, 1
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferDouble
	compare VAR_FRONTIER_MANIAC_FACILITY, 2
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferMulti
	compare VAR_FRONTIER_MANIAC_FACILITY, 3
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferMultiLink
	compare VAR_FRONTIER_MANIAC_FACILITY, 4
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattleDome
	compare VAR_FRONTIER_MANIAC_FACILITY, 5
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattleFactory
	compare VAR_FRONTIER_MANIAC_FACILITY, 6
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattlePalace
	compare VAR_FRONTIER_MANIAC_FACILITY, 7
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattleArena
	compare VAR_FRONTIER_MANIAC_FACILITY, 8
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattlePike
	compare VAR_FRONTIER_MANIAC_FACILITY, 9
	call_if_eq BattleFrontier_Lounge2_EventScript_BufferBattlePyramid
	compare VAR_FRONTIER_MANIAC_FACILITY, 3
	call_if_le BattleFrontier_Lounge2_EventScript_BattleTowerNews
	compare VAR_FRONTIER_MANIAC_FACILITY, 4
	call_if_ge BattleFrontier_Lounge2_EventScript_FacilityNews
	special ShowFrontierManiacMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge2_EventScript_BattleTowerNews:: @ 82606F8
	msgbox BattleFrontier_Lounge2_Text_BattleTowerIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_FacilityNews:: @ 8260701
	msgbox BattleFrontier_Lounge2_Text_FacilityIsHottest, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge2_EventScript_BufferSingle:: @ 826070A
	bufferstdstring 0, STDSTRING_SINGLE
	return

BattleFrontier_Lounge2_EventScript_BufferDouble:: @ 826070F
	bufferstdstring 0, STDSTRING_DOUBLE
	return

BattleFrontier_Lounge2_EventScript_BufferMulti:: @ 8260714
	bufferstdstring 0, STDSTRING_MULTI
	return

BattleFrontier_Lounge2_EventScript_BufferMultiLink:: @ 8260719
	bufferstdstring 0, STDSTRING_MULTI_LINK
	return

BattleFrontier_Lounge2_EventScript_BufferBattleDome:: @ 826071E
	bufferstdstring 0, STDSTRING_BATTLE_DOME
	return

BattleFrontier_Lounge2_EventScript_BufferBattleFactory:: @ 8260723
	bufferstdstring 0, STDSTRING_BATTLE_FACTORY
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePalace:: @ 8260728
	bufferstdstring 0, STDSTRING_BATTLE_PALACE
	return

BattleFrontier_Lounge2_EventScript_BufferBattleArena:: @ 826072D
	bufferstdstring 0, STDSTRING_BATTLE_ARENA
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePike:: @ 8260732
	bufferstdstring 0, STDSTRING_BATTLE_PIKE
	return

BattleFrontier_Lounge2_EventScript_BufferBattlePyramid:: @ 8260737
	bufferstdstring 0, STDSTRING_BATTLE_PYRAMID
	return

BattleFrontier_Lounge2_EventScript_Maniac1:: @ 826073C
	lock
	msgbox BattleFrontier_Lounge2_Text_NewsGatheringPower, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac2:: @ 8260747
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowersOfObservation, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_Maniac3:: @ 8260752
	lock
	msgbox BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge2_EventScript_TriathleteF:: @ 826075D
	msgbox BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe, MSGBOX_NPC
	end

BattleFrontier_Lounge2_Text_FrontierManiacIntro:: @ 8260766
	.string "나는 배틀프런티어 최고의\n"
	.string "정보통!\p"
	.string "프런티어마니아라고 불러줘!\p"
	.string "너 트레이너지?\p"
	.string "내가 모은 배틀프런티어의\n"
	.string "핫한 정보를 알려줄게!$"
	// ぼくは バトルフロンティアいちのｎ
	// じょうほうつう!ｐ
	// フロンティアマニアって よんでくれよ!ｐ
	// きみ トレ-ナ-だろ?ｐ
	// ぼくが あつめた バトルフロンティアのｎ
	// ホットな じょうほうを おしえて あげるよ!

BattleFrontier_Lounge2_Text_SwingByForTheLatestWord:: @ 8260857
	.string "여어 또 내 정보를\n"
	.string "들으러 왔구나! 어쩔 수 없구만-!$"
	// やあやあ また ぼくの じょうほうをｎ
	// ききに きたんだね! しかたないな-!

@ Unused
BattleFrontier_Lounge2_Text_MyInformationsBeenUsefulRight:: @ 82608A1
	.string "어때? 어때? 어때?\p"
	.string "내 정보는 물론\n"
	.string "엄청 도움이 됐겠지?$"
	// どう? どう? どう?ｐ
	// ぼくの じょうほうは もちろんｎ
	// すご-く さんこうに なってるだろ?

BattleFrontier_Lounge2_Text_FacilityIsHottest:: @ 82608F2
	.string "그렇군...\p"
	.string "지금은 {STR_VAR_1}{K_IGA}\n"
	.string "인기가 많은 거 같아!$"
	// そうだねぇ……ｐ
	// いまは §いがｎ
	// アッつい みたいだね!

BattleFrontier_Lounge2_Text_BattleTowerIsHottest:: @ 8260933
	.string "그렇군...\p"
	.string "지금은 배틀타워 {STR_VAR_1}{K_IGA}\n"
	.string "인기가 많은 거 같아!$"
	// そうだねぇ……ｐ
	// いまは バトルタワ-§いがｎ
	// アッつい みたいだね!

BattleFrontier_Lounge2_Text_SalonMaidenIsThere:: @ 8260971
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "타워타이쿤이라고 하는\l"
	.string "수수께끼의 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこは エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// タワ-タイク-ンって いうｌ
	// なぞの トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_SalonMaidenSilverMons:: @ 8260A1E
	.string "너는 타워타이쿤과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 상대의 힘을 시험할 때\n"
	.string "에스퍼의 초능력포켓몬!\l"
	.string "불꽃의 화산포켓몬!\l"
	.string "노말의 졸음포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは タワ-タイク-ンとｎ
	// たたかったこと あるかい?ｐ
	// やつは あいての ちからを はかるときｎ
	// エスパ-の ねんりきポケモン!ｌ
	// ほのおの かざんポケモン!ｌ
	// ノ-マルの いねむりポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_SalonMaidenGoldMons:: @ 8260AE7
	.string "너는 진심인 타워타이쿤과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 진심으로 싸울 때\n"
	.string "드래곤, 에스퍼의 무한포켓몬!\l"
	.string "전기의 우뢰포켓몬!\l"
	.string "노말의 졸음포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの タワ-タイク-ンとｎ
	// たたかったこと あるかい?ｐ
	// やつは ほんとの ちからで たたかうときｎ
	// ドラゴンと エスパ-の むげんポケモン!ｌ
	// でんきの いかづちポケモン!ｌ
	// ノ-マルの いねむりポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_DomeAceIsThere:: @ 8260BC4
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "돔슈퍼스타라고 하는\l"
	.string "매우 화려한 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこは エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// ド-ムス-パ-スタ-って いうｌ
	// どハデな トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_DomeAceSilverMons:: @ 8260C6D
	.string "너는 돔슈퍼스타와\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 상대의 힘을 얕볼 때\n"
	.string "드래곤, 비행의 드래곤포켓몬!\l"
	.string "물, 땅의 늪물고기포켓몬!\l"
	.string "불, 비행의 화염포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ド-ムス-パ-スタ-とｎ
	// たたかったこと あるかい?ｐ
	// やつは あいての ちからを なめてるときｎ
	// ドラゴンと ひこうの ドラゴンポケモン!ｌ
	// みずと じめんの ぬまうおポケモン!ｌ
	// ほのおと ひこうの かえんポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_DomeAceGoldMons:: @ 8260D3A
	.string "너는 진심인 돔슈퍼스타와\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 전력으로 싸울 때\n"
	.string "드래곤, 에스퍼의 무한포켓몬!\l"
	.string "물, 땅의 늪물고기포켓몬!\l"
	.string "강철, 에스퍼의 무쇠다리포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの ド-ムス-パ-スタ-とｎ
	// たたかったこと あるかい?ｐ
	// やつは じぶんの せんりゃくを みせるときｎ
	// ドラゴンと エスパ-の むげんポケモン!ｌ
	// みずと じめんの ぬまうおポケモン!ｌ
	// はがねと エスパ-の てつあしポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_FactoryHeadIsThere:: @ 8260E1E
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "팩토리책임자라고 하는\l"
	.string "위험한 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこは エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// ファクトリ-ヘッドって いうｌ
	// やばい トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_FactoryHeadSilverMons:: @ 8260EC7
	.string "너는 팩토리책임자와\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 사용하는 포켓몬은\n"
	.string "대여 포켓몬 중\l"
	.string "랜덤으로 3마리!\l"
	.string "너와 거의 같은 조건인 듯해!$"
	// きみは もう ファクトリ-ヘッドとｎ
	// たたかったこと あるかい?ｐ
	// あいつが つかう ポケモンはｎ
	// レンタルポケモンのｌ
	// なかから どれか 3ひき!ｌ
	// きみと ほぼ おなじ じょうけん らしいぜ!

BattleFrontier_Lounge2_Text_FactoryHeadGoldMons:: @ 8260F74
	.string "너는 진심인 팩토리책임자와\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 진심으로 싸울 때도\n"
	.string "대여 포켓몬 중에서\l"
	.string "랜덤으로 3마리!\l"
	.string "너와 거의 같은 조건으로\n"
	.string "싸우는 듯해!$"
	// きみは ほんきの ファクトリ-ヘッドとｎ
	// たたかったこと あるかい?ｐ
	// あいつは ほんきで たたかう ときでもｎ
	// レンタルポケモンのｌ
	// なかから どれか 3ひき!ｌ
	// きみと ほとんど おなじ じょうけんでｌ
	// たたかう らしいぜ!

BattleFrontier_Lounge2_Text_PikeQueenIsThere:: @ 8261026
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "튜브퀸이라고 하는\l"
	.string "무서운 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこには エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// チュ-ブクイ-ンって いうｌ
	// こわ-い トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_PikeQueenSilverMons:: @ 82610CC
	.string "너는 튜브퀸과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 기분이 좋을 때\n"
	.string "독의 송곳뱀포켓몬!\l"
	.string "벌레의 발효포켓몬!\l"
	.string "물의 사랑포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは チュ-ブクイ-ンとｎ
	// たたかったこと あるかい?ｐ
	// やつは きげんの いいときｎ
	// どくの キバへびポケモン!ｌ
	// むしと いわの はっこうポケモン!ｌ
	// みずの いつくしみポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_PikeQueenGoldMons:: @ 8261194
	.string "너는 진심인 튜브퀸과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 정말로 화났을 때\n"
	.string "독의 송곳뱀포켓몬!\l"
	.string "강철, 땅의 철뱀포켓몬!\l"
	.string "물, 비행의 흉악포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの チュ-ブクイ-ンとｎ
	// たたかったこと あるかい?ｐ
	// やつは ほんきで おこったときｎ
	// どくの キバへびポケモン!ｌ
	// はがねと じめんの てつへびポケモン!ｌ
	// みずと ひこうの きょうあくポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_ArenaTycoonIsThere:: @ 8261282
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "아레나캡틴이라고 하는\l"
	.string "귀여운 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこには エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// アリ-ナキャプテンって いうｌ
	// かわいい トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_ArenaTycoonSilverMons:: @ 8261329
	.string "너는 이미 아레나캡틴과\n"
	.string "배틀한 적이 있어?\p"
	.string "그 애는 상대의 힘을 살필 때\n"
	.string "벌레, 격투의 외뿔포켓몬!\l"
	.string "악의 달빛포켓몬!\l"
	.string "벌레, 고스트의 허물포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは もう アリ-ナキャプテンとｎ
	// たたかったこと あるかい?ｐ
	// あのこは あいての ちからを うかがうときｎ
	// むしと かくとうの 1ぽんヅノポケモン!ｌ
	// あくの げっこうポケモン!ｌ
	// むしと ゴ-ストの ぬけがらポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_ArenaTycoonGoldMons:: @ 8261403
	.string "너는 진심인 아레나캡틴과\n"
	.string "배틀한 적이 있어?\p"
	.string "그 애는 진심으로 싸울 때\n"
	.string "악의 달빛포켓몬!\l"
	.string "고스트, 독의 그림자포켓몬!\l"
	.string "풀, 격투의 버섯포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの アリ-ナキャプテンとｎ
	// たたかったこと あるかい?ｐ
	// あのこは マジで たたかう ときｎ
	// あくの げっこうポケモン!ｌ
	// ゴ-ストと どくの シャド-ポケモン!ｌ
	// くさと かくとうの きのこポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_PalaceMavenIsThere:: @ 82614E6
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "팰리스가디언이라고 하는\l"
	.string "수상한 트레이너가 관리한다고!$"
	// あそこには エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// パレスガ-ディアンって いうｌ
	// あやしい トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_PalaceMavenSilverMons:: @ 8261591
	.string "너는 팰리스가디언과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석은 상대의 마음을 시험할 때\n"
	.string "독, 비행의 박쥐포켓몬!\l"
	.string "노말의 나태함포켓몬!\l"
	.string "물, 얼음의 탈것포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは パレスガ-ディアンとｎ
	// たたかったこと あるかい?ｐ
	// やつは あいての こころを ためすときｎ
	// どくと ひこうの こうもりポケモン!ｌ
	// ノ-マルの ものぐさポケモンｌ
	// みずと こおりの のりものポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_PalaceMavenGoldMons:: @ 826166F
	.string "너는 진심인 팰리스가디언과\n"
	.string "배틀한 적이 있어?\p"
	.string "녀석는 적당히 하지 않을 때\n"
	.string "불꽃의 전설포켓몬!\l"
	.string "노말의 나태함포켓몬!\l"
	.string "물의 오로라포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの パレスガ-ディアンとｎ
	// たたかったこと あるかい?ｐ
	// やつが てかげんぬきで たたかうときはｎ
	// ほのおの でんせつポケモン!ｌ
	// ノ-マルの ものぐさポケモンｌ
	// みずの オ-ロラポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_PyramidKingIsThere:: @ 826174D
	.string "알고 있어?\p"
	.string "그곳은 금작화가\n"
	.string "프런티어브레인이라고 부르는\l"
	.string "트레이너들 중 하나...\l"
	.string "피라미드킹이라고 하는\l"
	.string "뜨거운 트레이너가 관리한다고!$"
	// しってるかい?ｐ
	// あそこには エニシダがｎ
	// フロンティアブレ-ンって よんでるｌ
	// トレ-ナ-の うちの ひとり……ｌ
	// ピラミッドキングって いうｌ
	// アツ-い トレ-ナ-が おさめてるのさ!

BattleFrontier_Lounge2_Text_PyramidKingSilverMons:: @ 82617F9
	.string "너는 이미 피라미드킹과\n"
	.string "배틀한 적이 있어?\p"
	.string "그는 상대의 힘을 시험할 때\n"
	.string "바위의 바위산포켓몬!\l"
	.string "얼음의 빙산포켓몬!\l"
	.string "강철의 쇠철포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは もう ピラミッドキングとｎ
	// たたかったこと あるかい?ｐ
	// かれは あいての ちからを ためすときｎ
	// いわの いわやまポケモン!ｌ
	// こおりの ひょうざんポケモン!ｌ
	// はがねの くろがねポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_PyramidKingGoldMons:: @ 82618C4
	.string "너는 진심인 피라미드킹과\n"
	.string "배틀한 적이 있어?\p"
	.string "그는 뜨거운 힘이 끓어오를 때\n"
	.string "얼음, 비행의 냉동포켓몬!\l"
	.string "전기, 비행의 전기포켓몬!\l"
	.string "불꽃, 비행의 화염포켓몬\l"
	.string "3마리를 내보낸다는 것 같아!$"
	// きみは ほんきの ピラミッドキングとｎ
	// たたかったこと あるかい?ｐ
	// かれに あつい ちからが みなぎるときはｎ
	// こおりと ひこうの れいとうポケモン!ｌ
	// でんきと ひこうの でんげきポケモン!ｌ
	// ほのおと ひこうの かえんポケモンのｌ
	// 3ひきを つかってくる らしいぜ!

BattleFrontier_Lounge2_Text_DoubleBattleAdvice1:: @ 82619AC
	.string "더블배틀을 할 수 있는 장소는\n"
	.string "몇 개 있지만 역시 기본은\l"
	.string "배틀타워의 더블 배틀룸!\p"
	.string "일단 거기서 배틀프런티어에서의\n"
	.string "더블배틀을 배워 보라고!$"
	// ダブルバトルが できる ばしょはｎ
	// いくつか あるけど やっぱり きほんはｌ
	// バトルタワ-の ダブル バトルル-ム!ｐ
	// まずは ここから バトルフロンティアでのｎ
	// ダブルバトルを まなんで いくと いいぜ!

BattleFrontier_Lounge2_Text_DoubleBattleAdvice2:: @ 8261A91
	.string "이곳의 배틀에서는\n"
	.string "조심하도록 해!\p"
	.string "더블배틀에서만 가능한 전략을\n"
	.string "쓰는 트레이너도 있는 거 같아!$"
	// ここでの たたかいにはｎ
	// ちゅうい しなよ!ｐ
	// ダブルバトル ならではの せんぽうでｎ
	// たたかう トレ-ナ-も いるみたいだぜ!

BattleFrontier_Lounge2_Text_DoubleBattleAdvice3:: @ 8261B0C
	.string "이곳의 배틀에서\n"
	.string "더블배틀에 자신이 생겼다면\l"
	.string "다른 더블배틀이 있는 장소에\l"
	.string "도전하는 것도 좋을 거야!$"
	// ここの たたかいでｎ
	// ダブルバトルに じしんが ついたらｌ
	// ほかの ダブルバトルが できる ばしょにｌ
	// チャレンジ してみると いいかもな!

BattleFrontier_Lounge2_Text_MultiBattleAdvice:: @ 8261B95
	.string "배틀살롱에는\n"
	.string "여러 트레이너가 모여 있어!\p"
	.string "어쩌면 네 친구나\n"
	.string "제자를 만날지도 모르지!\l"
	.string "잘 찾아보라고!$"
	// バトルサロンにはｎ
	// いろんな トレ-ナ-が あつまるんだぜ!ｐ
	// もしかしたら きみの ともだちやｎ
	// でしにも あえるかも しれないな!ｌ
	// よ-く さがして みると いいぜ!

BattleFrontier_Lounge2_Text_LinkMultiBattleAdvice:: @ 8261C1A
	.string "친구와 모였다면\n"
	.string "통신멀티 배틀룸!!\p"
	.string "강한 친구와 같이 간다면\n"
	.string "강한 트레이너들과의\l"
	.string "배틀이 기다리고 있을 거야!!$"
	// ともだちが あつまったらｎ
	// つうしんマルチ バトルル-ム!!ｐ
	// つよい ともだちと いっしょに あそべばｎ
	// つよい トレ-ナ-たち とのｌ
	// たたかいが まってるぜ!

BattleFrontier_Lounge2_Text_NewsGatheringPower:: @ 8261C9C
	.string "굉장한 정보력-!!\n"
	.string "역시 선배는 다르군요-$"
	// すっげえ じょうほうりょく-!!ｎ
	// やっぱ センパイは ちがうっすよ-

BattleFrontier_Lounge2_Text_AmazingPowersOfObservation:: @ 8261CDC
	.string "굉장한 관찰력-!!\n"
	.string "역시 선배는 다르군요-$"
	// すっげえ かんさつりょく-!!ｎ
	// やっぱ センパイは ちがうっすわ-

BattleFrontier_Lounge2_Text_AmazingPowerOfPersuasion:: @ 8261D1D
	.string "굉장한 설득력-!!\n"
	.string "역시 선배는 다르군요-$"
	// すっげえ せっとくりょく-!!ｎ
	// やっぱ センパイは ちがうっすね-

BattleFrontier_Lounge2_Text_ThisPlaceIsScaringMe:: @ 8261D5C
	.string "여기 뭐야...\n"
	.string "좀 무서워...$"
	// なによ ここ……ｎ
	// ちょっと こわい……

