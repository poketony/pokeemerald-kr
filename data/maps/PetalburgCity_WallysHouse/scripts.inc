.set LOCALID_WALLYS_DAD, 1

PetalburgCity_WallysHouse_MapScripts:: @ 8204229
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PetalburgCity_WallysHouse_OnFrame
	map_script MAP_SCRIPT_ON_WARP_INTO_MAP_TABLE, PetalburgCity_WallysHouse_OnWarp
	.byte 0

PetalburgCity_WallysHouse_OnWarp: @ 8204234
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther
	.2byte 0

PetalburgCity_WallysHouse_EventScript_PlayerWallysDadFaceEachOther:: @ 820423E
	turnobject OBJ_EVENT_ID_PLAYER, DIR_EAST
	turnobject LOCALID_WALLYS_DAD, DIR_WEST
	end

PetalburgCity_WallysHouse_OnFrame: @ 8204247
	map_script_2 VAR_PETALBURG_CITY_STATE, 4, PetalburgCity_WallysHouse_EventScript_GiveHM03Surf
	.2byte 0

PetalburgCity_WallysHouse_EventScript_GiveHM03Surf:: @ 8204251
	lockall
	msgbox PetalburgCity_WallysHouse_Text_PleaseExcuseUs, MSGBOX_DEFAULT
	giveitem ITEM_HM03
	setflag FLAG_RECEIVED_HM03
	msgbox PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces, MSGBOX_DEFAULT
	setvar VAR_PETALBURG_CITY_STATE, 5
	releaseall
	end

PetalburgCity_WallysHouse_EventScript_WallysDad:: @ 8204278
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_WALLY_VICTORY_ROAD, PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_WallysHouse_EventScript_ReceievedHM03Surf
	goto_if_set FLAG_THANKED_FOR_PLAYING_WITH_WALLY, PetalburgCity_WallysHouse_EventScript_PlayedWithWally
	msgbox PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally, MSGBOX_DEFAULT
	setflag FLAG_THANKED_FOR_PLAYING_WITH_WALLY
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceievedHM03Surf:: @ 82042A2
	msgbox PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_DefeatedWallyInVictoryRoad:: @ 82042AC
	msgbox PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_PlayedWithWally:: @ 82042B6
	msgbox PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_WallysMom:: @ 82042C0
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_HM03, PetalburgCity_WallysHouse_EventScript_ReceivedHM03Surf
	msgbox PetalburgCity_WallysHouse_Text_WallyWasReallyHappy, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_EventScript_ReceivedHM03Surf:: @ 82042D5
	msgbox PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling, MSGBOX_DEFAULT
	release
	end

PetalburgCity_WallysHouse_Text_ThanksForPlayingWithWally: @ 82042DF
	.string "넌...\n"
	.string "그렇구나 {PLAYER}{K_I} 맞지?\p"
	.string "아까 민진이를 도와줘서\n"
	.string "고맙구나...\p"
	.string "그 애는 태어났을 때부터\n"
	.string "몸이 별로 안 좋단다\p"
	.string "그래서 잠깐 잔디마을의\n"
	.string "친척 집에서\l"
	.string "신세 좀 지라고 했지\p"
	.string "거긴 여기보다 훨씬\n"
	.string "공기가 깨끗한 곳이거든!\p"
	.string "...그래서 민진이는 어딨냐고? 민진이라면\n"
	.string "이미 출발했단다\p"
	.string "지금이면 어디쯤 갔으려나...$"
	// きみは……ｎ
	// そうか §あ§お だね?ｐ
	// さっきは ミツルの あいてを してくれてｎ
	// ありがとう……ｐ
	// あのこは うまれた ときからｎ
	// からだが じょうぶでは なくてねｐ
	// それで すこしの あいだ シダケタウンのｎ
	// わたしの しんせきの うちでｌ
	// あずかってもらう ことに したんだよｐ
	// あそこは ここよりも ずっとｎ
	// くうきが きれいな ところ だからね!ｐ
	// ……で ミツルかい? ミツルならｎ
	// もう しゅっぱつ していったよｐ
	// いまごろは どの あたりかなあ……

PetalburgCity_WallysHouse_Text_WonderHowWallyIsDoing: @ 820444D
	.string "민진이는 잘 있으려나...$"
	// ミツルは どうしてるかなあ……

PetalburgCity_WallysHouse_Text_PleaseExcuseUs: @ 820446E
	.string "안녕 {PLAYER}{K_AYA}!\n"
	.string "무리하게 불러내서 미안하구나!\p"
	.string "민진이는 잔디마을에 가고 나서\n"
	.string "훨씬 건강해졌단다!\p"
	.string "모두 네 덕분이야!\p"
	.string "무엇보다 이 마을을 떠날 때\n"
	.string "민진이가 포켓몬을 잡는 걸\l"
	.string "도와줬었지?\p"
	.string "민진이는 그 일에 대해\n"
	.string "아주 기뻤다고 하더구나!\p"
	.string "아니 민진이뿐만이 아니지\n"
	.string "아버지인 나도 기쁘단다!\p"
	.string "그 애에게 너 같은\n"
	.string "상냥한 친구가 생긴 게 말이지!\p"
	.string "보답이라고 하긴 좀 그렇다만\n"
	.string "이걸 받아주지 않겠니!$"
	// §あ§お!ｎ
	// むりに よびだして すまなかったね!ｐ
	// ミツルは シダケタウンに いってからｎ
	// すっかり げんきを とりもどしたよ!ｐ
	// それも みんな きみの おかげさ!ｐ
	// なにしろ このまちを でるときにｎ
	// ミツルが ポケモンを つかまえるのをｌ
	// てつだって くれただろう?ｐ
	// あのときの ことが ミツルは とってもｎ
	// うれしかった らしいんだ!ｐ
	// いや ミツル だけじゃないｎ
	// ちちおやの わたしも うれしいよ!ｐ
	// あのこに きみの ようなｎ
	// やさしい ともだちが できたことが ね!ｐ
	// そのおれい という わけでは ないけどｎ
	// これを うけとって くれないか!

PetalburgCity_WallysHouse_Text_SurfGoAllSortsOfPlaces: @ 820461A
	.string "파도타기를 쓸 수 있게 되면\n"
	.string "여러 장소에 갈 수 있게 될 거다!$"
	// なみのりを つかえるように なればｎ
	// いろんな ばしょに いけるように なるよ!

PetalburgCity_WallysHouse_Text_WallyIsComingHomeSoon: @ 8204661
	.string "곧 민진이가 돌아온단다!\n"
	.string "기대되는걸...!$"
	// もうすぐ ミツルが かえってくるぞ!ｎ
	// たのしみだなあ……!

PetalburgCity_WallysHouse_Text_YouMetWallyInEverGrandeCity: @ 8204698
	.string "에엥!? 그랜드시티에서\n"
	.string "민진이를 만났다고...?\p"
	.string "에이 {PLAYER}{K_AYA}-\p"
	.string "아무리 그 애가 건강해졌다고 해도\n"
	.string "그렇게 먼 곳까지\l"
	.string "혼자 갈 수 있을 리가 없잖니...$"
	// ええっ!? サイユウシティでｎ
	// ミツルと であった だって……?ｐ
	// んもう §あ§おってば-ｐ
	// いくら あのこが げんきに なったからってｎ
	// そんな とおくの まち までｌ
	// ひとりで いけるわけ ないよねえ……

PetalburgCity_WallysHouse_Text_WallyWasReallyHappy: @ 8204732
	.string "민진이가 포켓몬 잡았다면서\n"
	.string "엄청 기쁜 듯이 얘기했단다\p"
	.string "그 애의 그런 미소는 오랜만이었지$"
	// ミツルが ポケモンを つかまえた ってｎ
	// すごく うれしそうに はなしていたのｐ
	// あのこの あんな えがお ひさしぶり

PetalburgCity_WallysHouse_Text_WallyLeftWithoutTelling: @ 82047A7
	.string "우리 남편한테는 비밀인데\p"
	.string "사실 민진이가 잔디마을을\n"
	.string "멋대로 나가버렸다고 하더구나...\p"
	.string "그 애는 몸이 약하지만\n"
	.string "의외로 활기찬 성격이니까\l"
	.string "반드시 무사히 돌아올 거라고\l"
	.string "난 믿고 있단다!$"
	// うちの しゅじんには ないしょ だけどｐ
	// じつは ミツルったら シダケタウンをｎ
	// かってに でて いっちゃった らしいの……ｐ
	// あのこ からだは よわかったけどｎ
	// あんがい しっかりした せいかく だからｌ
	// かならず ぶじで かえってくるとｌ
	// わたしは しんじてるわ!

