.set LOCALID_CURATOR, 2
.set LOCALID_ARTIST_2, 8

LilycoveCity_LilycoveMuseum_1F_MapScripts:: @ 8218CB8
	.byte 0

LilycoveCity_LilycoveMuseum_1F_EventScript_Greeter:: @ 8218CB9
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Curator:: @ 8218CC2
	lockall
	applymovement LOCALID_CURATOR, Common_Movement_FacePlayer
	message LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings
	waitmessage
	multichoice 20, 8, MULTI_VIEWED_PAINTINGS, 1
	compare VAR_RESULT, 0
	goto_if_eq LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings
	compare VAR_RESULT, 1
	goto_if_eq LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotYet:: @ 8218CEC
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SawPaintings:: @ 8218CF5
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested
	compare VAR_RESULT, YES
	goto_if_eq LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NotInterested:: @ 8218D14
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat, MSGBOX_SIGN
	releaseall
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_InterestedInPaintings:: @ 8218D1E
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe, MSGBOX_SIGN
	applymovement LOCALID_CURATOR, LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs
	waitmovement 0
	removeobject LOCALID_CURATOR
	switch VAR_FACING
	case DIR_NORTH, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth
	case DIR_WEST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest
	case DIR_EAST, LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorNorth:: @ 8218D5A
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 255, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorWest:: @ 8218D6F
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 255, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FollowCuratorEast:: @ 8218D84
	lockall
	applymovement OBJ_EVENT_ID_PLAYER, LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast
	waitmovement 0
	warp MAP_LILYCOVE_CITY_LILYCOVE_MUSEUM_2F, 255, 11, 8
	waitstate
	end

LilycoveCity_LilycoveMuseum_1F_Movement_CuratorEnterStairs: @ 8218D99
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorWest: @ 8218D9B
	walk_left
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorEast: @ 8218D9E
	walk_right
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_Movement_FollowCuratorNorth: @ 8218DA1
	walk_up
	walk_up
	step_end

LilycoveCity_LilycoveMuseum_1F_EventScript_OldPainting:: @ 8218DA4
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FantasyPainting:: @ 8218DAD
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_WomanPainting:: @ 8218DB6
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_LegendaryPokemonPainting:: @ 8218DBF
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_GrassPokemonPainting:: @ 8218DC8
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_BerryPainting:: @ 8218DD1
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_EventScript_BirdSculpture:: @ 8218DDA
	msgbox LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PokeBallSculpture:: @ 8218DE3
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_StoneTablet:: @ 8218DEC
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_SchoolKidM:: @ 8218DF5
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist1:: @ 8218DFE
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_NinjaBoy:: @ 8218E07
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman1:: @ 8218E10
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable, MSGBOX_SIGN
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Woman2:: @ 8218E19
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_PsychicM:: @ 8218E22
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_Artist2:: @ 8218E2B
	lock
	faceplayer
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARTIST_2, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

LilycoveCity_LilycoveMuseum_1F_EventScript_FatMan:: @ 8218E42
	msgbox LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination, MSGBOX_NPC
	end

LilycoveCity_LilycoveMuseum_1F_Text_WelcomeToLilycoveMuseum: @ 8218E4B
	.string "해안 미술관에 어서 오세요!\p"
	.string "포켓몬들을 그린\n"
	.string "굉장한 명화들을\l"
	.string "천천히 관람해 주세요!$"
	@ ミナモ びじゅつかん へ ようこそ!ｐ
	@ ポケモンたちを えがいたｎ
	@ すばらしい めいがの かずかずをｌ
	@ ゆっくり ごらんに なって くださいね!

LilycoveCity_LilycoveMuseum_1F_Text_ImCuratorHaveYouViewedOurPaintings: @ 8218EBC
	.string "전 이 미술관의\n"
	.string "관장이지요!\p"
	.string "당신은 젊은데도 미술관에\n"
	.string "오시다니 감탄했습니다!\p"
	.string "이제 그림 관람은 끝나신 건가요?$"
	@ わたしは この びじゅつかんのｎ
	@ かんちょう です!ｐ
	@ あなたは おわかいのに びじゅつかんにｎ
	@ いらっしゃる とは かんしん ですね!ｐ
	@ もう えは ごらんに なりましたか?

LilycoveCity_LilycoveMuseum_1F_Text_NotDisturbYouTakeYourTime: @ 8218F5C
	.string "그럼 방해 안 할 테니\n"
	.string "천천히 봐 주십시오!$"
	@ では おじゃま いたしません からｎ
	@ ゆっくり みていって ください!

LilycoveCity_LilycoveMuseum_1F_Text_HaveYouAnInterestInPaintings: @ 8218F98
	.string "으음? 당신은\n"
	.string "포켓몬 트레이너인 것 같군요\p"
	.string "그림에도 흥미가 있으신가요?$"
	@ おや? あなたはｎ
	@ ポケモントレ-ナ-さん みたい ですねｐ
	@ えにも きょうみが おあり ですか?

LilycoveCity_LilycoveMuseum_1F_Text_HonoredYoudVisitInSpiteOfThat: @ 8218FF8
	.string "그렇군요...\p"
	.string "그럼에도 일부러 와주시다니\n"
	.string "영광입니다$"
	@ そうですか……ｐ
	@ それなのに わざわざ おいで くださってｎ
	@ こうえい ですよ

LilycoveCity_LilycoveMuseum_1F_Text_ExcellentCanYouComeWithMe: @ 8219035
	.string "그렇군요! 그림을 좋아하시는군요!\p"
	.string "그럼 잠시 저를\n"
	.string "따라와 주시지 않겠습니까?$"
	@ そうですか! えが おすき ですか!ｐ
	@ では ちょっと わたしにｎ
	@ ついてきて ください ませんか?

LilycoveCity_LilycoveMuseum_1F_Text_VeryOldPainting: @ 8219080
	.string "옛날 사람이 그린 그림이다!\n"
	.string "부분 부분 물감이 벗겨져 있다$"
	@ むかしの ひとが かいた えだ!ｎ
	@ ところどころ えのぐが はがれてる

LilycoveCity_LilycoveMuseum_1F_Text_OddLandscapeFantasticScenery: @ 82190BF
	.string "본 적 없는 신비한\n"
	.string "경치가 그려져 있다$"
	@ みたことも ないような ふしぎなｎ
	@ けしきが えがかれている

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBeautifulWoman: @ 82190F9
	.string "무릎에 포켓몬을 올려놓고 미소 짓는\n"
	.string "아름다운 여성이 그려져 있다$"
	@ ひざに ポケモンを のせて ほほえむｎ
	@ うつくしい じょせいが えがかれている

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfLegendaryPokemon: @ 8219142
	.string "옛날 사람이 상상해서 그린\n"
	.string "전설의 포켓몬의 그림이다!$"
	@ むかしの ひとが そうぞうで かいたｎ
	@ でんせつの ポケモンの えだ!

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfGrassPokemon: @ 82191A2
	.string "바람에 나부끼며 기분 좋은 듯이\n"
	.string "흔들리는 풀포켓몬이 그려져 있다$"
	@ かぜに なびいて きもち よさそうにｎ
	@ ゆれている くさポケモンが えがかれている

LilycoveCity_LilycoveMuseum_1F_Text_PaintingOfBerries: @ 821920D
	.string "맛있어 보이는 나무열매가 그려져 있다\n"
	.string "배가 고파 온다!$"
	@ おいしそうな きのみが えがかれているｎ
	@ おなかが すいて きそう!

LilycoveCity_LilycoveMuseum_Text_BirdPokemonSculptureReplica: @ 8219260
	.string "고대의 새포켓몬을 조각한\n"
	.string "유명한 조각상의 레플리카다!$"
	@ こだいの とりポケモンを ほったｎ
	@ ゆうめいな ちょうこくの レプリカだ!

LilycoveCity_LilycoveMuseum_1F_Text_BigPokeBallCarvedFromStone: @ 82192AA
	.string "검은 돌로 만들어진\n"
	.string "커다란 몬스터볼이다!\l"
	.string "옛날 축제 때 사용되었다고 한다$"
	@ くろい いしで つくられたｎ
	@ おおきい モンスタ-ボ-ルだ!ｌ
	@ むかし おまつりに つかって いたらしい

LilycoveCity_LilycoveMuseum_1F_Text_StoneTabletWithAncientText: @ 8219311
	.string "포켓몬의 모습과 알 수 없는 문자가\n"
	.string "촘촘히 새겨져 있는 석판이다!$"
	@ ポケモンの すがたと しらない もじがｎ
	@ こまかく ほられてある せきばんだ!

LilycoveCity_LilycoveMuseum_1F_Text_WorksOfMagnificence: @ 821938C
	.string "음- 정말 멋진 작품이야...$"
	@ う-ん すばらしい さくひんだ……

LilycoveCity_LilycoveMuseum_1F_Text_MustntForgetLoveForFineArts: @ 82193B4
	.string "포켓몬 승부도 좋지만\p"
	.string "예술을 사랑하는 마음도\n"
	.string "잊지 말아야 해!$"
	@ ポケモン しょうぶも いいけどｐ
	@ げいじゅつを あいする きもちもｎ
	@ わすれずに いないとね!

LilycoveCity_LilycoveMuseum_1F_Text_ThisMuseumIsInspiration: @ 821941A
	.string "이 미술관은\n"
	.string "대단한 그림을 많이 볼 수 있고\l"
	.string "관장도 멋있는 사람이라서\l"
	.string "우리 화가들도\l"
	.string "정말 동경하는 장소야$"
	@ この びじゅつかんはｎ
	@ すごい えが たくさん みられるしｌ
	@ かんちょうも すばらしい ひとだしｌ
	@ ぼくたち がかの あいだ でもｌ
	@ あこがれの ばしょ なんだよ

LilycoveCity_LilycoveMuseum_1F_Text_ThisLadyIsPretty: @ 82194BA
	.string "여기 있는 여자 예쁘다-!\n"
	.string "엄마 같아-!$"
	@ この おんなの ひと きれ-い!ｎ
	@ ママみた-い!

LilycoveCity_LilycoveMuseum_1F_Text_ThisPokemonIsAdorable: @ 82194E1
	.string "이 포켓몬 너무 귀엽다!\n"
	.string "우리 아이 같아!$"
	@ この ポケモン かわいいわ!ｎ
	@ うちの ぼうや みたい!

LilycoveCity_LilycoveMuseum_1F_Text_HeardMuseumGotNewPaintings: @ 8219515
	.string "이 미술관에 새로운 그림이\n"
	.string "전시된다고 하길래\l"
	.string "바로 보러 왔어!\p"
	.string "새로운 그림은 2층에 있는 건가?$"
	@ この びじゅつかんに あたらしい えがｎ
	@ はいったって きいたからｌ
	@ さっそく みにきて みたの!ｐ
	@ あたらしい えは 2かい かな?

LilycoveCity_LilycoveMuseum_1F_Text_CuratorHasBeenCheerful: @ 821959B
	.string "최근 관장의 기분이\n"
	.string "굉장히 좋은 거 같아\p"
	.string "뭔가 좋은 일이라도 있었나 봐$"
	@ さいきん かんちょうの ごきげんがｎ
	@ とても いいみたいｐ
	@ いいこと あったんだね きっと

LilycoveCity_LilycoveMuseum_1F_Text_AimToSeeGreatPaintings: @ 82195FF
	.string "여기서 좋은 그림을 많이 보고\n"
	.string "공부해 둬야지!\p"
	.string "언젠가 이곳에 내 작품을\n"
	.string "전시하는 게 꿈이야!$"
	@ ここで いい えを たくさん みてｎ
	@ べんきょう しないとな!ｐ
	@ ここに いつか じぶんの さくひんをｎ
	@ かざって もらうのが ゆめ なんだ!

LilycoveCity_LilycoveMuseum_1F_Text_MuseumTouristDestination: @ 821967A
	.string "이 미술관도 완전히 해안시티의...\n"
	.string "...아니 호연지방의\l"
	.string "관광 명소가 됐어!\p"
	.string "들은 얘기로는\n"
	.string "한 명의 트레이너가 2층의 그림을\l"
	.string "모아준 것 같아!$"
	@ この びじゅつかんも すっかり ミナモのｎ
	@ ……いや ホウエンちほうのｌ
	@ かんこう めいしょに なったねえ!ｐ
	@ きいた はなしだとｎ
	@ ひとりの トレ-ナ-が 2かいの えをｌ
	@ そろえて くれた らしいよ!

