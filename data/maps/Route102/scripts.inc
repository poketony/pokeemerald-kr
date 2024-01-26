Route102_MapScripts:: @ 81EC0E0
	.byte 0

Route102_EventScript_LittleBoy:: @ 81EC0E1
	msgbox Route102_Text_ImNotVeryTall, MSGBOX_NPC
	end

Route102_EventScript_RouteSignOldale:: @ 81EC0EA
	msgbox Route102_Text_RouteSignOldale, MSGBOX_SIGN
	end

Route102_EventScript_RouteSignPetalburg:: @ 81EC0F3
	msgbox Route102_Text_RouteSignPetalburg, MSGBOX_SIGN
	end

Route102_EventScript_Boy:: @ 81EC0FC
	msgbox Route102_Text_CatchWholeBunchOfPokemon, MSGBOX_NPC
	end

Route102_EventScript_Calvin:: @ 81EC105
	trainerbattle_single TRAINER_CALVIN_1, Route102_Text_CalvinIntro, Route102_Text_CalvinDefeated, Route102_EventScript_CalvinRegisterMatchCallAfterBattle
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route102_EventScript_CalvinRematch
	setvar VAR_0x8004, TRAINER_CALVIN_1
	specialvar VAR_RESULT, IsTrainerRegistered
	compare VAR_RESULT, FALSE
	goto_if_eq Route102_EventScript_CalvinTryRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegisterMatchCallAfterBattle:: @ 81EC146
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegisterMatchCall
	release
	end

Route102_EventScript_CalvinRegisterMatchCall:: @ 81EC157
	msgbox Route102_Text_CalvinRegisterShort, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinTryRegister:: @ 81EC170
	goto_if_set FLAG_HAS_MATCH_CALL, Route102_EventScript_CalvinRegister
	msgbox Route102_Text_CalvinPostBattle, MSGBOX_DEFAULT
	release
	end

Route102_EventScript_CalvinRegister:: @ 81EC183
	msgbox Route102_Text_CalvinRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_CALVIN_1
	release
	end

Route102_EventScript_CalvinRematch:: @ 81EC19C
	trainerbattle_rematch TRAINER_CALVIN_1, Route102_Text_CalvinRematchIntro, Route102_Text_CalvinRematchDefeated
	msgbox Route102_Text_CalvinRematchPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Rick:: @ 81EC1B3
	trainerbattle_single TRAINER_RICK, Route102_Text_RickIntro, Route102_Text_RickDefeated
	msgbox Route102_Text_RickPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Tiana:: @ 81EC1CA
	trainerbattle_single TRAINER_TIANA, Route102_Text_TianaIntro, Route102_Text_TianaDefeated
	msgbox Route102_Text_TianaPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_EventScript_Allen:: @ 81EC1E1
	trainerbattle_single TRAINER_ALLEN, Route102_Text_AllenIntro, Route102_Text_AllenDefeated
	msgbox Route102_Text_AllenPostBattle, MSGBOX_AUTOCLOSE
	end

Route102_Text_WatchMeCatchPokemon: @ 81EC1F8
	.string "민진: {PLAYER}님...\n"
	.string "포켓몬은 이런 풀숲에\l"
	.string "잘 있지 않나요...?\p"
	.string "제가 잘 잡는지\n"
	.string "옆에서 지켜봐 주세요...\p"
	.string "...우왓!!$"
	// ミツル『§あさん……ｎ
	// ポケモンって こういう くさむらにｌ
	// いたり するんでしょ……?ｐ
	// ぼくが じょうずに つかまえられるかｎ
	// そこで みてて くださいね……ｐ
	// ……うわっ!!

Route102_Text_WallyIDidIt: @ 81EC271
	.string "민진: 해냈어... 내...\n"
	.string "내 포켓몬이다...!!$"
	// ミツル『やった…… ぼくの……ｎ
	// ぼくの ポケモンだ……!!

Route102_Text_LetsGoBack: @ 81EC297
	.string "{PLAYER}님 감사합니다!\n"
	.string "체육관으로 돌아가죠!$"
	// §あさん ありがとう!ｎ
	// ジムに もどろうよ!

Route102_Text_ImNotVeryTall: @ 81EC2C0
	.string "난... 키가 작아서\n"
	.string "풀숲을 걸으면 풀에 파묻히지\p"
	.string "나뭇잎이 코에 들어가서\n"
	.string "흐에 흐에 흐에 흐에...\p"
	.string "흐엣취-!$"
	// ぼく…… せが ひくいからｎ
	// くさむらを あるくと もぐっちゃうんだｐ
	// ハッパが はなの あなに はいってｎ
	// ふぁ ふぁ ふぁ ふぁ……ｐ
	// ぶわっくしょ-ん!

Route102_Text_CatchWholeBunchOfPokemon: @ 81EC32E
	.string "포켓몬 잔뜩 잡아야지-!$"
	// ポケモン たくさん つかまえよ-っと!

Route102_Text_RouteSignOldale: @ 81EC35B
	.string "여기는 102번 도로\n"
	.string "{RIGHT_ARROW} 고도마을$"
	// ここは 102ばん どうろｎ
	// ©しう コトキタウン

Route102_Text_RouteSignPetalburg: @ 81EC373
	.string "여기는 102번 도로\n"
	.string "{LEFT_ARROW} 등화도시$"
	// ここは 102ばん どうろｎ
	// ©しい トウカシティ
