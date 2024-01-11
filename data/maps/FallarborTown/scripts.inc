FallarborTown_MapScripts:: @ 81EB1FA
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_OnTransition
	.byte 0

FallarborTown_OnTransition: @ 81EB200
	setflag FLAG_VISITED_FALLARBOR_TOWN
	setvar VAR_CONTEST_HALL_STATE, 0
	clearflag FLAG_CONTEST_SKETCH_CREATED
	end

FallarborTown_EventScript_ExpertM:: @ 81EB20C
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_EVIL_TEAM_MT_CHIMNEY, FallarborTown_EventScript_ExpertMNormal
	msgbox FallarborTown_Text_ShadyCharactersCozmosHome, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_ExpertMNormal:: @ 81EB221
	msgbox FallarborTown_Text_RegionKnownForMeteors, MSGBOX_DEFAULT
	release
	end

FallarborTown_EventScript_Girl:: @ 81EB22B
	msgbox FallarborTown_Text_MyPreciousAzurill, MSGBOX_NPC
	end

FallarborTown_EventScript_Gentleman:: @ 81EB234
	msgbox FallarborTown_Text_HaveYouChallengedFlannery, MSGBOX_NPC
	end

FallarborTown_EventScript_Azurill:: @ 81EB23D
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZURILL, 0
	msgbox FallarborTown_Text_Azurill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

FallarborTown_EventScript_BattleTentSign:: @ 81EB250
	msgbox FallarborTown_Text_BattleTentSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_TownSign:: @ 81EB259
	msgbox FallarborTown_Text_TownSign, MSGBOX_SIGN
	end

FallarborTown_EventScript_MoveTutorSign:: @ 81EB262
	msgbox FallarborTown_Text_MoveTutorSign, MSGBOX_SIGN
	end

FallarborTown_Text_ShadyCharactersCozmosHome: @ 81EB26B
	.string "뭔가 뭔가!?\p"
	.string "공석박사의 집에\n"
	.string "수상한 사람들이\l"
	.string "드나들던 것 같은데...$"
	// なんだ なんだ!?ｐ
	// ソライシはかせの いえにｎ
	// あやしげな じんぶつがｌ
	// ではいり しておった ようだが……

FallarborTown_Text_RegionKnownForMeteors: @ 81EB2DE
	.string "여기 일대는\n"
	.string "옛날부터 운석이 많아서 말이지\p"
	.string "유성의 폭포도 운석이 떨어져서\n"
	.string "만들어졌다고 전해지고 있단다$"
	// ここいら いったいはｎ
	// むかしから いんせきが おおくてなｐ
	// りゅうせいのたきも いんせきが おちてｎ
	// できたとか そう いわれておる

FallarborTown_Text_MyPreciousAzurill: @ 81EB35F
	.string "자! 이것 봐!\n"
	.string "내 소중한 루리리!\p"
	.string "매끈매끈하고 쓰다듬으면 푹신푹신해!$"
	// ほら! みてちょうだい!ｎ
	// わたしの たいせつな ルリリ!ｐ
	// ツヤツヤの ナデナデの フカフカよ!

FallarborTown_Text_Azurill: @ 81EB3B5
	.string "루리리: 루-리-루-$"
	// ルリリ『る-り-る-

FallarborTown_Text_HaveYouChallengedFlannery: @ 81EB3CA
	.string "용암마을의 체육관 관장\n"
	.string "민지하고 배틀했니?\p"
	.string "그 아이의 할아버지는 굉장했지\n"
	.string "듣자 하니 포켓몬리그의\l"
	.string "사천왕이라고 했었나\p"
	.string "분명 민지도 이제부터\n"
	.string "훌륭한 트레이너가 되겠지$"
	// フエンタウンの ジムリ-ダ-ｎ
	// アスナとは たたかったかね?ｐ
	// あのこの おじいさんは すごかったよｎ
	// なんでも ポケモンリ-グのｌ
	// してんのう だった らしいからねｐ
	// きっと アスナも これからｎ
	// すばらしい トレ-ナ-に なるだろうね

FallarborTown_Text_BattleTentSign: @ 81EB4C2
	.string "배틀텐트 단풍마을 회장\n"
	.string "모아라! 최강 팀$"
	// バトルテント ハジツゲタウン かいじょうｎ
	// つどえ! さいきょう チ-ム
	
FallarborTown_Text_TownSign: @ 81EB4FE
	.string "여기는 단풍마을\n"
	.string "작은 밭이 있는 농촌$"
	// ここは ハジツゲ タウンｎ
	// ちいさな はたけが ある のうそん

FallarborTown_Text_MoveTutorSign: @ 81EB534
	.string "“기술마니아의 집”\n"
	.string "포켓몬 기술을 가르쳐 드립니다!$"
	// 「わざおしえマニアの いえ」ｎ
	// ポケモンの わざ おしえます!

