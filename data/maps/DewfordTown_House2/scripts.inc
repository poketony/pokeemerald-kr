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
	.string "어때! 요즘 가장 유행하는\n"
	.string "이 실크스카프가 멋지지 않아!?\p"
	.string "오 흥미가 생긴 모양이네!\n"
	.string "내 센스를 알아주는구나 넌!\p"
	.string "정말 기쁜걸!\n"
	.string "이걸 선물할게!$"
	// ほら! りゅうこう さいせんたんのｎ
	// この シルクのスカ-フ ステキだろ!ｐ
	// おっ めが かがやいてるね!ｎ
	// オレの センスが わかるんだな きみは!ｐ
	// うれしいね!ｎ
	// これは プレゼント するよ!

DewfordTown_House2_Text_NoRoom: @ 81FE356
	.string "엇 못 가진다고?\n"
	.string "네 물건을 전부 팔아서라도\l"
	.string "얻을 만큼 가치 있는 스카프라고 이건!$"
	// え もてないの?ｎ
	// きみの にもつを ぜんぶ うってでもｌ
	// もつべき スカ-フだぜ これは!

DewfordTown_House2_Text_ExplainSilkScarf: @ 81FE3D1
	.string "실크스카프는 노말타입\n"
	.string "기술의 위력을 높여주지!\p"
	.string "대부분의 포켓몬에게 어울리는\n"
	.string "멋진 스카프야!$"
	// シルクのスカ-フは ノ-マルタイプのｎ
	// わざの いりょくを あげてくれる!ｐ
	// ほとんどの ポケモンに にあうｎ
	// すてきな スカ-フ ってことだぜ!

DewfordTown_House2_Text_BrawlySoCool: @ 81FE444
	.string "헤에! 바다를 건너\n"
	.string "기어코 무로마을까지 왔구나!\p"
	.string "혹시 철구님의 소문을 듣고\n"
	.string "만나러 온 거야?\p"
	.string "철구님은 정말 멋있어서\n"
	.string "모두가 동경하잖아!$"
	// へえ! きみ うみを こえてｎ
	// わざわざ ムロまで きたの!ｐ
	// もしかして トウキさんの うわさを きいてｎ
	// あいに きたんじゃない?ｐ
	// トウキさん かっこよくてｎ
	// みんなが あこがれるもんな!

