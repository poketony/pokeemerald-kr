.set LOCALID_COLE, 2
.set LOCALID_GERALD, 3
.set LOCALID_AXLE, 4
.set LOCALID_DANIELLE, 5

LavaridgeTown_Gym_1F_MapScripts:: @ 81FE6F4
	map_script MAP_SCRIPT_ON_TRANSITION, LavaridgeTown_Gym_1F_OnTransition
	.byte 0

LavaridgeTown_Gym_1F_OnTransition: @ 81FE6FA
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	call LavaridgeTown_Gym_1F_EventScript_CheckHideTrainers
	end

@ Unclear where/if these temp vars are getting checked
LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars:: @ 81FE705
	setvar VAR_TEMP_B, 0
	setvar VAR_TEMP_C, 0
	setvar VAR_TEMP_D, 0
	setvar VAR_TEMP_E, 0
	setvar VAR_TEMP_F, 0
	goto_if_defeated TRAINER_COLE LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar
	setvar VAR_TEMP_B, 1
LavaridgeTown_Gym_1F_EventScript_SetGeraldTempVar:: @ 81FE72C
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar
	setvar VAR_TEMP_C, 1
LavaridgeTown_Gym_1F_EventScript_SetAxleTempVar:: @ 81FE73A
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar
	setvar VAR_TEMP_D, 1
LavaridgeTown_Gym_1F_EventScript_SetDanielleTempVar:: @ 81FE748
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars
	setvar VAR_TEMP_E, 1
LavaridgeTown_Gym_1F_EventScript_EndSetTrainerTempVars:: @ 81FE756
	return

LavaridgeTown_Gym_1F_EventScript_CheckHideTrainers:: @ 81FE757
	goto_if_defeated TRAINER_COLE, LavaridgeTown_Gym_1F_EventScript_CheckHideGerald
	setobjectmovementtype LOCALID_COLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideGerald:: @ 81FE764
	goto_if_defeated TRAINER_GERALD, LavaridgeTown_Gym_1F_EventScript_CheckHideAxle
	setobjectmovementtype LOCALID_GERALD, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideAxle:: @ 81FE771
	goto_if_defeated TRAINER_AXLE, LavaridgeTown_Gym_1F_EventScript_CheckHideDanielle
	setobjectmovementtype LOCALID_AXLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_CheckHideDanielle:: @ 81FE77E
	goto_if_defeated TRAINER_DANIELLE, LavaridgeTown_Gym_1F_EventScript_EndCheckHideTrainers
	setobjectmovementtype LOCALID_DANIELLE, MOVEMENT_TYPE_HIDDEN
LavaridgeTown_Gym_1F_EventScript_EndCheckHideTrainers:: @ 81FE78B
	return

LavaridgeTown_Gym_1F_EventScript_Flannery:: @ 81FE78C
	trainerbattle_single TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryIntro, LavaridgeTown_Gym_1F_Text_FlanneryDefeat, LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated, NO_MUSIC
	specialvar VAR_RESULT, ShouldTryRematchBattle
	compare VAR_RESULT, TRUE
	goto_if_eq LavaridgeTown_Gym_1F_EventScript_FlanneryRematch
	goto_if_unset FLAG_RECEIVED_TM50, LavaridgeTown_Gym_1F_EventScript_GiveOverheat2
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostBattle, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_FlanneryDefeated:: @ 81FE7C1
	message LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge
	waitmessage
	call Common_EventScript_PlayGymBadgeFanfare
	msgbox LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis, MSGBOX_DEFAULT
	setflag FLAG_WHITEOUT_TO_LAVARIDGE
	setflag FLAG_DEFEATED_LAVARIDGE_GYM
	setflag FLAG_BADGE04_GET
	addvar VAR_PETALBURG_GYM_STATE, 1
	compare VAR_PETALBURG_GYM_STATE, 6
	call_if_eq Common_EventScript_ReadyPetalburgGymForBattle
	setvar VAR_0x8008, 4
	call Common_EventScript_SetGymTrainers
	setflag FLAG_HIDE_VERDANTURF_TOWN_WANDAS_HOUSE_WALLY
	setvar VAR_LAVARIDGE_TOWN_STATE, 1
	call LavaridgeTown_Gym_1F_EventScript_GiveOverheat
	closemessage
	delay 30
	playfanfare MUS_REGISTER_MATCH_CALL
	msgbox LavaridgeTown_Gym_1F_Text_RegisteredFlannery, MSGBOX_DEFAULT
	waitfanfare
	closemessage
	delay 30
	setflag FLAG_ENABLE_FLANNERY_MATCH_CALL
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat2:: @ 81FE81D
	giveitem ITEM_TM50
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowBagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	release
	end

LavaridgeTown_Gym_1F_EventScript_GiveOverheat:: @ 81FE841
	giveitem ITEM_TM50
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_BagIsFull
	msgbox LavaridgeTown_Gym_1F_Text_ExplainOverheat, MSGBOX_DEFAULT
	setflag FLAG_RECEIVED_TM50
	return

LavaridgeTown_Gym_1F_EventScript_FlanneryRematch:: @ 81FE864
	trainerbattle_rematch_double TRAINER_FLANNERY_1, LavaridgeTown_Gym_1F_Text_FlanneryPreRematch, LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat, LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons
	msgbox LavaridgeTown_Gym_1F_Text_FlanneryPostRematch, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Cole:: @ 81FE87F
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_COLE, LOCALID_COLE, LavaridgeTown_Gym_1F_Text_ColeIntro, LavaridgeTown_Gym_1F_Text_ColeDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_ColePostBattle MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_EventScript_CheckTrainerScript:: @ 81FE89A
	call LavaridgeTown_Gym_1F_EventScript_SetTrainerTempVars
	release
	special ShouldTryGetTrainerScript
	compare VAR_RESULT, 1
	goto_if_eq EventScript_GotoTrainerScript
	end

LavaridgeTown_Gym_1F_EventScript_Axle:: @ 81FE8AF
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_AXLE, LOCALID_AXLE, LavaridgeTown_Gym_1F_Text_AxleIntro, LavaridgeTown_Gym_1F_Text_AxleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_AxlePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Keegan:: @ 81FE8CA
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_KEEGAN, LOCALID_KEEGAN, LavaridgeTown_Gym_B1F_Text_KeeganIntro, LavaridgeTown_Gym_B1F_Text_KeeganDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_KeeganPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Danielle:: @ 81FE8E5
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_DANIELLE, LOCALID_DANIELLE, LavaridgeTown_Gym_1F_Text_DanielleIntro, LavaridgeTown_Gym_1F_Text_DanielleDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_DaniellePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_Gerald:: @ 81FE900
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_GERALD, LOCALID_GERALD, LavaridgeTown_Gym_1F_Text_GeraldIntro, LavaridgeTown_Gym_1F_Text_GeraldDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_1F_Text_GeraldPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jace:: @ 81FE91B
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JACE, LOCALID_JACE, LavaridgeTown_Gym_B1F_Text_JaceIntro, LavaridgeTown_Gym_B1F_Text_JaceDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JacePostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Jeff:: @ 81FE936
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_JEFF, LOCALID_JEFF, LavaridgeTown_Gym_B1F_Text_JeffIntro, LavaridgeTown_Gym_B1F_Text_JeffDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_JeffPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_B1F_EventScript_Eli:: @ 81FE951
	trainerbattle TRAINER_BATTLE_CONTINUE_SCRIPT, TRAINER_ELI, LOCALID_ELI, LavaridgeTown_Gym_B1F_Text_EliIntro, LavaridgeTown_Gym_B1F_Text_EliDefeat, LavaridgeTown_Gym_EventScript_CheckTrainerScript
	msgbox LavaridgeTown_Gym_B1F_Text_EliPostBattle, MSGBOX_AUTOCLOSE
	end

LavaridgeTown_Gym_1F_EventScript_GymGuide:: @ 81FE96C
	lock
	faceplayer
	goto_if_set FLAG_DEFEATED_LAVARIDGE_GYM, LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory
	msgbox LavaridgeTown_Gym_1F_Text_GymGuideAdvice, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_GymGuidePostVictory:: @ 81FE981
	msgbox LavaridgeTown_Gym_1F_Text_GymGuidePostVictory, MSGBOX_DEFAULT
	release
	end

LavaridgeTown_Gym_1F_EventScript_LeftGymStatue:: @ 81FE98B
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_RightGymStatue:: @ 81FE99B
	lockall
	goto_if_set FLAG_BADGE04_GET, LavaridgeTown_Gym_1F_EventScript_GymStatueCertified
	goto LavaridgeTown_Gym_1F_EventScript_GymStatue
	end

LavaridgeTown_Gym_1F_EventScript_GymStatueCertified:: @ 81FE9AB
	msgbox LavaridgeTown_Gym_1F_Text_GymStatueCertified, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_EventScript_GymStatue:: @ 81FE9B5
	msgbox LavaridgeTown_Gym_1F_Text_GymStatue, MSGBOX_DEFAULT
	releaseall
	end

LavaridgeTown_Gym_1F_Text_GymGuideAdvice: @ 81FE9BF
	.string "잘 있었나!!\n"
	.string "챔피언을 목표로 하는 {PLAYER}!!\p"
	.string "용암마을 체육관 관장 민지는\n"
	.string "불꽃타입 포켓몬 사용자다!\p"
	.string "포켓몬에 대한 정열은\n"
	.string "화산보다 격렬하고 뜨겁지!\p"
	.string "잘못해서 가까이라도 가면\n"
	.string "화상 입으니 물로 식히면서\l"
	.string "힘내라-구!!$"
	// げんき しとぉや!!ｎ
	// チャンピオンを めざす §あ!!ｐ
	// フエンタウン ジムの リ-ダ- アスナはｎ
	// ほのおタイプ ポケモンの つかいてだ!ｐ
	// ポケモンに たいする じょうねつはｎ
	// かざん よりも はげしく あちィ!ｐ
	// うっかり ちかづくと やけど するからｎ
	// みずで ひやしながらｌ
	// きばってこ- な!!

LavaridgeTown_Gym_1F_Text_GymGuidePostVictory: @ 81FEAB8
	.string "이야- 뜨거운 배틀이었어!$"
	// いやあ- あちィ たたかい だった!

LavaridgeTown_Gym_1F_Text_ColeIntro: @ 81FEADE
	.string "아뜨뜨뜨뜨뜨거!\n"
	.string "푸하-앗! 뜨거웠어-!$"
	// あちちちちちっ!ｎ
	// ぷは-っ! あつかった-っ!

LavaridgeTown_Gym_1F_Text_ColeDefeat: @ 81FEAFB
	.string "땀이 눈에 들어갔어...$"
	// あせが めに しみるぜ……

LavaridgeTown_Gym_1F_Text_ColePostBattle: @ 81FEB1C
	.string "모래찜질은 혈액순환을 도와서\n"
	.string "관절 통증에 효과적이라고!$"
	// すなブロは けっこうが よくなってｎ
	// かんせつの いたみに こうかてき だぜ!

LavaridgeTown_Gym_1F_Text_AxleIntro: @ 81FEB7B
	.string "내 소중한 스트레스 해소 시간을\n"
	.string "방해하지 마-!$"
	// ストレスを かいしょう するｎ
	// おれの ひとときを ジャマ するな-っ!

LavaridgeTown_Gym_1F_Text_AxleDefeat: @ 81FEBC0
	.string "민지님에게 져버려랏-!$"
	// アスナさんに まけてしまえ-っ!

LavaridgeTown_Gym_1F_Text_AxlePostBattle: @ 81FEBE1
	.string "하아 후우...\p"
	.string "모래찜질을 하고 있으면\n"
	.string "꽤 피곤해져...$"
	// はあ ふう……ｐ
	// すなブロに ながく はいっているとｎ
	// けっこう つかれちゃう もんだよ……

LavaridgeTown_Gym_B1F_Text_KeeganIntro: @ 81FEC31
	.string "역시 지친 것 같군\n"
	.string "모래찜질하면서 한숨 쉬었다 가고 싶지?\p"
	.string "하지만 기력을 유지하는 것도\n"
	.string "트레이너에게 필요한 능력 중 하나다$"
	// さすがに つかれてきた ようだねｎ
	// すなブロで ひとやすみ したいだろう?ｐ
	// だが きりょくを たもつ こともｎ
	// トレ-ナ-に ひつような さいのう だよ

LavaridgeTown_Gym_B1F_Text_KeeganDefeat: @ 81FECE3
	.string "불장난이 부상의 원인인 건가...$"
	// ひあそびは けがのもと だったか……

LavaridgeTown_Gym_B1F_Text_KeeganPostBattle: @ 81FED02
	.string "네 실력은 진짜다...\n"
	.string "하지만 관장인 민지님은 강해!\p"
	.string "방심하면 크게 화상 입을 거다!$"
	// きみの ちからは ほんものだ……ｎ
	// でも リ-ダ- アスナさんは つよいよ!ｐ
	// あまく みていると おおやけど するぜ!

LavaridgeTown_Gym_1F_Text_GeraldIntro: @ 81FED72
	.string "네 포켓몬은\n"
	.string "200도의 열기를 이겨낼 수 있나!?$"
	// おまえの ポケモンｎ
	// 200どの あつさに たえられるかよ!?

LavaridgeTown_Gym_1F_Text_GeraldDefeat: @ 81FED9E
	.string "불태우는 방법이 이상했나...$"
	// もえかたが たりなかったか……

LavaridgeTown_Gym_1F_Text_GeraldPostBattle: @ 81FEDBB
	.string "200도의 열기라는 건\n"
	.string "용암의 온도!\p"
	.string "네 포켓몬은 나를 이겼으니까\n"
	.string "용암 속에서도 문제없겠군!$"
	// 200どの あつさ ってのはｎ
	// ようがんの おんど!ｐ
	// おまえの ポケモン おれに かてたんだからｎ
	// ようがんの なかでも へいき だろうな!

LavaridgeTown_Gym_1F_Text_DanielleIntro: @ 81FEE22
	.string "으-음!\n"
	.string "그럼 상대해 줄게!$"
	// え-っと!ｎ
	// じゃあ しょうぶの あいて しますね!

LavaridgeTown_Gym_1F_Text_DanielleDefeat: @ 81FEE42
	.string "왜 이렇게 강해!?$"
	// なんて つよいの!?

LavaridgeTown_Gym_1F_Text_DaniellePostBattle: @ 81FEE5D
	.string "나도 민지님처럼\n"
	.string "아름답고 강한 트레이너가 될 거야!$"
	// あたしも アスナさんと いっしょにｎ
	// きれいで つよい トレ-ナ-に なるんだ!

LavaridgeTown_Gym_B1F_Text_JaceIntro: @ 81FEE9D
	.string "자자!\n"
	.string "마음이 식기 전에 하자고!$"
	// ほら ほらっ!ｎ
	// きもちが さめない うちに いくぜっ!

LavaridgeTown_Gym_B1F_Text_JaceDefeat: @ 81FEED5
	.string "이렇게나 뜨거운데\n"
	.string "내 마음은 쓸쓸하구만...$"
	// こんなに あついのにｎ
	// おれの こころが さむい……

LavaridgeTown_Gym_B1F_Text_JacePostBattle: @ 81FEF07
	.string "그 정도의 투지를 불태울 수 있다면\n"
	.string "어쩌면 관장을 이길지도 모르지$"
	// そのくらい とうしを もやして いればｎ
	// もしかしたら リ-ダ-にも かてるかもな

LavaridgeTown_Gym_B1F_Text_JeffIntro: @ 81FEF60
	.string "봐 이 솟아오르는 불꽃을!\n"
	.string "내 승리를 축하하고 있는 거야!$"
	// みよ この もえさかる ほのおを!ｎ
	// オレの しょうりを よげんして いるのだ!

LavaridgeTown_Gym_B1F_Text_JeffDefeat: @ 81FEFA7
	.string "이상하네$"
	// おかしいなあ

LavaridgeTown_Gym_B1F_Text_JeffPostBattle: @ 81FEFC2
	.string "역시 난 대단해!\n"
	.string "모닥불 위를 맨발로 걷고 있잖아!\p"
	.string "... 너는 따라하면 안 돼$"
	// いいもんね! オレなんてｎ
	// たきびの うえを はだしで はしれるぜ!ｐ
	// …… おまえは まね するなよ

LavaridgeTown_Gym_B1F_Text_EliIntro: @ 81FF025
	.string "산 중에서도 특히\n"
	.string "화산이 제일 좋아서...$"
	// やまの なかでも とくにｎ
	// かざんが だいすき でして……

LavaridgeTown_Gym_B1F_Text_EliDefeat: @ 81FF05F
	.string "갈팡질팡하는 사이에\n"
	.string "져버린 겁니까$"
	// あれよ あれよと いうまにｎ
	// まけちまった わけでして

LavaridgeTown_Gym_B1F_Text_EliPostBattle: @ 81FF09A
	.string "민지님의 강함에 반해서\n"
	.string "전 여기에 있는 겁니다...\l"
	.string "헤헤헤헤$"
	// アスナさんの つよさに ほれてｎ
	// わしは ここに いるわけ でして……ｌ
	// へへへへ

LavaridgeTown_Gym_1F_Text_FlanneryIntro: @ 81FF0DC
	.string "어서 오세요 ...가 아니라\p"
	.string "용케 여기까지 왔군!\p"
	.string "전 여기 체육관 관장을\n"
	.string "맡게 된 ...이 아니라\p"
	.string "체육관 관장을 맡은 민지다!\p"
	.string "크윽...\n"
	.string "체육관 관장 된 지 얼마 안 됐다고\l"
	.string "방심하지 마라!\p"
	.string "할아버지에게 물려받은 재능과\n"
	.string "이 땅에서 갈고닦은 핫한 기술\l"
	.string "너에게 보여주겠어!$"
	// ようこそ ……じゃなくてｐ
	// よくぞ ここまで きた ものだな!ｐ
	// わたしは ここの ジムリ-ダ-をｎ
	// つとめさせて いただく ……じゃなくてｐ
	// ジムリ-ダ-を まかされた アスナだ!ｐ
	// くう……ｎ
	// ジムリ-ダ-に なりたて だからってｌ
	// ゆだん など しないことだ!ｐ
	// おじいちゃん ゆずりの さいのうとｎ
	// このとちで みがきあげた ホットな わざｌ
	// あなたに みせてやる!

LavaridgeTown_Gym_1F_Text_FlanneryDefeat: @ 81FF233
	.string "크윽...\n"
	.string "어깨에 힘이 들어가고 말았네...\p"
	.string "나...\n"
	.string "체육관 관장 된 지 얼마 안 됐다고\l"
	.string "좀 무리한 걸까...\p"
	.string "역시 나답게 하지 않으면\n"
	.string "같이 싸워주는\l"
	.string "포켓몬도 힘들 거야!\p"
	.string "그걸 가르쳐준\n"
	.string "너에게 이걸 줄게!$"
	// くう……ｎ
	// かたに ちから はいっちゃって……ｐ
	// あたし……ｎ
	// ジムリ-ダ-に なりたて だからってｌ
	// ちょっと むり していたのかな……ｐ
	// やっぱ じぶんらしく でないとｎ
	// いっしょに たたかってくれるｌ
	// ポケモンも こまっちゃうよね!ｐ
	// それを おしえてくれたｎ
	// あなたに これ あげる!

LavaridgeTown_Gym_1F_Text_ReceivedHeatBadge: @ 81FF32F
	.string "{PLAYER}{K_EUNNEUN} 민지에게서\n"
	.string "히트배지를 받았다!$"
	// §あは アスナからｎ
	// ヒ-トバッジを もらった!

LavaridgeTown_Gym_1F_Text_ExplainHeatBadgeTakeThis: @ 81FF359
	.string "히트배지가 있으면\n"
	.string "레벨 50까지는\l"
	.string "다른 사람에게 받은 포켓몬도\l"
	.string "말을 잘 들어줘!\p"
	.string "그리고 비전기술 괴력을\n"
	.string "사용할 수 있게 되지!\p"
	.string "이건 감사의 마음이야\n"
	.string "사양하지 말고 받아줘!$"
	// ヒ-トバッジが あればｎ
	// レベル50 までならｌ
	// ひとから もらった ポケモンでもｌ
	// いうことを きいて くれるんだ!ｐ
	// それに ひでんわざの かいりき がｎ
	// つかえるようにも なるよ!ｐ
	// これは かんしゃの きもちｎ
	// えんりょ せずに もらって!

LavaridgeTown_Gym_1F_Text_ExplainOverheat: @ 81FF45C
	.string "기술머신50에는\n"
	.string "오버히트가 들어 있어!\p"
	.string "그 기술은 상대에게\n"
	.string "큰 데미지를 주지!\p"
	.string "하지만 특수공격이\n"
	.string "크게 떨어지니까\l"
	.string "장기전엔 안 맞을지도...\p"
	.string "...... ...... ......$"
	// わざマシン50 にはｎ
	// オ-バ-ヒ-トが はいってるよ!ｐ
	// その わざは あいてにｎ
	// おおきな ダメ-ジを あたえるんだ!ｐ
	// だけど とくこうがｎ
	// がくっと さがっちゃう からｌ
	// ながい しょうぶには むかないかもｐ
	// …… …… ……

LavaridgeTown_Gym_1F_Text_RegisteredFlannery: @ 81FF517
	.string "체육관 관장 민지를\n"
	.string "포켓내비에 등록했다!$"
	// ジムリ-ダ- アスナをｎ
	// ポケナビに とうろく した!

LavaridgeTown_Gym_1F_Text_FlanneryPostBattle: @ 81FF546
	.string "너의 강함\n"
	.string "누군가를 떠올리게 하네...\p"
	.string "그래! 등화도시의 체육관 관장\n"
	.string "종길님과 닮았어!$"
	// あなたの つよさｎ
	// だれかを おもいださせるの よね……ｐ
	// そうだ! トウカシティの ジムリ-ダ-ｎ
	// センリさんに にているんだ!

LavaridgeTown_Gym_1F_Text_GymStatue: @ 81FF5A9
	.string "용암마을 포켓몬체육관$"
	// フエンタウン ポケモンジム

LavaridgeTown_Gym_1F_Text_GymStatueCertified: @ 81FF5C4
	.string "용암마을 포켓몬체육관\p"
	.string "민지 인정 트레이너!\n"
	.string "{PLAYER}$"
	// フエンタウン ポケモンジムｐ
	// アスナ にんてい トレ-ナ-!ｎ
	// §あ

LavaridgeTown_Gym_1F_Text_FlanneryPreRematch: @ 81FF601
	.string "민지: 승부에서 진 정도로\n"
	.string "난 주저않지 않아!\p"
	.string "왜냐면 나는 포켓몬을 좋아하고\n"
	.string "승부하는 게 좋고\l"
	.string "그리고... 이 체육관이 좋으니까!\p"
	.string "자 다시 한 번 함께\n"
	.string "핫한 기술을 부딪쳐 보자!$"
	// アスナ『しょうぶに まけた ぐらいでｎ
	// あたしは へこたれたり しない!ｐ
	// なぜなら あたしは ポケモンが すきでｎ
	// しょうぶを するのが すきでｌ
	// それに…… このジムが すきだから!ｐ
	// さあ もういちど いっしょにｎ
	// ホットな わざを ぶつけあいましょう!

LavaridgeTown_Gym_1F_Text_FlanneryRematchDefeat: @ 81FF69F
	.string "후우! 폭발 직전!$"
	// ふぅ! ばくはつ すんぜん!

LavaridgeTown_Gym_1F_Text_FlanneryPostRematch: @ 81FF6BF
	.string "민지: 승부에선 졌지만\n"
	.string "이런 히트한 배틀을 할 수 있어서\l"
	.string "난 만족했어!\p"
	.string "나중에 또 승부하자!$"
	// アスナ『しょうぶには まけたけどｎ
	// こんなに ヒ-トする たたかいが できてｌ
	// あたしは まんぞくよ!ｐ
	// そのうち また しょうぶ しましょうね!

LavaridgeTown_Gym_1F_Text_FlanneryRematchNeedTwoMons: @ 81FF75E
	.string "민지: 승부에서 진 정도로\n"
	.string "난 주저않지 않아!\p"
	.string "왜냐면 나는 포켓몬을 좋아하고\n"
	.string "승부하는 게 좋고\l"
	.string "그리고... 이 체육관이 좋으니까!\p"
	.string "자 다시 한 번 함께\n"
	.string "핫한 기술을 부딪쳐 보자!\p"
	.string "...어라? 싸울 수 있는 포켓몬이\n"
	.string "한 마리밖에 없구나\p"
	.string "미안하지만 두 마리 이상\n"
	.string "포켓몬을 데리고 와줘$"
	// アスナ『しょうぶに まけた ぐらいでｎ
	// あたしは へこたれたり しない!ｐ
	// なぜなら あたしは ポケモンが すきでｎ
	// しょうぶを するのが すきでｌ
	// それに…… このジムが すきだから!ｐ
	// さあ もういちど いっしょにｎ
	// ホットな わざを ぶつけあいましょう!ｐ
	// ……あら? たたかえる ポケモンをｎ
	// 1ひきしか もって いないんですねｐ
	// すみませんけど 2ひき いじょうのｎ
	// ポケモンを もって きてください
