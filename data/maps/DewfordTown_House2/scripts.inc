DewfordTown_House2_MapScripts:: @ 81FE22D
	.byte 0

DewfordTown_House2_EventScript_Man:: @ 81FE22E
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_SILK_SCARF, DewfordTown_House2_EventScript_ExplainSilkScarf
	msgbox DewfordTown_House2_Text_WantYouToHaveSilkScarf, MSGBOX_DEFAULT
	giveitem ITEM_SILK_SCARF
	compare VAR_RESULT, FALSE
	goto_if_eq DewfordTown_House2_EventScript_NoRoomForScarf
	setflag FLAG_RECEIVED_SILK_SCARF
	release
	end

DewfordTown_House2_EventScript_NoRoomForScarf:: @ 81FE25D
	msgbox DewfordTown_House2_Text_NoRoom, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_ExplainSilkScarf:: @ 81FE267
	msgbox DewfordTown_House2_Text_ExplainSilkScarf, MSGBOX_DEFAULT
	release
	end

DewfordTown_House2_EventScript_Boy:: @ 81FE271
	msgbox DewfordTown_House2_Text_BrawlySoCool, MSGBOX_NPC
	end

DewfordTown_House2_Text_WantYouToHaveSilkScarf: @ 81FE27A
	.string "이게 바로!\p"
	.string "요즘 가장 유행하는 실크스카프야!\n"
	.string "어때? 정말 멋지지?!\p"
	.string "오! 흥미가 생긴 모양인데?\n"
	.string "넌 내 센스를 알아주는구나!\p"
	.string "정말 고마워!\n"
	.string "이건 선물로 줄게!$"

DewfordTown_House2_Text_NoRoom: @ 81FE356
	.string "이런 가방이 가득 찼구나!\p"
	.string "이 실크스카프는 필수 구매\n"
	.string "아이템이라고! 다른 물건을\l"
	.string "팔아서라도\l"
	.string "구매할 만큼 말야!$"

DewfordTown_House2_Text_ExplainSilkScarf: @ 81FE3D1
	.string "실크스카프는 노말타입의 기술의\n"
	.string "위력을 높여주지!\p"
	.string "대부분의 포켓몬에게 어울리는\n"
	.string "멋진 스카프야!$"

DewfordTown_House2_Text_BrawlySoCool: @ 81FE444
	.string "우와! 일부러 바다를 건너\n"
	.string "무로마을까지 왔구나!\p"
	.string "혹시 철구님의 소문을 듣고\n"
	.string "만나러 온 거야?\p"
	.string "철구님은 정말 멋있어서\n"
	.string "모두가 동경하잖아!$"

