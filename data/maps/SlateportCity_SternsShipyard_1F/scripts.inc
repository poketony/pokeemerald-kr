.set LOCALID_DOCK, 1

SlateportCity_SternsShipyard_1F_MapScripts:: @ 8207F3F
	.byte 0

SlateportCity_SternsShipyard_1F_EventScript_Dock:: @ 8207F40
	lockall
	goto_if_set FLAG_SYS_GAME_CLEAR, SlateportCity_SternsShipyard_1F_EventScript_FerryReady
	goto_if_set FLAG_BADGE07_GET, SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined
	goto_if_set FLAG_DELIVERED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran
	goto_if_set FLAG_DOCK_REJECTED_DEVON_GOODS, SlateportCity_SternsShipyard_1F_EventScript_GoFindStern
	msgbox SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails, MSGBOX_DEFAULT
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	setflag FLAG_DOCK_REJECTED_DEVON_GOODS
	setflag FLAG_HIDE_SLATEPORT_CITY_TEAM_AQUA
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_FerryReady:: @ 8207F92
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_FerryIsReady, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_BrineyJoined:: @ 8207FA6
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_GoFindStern:: @ 8207FBA
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_DOCK, Common_Movement_FaceOriginalDirection
	waitmovement 0
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_NeedVeteran:: @ 8207FD9
	applymovement LOCALID_DOCK, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran, MSGBOX_DEFAULT
	releaseall
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist1:: @ 8207FED
	msgbox SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Scientist2:: @ 8207FF6
	msgbox SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_EventScript_Briney:: @ 8207FFF
	msgbox SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock, MSGBOX_NPC
	end

SlateportCity_SternsShipyard_1F_Text_CantMakeHeadsOrTails: @ 8208008
	.string "음 그러니까... 이게 이렇게 되고\n"
	.string "그리고 저게 저렇게 되니까\l"
	.string "음... 그럼 이거랑 저건 뭐지?\p"
	.string "아 정말 뭐가 뭔지 모르겠어!$"

SlateportCity_SternsShipyard_1F_Text_MeetDockDeliverToStern: @ 82080A5
	.string "...응?\p"
	.string "난 해양관장의 지시로\n"
	.string "연락선의 설계를 맡게 된\l"
	.string "솔방울이라고 하는데...\p"
	.string "아!?\n"
	.string "그건 데봉화물!\p"
	.string "음...\n"
	.string "곤란한데 이거...\p"
	.string "해양관장\n"
	.string "또 과학박물관에\l"
	.string "가 있나?\p"
	.string "미안한데\n"
	.string "네가 해양관장 좀 찾아서\l"
	.string "그 화물 좀 전달해줘!$"

SlateportCity_SternsShipyard_1F_Text_CouldYouFindStern: @ 82081A5
	.string "솔방울: 해양관장\n"
	.string "또 과학박물관에\l"
	.string "가 있나?\p"
	.string "미안한데\n"
	.string "네가 해양관장 좀 찾아서\l"
	.string "그 화물 좀 전달해줘!$"

SlateportCity_SternsShipyard_1F_Text_CouldUseAdviceFromVeteran: @ 8208213
	.string "솔방울: 배를 만드는 건\n"
	.string "책상 위에서 하는 계산만으로는\l"
	.string "알 수 없는 것도 많아서 말이지\p"
	.string "역시 바다에 대해 자세히 알고 있는\n"
	.string "베테랑의 지혜가 필요해...$"

SlateportCity_SternsShipyard_1F_Text_BrineyJoinedUs: @ 82082A8
	.string "솔방울: 안녕! 하기노인이 여기서\n"
	.string "도와주게 됐어!\p"
	.string "전설의 선원이 도와줘서\n"
	.string "연락선은 순조롭게\l"
	.string "완성되어 가고 있어!$"

SlateportCity_SternsShipyard_1F_Text_FerryIsReady: @ 8208323
	.string "솔방울: 드디어 배가 완성됐어!\p"
	.string "완성된 연락선 타이드립호는\n"
	.string "정말 최고의 걸작이야!\p"
	.string "그치만 좀 더 잘 만들 수도\n"
	.string "있었을 것 같은...\l"
	.string "그런 생각도 들어\p"
	.string "그래...\n"
	.string "뭔갈 만드는 데 끝이란 건 없으니까!$"

SlateportCity_SternsShipyard_1F_Text_DecidedToHelpDock: @ 82083EE
	.string "하기: 오오! {PLAYER}!\n"
	.string "오랜만이구나!\p"
	.string "아니 자네랑 만난 뒤로\n"
	.string "선원의 피가 끓어올라서 말이지...\p"
	.string "솔방울이랑 협력해서\n"
	.string "연락선을 만들고 싶어졌지 뭔가!\p"
	.string "연락선이 완성되면\n"
	.string "많은 사람들이 이동이\l"
	.string "가능해지니 말이지\p"
	.string "그런데 말이네... 흠...\n"
	.string "솔방울은 정말 대단해...\p"
	.string "그의 기술이랑 내 경험이\n"
	.string "하나로 합쳐지면\l"
	.string "분명 엄청난 배가 만들어질 거네!$"

SlateportCity_SternsShipyard_1F_Text_SeaIsLikeLivingThing: @ 8208558
	.string "계절이나 날씨, 달의 위치 등\n"
	.string "여러 가지 조건에 따라\l"
	.string "바다는 항상 모습이 바뀐답니다\p"
	.string "그렇죠! 바다는 바로\n"
	.string "살아 있는 생물 같은 거예요!$"

SlateportCity_SternsShipyard_1F_Text_GetSeasickEasily: @ 82085FF
	.string "난 배만 타면\n"
	.string "바로 멀미를 한단 말이지\l"
	.string "그래서 여기서 일하고 있는 거야$"

