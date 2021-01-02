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
	.string "Ehehe!\n"
	.string "I can tell what POKéMON are thinking!\p"
	.string "Please!\n"
	.string "Can I see your POKéMON?$"
	// いへへ! あたち ポケモンのｎ
	// きもち わかるの!ｐ
	// ね! ポケモン みちて! みちて!

BattleFrontier_Lounge5_Text_NatureGirlNoneShown:: @ 826467F
	.string "Boo!\n"
	.string "Cheapie!$"
	// ぷ-! けち!!

BattleFrontier_Lounge5_Text_NatureGirlHardy:: @ 826468D
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "It will battle even if it has a lot\l"
	.string "of ouchies!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlLonely:: @ 82646E5
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlBrave:: @ 8264741
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// だけど あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlAdamant:: @ 82647A4
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "It will battle even if it has a lot\l"
	.string "of ouchies!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌたたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlNaughty:: @ 82647FC
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlBold:: @ 8264858
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlDocileNaiveQuietQuirky:: @ 82648BE
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "It will battle even if it has a lot\l"
	.string "of ouchies!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlRelaxed:: @ 8264916
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlImpish:: @ 8264972
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlLax:: @ 82649D5
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "It says it likes to be sneaky even\l"
	.string "if it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlTimid:: @ 8264A3F
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlHasty:: @ 8264A9B
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "It will battle even if it has a lot\l"
	.string "of ouchies!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// たたかうよ! って!

BattleFrontier_Lounge5_Text_NatureGirlSerious:: @ 8264AF3
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "It says it likes to be sneaky even\l"
	.string "if it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlJolly:: @ 8264B5D
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will worry about itself!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// じぶんが ちんぱい なるよ! って!

BattleFrontier_Lounge5_Text_NatureGirlModest:: @ 8264BC3
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "It says it worries about itself whether\l"
	.string "or not it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlMild:: @ 8264C36
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlBashful:: @ 8264C95
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "It says it worries about itself even\l"
	.string "if it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlRash:: @ 8264D01
	.string "Hmhm…\p"
	.string "This one says it likes to be sneaky!\n"
	.string "It says it likes to be sneaky even\l"
	.string "if it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ ずるいの ちゅき! って!ｎ
	// いっぱい いたいいたい でもｌ
	// ずるいのが いい! って!

BattleFrontier_Lounge5_Text_NatureGirlCalm:: @ 8264D6B
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "It says it worries about itself even\l"
	.string "if it has a lot of ouchies!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// いっぱい いたいいたい でもｌ
	// じぶん だいじ! って!

BattleFrontier_Lounge5_Text_NatureGirlGentle:: @ 8264DD7
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will hit back!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ちかえし してやる! って!

BattleFrontier_Lounge5_Text_NatureGirlSassy:: @ 8264E33
	.string "Hmhm…\p"
	.string "This one says it likes to battle!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"
	// ふんふん……ｐ
	// このこ たたかうの ちゅき! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlCareful:: @ 8264E8F
	.string "Hmhm…\p"
	.string "This one says it looks after itself!\n"
	.string "But if it gets enough ouchies,\l"
	.string "it will turn sneaky!$"
	// ふんふん……ｐ
	// このこ じぶん だいじ! って!ｎ
	// でも あんまし いたいいたい だとｌ
	// ずるいの するよ! って!

BattleFrontier_Lounge5_Text_NatureGirlEgg:: @ 8264EEE
	.string "That's silly! An EGG is asleep!\n"
	.string "I can't talk to it!$"
	// たまごは ねんね してる からｎ
	// おはなち できない よぉ!

BattleFrontier_Lounge5_Text_LadyClaimsSheUnderstandsPokemon:: @ 8264F22
	.string "How charming!\n"
	.string "That little lady claims she can\l"
	.string "understand POKéMON!$"
	// ポケモンの きもちが わかるとはｎ
	// あの おじょうちゃん なかなかｌ
	// シャレた ことを もうしますな!

BattleFrontier_Lounge5_Text_GirlSayingSomethingProfound:: @ 8264F64
	.string "I have this feeling that the little girl\n"
	.string "is saying something profound.$"
	// じぶん あのこが すごく だいじなことをｎ
	// いっている きが するで あります!

BattleFrontier_Lounge5_Text_GirlPlaysAtRedHouseALot:: @ 8264FAB
	.string "I know something!\p"
	.string "That little girl plays at the red house\n"
	.string "a lot!$"
	// ぼく ちってるぜ!ｐ
	// あのこ あかい おうちでｎ
	// よく あそんでる!

