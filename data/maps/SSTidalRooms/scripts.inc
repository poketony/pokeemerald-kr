SSTidalRooms_MapScripts:: @ 823C9F1
	.byte 0

SSTidalRooms_EventScript_SnatchGiver:: @ 823C9F2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_TM49, SSTidalRooms_EventScript_ExplainSnatch
	msgbox SSTidalRooms_Text_NotSuspiciousTakeThis, MSGBOX_DEFAULT
	giveitem ITEM_TM49
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	setflag FLAG_RECEIVED_TM49
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_ExplainSnatch:: @ 823CA29
	msgbox SSTidalRooms_Text_ExplainSnatch, MSGBOX_DEFAULT
	release
	end

SSTidalRooms_EventScript_Bed:: @ 823CA33
	lockall
	msgbox SSTidalRooms_Text_TakeRestOnBed, MSGBOX_DEFAULT
	closemessage
	call Common_EventScript_OutOfCenterPartyHeal
	call SSTidalRooms_EventScript_ProgessCruiseAfterBed
	releaseall
	end

SSTidalRooms_EventScript_Colton:: @ 823CA49
	trainerbattle_single TRAINER_COLTON, SSTidalRooms_Text_ColtonIntro, SSTidalRooms_Text_ColtonDefeat
	msgbox SSTidalRooms_Text_ColtonPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Micah:: @ 823CA60
	trainerbattle_single TRAINER_MICAH, SSTidalRooms_Text_MicahIntro, SSTidalRooms_Text_MicahDefeat
	msgbox SSTidalRooms_Text_MicahPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Thomas:: @ 823CA77
	trainerbattle_single TRAINER_THOMAS, SSTidalRooms_Text_ThomasIntro, SSTidalRooms_Text_ThomasDefeat
	msgbox SSTidalRooms_Text_ThomasPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Jed:: @ 823CA8E
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_JedIntro, SSTidalRooms_Text_JedDefeat, SSTidalRooms_Text_JedNotEnoughMons
	msgbox SSTidalRooms_Text_JedPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Lea:: @ 823CAA9
	trainerbattle_double TRAINER_LEA_AND_JED, SSTidalRooms_Text_LeaIntro, SSTidalRooms_Text_LeaDefeat, SSTidalRooms_Text_LeaNotEnoughMons
	msgbox SSTidalRooms_Text_LeaPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Garret:: @ 823CAC4
	trainerbattle_single TRAINER_GARRET, SSTidalRooms_Text_GarretIntro, SSTidalRooms_Text_GarretDefeat
	msgbox SSTidalRooms_Text_GarretPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_EventScript_Naomi:: @ 823CADB
	trainerbattle_single TRAINER_NAOMI, SSTidalRooms_Text_NaomiIntro, SSTidalRooms_Text_NaomiDefeat
	msgbox SSTidalRooms_Text_NaomiPostBattle, MSGBOX_AUTOCLOSE
	end

SSTidalRooms_Text_TakeRestOnBed: @ 823CAF2
	.string "침대가 있다...\n"
	.string "조금 쉬었다 가자$"

SSTidalRooms_Text_ColtonIntro: @ 823CB14
	.string "해안시티와 잿빛도시를\n"
	.string "왔다 갔다 하면서...\p"
	.string "콘테스트를 보는 게\n"
	.string "내 취미야$"

SSTidalRooms_Text_ColtonDefeat: @ 823CB58
	.string "즐거운 승부였어$"

SSTidalRooms_Text_ColtonPostBattle: @ 823CB75
	.string "다음 콘테스트에는\n"
	.string "어떤 포켓몬이 등장할지\l"
	.string "너무 기대돼서 참을 수가 없어$"

SSTidalRooms_Text_MicahIntro: @ 823CBEB
	.string "자네의 친구들은 강한가?$"

SSTidalRooms_Text_MicahDefeat: @ 823CC04
	.string "강한 친구들이군!$"

SSTidalRooms_Text_MicahPostBattle: @ 823CC26
	.string "사람만이 친구가\n"
	.string "될 수 있는 건 아니지\p"
	.string "나에게는 포켓몬이\n"
	.string "너무나도 소중한 친구라네!$"

SSTidalRooms_Text_ThomasIntro: @ 823CC68
	.string "이보시게\n"
	.string "노크는 하셨는가?$"

SSTidalRooms_Text_ThomasDefeat: @ 823CC8A
	.string "패배해도\n"
	.string "침착하게 의연하게$"

SSTidalRooms_Text_ThomasPostBattle: @ 823CCBB
	.string "어떤 일이 있더라도 평정심을\n"
	.string "잃지 않는 것이 신사의 마음가짐이지$"

SSTidalRooms_Text_JedIntro: @ 823CD04
	.string "진: 좀 부끄럽지만\n"
	.string "우리들의 러브러브파워를 보여줄까?$"

SSTidalRooms_Text_JedDefeat: @ 823CD54
	.string "진: 하아...$"

SSTidalRooms_Text_JedPostBattle: @ 823CD5F
	.string "진: 우리들의 러브러브파워로도\n"
	.string "이길 수 없었던 건 처음이야!\l"
	.string "정말 대단한 트레이너구나 너는!?$"

SSTidalRooms_Text_JedNotEnoughMons: @ 823CDC6
	.string "진: 포켓몬이 한 마리라고?\n"
	.string "그럼 너무 외롭지 않나?$"

SSTidalRooms_Text_LeaIntro: @ 823CE04
	.string "가애: 좀 부끄럽지만\n"
	.string "둘만의 러브러브파워를 보여주겠어!$"

SSTidalRooms_Text_LeaDefeat: @ 823CE4B
	.string "가애: 으앙!$"

SSTidalRooms_Text_LeaPostBattle: @ 823CE59
	.string "가애: 우리들의 러브러브파워로도\n"
	.string "이길 수 없다니\l"
	.string "넌 정말 대단한 트레이너구나!$"

SSTidalRooms_Text_LeaNotEnoughMons: @ 823CEB0
	.string "가애: 승부하고 싶었는데...\n"
	.string "포켓몬이 한 마리밖에 없구나...$"

SSTidalRooms_Text_GarretIntro: @ 823CEEE
	.string "마침 잘 왔어!\p"
	.string "난 지금 심심해서 못 참겠거든\n"
	.string "잠깐만 승부를 즐기게 해줘$"

SSTidalRooms_Text_GarretDefeat: @ 823CF36
	.string "...이제 됐어$"

SSTidalRooms_Text_GarretPostBattle: @ 823CF45
	.string "아빠한테 말해서 내 전용\n"
	.string "요트를 사달라고 할까?\p"
	.string "포켓몬이랑 같이\n"
	.string "탈 수 있는 요트를 말이야!$"

SSTidalRooms_Text_NaomiIntro: @ 823CF97
	.string "어머 귀여운 트레이너님\n"
	.string "차라도 한잔하시겠어요?\l"
	.string "아니면 승부?$"

SSTidalRooms_Text_NaomiDefeat: @ 823CFF4
	.string "참 활발하신 분이군요$"

SSTidalRooms_Text_NaomiPostBattle: @ 823D013
	.string "우아한 호화 여객선으로\n"
	.string "세계를 일주하는 것도 좋지만...\p"
	.string "연락선에서 느긋하게\n"
	.string "호연지방을 지켜보는 것도\l"
	.string "정말 멋져요$"

SSTidalRooms_Text_NotSuspiciousTakeThis: @ 823D098
	.string "전 이상한 사람 아닙니다!\n"
	.string "그래서 이것을 당신에게 드릴게요!\p"
	.string "누군가로부터\n"
	.string "가로챈 건 아니에요!\l"
	.string "안심하고 써주세요!$"

SSTidalRooms_Text_ExplainSnatch: @ 823D145
	.string "가로챔이라는 기술은\n"
	.string "상대가 쓰려고 한 기술을\l"
	.string "자신이 쓰게 만들어요!$"

