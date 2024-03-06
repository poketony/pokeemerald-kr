BerryTreeScript:: @ 82742F9
	special ObjectEventInteractionGetBerryTreeData
	switch VAR_0x8004
	case BERRY_STAGE_SPARKLING, BerryTree_EventScript_Sparkling
	case BERRY_STAGE_NO_BERRY, BerryTree_EventScript_CheckSoil
	case BERRY_STAGE_PLANTED, BerryTree_EventScript_CheckBerryStage1
	case BERRY_STAGE_SPROUTED, BerryTree_EventScript_CheckBerryStage2
	case BERRY_STAGE_TALLER, BerryTree_EventScript_CheckBerryStage3
	case BERRY_STAGE_FLOWERING, BerryTree_EventScript_CheckBerryStage4
	case BERRY_STAGE_BERRIES, BerryTree_EventScript_CheckBerryFullyGrown
	end

BerryTree_EventScript_Sparkling:: @ 827434F
	lockall
	message BerryTree_Text_ExclamationPoint
	waitmessage
	waitbuttonpress
	releaseall
	end

BerryTree_EventScript_CheckSoil:: @ 8274359
	lock
	faceplayer
	specialvar VAR_RESULT, PlayerHasBerries
	compare VAR_RESULT, TRUE
	goto_if_eq BerryTree_EventScript_WantToPlant
	message BerryTree_Text_ItsSoftLoamySoil
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_WantToPlant:: @ 8274374
	msgbox BerryTree_Text_WantToPlant, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_ChooseBerryToPlant
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_CancelPlanting
	end

BerryTree_EventScript_ChooseBerryToPlant:: @ 8274393
	fadescreen FADE_TO_BLACK
	closemessage
	special Bag_ChooseBerry
	waitstate
	compare VAR_ITEM_ID, 0
	goto_if_eq BerryTree_EventScript_CancelPlanting
	removeitem VAR_ITEM_ID
	call BerryTree_EventScript_PlantBerry

BerryTree_EventScript_CancelPlanting:: @ 82743AF
	release
	end

BerryTree_EventScript_CheckBerryStage1:: @ 82743B1
	lockall
	special ObjectEventInteractionGetBerryCountString
	message BerryTree_Text_BerryGrowthStage1
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage2:: @ 82743C1
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage2
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage3:: @ 82743D1
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage3
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

BerryTree_EventScript_CheckBerryStage4:: @ 82743E1
	call BerryTree_EventScript_GetCareAdverb
	lockall
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_BerryGrowthStage4
	waitmessage
	waitbuttonpress
	goto BerryTree_EventScript_WantToWater

@ VAR_0x8005 here is the number of times watered
@ Buffered by ObjectEventInteractionGetBerryTreeData
BerryTree_EventScript_GetCareAdverb:: @ 82743F6
	compare VAR_0x8005, 0
	goto_if_eq BerryTree_EventScript_SetAdverbPoor
	compare VAR_0x8005, 4
	goto_if_eq BerryTree_EventScript_SetAdverbGreat
	bufferstring 1, BerryTree_Text_CareAdverbGood
	return

BerryTree_EventScript_SetAdverbGreat:: @ 8274413
	bufferstring 1, BerryTree_Text_CareAdverbGreat
	return

BerryTree_EventScript_SetAdverbPoor:: @ 827441A
	bufferstring 1, BerryTree_Text_CareAdverbPoor
	return

@ VAR_0x8006 here is the number of berries
BerryTree_EventScript_CheckBerryFullyGrown:: @ 8274421
	buffernumberstring 1, VAR_0x8006
	lock
	faceplayer
	special ObjectEventInteractionGetBerryCountString
	msgbox BerryTree_Text_WantToPick, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_PickBerry
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_CancelPickingBerry

BerryTree_EventScript_PickBerry:: @ 8274448
	special ObjectEventInteractionPickBerryTree
	compare VAR_0x8004, 0
	goto_if_eq BerryTree_EventScript_BerryPocketFull
	special IncrementDailyPickedBerries
	special ObjectEventInteractionRemoveBerryTree
	message BerryTree_Text_PickedTheBerry
	playfanfare MUS_OBTAIN_BERRY
	waitmessage
	waitfanfare
	waitbuttonpress
	message BerryTree_Text_PutAwayBerry
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_BerryPocketFull:: @ 8274470
	message BerryTree_Text_BerryPocketFull
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_CancelPickingBerry:: @ 8274479
	message BerryTree_Text_BerryLeftUnpicked
	waitmessage
	waitbuttonpress
	release
	end

BerryTree_EventScript_ItemUsePlantBerry:: @ 8274482
	lockall
	special ObjectEventInteractionGetBerryTreeData
	call BerryTree_EventScript_PlantBerry
	releaseall
	end

BerryTree_EventScript_WantToWater:: @ 827448D
	checkitem ITEM_WAILMER_PAIL, 1
	compare VAR_RESULT, 0
	goto_if_eq BerryTree_EventScript_DontWater
	special ObjectEventInteractionGetBerryName
	msgbox BerryTree_Text_WantToWater, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq BerryTree_EventScript_WaterBerry
	compare VAR_RESULT, NO
	goto_if_eq BerryTree_EventScript_DontWater

BerryTree_EventScript_DontWater:: @ 82744BE
	releaseall
	end

BerryTree_EventScript_ItemUseWailmerPail:: @ 82744C0
	special ObjectEventInteractionGetBerryTreeData
	lockall
BerryTree_EventScript_WaterBerry:: @ 82744C4
	special ObjectEventInteractionGetBerryName
	message BerryTree_Text_WateredTheBerry
	waitmessage
	special ObjectEventInteractionWaterBerryTree
	special DoWateringBerryTreeAnim
	waitstate
	message BerryTree_Text_PlantIsDelighted
	waitmessage
	waitbuttonpress
	releaseall
	end

BerryTree_EventScript_PlantBerry:: @ 82744DD
	special ObjectEventInteractionPlantBerryTree
	incrementgamestat GAME_STAT_PLANTED_BERRIES
	special IncrementDailyPlantedBerries
	special ObjectEventInteractionGetBerryCountString
	message BerryTree_Text_PlantedOneBerry
	waitmessage
	waitbuttonpress
	return

BerryTree_Text_ItsSoftLoamySoil: @ 82744F0
	.string "푹신푹신한 흙이다!$"
	@ ふかふかの つちだ!

BerryTree_Text_WantToPlant: @ 8274507
	.string "푹신푹신한 흙이다!\n"
	.string "나무열매를 심겠습니까?$"
	@ ふかふかの つちだ!ｎ
	@ きのみを うめますか?

BerryTree_Text_PlantedOneBerry: @ 8274535
	.string "{PLAYER}{K_EUNNEUN} 푹신푹신한 흙에\n"
	.string "{STR_VAR_1}{K_EULREUL} 심었다!$"
	@ §あは ふかふかの つちにｎ
	@ §いのみを うめた!
	@ 오랭열매, 이것과 아래의 주석들은 해당 대사가 출력되었을 때 
	@ {STR_VAR_1}에 들어가는 단어의 예시를 적어놓은 것입니다.

BerryTree_Text_BerryGrowthStage1: @ 8274560
	.string "{STR_VAR_1}{K_EULREUL} 심은 장소다!$"
	@ §いのみを うめた ばしょだ!
	@ 오랭열매

BerryTree_Text_BerryGrowthStage2: @ 8274579
	.string "{STR_VAR_1}의 싹이 나왔다!$"
	@ §いの めが でてきた!
	@ 오랭

BerryTree_Text_BerryGrowthStage3: @ 827458A
	.string "{STR_VAR_1}의 줄기가 크게 자랐다!$"
	@ §いの みきが おおきく なってきた!
	@ 오랭

BerryTree_Text_BerryGrowthStage4: @ 82745AB
	.string "{STR_VAR_1}의 꽃이 {STR_VAR_2} 피어있다!$"
	@ §いの はなが §う さいてる!
	@ 오랭

BerryTree_Text_CareAdverbGreat: @ 82745CD
	.string "매우 아름답게$"

BerryTree_Text_CareAdverbPoor: @ 82745DE
	.string "아기자기하게$"

BerryTree_Text_CareAdverbGood: @ 82745E5
	.string "예쁘게$"

BerryTree_Text_WantToPick: @ 82745EE
	.string "{STR_VAR_1}가 {STR_VAR_2}개 열려있다!\n"
	.string "{STR_VAR_1}{K_EULREUL} 따겠습니까?$"
	@ §いのみが §うこ できてる!ｐ
	@ §いのみを とりますか?
	@ 오랭열매
	@ 오랭열매

BerryTree_Text_PickedTheBerry: @ 827461B
	.string "{PLAYER}{K_EUNNEUN} {STR_VAR_1}{K_EULREUL} {STR_VAR_2}개 땄다!$"
	@ §あは §いのみを §うこ とった!
	@ 오랭열매

BerryTree_Text_PutAwayBerry: @ 8274630
	.string "{PLAYER}{K_EUNNEUN} {STR_VAR_1}{K_EULREUL}\n"
	.string "나무열매 포켓에 넣었다!\p"
	.string "푹신푹신한 흙으로 되돌아갔다!$"
	@ §あは §いのみをｎ
	@ きのみポケットに しまった!ｐ
	@ つちは もとの ふかふかに もどった!
	@ 오랭열매

BerryTree_Text_BerryPocketFull: @ 827468F
	.string "가방의 나무열매 포켓이 가득 찼다\n"
	.string "{STR_VAR_1}{K_EULREUL} 포기했다$"
	@ バッグの きのみポケットが いっぱいだったｐ
	@ §いのみを あきらめた

BerryTree_Text_BerryLeftUnpicked: @ 82746CB
	.string "{PLAYER}{K_EUNNEUN} {STR_VAR_1}{K_EULREUL}\n"
	.string "그대로 뒀다$"
	@ §あは §いのみをｎ
	@ そのままに しておいた
	@ 오랭열매

BerryTree_Text_WantToWater: @ 82746E4
	.string "지니고 있는 고래왕자물뿌리개로\n"
	.string "{STR_VAR_1}에 물을 주겠습니까?$"
	@ もっている ホエルコじょうろ でｎ
	@ §いに みずを あげますか?
	@ 오랭

BerryTree_Text_WateredTheBerry: @ 8274710
	.string "{PLAYER}{K_EUNNEUN} {STR_VAR_1}에 물을 주었다!$"
	@ §あは §いに みずを あげた!
	@ 오랭

BerryTree_Text_PlantIsDelighted: @ 8274723
	.string "매우 기뻐하는 듯하다!$"

BerryTree_Text_ExclamationPoint: @ 8274744
	.string "!$"
