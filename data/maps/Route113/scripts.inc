Route113_MapScripts:: @ 81F2153
	map_script MAP_SCRIPT_ON_RESUME, Route113_OnResume
	map_script MAP_SCRIPT_ON_TRANSITION, Route113_OnTransition
	.byte 0

Route113_OnResume: @ 81F215E
	setstepcallback STEP_CB_ASH
	end

Route113_OnTransition: @ 81F2161
	clearflag FLAG_FORCE_MIRAGE_TOWER_VISIBLE
	call Route113_EventScript_CheckSetAshWeather
	end

Route113_EventScript_CheckSetAshWeather:: @ 81F216A
	getplayerxy VAR_TEMP_0, VAR_TEMP_1
	compare VAR_TEMP_0, 19
	goto_if_lt Route113_EventScript_DontSetAshWeather
	compare VAR_TEMP_0, 84
	goto_if_gt Route113_EventScript_DontSetAshWeather
	setweather WEATHER_VOLCANIC_ASH
	return

Route113_EventScript_DontSetAshWeather:: @ 81F2189
	return

Route113_EventScript_Gentleman:: @ 81F218A
	msgbox Route113_Text_AshCanBeFashionedIntoGlass, MSGBOX_NPC
	end

Route113_EventScript_NinjaBoy:: @ 81F2193
	msgbox Route113_Text_FunWalkingThroughAsh, MSGBOX_NPC
	end

Route113_EventScript_RouteSign111:: @ 81F219C
	msgbox Route113_Text_RouteSign111, MSGBOX_SIGN
	end

Route113_EventScript_RouteSignFallarbor:: @ 81F21A5
	msgbox Route113_Text_RouteSignFallarbor, MSGBOX_SIGN
	end

Route113_EventScript_GlassWorkshopSign:: @ 81F21AE
	msgbox Route113_Text_GlassWorkshopSign, MSGBOX_SIGN
	end

Route113_EventScript_TrainerTipsRegisterKeyItems:: @ 81F21B7
	msgbox Route113_Text_TrainerTipsRegisterKeyItems, MSGBOX_SIGN
	end

Route113_EventScript_Jaylen:: @ 81F21C0
	trainerbattle_single TRAINER_JAYLEN, Route113_Text_JaylenIntro, Route113_Text_JaylenDefeat
	msgbox Route113_Text_JaylenPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Dillon:: @ 81F21D7
	trainerbattle_single TRAINER_DILLON, Route113_Text_DillonIntro, Route113_Text_DillonDefeat
	msgbox Route113_Text_DillonPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Madeline:: @ 81F21EE
	trainerbattle_single TRAINER_MADELINE_1, Route113_Text_MadelineIntro, Route113_Text_MadelineDefeat, Route113_EventScript_RegisterMadeline
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route113_EventScript_RematchMadeline
	msgbox Route113_Text_MadelinePostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterMadeline:: @ 81F221A
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_MadelineRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_MADELINE_1
	release
	end

Route113_EventScript_RematchMadeline:: @ 81F2239
	trainerbattle_rematch TRAINER_MADELINE_1, Route113_Text_MadelineRematchIntro, Route113_Text_MadelineRematchDefeat
	msgbox Route113_Text_MadelinePostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lao:: @ 81F2250
	trainerbattle_single TRAINER_LAO_1, Route113_Text_LaoIntro, Route113_Text_LaoDefeat, Route113_EventScript_RegisterLao
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq Route113_EventScript_RematchLao
	msgbox Route113_Text_LaoPostBattle, MSGBOX_DEFAULT
	release
	end

Route113_EventScript_RegisterLao:: @ 81F227C
	special PlayerFaceTrainerAfterBattle
	waitmovement 0
	msgbox Route113_Text_LaoRegister, MSGBOX_DEFAULT
	register_matchcall TRAINER_LAO_1
	release
	end

Route113_EventScript_RematchLao:: @ 81F229B
	trainerbattle_rematch TRAINER_LAO_1, Route113_Text_LaoRematchIntro, Route113_Text_LaoRematchDefeat
	msgbox Route113_Text_LaoPostRematch, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lung:: @ 81F22B2
	trainerbattle_single TRAINER_LUNG, Route113_Text_LungIntro, Route113_Text_LungDefeat
	msgbox Route113_Text_LungPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tori:: @ 81F22C9
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_ToriIntro, Route113_Text_ToriDefeat, Route113_Text_ToriNotEnoughMons
	msgbox Route113_Text_ToriPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Tia:: @ 81F22E4
	trainerbattle_double TRAINER_TORI_AND_TIA, Route113_Text_TiaIntro, Route113_Text_TiaDefeat, Route113_Text_TiaNotEnoughMons
	msgbox Route113_Text_TiaPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Sophie:: @ 81F22FF
	trainerbattle_single TRAINER_SOPHIE, Route113_Text_SophieIntro, Route113_Text_SophieDefeat
	msgbox Route113_Text_SophiePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Coby:: @ 81F2316
	trainerbattle_single TRAINER_COBY, Route113_Text_CobyIntro, Route113_Text_CobyDefeat
	msgbox Route113_Text_CobyPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Lawrence:: @ 81F232D
	trainerbattle_single TRAINER_LAWRENCE, Route113_Text_LawrenceIntro, Route113_Text_LawrenceDefeat
	msgbox Route113_Text_LawrencePostBattle, MSGBOX_AUTOCLOSE
	end

Route113_EventScript_Wyatt:: @ 81F2344
	trainerbattle_single TRAINER_WYATT, Route113_Text_WyattIntro, Route113_Text_WyattDefeat
	msgbox Route113_Text_WyattPostBattle, MSGBOX_AUTOCLOSE
	end

Route113_Text_AshCanBeFashionedIntoGlass: @ 81F235B
	.string "와하하!!\n"
	.string "요즘 과학의 힘은 정말 대단해요!\p"
	.string "놀랍게도 이 화산재를\n"
	.string "유리로 바꿀 수 있으니까요!$"
	@ ワハハ!!ｎ
	@ いまの かがくりょくは すごいですぞ!ｐ
	@ なんと この かざんばいをｎ
	@ ガラスに かえることが できるのです!

Route113_Text_FunWalkingThroughAsh: @ 81F23CA
	.string "화산재가 가득 쌓인 풀숲 위에서\n"
	.string "걸으면 지나온 곳을 알 수 있어서\l"
	.string "엄청 재밌어!$"
	@ かざんばい つもった くさむらの うえｎ
	@ あるくと どこを とおったか わかるからｌ
	@ たのしく なっちゃう!

Route113_Text_RouteSign111: @ 81F2440
	.string "여기는 113번 도로\n"
	.string "{RIGHT_ARROW} 111번 도로$"
	@ ここは 113ばん どうろｎ
	@ ©しう 111ばん どうろ

Route113_Text_RouteSignFallarbor: @ 81F2456
	.string "여기는 113번 도로\n"
	.string "{LEFT_ARROW} 단풍마을$"
	@ ここは 113ばん どうろｎ
	@ ©しい ハジツゲタウン

Route113_Text_TrainerTipsRegisterKeyItems: @ 81F2471
	.string "정보 나눔 게시판!!\p"
	.string "가방의 중요한 물건에 넣은\n"
	.string "도구를 등록해 두면\l"
	.string "SELECT 버튼을 누르는 것만으로도\l"
	.string "쓸 수 있어서 편리해요!$"
	@ おとくな けいじばん!!ｐ
	@ バッグの たいせつなものに いれたｎ
	@ どうぐを とうろく しておくとｌ
	@ セレクトボタンを おすだけでｌ
	@ つかえるように なって べんり です!

Route113_Text_GlassWorkshopSign: @ 81F24F8
	.string "“유리 세공 가게”\n"
	.string "화산재로 유리를 만들어요$"
	@ 「ガラスざいくの おみせ」ｎ
	@ かざんばい から ガラスの どうぐ

