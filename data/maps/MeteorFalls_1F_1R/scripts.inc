.set LOCALID_MAGMA_GRUNT_1, 5
.set LOCALID_MAGMA_GRUNT_2, 6
.set LOCALID_ARCHIE, 7
.set LOCALID_AQUA_GRUNT_1, 8
.set LOCALID_AQUA_GRUNT_2, 9

MeteorFalls_1F_1R_MapScripts:: @ 822BD2A
	map_script MAP_SCRIPT_ON_LOAD, MeteorFalls_1F_1R_OnLoad
	.byte 0

MeteorFalls_1F_1R_OnLoad: @ 822BD30
	call_if_set FLAG_SYS_GAME_CLEAR, MeteorFalls_1F_1R_EventScript_OpenStevensCave
	end

MeteorFalls_1F_1R_EventScript_OpenStevensCave:: @ 822BD3A
	setmetatile 4, 1, METATILE_MeteorFalls_CaveEntrance_Top, 1
	setmetatile 3, 2, METATILE_MeteorFalls_CaveEntrance_Left, 1
	setmetatile 4, 2, METATILE_MeteorFalls_CaveEntrance_Bottom, 0
	setmetatile 5, 2, METATILE_MeteorFalls_CaveEntrance_Right, 1
	return

MeteorFalls_1F_1R_EventScript_MagmaStealsMeteoriteScene:: @ 822BD5F
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
	waitmovement 0
	delay 30
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_WithThisMeteorite, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFastestUp
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	playse SE_PIN
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_Delay48
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_HoldItRightThereMagma, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	addobject LOCALID_ARCHIE
	addobject LOCALID_AQUA_GRUNT_1
	addobject LOCALID_AQUA_GRUNT_2
	playbgm MUS_ENCOUNTER_AQUA, 0
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieArrive
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive
	waitmovement 0
	applymovement LOCALID_MAGMA_GRUNT_1, Common_Movement_WalkInPlaceFastestLeft
	applymovement LOCALID_MAGMA_GRUNT_2, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay
	applymovement LOCALID_MAGMA_GRUNT_1, MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit
	applymovement LOCALID_MAGMA_GRUNT_2, MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit
	waitmovement 0
	removeobject LOCALID_MAGMA_GRUNT_1
	removeobject LOCALID_MAGMA_GRUNT_2
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieSeenYouBefore, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo, MSGBOX_DEFAULT
	applymovement LOCALID_ARCHIE, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox MeteorFalls_1F_1R_Text_ArchieFarewell, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, MeteorFalls_1F_1R_Movement_ArchieExit
	applymovement LOCALID_AQUA_GRUNT_1, MeteorFalls_1F_1R_Movement_AquaGrunt1Exit
	applymovement LOCALID_AQUA_GRUNT_2, MeteorFalls_1F_1R_Movement_AquaGrunt2Exit
	waitmovement 0
	fadedefaultbgm
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_AQUA_GRUNT_1
	removeobject LOCALID_AQUA_GRUNT_2
	setflag FLAG_HIDE_ROUTE_112_TEAM_MAGMA
	setflag FLAG_MET_ARCHIE_METEOR_FALLS
	setflag FLAG_HIDE_FALLARBOR_TOWN_BATTLE_TENT_SCOTT
	setvar VAR_METEOR_FALLS_STATE, 1
	releaseall
	end

MeteorFalls_1F_1R_Movement_MagmaGruntApproachPlayer: @ 822BEC0
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt1Exit: @ 822BEC4
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_MagmaGrunt2Exit: @ 822BECE
	walk_fast_up
	walk_fast_up
	walk_fast_up
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieArrive: @ 822BED9
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Arrive: @ 822BEE0
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Arrive: @ 822BEE8
	delay_16
	delay_16
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieExit: @ 822BEF0
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_ArchieApproachPlayer: @ 822BEF8
	walk_right
	walk_right
	walk_up
	walk_up
	walk_in_place_fastest_left
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1Exit: @ 822BEFE
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt1ApproachArchie: @ 822BF08
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2Exit: @ 822BF0D
	walk_up
	walk_up
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

MeteorFalls_1F_1R_Movement_AquaGrunt2ApproachArchie: @ 822BF18
	walk_right
	walk_right
	walk_right
	walk_in_place_fastest_up
	step_end

MeteorFalls_1F_1R_Movement_PushPlayerOutOfWay: @ 822BF1D
	walk_in_place_fastest_down
	delay_4
	walk_in_place_fastest_right
	lock_facing_direction
	walk_left
	unlock_facing_direction
	face_right
	step_end

MeteorFalls_1F_1R_EventScript_ProfCozmo:: @ 822BF25
	lock
	faceplayer
	goto_if_set FLAG_MET_PROF_COZMO, MeteorFalls_1F_1R_EventScript_MetCozmo
	setflag FLAG_MET_PROF_COZMO
	msgbox MeteorFalls_1F_1R_Text_MeetProfCozmo, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_EventScript_MetCozmo:: @ 822BF3D
	msgbox MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney, MSGBOX_DEFAULT
	release
	end

MeteorFalls_1F_1R_Text_WithThisMeteorite: @ 822BF47
	.string "우효효...!\p"
	.string "이 운석이 있으면\n"
	.string "굴뚝산의 그 녀석이...$"
	// ウヒョヒョ……!ｐ
	// この いんせきが あればｎ
	// えんとつやまの アイツが……

MeteorFalls_1F_1R_Text_DontExpectMercyFromMagma: @ 822BF84
	.string "우효?\p"
	.string "네가 누군지는 모르겠지만\n"
	.string "마그마단의 방해를 한다면\l"
	.string "용서하지 않겠다!$"
	// ウヒョ?ｐ
	// だれだか しらないがｎ
	// マグマだんの ジャマを するきならｌ
	// ようしゃ しないぜ!

MeteorFalls_1F_1R_Text_HoldItRightThereMagma: @ 822BFE4
	.string "멈춰라! 마그마단!\p"
	.string "세계를 너희들 마음대로\n"
	.string "하겠다니 착각하지 마라!$"
	// まてっ! マグマだん!ｐ
	// せかいを おまえらの おもいどおりにｎ
	// できるなんて おおまちがいだ!

MeteorFalls_1F_1R_Text_BeSeeingYouTeamAqua: @ 822C04E
	.string "우효효...!\n"
	.string "아쿠아단까지 온 건가!\p"
	.string "하나하나 상대하는 것도\n"
	.string "귀찮군...\p"
	.string "뭐 됐어!\n"
	.string "운석은 손에 넣었고\l"
	.string "서둘러 굴뚝산에 가볼까!\p"
	.string "우효효!\n"
	.string "안녕이다! 멍청한 아쿠아단!$"
	// ウヒョヒョ……!ｎ
	// アクアだん まで やってきたのかよ!ｐ
	// いちいち あいてを してやるのもｎ
	// めんどうだな……ｐ
	// まあ いいや!ｎ
	// いんせきは てに いれたしｌ
	// さっさと えんとつやまに いくか!ｐ
	// ウヒョヒョ!ｎ
	// あばよ! まぬけな アクアだん!

MeteorFalls_1F_1R_Text_ArchieSeenYouBefore: @ 822C11C
	.string "아강: 너하고는 분명...\n"
	.string "잿빛도시의 박물관에서 만났었지\p"
	.string "그런가 {PLAYER}{K_I}라고 하는군\p"
	.string "그때는 마그마단의 조무래기라고\n"
	.string "생각했었는데\l"
	.string "흠...\l"
	.string "이상한 녀석이로군...\p"
	.string "마그마단이라는 건\n"
	.string "땅을 넓히려고 하면서\l"
	.string "파괴활동을 계속하는\l"
	.string "위험한 집단이다!\p"
	.string "바다를 사랑하는 우리 아쿠아단의\n"
	.string "숙적인 거지!$"
	// アオギリ『おまえとは たしか……ｎ
	// カイナの はくぶつかんでも あったがｐ
	// そうか §あと いうのかｐ
	// あのときは マグマだんの したっぱだとｎ
	// おもったんだがｌ
	// ふん……ｌ
	// おかしな やつだな……ｐ
	// マグマだん というのはｎ
	// りくちをふやす などと いってはｌ
	// はかいかつどうを くりかえすｌ
	// きけんな しゅうだんだ!ｐ
	// うみを あいする われわれ アクアだんのｎ
	// しゅくてき なのだよ!

MeteorFalls_1F_1R_Text_BossWeShouldChaseMagma: @ 822C268
	.string "아강님\n"
	.string "마그마단을 쫓아가야죠...$"
	// アオギリさまｎ
	// マグマだんを おいかけないと……

MeteorFalls_1F_1R_Text_ArchieYesNoTellingWhatMagmaWillDo: @ 822C292
	.string "아강: 그래!\p"
	.string "마그마단 녀석들이 굴뚝산에서\n"
	.string "무슨 짓을 할지 모른다!$"
	// アオギリ『そうだな!ｐ
	// マグマだんの やつら えんとつやまでｎ
	// なにを しでかすか わからない!

MeteorFalls_1F_1R_Text_ArchieFarewell: @ 822C2FC
	.string "아강: {PLAYER}... 너도\n"
	.string "마그마단은 조심하도록 해라\p"
	.string "그럼 작별이다!$"
	// アオギリ『§あ…… おまえもｎ
	// マグマだんには ようじん するんだなｐ
	// では さらばだ!

MeteorFalls_1F_1R_Text_MeetProfCozmo: @ 822C342
	.string "난 공석...\p"
	.string "마그마단에게 부탁받아서\n"
	.string "여기까지 안내해줬는데\l"
	.string "속아서 운석을\l"
	.string "빼앗겨버렸어...\p"
	.string "게다가 아쿠아단이라고 하는\n"
	.string "비슷한 녀석들까지 나타나서\l"
	.string "뭐가 어떻게 된 건지...\p"
	.string "그건 그렇고 마그마단은\n"
	.string "운석 같은 걸 가지고\l"
	.string "굴뚝산에서\l"
	.string "뭘 하려는 걸까...?$"
	// ぼく ソライシ……ｐ
	// マグマだんに たのまれてｎ
	// ここまで あんない してきたんだけどｌ
	// だまされてｌ
	// いんせき とられちゃったよ……ｐ
	// おまけに アクアだん っていうｎ
	// にたような れんちゅうまで あらわれてｌ
	// もう なにが なんだか……ｐ
	// それにしても マグマだんはｎ
	// いんせき なんか もっていってｌ
	// えんとつやまでｌ
	// なにする つもり なんだろう……?

MeteorFalls_1F_1R_Text_WhatsTeamMagmaDoingAtMtChimney: @ 822C47D
	.string "공석: 그건 그렇고 마그마단은\n"
	.string "운석 같은 걸 가지고\l"
	.string "굴뚝산에서\l"
	.string "뭘 하려는 걸까...?$"
	// ソライシ『それにしても マグマだんはｎ
	// いんせき なんか もっていってｌ
	// えんとつやまでｌ
	// なにする つもり なんだろう……?
