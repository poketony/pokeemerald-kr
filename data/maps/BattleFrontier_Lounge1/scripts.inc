BattleFrontier_Lounge1_MapScripts:: @ 825E774
	.byte 0

@ NPC that rates pokemon based on their IVs
BattleFrontier_Lounge1_EventScript_Breeder:: @ 825E775
	lock
	faceplayer
	call_if_unset FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_BreederIntro
	call_if_set FLAG_MET_BATTLE_FRONTIER_BREEDER, BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder
	setflag FLAG_MET_BATTLE_FRONTIER_BREEDER
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder:: @ 825E792
	special ChoosePartyMon
	waitstate
	compare VAR_0x8004, 255
	goto_if_ne BattleFrontier_Lounge1_EventScript_ShowMonToBreeder
	compare VAR_0x8004, 255
	goto_if_eq BattleFrontier_Lounge1_EventScript_CancelMonSelect
	end

BattleFrontier_Lounge1_EventScript_BreederIntro:: @ 825E7AD
	msgbox BattleFrontier_Lounge1_Text_PokemonBreederIntro, MSGBOX_DEFAULT
	return

BattleFrontier_Lounge1_EventScript_AlreadyMetBreeder:: @ 825E7B6
	msgbox BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon, MSGBOX_DEFAULT
	return

@ BufferVarsForIVRater buffers the following values
@ VAR_0x8005: Sum of the mons IVs
@ VAR_0x8006: Stat id of highest IV stat
@ VAR_0x8007: IV of the highest IV stat
BattleFrontier_Lounge1_EventScript_ShowMonToBreeder:: @ 825E7BF
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge1_EventScript_ShowEggToBreeder
	special BufferVarsForIVRater
	compare VAR_0x8005, 90   @ Average of 15
	goto_if_le BattleFrontier_Lounge1_EventScript_AverageTotalIVs
	compare VAR_0x8005, 120  @ Average of 20
	goto_if_le BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs
	compare VAR_0x8005, 150  @ Average of 25
	goto_if_le BattleFrontier_Lounge1_EventScript_HighTotalIVs
	compare VAR_0x8005, 151  @ Average of > 25
	goto_if_ge BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs
	end

BattleFrontier_Lounge1_EventScript_ShowEggToBreeder:: @ 825E7FF
	msgbox BattleFrontier_Lounge1_Text_EvenICantTell, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_ChooseMonToShowBreeder
	end

@ Comment on the highest IV stat
BattleFrontier_Lounge1_EventScript_HighestIVStat:: @ 825E80D
	compare VAR_0x8006, STAT_HP
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVHP
	compare VAR_0x8006, STAT_ATK
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVAtk
	compare VAR_0x8006, STAT_DEF
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVDef
	compare VAR_0x8006, STAT_SPEED
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpeed
	compare VAR_0x8006, STAT_SPATK
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpAtk
	compare VAR_0x8006, STAT_SPDEF
	goto_if_eq BattleFrontier_Lounge1_EventScript_HighestIVSpDef
	end

@ Comment on the highest IV value
BattleFrontier_Lounge1_EventScript_HighestIVValue:: @ 825E850
	compare VAR_0x8007, 15
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVLow
	compare VAR_0x8007, 25
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVMid
	compare VAR_0x8007, 30
	goto_if_le BattleFrontier_Lounge1_EventScript_HighestIVHigh
	compare VAR_0x8007, 31
	goto_if_ge BattleFrontier_Lounge1_EventScript_HighestIVMax
	end

BattleFrontier_Lounge1_EventScript_EndBreederComments:: @ 825E87D
	release
	end

BattleFrontier_Lounge1_EventScript_AverageTotalIVs:: @ 825E87F
	msgbox BattleFrontier_Lounge1_Text_AverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_AboveAverageTotalIVs:: @ 825E88D
	msgbox BattleFrontier_Lounge1_Text_BetterThanAverageAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighTotalIVs:: @ 825E89B
	msgbox BattleFrontier_Lounge1_Text_ImpressiveAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_VeryHighTotalIVs:: @ 825E8A9
	msgbox BattleFrontier_Lounge1_Text_OutstandingAbility, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVStat
	end

BattleFrontier_Lounge1_EventScript_HighestIVHP:: @ 825E8B7
	msgbox BattleFrontier_Lounge1_Text_BestAspectHP, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVAtk:: @ 825E8C5
	msgbox BattleFrontier_Lounge1_Text_BestAspectAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVDef:: @ 825E8D3
	msgbox BattleFrontier_Lounge1_Text_BestAspectDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpeed:: @ 825E8E1
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpeed, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpAtk:: @ 825E8EF
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpAtk, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVSpDef:: @ 825E8FD
	msgbox BattleFrontier_Lounge1_Text_BestAspectSpDef, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_HighestIVValue
	end

BattleFrontier_Lounge1_EventScript_HighestIVLow:: @ 825E90B
	msgbox BattleFrontier_Lounge1_Text_StatRelativelyGood, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMid:: @ 825E919
	msgbox BattleFrontier_Lounge1_Text_StatImpressive, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVHigh:: @ 825E927
	msgbox BattleFrontier_Lounge1_Text_StatOutstanding, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_HighestIVMax:: @ 825E935
	msgbox BattleFrontier_Lounge1_Text_StatFlawless, MSGBOX_DEFAULT
	goto BattleFrontier_Lounge1_EventScript_EndBreederComments
	end

BattleFrontier_Lounge1_EventScript_CancelMonSelect:: @ 825E943
	msgbox BattleFrontier_Lounge1_Text_NoTimeForMyAdvice, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge1_EventScript_Boy1:: @ 825E94D
	msgbox BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding, MSGBOX_NPC
	end

BattleFrontier_Lounge1_EventScript_Boy2:: @ 825E956
	msgbox BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt, MSGBOX_NPC
	end

BattleFrontier_Lounge1_Text_PokemonBreederIntro: @ 825E95F
	.string "나는 포켓몬을 키운 지 70년!\n"
	.string "전설의 포켓몬 브리더로\l"
	.string "불리는 남자다!\p"
	.string "나 정도 되면 포켓몬의\n"
	.string "능력을 한눈에 알 수 있지!\p"
	.string "너도 트레이너라면\n"
	.string "자신의 포켓몬의 능력을\l"
	.string "알고 싶지?\p"
	.string "자! 내게 포켓몬을 보여주거라!$"
	// わしは ポケモン そだてて 70ねん!ｎ
	// でんせつの ポケモントップブリ-ダ-とｌ
	// あがめられる おとこ じゃ!ｐ
	// わしくらいに なると ポケモンのｎ
	// のうりょくが ひとめで わかるんじゃぞっ!ｐ
	// おまえさんも トレ-ナ-ならｎ
	// じぶんの ポケモンの のうりょくがｌ
	// きになる じゃろ?ｐ
	// ほれ! わしに ポケモンを みせて みいっ!

BattleFrontier_Lounge1_Text_AverageAbility: @ 825EA92
	.string "... 음-\p"
	.string "이 포켓몬은 전체적으로\n"
	.string "그럭저럭인 능력을\l"
	.string "가지고 있구먼...$"
	// …… ん-ｐ
	// こいつは ぜんたいてきに いうとｎ
	// まずまずの のうりょくとｌ
	// いう ところかの……

BattleFrontier_Lounge1_Text_BetterThanAverageAbility: @ 825EAD9
	.string "... 음-\p"
	.string "이 포켓몬은 전체적으로\n"
	.string "평균 이상의 능력을\l"
	.string "가지고 있구먼...$"
	// …… ん-ｐ
	// こいつは ぜんたいてきに いうとｎ
	// へいきん いじょうのｌ
	// のうりょくを もっとるな……

BattleFrontier_Lounge1_Text_ImpressiveAbility: @ 825EB2A
	.string "... 음-\p"
	.string "이 포켓몬은 전체적으로\n"
	.string "상당히 우수한 능력을\l"
	.string "가지고 있구먼...$"
	// …… ん-ｐ
	// こいつは ぜんたいてきに いうとｎ
	// そうとう ゆうしゅうなｌ
	// のうりょくを もっとるぞ!

BattleFrontier_Lounge1_Text_OutstandingAbility: @ 825EB6F
	.string "... 음-\p"
	.string "이 포켓몬은 전체적으로\n"
	.string "훌륭한 능력을\l"
	.string "가지고 있구먼...$"
	// …… ん-ｐ
	// こいつは ぜんたいてきに いうとｎ
	// すばらしい のうりょく じゃな!

BattleFrontier_Lounge1_Text_BestAspectHP: @ 825EBBB
	.string "덧붙여서 제일 좋은 건\n"
	.string "HP인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// HP かの……

BattleFrontier_Lounge1_Text_BestAspectAtk: @ 825EBF8
	.string "덧붙여서 제일 좋은 건\n"
	.string "공격인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// こうげき かの……

BattleFrontier_Lounge1_Text_BestAspectDef: @ 825EC39
	.string "덧붙여서 제일 좋은 건\n"
	.string "방어인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// ぼうぎょ かの……

BattleFrontier_Lounge1_Text_BestAspectSpAtk: @ 825EC7B
	.string "덧붙여서 제일 좋은 건\n"
	.string "특수공격인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// とくこう かの……

BattleFrontier_Lounge1_Text_BestAspectSpDef: @ 825ECC4
	.string "덧붙여서 제일 좋은 건\n"
	.string "특수방어인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// とくぼう かの……

BattleFrontier_Lounge1_Text_BestAspectSpeed: @ 825ED0E
	.string "덧붙여서 제일 좋은 건\n"
	.string "스피드인 것 같네...$"
	// ちなみに いちばん いいかんじ なのはｎ
	// すばやさ かの……

BattleFrontier_Lounge1_Text_StatRelativelyGood: @ 825ED4E
	.string "그럭저럭의 힘을 가지고 있다...\n"
	.string "...흠... 그렇게 느꼈다!$"
	// まあまあの のうりょくを もっとるぞ……ｎ
	// ……ふむ…… そんな かんじ かのう!

BattleFrontier_Lounge1_Text_StatImpressive: @ 825ED87
	.string "상당한 힘을 가지고 있다...\n"
	.string "...흠... 그렇게 느꼈다!$"
	// かなりの ちからを もっとるな!ｎ
	// ……ふむ…… そんな かんじ かのう!

BattleFrontier_Lounge1_Text_StatOutstanding: @ 825EDC1
	.string "훌륭한 힘을 가지고 있다...\n"
	.string "...흠... 그렇게 느꼈다!$"
	// すばらしい ちからを もっとる!ｎ
	// ……ふむ…… そんな かんじ かのう!

BattleFrontier_Lounge1_Text_StatFlawless: @ 825EDF6
	.string "최고의 힘을 가지고 있다...\n"
	.string "...흠... 그렇게 느꼈다!$"
	// ばっちりっ! ぱ-ふぇくと じゃ!ｎ
	// ……ふむ…… そんな かんじ かのう!

BattleFrontier_Lounge1_Text_NoTimeForMyAdvice: @ 825EE37
	.string "뭐라!\n"
	.string "내 어드바이스가 필요없다는 겐가!\p"
	.string "인생 선배의 가르침을\n"
	.string "잠자코 들으라고!!$"
	// なんじゃい!ｎ
	// わしの あどばいすは いらんと いうのか!ｐ
	// じんせいの せんぱいの おしえはｎ
	// だまって きく もんじゃぞ!!

@ Unused
BattleFrontier_Lounge1_Text_HaveBusinessNeedsTending: @ 825EEA6
	.string "뭔가?\p"
	.string "나도 바쁜 몸이라네!\n"
	.string "다음에 또 오게나!$"
	// なんじゃ-?ｐ
	// わしも いろいろ いそがしい からのう!ｎ
	// また こんどに せい!

BattleFrontier_Lounge1_Text_LetsLookAtYourPokemon: @ 825EEF6
	.string "오오! 젊은이!\n"
	.string "포켓몬의 능력이 궁금하지?\p"
	.string "자자!\n"
	.string "내게 포켓몬을 보여주게나!$"
	// おお! わかいの!ｎ
	// ポケモンの のうりょくが きになるんか?ｐ
	// ほれほれ!ｎ
	// わしに ポケモンを みせて みい!

BattleFrontier_Lounge1_Text_EvenICantTell: @ 825EF5E
	.string "아무리 나라도 아직 태어나지 않은\n"
	.string "포켓몬에 대해서는 알 수가 없네!\p"
	.string "포켓몬을 보여주게! 포켓몬을!$"
	// さすがの わしも まだ うまれても いないｎ
	// ポケモンの ことは わからんぞっ!ｐ
	// ポケモンを みせんか! ポケモンを!

BattleFrontier_Lounge1_Text_SaidMyMonIsOutstanding: @ 825EFDD
	.string "내 포켓몬이 훌륭하대!\n"
	.string "소중히 키워온 보람이 있었어!$"
	// ぼくの ポケモン すばらしいって!ｎ
	// だいじに そだてて きてよかった!

BattleFrontier_Lounge1_Text_DidntDoAnythingSpecialRaisingIt: @ 825F020
	.string "내 포켓몬이 훌륭하대!\n"
	.string "딱히 특별하게 키우진 않았는데...$"
	// ぼくの ポケモン すばらしいって!ｎ
	// べつに ふつうに そだてたん だけどな……

