.set LOCALID_CAPT_STERN, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_GRUNT_1, 3
.set LOCALID_GRUNT_2, 4

SlateportCity_OceanicMuseum_2F_MapScripts:: @ 820BAFF
	.byte 0

SlateportCity_OceanicMuseum_2F_EventScript_CaptStern:: @ 820BB00
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts, MSGBOX_DEFAULT
	closemessage
	playbgm MUS_ENCOUNTER_AQUA, 1
	addobject LOCALID_GRUNT_1
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter
	waitmovement 0
	addobject LOCALID_GRUNT_2
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach
	waitmovement 0
	compare VAR_FACING, DIR_SOUTH
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	compare VAR_FACING, DIR_EAST
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts, MSGBOX_DEFAULT
	compare VAR_FACING, DIR_EAST
	call_if_ne SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou, MSGBOX_DEFAULT
	msgbox SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	compare VAR_FACING, DIR_SOUTH
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth
	compare VAR_FACING, DIR_WEST
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_1, SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat
	msgbox SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_MUSEUM_2, SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat
	applymovement LOCALID_GRUNT_1, SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated
	waitmovement 0
	applymovement LOCALID_GRUNT_1, Common_Movement_WalkInPlaceFastestDown
	applymovement LOCALID_GRUNT_2, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_MeddlingKid, MSGBOX_DEFAULT
	closemessage
	delay 35
	addobject LOCALID_ARCHIE
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter
	applymovement LOCALID_GRUNT_2, SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_ARCHIE, SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_ArchieWarning, MSGBOX_DEFAULT
	closemessage
	savebgm MUS_DUMMY
	fadedefaultbgm
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_ARCHIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	fadescreen FADE_FROM_BLACK
	delay 30
	setflag FLAG_HIDE_SLATEPORT_CITY_OCEANIC_MUSEUM_AQUA_GRUNTS
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs, MSGBOX_DEFAULT
	setvar VAR_0x8004, ITEM_DEVON_GOODS
	call Common_EventScript_PlayerHandedOverTheItem
	msgbox SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo, MSGBOX_DEFAULT
	closemessage
	fadescreen FADE_TO_BLACK
	playfanfare MUS_HEAL
	waitfanfare
	special HealPlayerParty
	removeobject LOCALID_CAPT_STERN
	setflag FLAG_HIDE_ROUTE_110_TEAM_AQUA
	compare VAR_REGISTER_BIRCH_STATE, 0
	call_if_eq SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch
	setflag FLAG_DELIVERED_DEVON_GOODS
	clearflag FLAG_HIDE_ROUTE_116_DEVON_EMPLOYEE
	setflag FLAG_HIDE_RUSTBORO_CITY_DEVON_CORP_3F_EMPLOYEE
	setvar VAR_SLATEPORT_OUTSIDE_MUSEUM_STATE, 1
	fadescreen FADE_FROM_BLACK
	release
	end

SlateportCity_OceanicMuseum_2F_EventScript_ReadyRegisterBirch:: @ 820BC8C
	setvar VAR_REGISTER_BIRCH_STATE, 1
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerFaceGrunts:: @ 820BC92
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_SternFaceGrunts:: @ 820BC9D
	applymovement LOCALID_CAPT_STERN, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntSouth:: @ 820BCA8
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_EventScript_PlayerApproachGruntWest:: @ 820BCB3
	applymovement OBJ_EVENT_ID_PLAYER, SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest
	waitmovement 0
	return

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntSouth: @ 820BCBE
	walk_left
	walk_down
	walk_in_place_fastest_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_PlayerApproachGruntWest: @ 820BCC2
	walk_up
	walk_left
	walk_left
	walk_down
	walk_in_place_fastest_left
	step_end

SlateportCity_OceanicMuseum_2F_Movement_Unused: @ 820BCC8
	walk_up
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_up
	walk_up
	walk_left
	walk_left
	walk_up
	walk_up
	delay_8
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieApproachPlayer: @ 820BCD6
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_ArchieEnter: @ 820BCD8
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntApproachToBattle: @ 820BCE2
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntEnter: @ 820BCE4
	walk_down
	walk_right
	walk_in_place_fastest_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_FirstGruntApproach: @ 820BCE8
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntDefeated: @ 820BCEF
	lock_facing_direction
	walk_left
	unlock_facing_direction
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntEnter: @ 820BCF3
	walk_down
	step_end

SlateportCity_OceanicMuseum_2F_Movement_SecondGruntApproach: @ 820BCF5
	walk_down
	walk_down
	walk_down
	walk_down
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SlateportCity_OceanicMuseum_2F_Movement_GruntMoveForArchie: @ 820BCFE
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_16
	delay_8
	walk_fast_down
	walk_in_place_fastest_up
	step_end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample1:: @ 820BD0A
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_WaterQualitySample2:: @ 820BD13
	msgbox SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_PressureExperiment:: @ 820BD1C
	msgbox SlateportCity_OceanicMuseum_2F_Text_PressureExperiment, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_HoennModel:: @ 820BD25
	msgbox SlateportCity_OceanicMuseum_2F_Text_HoennModel, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_DeepSeawaterDisplay:: @ 820BD2E
	msgbox SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SurfaceSeawaterDisplay:: @ 820BD37
	msgbox SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSTidalReplica:: @ 820BD40
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmarineReplica:: @ 820BD49
	msgbox SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SubmersibleReplica:: @ 820BD52
	msgbox SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_SSAnneReplica:: @ 820BD5B
	msgbox SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica, MSGBOX_SIGN
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron1:: @ 820BD64
	msgbox SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron2:: @ 820BD6D
	msgbox SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum, MSGBOX_NPC
	end

SlateportCity_OceanicMuseum_2F_EventScript_MuseumPatron3:: @ 820BD76
	lock
	faceplayer
	msgbox SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

SlateportCity_OceanicMuseum_2F_Text_ThankYouForTheParts: @ 820BD8D
	.string "응?\n"
	.string "해양관장은 나다만...?\p"
	.string "오오! 그것은 데봉의\n"
	.string "나발명사장에게\l"
	.string "부탁해둔 파츠구나!\p"
	.string "이야- 정말 수고했다!\n"
	.string "덕분에 출발할 수 있을 것 같군...$"

SlateportCity_OceanicMuseum_2F_Text_WellTakeThoseParts: @ 820BE40
	.string "헤헤헤...\p"
	.string "그 파츠\n"
	.string "우리가 가져가겠어!$"

SlateportCity_OceanicMuseum_2F_Text_SternWhoAreYou: @ 820BE69
	.string "해양: 누... 누구냐!\n"
	.string "너희는!?$"

SlateportCity_OceanicMuseum_2F_Text_WereTeamAqua: @ 820BE93
	.string "우리는 아쿠아단!\p"
	.string "리더가 그 파츠를 원하고 있다!\n"
	.string "아무 말 말고 내놔!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt1Defeat: @ 820BEE2
	.string "하으으으...\n"
	.string "어린애에게 당했다!$"

SlateportCity_OceanicMuseum_2F_Text_BossGoingToBeFurious: @ 820BEFA
	.string "...큰일이다!\p"
	.string "이대로라면\n"
	.string "리더에게 혼나고 말 거야...$"

SlateportCity_OceanicMuseum_2F_Text_LetMeTakeCareOfThis: @ 820BF35
	.string "흥! 칠칠치 못한 녀석 같으니!\n"
	.string "나에게 맡겨두라고!$"

SlateportCity_OceanicMuseum_2F_Text_Grunt2Defeat: @ 820BF66
	.string "뭐라고!\n"
	.string "나도 져버렸어!$"

SlateportCity_OceanicMuseum_2F_Text_MeddlingKid: @ 820BF7A
	.string "어떡하지... 파츠를\n"
	.string "뺏지 못하면 곤란하지 않나?\p"
	.string "음...\p"
	.string "설마 어린애에게 방해를 받다니\n"
	.string "눈곱만큼도 생각 못했어$"

SlateportCity_OceanicMuseum_2F_Text_CameToSeeWhatsTakingSoLong: @ 820BFF2
	.string "파츠를 빼앗는데\n"
	.string "언제까지 걸리나 했더니\p"
	.string "이런 꼬마에게\n"
	.string "방해받고 있었나?$"

SlateportCity_OceanicMuseum_2F_Text_ArchieWarning: @ 820C059
	.string "We are TEAM AQUA,\n"
	.string "and we love the sea!\p"
	.string "And I am TEAM AQUA's leader,\n"
	.string "ARCHIE!\p"
	.string "What makes you interfere with us?\p"
	.string "…No! You can't be!\n"
	.string "You're not one of TEAM MAGMA?\p"
	.string "Wait, that can't be right.\n"
	.string "You're not dressed for the part.\p"
	.string "… … … … … …\n"
	.string "… … … … … …\p"
	.string "POKéMON, people… All life depends on\n"
	.string "the sea.\p"
	.string "So, TEAM AQUA is dedicated to\n"
	.string "the expansion of the sea.\p"
	.string "Don't you agree? What we are doing\n"
	.string "is a magnificent undertaking.\p"
	.string "Ah, fine…\n"
	.string "You're still too young to understand\l"
	.string "our noble objective.\p"
	.string "But, I warn you, don't even consider\n"
	.string "interfering with our plans again.\p"
	.string "The consequences will cost you\n"
	.string "dearly!\p"
	.string "And don't you forget it!$"

SlateportCity_OceanicMuseum_2F_Text_SternThankYouForSavingUs: @ 820C2BE
	.string "해양: 넌...\n"
	.string "그렇군 {PLAYER}{K_I}라고 하는구나...\p"
	.string "이거 큰일 날 뻔했어!\n"
	.string "도와줘서 고마워!\p"
	.string "참 그렇지!\n"
	.string "네가 데봉에 부탁해뒀던 파츠를\l"
	.string "가져온 걸 깜빡했구나!$"

SlateportCity_OceanicMuseum_2F_Text_SternIveGotToGo: @ 820C36C
	.string "CAPT. STERN: Whoops!\n"
	.string "There's no time to lose!\p"
	.string "We have to set out on our ocean-floor\n"
	.string "expedition really soon.\p"
	.string "Thanks again, but now I've got\n"
	.string "to go!\p"
	.string "Feel free to wander around and check\n"
	.string "out our facilities, though.$"

SlateportCity_OceanicMuseum_2F_Text_RemindsMeOfAbandonedShip: @ 820C43F
	.string "이 모형 배를 보고 있자니\p"
	.string "무로마을 근처의\n"
	.string "버려진 배가 생각나는구먼...$"

SlateportCity_OceanicMuseum_2F_Text_DontRunInMuseum: @ 820C495
	.string "박물관 안에서는\n"
	.string "뛰어다니면 못써!$"

SlateportCity_OceanicMuseum_2F_Text_WantToRideSubmarine: @ 820C4C2
	.string "잠수정 멋있다-!\n"
	.string "나도 타고 싶어-!$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample1: @ 820C4F9
	.string "“WATER QUALITY SAMPLE 1,” the\n"
	.string "label says.\p"
	.string "The sea is all connected, but the\n"
	.string "water seems to differ by region.$"

SlateportCity_OceanicMuseum_2F_Text_WaterQualitySample2: @ 820C566
	.string "“WATER QUALITY SAMPLE 2,” the\n"
	.string "label says.\p"
	.string "Does the saltiness of seawater differ\n"
	.string "by region, too?$"

SlateportCity_OceanicMuseum_2F_Text_PressureExperiment: @ 820C5C6
	.string "고무로 만들어진 볼이\n"
	.string "팽창과 수축을 반복하고 있다!\p"
	.string "“바닷속에서는 수압이라는\n"
	.string "  물 자체의 무게가 가해집니다\p"
	.string "  얕은 곳에서는 수압이 약하고\n"
	.string "  깊은 곳에서는 몇만 톤에 달하는\l"
	.string "  수압의 영향을 받게 됩니다”$"

SlateportCity_OceanicMuseum_2F_Text_HoennModel: @ 820C6C7
	.string "“호연지방의 모형”\p"
	.string "호연지방 전체를 축소한 모형이다!\p"
	.string "미로마을은 어디쯤일까?$"

SlateportCity_OceanicMuseum_2F_Text_DeepSeawaterDisplay: @ 820C72F
	.string "해수의 흐름에 대한 전시물이다!\p"
	.string "“바다의 바닥 가까운 곳에서는\n"
	.string "  물 온도나 염분의 차이로\l"
	.string "  바닷물이 흘러갑니다”$"

SlateportCity_OceanicMuseum_2F_Text_SurfaceSeawaterDisplay: @ 820C7C1
	.string "해수의 흐름에 대한 전시물이다!\p"
	.string "“바다 표면 근처에서는\n"
	.string "  바람의 힘에 의해\l"
	.string "  바닷물이 흘러갑니다”$"

SlateportCity_OceanicMuseum_2F_Text_SSTidalReplica: @ 820C82F
	.string "“연락선 타이드립호”\p"
	.string "이것은 현재 해양조선소에서\n"
	.string "만들어지는 배의 모형입니다!$"

SlateportCity_OceanicMuseum_2F_Text_SubmarineReplica: @ 820C88B
	.string "“잠수정 해연 1호”\p"
	.string "바다 밑을 조사하기 위한\n"
	.string "고성능 잠수정의 모형입니다!$"

SlateportCity_OceanicMuseum_2F_Text_SumbersibleReplica: @ 820C8E8
	.string "“잠수파드”\p"
	.string "해저에서 작업하기 위한\n"
	.string "무인 소형 파드의 모형입니다!$"

SlateportCity_OceanicMuseum_2F_Text_SSAnneReplica: @ 820C93A
	.string "“상트앙느호”\p"
	.string "세계를 일주하고 있는\n"
	.string "호화 여객선의 모형입니다!$"

