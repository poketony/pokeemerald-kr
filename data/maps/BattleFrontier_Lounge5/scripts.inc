BattleFrontier_Lounge5_MapScripts:: @ 82645C5
	.byte 0

BattleFrontier_Lounge5_EventScript_NatureGirl:: @ 82645C6
	lock
	faceplayer
	msgbox BattleFrontier_Lounge5_Text_NatureGirlGreeting, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	special ChoosePartyMon
	waitstate
	lock
	faceplayer
	compare VAR_0x8004, 255
	goto_if_eq BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown
	specialvar VAR_RESULT, ScriptGetPartyMonSpecies
	compare VAR_RESULT, SPECIES_EGG
	goto_if_eq BattleFrontier_Lounge5_EventScript_NatureGirlEgg
	special ShowNatureGirlMessage
	waitmessage
	waitbuttonpress
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlEgg:: @ 8264603
	msgbox BattleFrontier_Lounge5_Text_NatureGirlEgg, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_NatureGirlNoneShown:: @ 826460D
	msgbox BattleFrontier_Lounge5_Text_NatureGirlNoneShown, MSGBOX_DEFAULT
	release
	end

BattleFrontier_Lounge5_EventScript_Gentleman:: @ 8264617
	msgbox BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_BlackBelt:: @ 8264620
	msgbox BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound, MSGBOX_NPC
	end

BattleFrontier_Lounge5_EventScript_LittleBoy:: @ 8264629
	msgbox BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot, MSGBOX_NPC
	end

BattleFrontier_Lounge5_Text_NatureGirlGreeting:: @ 8264632
	.string "에헤헤! 나 포켓몬의\n"
	.string "기분을 알 수 있어!\p"
	.string "저기! 포켓몬 보여줘! 보여줘!$"
	// いへへ! あたち ポケモンのｎ
	// きもち わかるの!ｐ
	// ね! ポケモン みちて! みちて!

BattleFrontier_Lounge5_Text_NatureGirlNoneShown:: @ 826467F
	.string "메롱-! 너무해!!$"
	// ぷ-! けち!!

BattleFrontier_Lounge5_Text_NatureGirlHardy:: @ 826468D
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "싸울 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlLonely:: @ 82646E5
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "되갚아 줄 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlBrave:: @ 8264741
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// だけど あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlAdamant:: @ 82647A4
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "싸울 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlNaughty:: @ 82647FC
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "하지만 꽤 다치면\l"
	.string "되갚아 줄 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlBold:: @ 8264858
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky:: @ 82648BE
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "싸울 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlRelaxed:: @ 8264916
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "되갚아 줄 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlImpish:: @ 8264972
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlLax:: @ 82649D5
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlTimid:: @ 8264A3F
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlHasty:: @ 8264A9B
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "싸울 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlSerious:: @ 8264AF3
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlJolly:: @ 8264B5D
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlModest:: @ 8264BC3
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "엄청 아파도\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlMild:: @ 8264C36
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "하지만 꽤 다치면\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlBashful:: @ 8264C95
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "엄청 아파도\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlRash:: @ 8264D01
	.string "흠흠...\p"
	.string "이 애 치사한 게 좋대!\n"
	.string "엄청 아파도\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlCalm:: @ 8264D6B
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "엄청 아파도\l"
	.string "자기를 지킬 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlGentle:: @ 8264DD7
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "하지만 꽤 다치면\l"
	.string "되갚아 줄 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlSassy:: @ 8264E33
	.string "흠흠...\p"
	.string "이 애 싸우는 게 좋대!\n"
	.string "하지만 꽤 다치면\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlCareful:: @ 8264E8F
	.string "흠흠...\p"
	.string "이 애 자기를 지킬 거래!\n"
	.string "하지만 꽤 다치면\l"
	.string "치사하게 할 거래!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlEgg:: @ 8264EEE
	.string "알은 쿨쿨 자고 있어서\n"
	.string "얘기할 수 없어!$"
	// たまごは ねんね してる からｎ
	// おはなち できない よぉ!

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon:: @ 8264F22
	.string "포켓몬의 기분을 안다니\n"
	.string "저 소녀분 꽤나\l"
	.string "재치가 있군요!$"
	// ポケモンの きもちが わかるとはｎ
	// あの おじょうちゃん なかなかｌ
	// シャレた ことを もうしますな!

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound:: @ 8264F64
	.string "저는 저 애가 엄청 중요한 걸\n"
	.string "말하고 있다고 생각합니다!$"
	// じぶん あのこが すごく だいじなことをｎ
	// いっている きが するで あります!

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot:: @ 8264FAB
	.string "나 알고 있다고!\p"
	.string "저 애가 빨간 저택에\n"
	.string "자주 간다는 걸!$"
	// ぼく ちってるぜ!ｐ
	// あのこ あかい おうちでｎ
	// よく あそんでる!

