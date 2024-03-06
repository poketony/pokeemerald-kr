.set LOCALID_GRUNT, 1

SeafloorCavern_Entrance_MapScripts:: @ 823446E
	map_script MAP_SCRIPT_ON_RESUME, SeafloorCavern_Entrance_OnResume
	.byte 0

SeafloorCavern_Entrance_OnResume: @ 8234474
	setdivewarp MAP_UNDERWATER_SEAFLOOR_CAVERN, 255, 6, 5
	setescapewarp MAP_UNDERWATER_SEAFLOOR_CAVERN, 255, 6, 5
	end

SeafloorCavern_Entrance_EventScript_Grunt:: @ 8234485
	lockall
	compare VAR_HAS_TALKED_TO_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, 1
	goto_if_eq SeafloorCavern_Entrance_EventScript_GruntSpeechShort
	waitse
	playse SE_PIN
	applymovement LOCALID_GRUNT, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_GRUNT, Common_Movement_Delay48
	waitmovement 0
	delay 20
	compare VAR_FACING, DIR_WEST
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest
	compare VAR_FACING, DIR_EAST
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth
	delay 30
	setvar VAR_HAS_TALKED_TO_SEAFLOOR_CAVERN_ENTRANCE_GRUNT, 1
	copyobjectxytoperm LOCALID_GRUNT
	msgbox SeafloorCavern_Entrance_Text_HearMagmaNearMossdeep, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	releaseall
	end

SeafloorCavern_Entrance_EventScript_GruntSpeechShort:: @ 82344ED
	compare VAR_FACING, DIR_WEST
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest
	compare VAR_FACING, DIR_EAST
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast
	compare VAR_FACING, DIR_NORTH
	call_if_eq SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth
	msgbox SeafloorCavern_Entrance_Text_HearMagmaNearMossdeepShort, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	releaseall
	end

SeafloorCavern_Entrance_EventScript_GruntFacePlayerEast:: @ 8234523
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SeafloorCavern_Entrance_EventScript_GruntFacePlayerWest:: @ 823452E
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	return

SeafloorCavern_Entrance_EventScript_GruntFacePlayerNorth:: @ 8234539
	applymovement LOCALID_GRUNT, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

SeafloorCavern_Entrance_Text_HearMagmaNearMossdeep: @ 8234544
	.string "아-----앗!\n"
	.string "본 적 있는 얼굴!\p"
	.string "이런 곳까지 왔다는 건\n"
	.string "또 우리들을 방해하려고!?\p"
	.string "너 같은 녀석이 아쿠아단에게\n"
	.string "반항하다니\l"
	.string "100억만 년은 빠르다고-!\p"
	.string "너에겐 마그마단이 어울려!\p"
	.string "...그러고 보니 이끼시티 근처에\n"
	.string "마그마단이 나타났다는데\p"
	.string "그 녀석들...\n"
	.string "정--말 바다하고 안 어울려!$"
	@ あ-----っ!ｎ
	@ みおぼえの ある そのかおは!ｐ
	@ こんな ところまで きたって ことはｎ
	@ また オレたちの ジャマをしに!?ｐ
	@ おまえ ごときが アクアだんにｎ
	@ はむかおう だなんてｌ
	@ 100おくまんねん はえ-んだよ!ｐ
	@ おまえにゃ マグマだんが おにあいさ!ｐ
	@ ……そういえば トクサネの ちかくでｎ
	@ マグマだんを みかけたっけなｐ
	@ あいつら……ｎ
	@ ほんっと--に うみが にあわねえぜ!

SeafloorCavern_Entrance_Text_HearMagmaNearMossdeepShort: @ 82346C8
	.string "너 같은 녀석이 아쿠아단에게\n"
	.string "반항하다니\l"
	.string "100억만 년은 빠르다고-!\p"
	.string "너에겐 마그마단이 어울려!\p"
	.string "...그러고 보니 이끼시티 근처에\n"
	.string "마그마단이 나타났다는데\p"
	.string "녀석들...\n"
	.string "정--말 바다하고 안 어울려!$"
	@ おまえ ごときが アクアだんにｎ
	@ はむかおう だなんてｌ
	@ 100おくまんねん はえ-んだよ!ｐ
	@ おまえにゃ マグマだんが おにあいさ!ｐ
	@ ……そういえば トクサネの ちかくでｎ
	@ マグマだんを みかけたっけなｐ
	@ あいつら……ｎ
	@ ほんっと--に うみが にあわねえぜ!

