.set LOCALID_STAIR_GUARD, 2

RustboroCity_DevonCorp_1F_MapScripts:: @ 8211245
	map_script MAP_SCRIPT_ON_TRANSITION, RustboroCity_DevonCorp_1F_OnTransition
	.byte 0

RustboroCity_DevonCorp_1F_OnTransition: @ 821124B
	call_if_unset FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_BlockStairs
	end

RustboroCity_DevonCorp_1F_EventScript_BlockStairs:: @ 8211255
	setobjectxyperm LOCALID_STAIR_GUARD, 14, 2
	setobjectmovementtype LOCALID_STAIR_GUARD, MOVEMENT_TYPE_FACE_DOWN
	return

RustboroCity_DevonCorp_1F_EventScript_Employee:: @ 8211261
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright
	msgbox RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RobberWasntBright:: @ 821127F
	msgbox RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GoodsRecovered:: @ 8211289
	msgbox RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StairGuard:: @ 8211293
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_GotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_AlwaysWelcome:: @ 82112BA
	msgbox RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_GotRobbed:: @ 82112C4
	msgbox RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_Greeter:: @ 82112CE
	lock
	faceplayer
	goto_if_set FLAG_RETURNED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp
	goto_if_set FLAG_RECOVERED_DEVON_GOODS, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	goto_if_set FLAG_DEVON_GOODS_STOLEN, RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_WelcomeToDevonCorp:: @ 82112F5
	msgbox RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_StaffGotRobbed:: @ 82112FF
	msgbox RustboroCity_DevonCorp_1F_Text_StaffGotRobbed, MSGBOX_DEFAULT
	release
	end

RustboroCity_DevonCorp_1F_EventScript_RocksMetalDisplay:: @ 8211309
	msgbox RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_EventScript_ProductsDisplay:: @ 8211312
	msgbox RustboroCity_DevonCorp_1F_Text_ProductDisplay, MSGBOX_SIGN
	end

RustboroCity_DevonCorp_1F_Text_WelcomeToDevonCorp: @ 821131B
	.string "어서 오세요!\n"
	.string "데봉 코포레이션입니다!\p"
	.string "여러분의 생활에 도움이 되는\n"
	.string "도구나 약을 만들고 있습니다!$"

RustboroCity_DevonCorp_1F_Text_StaffGotRobbed: @ 821138B
	.string "얼빠진 연구원이\n"
	.string "화물을 빼앗겨서...$"

RustboroCity_DevonCorp_1F_Text_ThoseShoesAreOurProduct: @ 82113D1
	.string "오! 러닝슈즈!\n"
	.string "우리 회사의 발명품이잖아!\p"
	.string "우리 회사 제품을\n"
	.string "실제로 사용하고 있는 사람을 보면\l"
	.string "굉장히 기뻐지지!$"

RustboroCity_DevonCorp_1F_Text_RobberWasntVeryBright: @ 8211446
	.string "확실히 그 화물은\n"
	.string "소중한 물건이지만...\p"
	.string "다른 사람이 훔쳐가도\n"
	.string "사용할 수 없을 거라 생각해\p"
	.string "내 추측으로는 그 도둑\n"
	.string "그리 똑똑해 보이진 않았거든$"

RustboroCity_DevonCorp_1F_Text_SoundsLikeStolenGoodsRecovered: @ 82114DE
	.string "듣자 하니 데봉화물은\n"
	.string "다시 돌아왔다더군$"

RustboroCity_DevonCorp_1F_Text_OnlyAuthorizedPeopleEnter: @ 821151B
	.string "어이쿠 관계자가 아니신 분은\n"
	.string "여기서부터\l"
	.string "앞으로 가실 수 없습니다!$"

RustboroCity_DevonCorp_1F_Text_HowCouldWeGetRobbed: @ 8211558
	.string "도둑에게 화물을 빼앗기다니\n"
	.string "왜 이렇게 얼빠진 거야...$"

RustboroCity_DevonCorp_1F_Text_YoureAlwaysWelcomeHere: @ 8211585
	.string "오!\n"
	.string "너라면 언제나 환영이지!$"

RustboroCity_DevonCorp_1F_Text_RocksMetalDisplay: @ 82115AC
	.string "돌이나 금속 샘플이\n"
	.string "유리 케이스 안에 줄지어 있다!\p"
	.string "패널에 설명이 적혀 있으니까\n"
	.string "읽어 보자...\p"
	.string "“데봉 코포레이션은 원래\n"
	.string "  산에서 돌을 캐내거나\p"
	.string "  사철로부터 철재를 만들기 위해\n"
	.string "  설립되었던 회사입니다”\p"
	.string "“이윽고 데봉 코포레이션은\n"
	.string "  재료에서 멈추지 않고\p"
	.string "  여러 가지 공업 제품도\n"
	.string "  만들게 되었습니다”$"
	// いしや きんぞくの サンプルがｎ
	// ガラスケ-スの なかに ならんでいる!ｐ
	// パネルに せつめいが かいてあるからｎ
	// よんでみよう……ｐ
	// 「デボン コ-ポレ-ションは もともとｎ
	// やまから いしを きりだしたりｐ
	// さてつから てつざいを つくるためにｎ
	// せつりつ された かいしゃ です」ｐ
	// 「やがて デボン コ-ポレ-ションはｎ
	// ざいりょう だけに とどまらずｐ
	// さまざまな こうぎょう せいひんもｎ
	// つくるように なったのです」

RustboroCity_DevonCorp_1F_Text_ProductDisplay: @ 8211722
	.string "여러 도구의 시작품이\n"
	.string "유리 케이스 안에 줄지어 있다!\p"
	.string "패널에 설명이 적혀 있으니까\n"
	.string "읽어 보자...\p"
	.string "“현재 데봉 코포레이션에서는\n"
	.string "  공업 제품 외에도\l"
	.string "  일용품이나 약 등\p"
	.string "  사람들에게 도움이 되는 것들을\n"
	.string "  개발하고 있습니다\p"
	.string "“또 현재로서는 몬스터볼이나\n"
	.string "  포켓내비 등의 트레이너 용품도\l"
	.string "  다루게 되었습니다”$"
	// いろんな どうぐの しさくひんがｎ
	// ガラスケ-スの なかに ならんでいる!ｐ
	// パネルに せつめいが かいてあるからｎ
	// よんでみよう……ｐ
	// 「げんざい デボン コ-ポレ-ションではｎ
	// 	こうぎょう せいひんの ほかにもｌ
	//	にちようひんや くすりなどｐ
	//	ひとびとの くらしに やくだつ ものをｎ
	//	かいはつ しています」ｐ
	// 「また げんざいでは モンスタ-ボ-ルやｎ
	//	ポケナビなどの トレ-ナ-ようひんもｌ
	//	てがけるように なりました」

