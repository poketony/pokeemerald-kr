Route124_DivingTreasureHuntersHouse_MapScripts:: @ 8270A28
	map_script MAP_SCRIPT_ON_TRANSITION, Route124_DivingTreasureHuntersHouse_OnTransition
	.byte 0

Route124_DivingTreasureHuntersHouse_OnTransition: @ 8270A2E
	setflag FLAG_LANDMARK_HUNTERS_HOUSE
	end

Route124_DivingTreasureHuntersHouse_EventScript_TreasureHunter:: @ 8270A32
	lock
	faceplayer
	goto_if_set FLAG_MET_DIVING_TREASURE_HUNTER, Route124_DivingTreasureHuntersHouse_EventScript_SkipGreeting
	msgbox Route124_DivingTreasureHuntersHouse_Text_Greeting, MSGBOX_DEFAULT
	setflag FLAG_MET_DIVING_TREASURE_HUNTER
	goto Route124_DivingTreasureHuntersHouse_EventScript_CheckPlayerHasShard
	end

Route124_DivingTreasureHuntersHouse_EventScript_SkipGreeting:: @ 8270A4E
	msgbox Route124_DivingTreasureHuntersHouse_Text_HaveYouSeenAnyShards, MSGBOX_DEFAULT
	goto Route124_DivingTreasureHuntersHouse_EventScript_CheckPlayerHasShard
	end

Route124_DivingTreasureHuntersHouse_EventScript_CheckPlayerHasShard:: @ 8270A5C
	call Route124_DivingTreasureHuntersHouse_EventScript_GetPlayersShards
	compare VAR_TEMP_1, 0
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_NoShards
	goto Route124_DivingTreasureHuntersHouse_EventScript_HasShard
	end

Route124_DivingTreasureHuntersHouse_EventScript_GetPlayersShards:: @ 8270A72
	setvar VAR_TEMP_1, 0
	checkitem ITEM_RED_SHARD, 1
	compare VAR_RESULT, TRUE
	call_if_eq Route124_DivingTreasureHuntersHouse_EventScript_HasRedShard
	checkitem ITEM_YELLOW_SHARD, 1
	compare VAR_RESULT, TRUE
	call_if_eq Route124_DivingTreasureHuntersHouse_EventScript_HasYellowShard
	checkitem ITEM_BLUE_SHARD, 1
	compare VAR_RESULT, TRUE
	call_if_eq Route124_DivingTreasureHuntersHouse_EventScript_HasBlueShard
	checkitem ITEM_GREEN_SHARD, 1
	compare VAR_RESULT, TRUE
	call_if_eq Route124_DivingTreasureHuntersHouse_EventScript_HasGreenShard
	return

Route124_DivingTreasureHuntersHouse_EventScript_HasRedShard:: @ 8270AB8
	addvar VAR_TEMP_1, 1
	return

Route124_DivingTreasureHuntersHouse_EventScript_HasYellowShard:: @ 8270ABE
	addvar VAR_TEMP_1, 2
	return

Route124_DivingTreasureHuntersHouse_EventScript_HasBlueShard:: @ 8270AC4
	addvar VAR_TEMP_1, 4
	return

Route124_DivingTreasureHuntersHouse_EventScript_HasGreenShard:: @ 8270ACA
	addvar VAR_TEMP_1, 8
	return

Route124_DivingTreasureHuntersHouse_EventScript_HasShard:: @ 8270AD0
	msgbox Route124_DivingTreasureHuntersHouse_Text_ThatsAShardIllTradeYou, MSGBOX_DEFAULT
	goto Route124_DivingTreasureHuntersHouse_EventScript_ShowTradeOptions
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShowTradeOptions:: @ 8270ADE
	message Route124_DivingTreasureHuntersHouse_Text_WhatDoYouWantToTrade
	waitmessage
	switch VAR_TEMP_1
	case 1,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsR
	case 2,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsY
	case 3,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRY
	case 4,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsB
	case 5,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRB
	case 6,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYB
	case 7,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYB
	case 8,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsG
	case 9,  Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRG
	case 10, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYG
	case 11, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYG
	case 12, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsBG
	case 13, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRBG
	case 14, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYBG
	case 15, Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYBG
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsR:: @ 8270B8F
	multichoice 0, 0, MULTI_SHARDS_R, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsY:: @ 8270BB5
	multichoice 0, 0, MULTI_SHARDS_Y, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRY:: @ 8270BDB
	multichoice 0, 0, MULTI_SHARDS_RY, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsB:: @ 8270C0C
	multichoice 0, 0, MULTI_SHARDS_B, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRB:: @ 8270C32
	multichoice 0, 0, MULTI_SHARDS_RB, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYB:: @ 8270C63
	multichoice 0, 0, MULTI_SHARDS_YB, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYB:: @ 8270C94
	multichoice 0, 0, MULTI_SHARDS_RYB, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 3, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsG:: @ 8270CD0
	multichoice 0, 0, MULTI_SHARDS_G, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRG:: @ 8270CF6
	multichoice 0, 0, MULTI_SHARDS_RG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYG:: @ 8270D27
	multichoice 0, 0, MULTI_SHARDS_YG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYG:: @ 8270D58
	multichoice 0, 0, MULTI_SHARDS_RYG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 3, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsBG:: @ 8270D94
	multichoice 0, 0, MULTI_SHARDS_BG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRBG:: @ 8270DC5
	multichoice 0, 0, MULTI_SHARDS_RBG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 3, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsYBG:: @ 8270E01
	multichoice 0, 0, MULTI_SHARDS_YBG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 3, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardOptionsRYBG:: @ 8270E3D
	multichoice 0, 0, MULTI_SHARDS_RYBG, 0
	switch VAR_RESULT
	case 0, Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard
	case 1, Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard
	case 2, Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard
	case 3, Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard
	case 4, Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_TradeRedShard:: @ 8270E84
	setvar VAR_0x8008, ITEM_RED_SHARD
	setvar VAR_0x8009, ITEM_FIRE_STONE
	goto Route124_DivingTreasureHuntersHouse_EventScript_TryTradeShard

Route124_DivingTreasureHuntersHouse_EventScript_TradeYellowShard:: @ 8270E93
	setvar VAR_0x8008, ITEM_YELLOW_SHARD
	setvar VAR_0x8009, ITEM_THUNDER_STONE
	goto Route124_DivingTreasureHuntersHouse_EventScript_TryTradeShard

Route124_DivingTreasureHuntersHouse_EventScript_TradeBlueShard:: @ 8270EA2
	setvar VAR_0x8008, ITEM_BLUE_SHARD
	setvar VAR_0x8009, ITEM_WATER_STONE
	goto Route124_DivingTreasureHuntersHouse_EventScript_TryTradeShard

Route124_DivingTreasureHuntersHouse_EventScript_TradeGreenShard:: @ 8270EB1
	setvar VAR_0x8008, ITEM_GREEN_SHARD
	setvar VAR_0x8009, ITEM_LEAF_STONE
	goto Route124_DivingTreasureHuntersHouse_EventScript_TryTradeShard

Route124_DivingTreasureHuntersHouse_EventScript_TryTradeShard:: @ 8270EC0
	bufferitemname 0, VAR_0x8008
	bufferitemname 1, VAR_0x8009
	msgbox Route124_DivingTreasureHuntersHouse_Text_YoullTradeShardForStone, MSGBOX_YESNO
	compare VAR_RESULT, NO
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	checkitemspace VAR_0x8009, 1
	compare VAR_RESULT, TRUE
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_TradeShard
	checkitem VAR_0x8008, 2
	compare VAR_RESULT, FALSE
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_TradeShard
	goto Route124_DivingTreasureHuntersHouse_EventScript_BagFull
	end

Route124_DivingTreasureHuntersHouse_EventScript_TradeShard:: @ 8270F01
	removeitem VAR_0x8008
	giveitem VAR_0x8009
	msgbox Route124_DivingTreasureHuntersHouse_Text_ItsADeal, MSGBOX_DEFAULT
	call Route124_DivingTreasureHuntersHouse_EventScript_GetPlayersShards
	compare VAR_TEMP_1, 0
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_EndTrade
	msgbox Route124_DivingTreasureHuntersHouse_Text_TradeSomethingElse, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route124_DivingTreasureHuntersHouse_EventScript_ShowTradeOptions
	goto Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade
	end

Route124_DivingTreasureHuntersHouse_EventScript_BagFull:: @ 8270F43
	msgbox Route124_DivingTreasureHuntersHouse_Text_BagFull, MSGBOX_DEFAULT
	release
	end

Route124_DivingTreasureHuntersHouse_EventScript_DeclineTrade:: @ 8270F4D
	msgbox Route124_DivingTreasureHuntersHouse_Text_ComeBackIfYouChangeMind, MSGBOX_DEFAULT
	release
	end

Route124_DivingTreasureHuntersHouse_EventScript_NoShards:: @ 8270F57
	msgbox Route124_DivingTreasureHuntersHouse_Text_YouHaventGotAnyShards, MSGBOX_DEFAULT
	release
	end

Route124_DivingTreasureHuntersHouse_EventScript_EndTrade:: @ 8270F61
	release
	end

Route124_DivingTreasureHuntersHouse_EventScript_ShardTradeBoard:: @ 8270F63
	msgbox Route124_DivingTreasureHuntersHouse_Text_ShardTradeBoard, MSGBOX_SIGN
	end

Route124_DivingTreasureHuntersHouse_Text_Greeting: @ 8270F6C
	.string "난 다이빙 트레져헌터!\p"
	.string "깊은 바닷속으로 잠수해서\n"
	.string "해저에 잠들어 있는 보물을 모으는\l"
	.string "대단한 녀석이야!$"
	@ オレは ダイビング トレジャ-ハンタ-!ｐ
	@ ふかい うみに もぐってはｎ
	@ かいていに ねむる おたからを あつめるｌ
	@ すげえ やろう なのさ!

Route124_DivingTreasureHuntersHouse_Text_HaveYouSeenAnyShards: @ 8270FE5
	.string "머나먼 옛날에 만들어졌다고 하는\n"
	.string "다양한 조각 발견했어?$"
	@ おおむかしに つくられた というｎ
	@ いろいろな かけら みつかったかい?

Route124_DivingTreasureHuntersHouse_Text_YouHaventGotAnyShards: @ 8271027
	.string "너 보물 안 가지고 있구나...\p"
	.string "빨강조각이라든가\n"
	.string "다양한 조각 발견하면\l"
	.string "교환해 줘!$"
	@ きみ おたから もってないのか……ｐ
	@ あかいかけら とかｎ
	@ いろいろな かけらを みつけたらｌ
	@ こうかん してくれよな!

Route124_DivingTreasureHuntersHouse_Text_ThatsAShardIllTradeYou: @ 8271098
	.string "오오! 그건!\n"
	.string "내가 찾고 있던 조각!!\p"
	.string "저기 말이야!\n"
	.string "네가 가지고 있는 보물이랑\l"
	.string "내 보물이랑 교환해 줘!$"
	@ おおっ! それは!ｎ
	@ オレが さがしている かけら!!ｐ
	@ なっ なっ!ｎ
	@ きみの もってる おたからとｌ
	@ オレの おたから こうかん してくれよ!

Route124_DivingTreasureHuntersHouse_Text_WhatDoYouWantToTrade: @ 8271117
	.string "어떤 거랑 교환해 줄 거야?$"
	@ どれを こうかん するんだい?

Route124_DivingTreasureHuntersHouse_Text_YoullTradeShardForStone: @ 8271132
	.string "{STR_VAR_1}{K_EULREUL} {STR_VAR_2}{K_I}랑\n"
	.string "교환하는 거지?$"
	@ §い を §うにｎ
	@ こうかん するんだな?

Route124_DivingTreasureHuntersHouse_Text_ItsADeal: @ 8271158
	.string "교환 성립!\n"
	.string "소중하게 써 줘!$"
	@ とりひき せいりつ!ｎ
	@ だいじに つかって くれよな!

Route124_DivingTreasureHuntersHouse_Text_TradeSomethingElse: @ 827117B
	.string "또 교환할래?$"
	@ まだ こうかん するかい?

Route124_DivingTreasureHuntersHouse_Text_BagFull: @ 82711A0
	.string "어이쿠 가방이 가득하잖아\n"
	.string "도구를 줄이고 와$"
	@ おっと バッグが いっぱい だぜｎ
	@ どうぐを へらして きなよ

Route124_DivingTreasureHuntersHouse_Text_ComeBackIfYouChangeMind: @ 82711D8
	.string "그거 실망인데\n"
	.string "마음이 바뀌면 다시 와 줘!$"
	@ そいつは がっかりだｎ
	@ きが むいたら また きてくれよな!

Route124_DivingTreasureHuntersHouse_Text_ShardTradeBoard: @ 8271217
	.string "{CLEAR_TO 0x0e}원하는 것{CLEAR_TO 0x7d}교환할 것\n"
	.string "{CLEAR_TO 0x0f}빨강조각{CLEAR_TO 0x51}{LEFT_ARROW}{RIGHT_ARROW}{CLEAR_TO 0x7e}불꽃의돌{CLEAR_TO 0xc8}\p"
	.string "{CLEAR_TO 0x0e}원하는 것{CLEAR_TO 0x7d}교환할 것\n"
	.string "{CLEAR_TO 0x0f}노랑조각{CLEAR_TO 0x51}{LEFT_ARROW}{RIGHT_ARROW}{CLEAR_TO 0x7e}천둥의돌{CLEAR_TO 0xc8}\p"
	.string "{CLEAR_TO 0x0e}원하는 것{CLEAR_TO 0x7d}교환할 것\n"
	.string "{CLEAR_TO 0x0f}파랑조각{CLEAR_TO 0x51}{LEFT_ARROW}{RIGHT_ARROW}{CLEAR_TO 0x82}물의돌{CLEAR_TO 0xc8}\p"
	.string "{CLEAR_TO 0x0e}원하는 것{CLEAR_TO 0x7d}교환할 것\n"
	.string "{CLEAR_TO 0x0f}초록조각{CLEAR_TO 0x51}{LEFT_ARROW}{RIGHT_ARROW}{CLEAR_TO 0x7e}리프의돌$"
	@ ほしいモノ       あげるモノｎ
	@  あかいかけら   ©しい©しう ほのおのいしｐ
	@ ほしいモノ       あげるモノｎ
	@  きいろいかけら  ©しい©しう かみなりのいしｐ
	@ ほしいモノ       あげるモノｎ
	@  あおいかけら   ©しい©しう みずのいしｐ
	@ ほしいモノ       あげるモノｎ
	@  みどりのかけら  ©しい©しう リ-フのいし
