.equ LOCALID_WANDAS_BF, 1
.set LOCALID_BRINEY, 5
.set LOCALID_GRUNT, 6
.set LOCALID_PEEKO, 7
.equ LOCALID_WANDA, 10

RusturfTunnel_MapScripts:: @ 822CE27
	map_script MAP_SCRIPT_ON_TRANSITION, RusturfTunnel_OnTransition
	map_script MAP_SCRIPT_ON_FRAME_TABLE, RusturfTunnel_OnFrame
	.byte 0

RusturfTunnel_OnFrame: @ 822CE32
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 4, RusturfTunnel_EventScript_ClearTunnelScene
	map_script_2 VAR_RUSTURF_TUNNEL_STATE, 5, RusturfTunnel_EventScript_ClearTunnelScene
	.2byte 0

RusturfTunnel_OnTransition: @ 822CE44
	compare VAR_RUSTURF_TUNNEL_STATE, 2
	call_if_eq RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos
	end

RusturfTunnel_EventScript_SetAquaGruntAndPeekoPos:: @ 822CE50
	setobjectxyperm LOCALID_PEEKO, 13, 4
	setobjectxyperm LOCALID_GRUNT, 13, 5
	return

RusturfTunnel_EventScript_Wanda:: @ 822CE5F
	lock
	faceplayer
	msgbox RusturfTunnel_Text_BoyfriendOnOtherSideOfRock, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_WandasBoyfriend:: @ 822CE76
	lock
	faceplayer
	goto_if_set FLAG_TEMP_1, RusturfTunnel_EventScript_AlreadySpokenTo
	setflag FLAG_TEMP_1
	msgbox RusturfTunnel_Text_WhyCantTheyKeepDigging, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_AlreadySpokenTo:: @ 822CE99
	msgbox RusturfTunnel_Text_ToGetToVerdanturf, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
	waitmovement 0
	release
	end

RusturfTunnel_EventScript_ClearTunnelScene:: @ 822CEAE
	lockall
	compare VAR_TEMP_1, 1
	call_if_eq RusturfTunnel_EventScript_FaceWandasBoyfriend1
	compare VAR_TEMP_1, 2
	call_if_eq RusturfTunnel_EventScript_FaceWandasBoyfriend2
	compare VAR_TEMP_1, 3
	call_if_eq RusturfTunnel_EventScript_FaceWandasBoyfriend3
	call RusturfTunnel_EventScript_WandasBoyfriendNotice
	msgbox RusturfTunnel_Text_YouShatteredBoulderTakeHM, MSGBOX_DEFAULT
	compare VAR_TEMP_1, 2
	call_if_eq RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer
	compare VAR_TEMP_1, 3
	call_if_eq RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer
	giveitem ITEM_HM04
	setflag FLAG_RECEIVED_HM04
	msgbox RusturfTunnel_Text_ExplainStrength, MSGBOX_DEFAULT
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq RusturfTunnel_EventScript_BoyfriendApproachWanda1
	compare VAR_TEMP_1, 2
	call_if_eq RusturfTunnel_EventScript_BoyfriendApproachWanda2
	compare VAR_TEMP_1, 3
	call_if_eq RusturfTunnel_EventScript_BoyfriendApproachWanda3
	msgbox RusturfTunnel_Text_WandaReunion, MSGBOX_DEFAULT
	closemessage
	compare VAR_TEMP_1, 1
	call_if_eq RusturfTunnel_EventScript_WandaAndBoyfriendExit1
	compare VAR_TEMP_1, 2
	call_if_eq RusturfTunnel_EventScript_WandaAndBoyfriendExit
	compare VAR_TEMP_1, 3
	call_if_eq RusturfTunnel_EventScript_WandaAndBoyfriendExit
	call RusturfTunnel_EventScript_SetRusturfTunnelOpen
	releaseall
	end

RusturfTunnel_EventScript_BoyfriendApproachWanda1:: @ 822CF5D
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend1
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda1
	waitmovement 0
	return

RusturfTunnel_EventScript_BoyfriendApproachWanda2:: @ 822CF6F
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda
	waitmovement 0
	applymovement LOCALID_WANDA, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RusturfTunnel_EventScript_BoyfriendApproachWanda3:: @ 822CF8B
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchBoyfriend
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_BoyfriendApproachWanda
	waitmovement 0
	applymovement LOCALID_WANDA, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend1:: @ 822CFA7
	applymovement LOCALID_WANDAS_BF, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend2:: @ 822CFBC
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_BoyfriendFaceRight
	waitmovement 0
	return

RusturfTunnel_EventScript_FaceWandasBoyfriend3:: @ 822CFC7
	return

RusturfTunnel_EventScript_WandasBoyfriendApproachPlayer:: @ 822CFC8
	closemessage
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendApproachPlayer
	waitmovement 0
	return

RusturfTunnel_EventScript_WandaAndBoyfriendExit1:: @ 822CFD4
	applymovement LOCALID_WANDA, RusturfTunnel_Movement_WandaExit1
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendExit1
	waitmovement 0
	return

RusturfTunnel_EventScript_WandaAndBoyfriendExit:: @ 822CFE6
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchWandaExit
	applymovement LOCALID_WANDA, RusturfTunnel_Movement_WandaExit
	applymovement LOCALID_WANDAS_BF, RusturfTunnel_Movement_WandasBoyfriendExit
	waitmovement 0
	return

RusturfTunnel_EventScript_WandasBoyfriendNotice:: @ 822CFFF
	playse SE_PIN
	applymovement LOCALID_WANDAS_BF, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement LOCALID_WANDAS_BF, Common_Movement_Delay48
	waitmovement 0
	return

RusturfTunnel_Movement_WandaExit1: @ 822D017
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandaExit: @ 822D023
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_PlayerWatchWandaExit: @ 822D02F
	delay_8
	walk_in_place_fastest_up
	delay_16
	delay_16
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_Unused1: @ 822D035
	walk_left
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_Unused2: @ 822D038
	walk_down
	walk_in_place_fastest_up
	delay_8
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_Unused3: @ 822D03D
	walk_up
	walk_in_place_fastest_down
	delay_8
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_PlayerWatchBoyfriend1: @ 822D042
	walk_left
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_PlayerWatchBoyfriend: @ 822D045
	walk_right
	walk_in_place_fastest_left
	step_end

RusturfTunnel_Movement_BoyfriendFaceRight: @ 822D048
	walk_up
	walk_in_place_fastest_right
	step_end

RusturfTunnel_Movement_WandasBoyfriendExit1: @ 822D04B
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandasBoyfriendExit: @ 822D058
	walk_up
	walk_right
	walk_right
	walk_right
	walk_right
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	walk_down
	step_end

RusturfTunnel_Movement_WandasBoyfriendApproachPlayer: @ 822D065
	walk_right
	step_end

RusturfTunnel_Movement_BoyfriendApproachWanda1: @ 822D067
	walk_in_place_fast_up
	walk_in_place_fast_up
	walk_fast_up
	walk_fast_right
	step_end

RusturfTunnel_Movement_BoyfriendApproachWanda: @ 822D06C
	walk_in_place_fast_right
	walk_in_place_fast_right
	walk_fast_right
	walk_in_place_fastest_up
	step_end

RusturfTunnel_EventScript_TunnelBlockagePos1:: @ 822D071
	setvar VAR_TEMP_1, 1
	end

RusturfTunnel_EventScript_TunnelBlockagePos2:: @ 822D077
	setvar VAR_TEMP_1, 2
	end

RusturfTunnel_EventScript_TunnelBlockagePos3:: @ 822D07D
	setvar VAR_TEMP_1, 3
	end

RusturfTunnel_EventScript_AquaGruntBackUp:: @ 822D083
	lockall
	msgbox RusturfTunnel_Text_ComeAndGetSome, MSGBOX_DEFAULT
	closemessage
	applymovement LOCALID_GRUNT, RusturfTunnel_Movement_GruntAndPeekoBackUp
	applymovement LOCALID_PEEKO, RusturfTunnel_Movement_GruntAndPeekoBackUp
	waitmovement 0
	copyobjectxytoperm LOCALID_GRUNT
	copyobjectxytoperm LOCALID_PEEKO
	setvar VAR_RUSTURF_TUNNEL_STATE, 3
	releaseall
	end

RusturfTunnel_Movement_GruntAndPeekoBackUp: @ 822D0AB
	lock_facing_direction
	walk_right
	unlock_facing_direction
	step_end

RusturfTunnel_EventScript_Peeko:: @ 822D0AF
	lock
	faceplayer
	waitse
	playmoncry SPECIES_WINGULL, 0
	msgbox RusturfTunnel_Text_Peeko, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RusturfTunnel_EventScript_Grunt:: @ 822D0C2
	lock
	faceplayer
	playbgm MUS_ENCOUNTER_AQUA, 0
	msgbox RusturfTunnel_Text_GruntIntro, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_GRUNT_RUSTURF_TUNNEL, RusturfTunnel_Text_GruntDefeat
	msgbox RusturfTunnel_Text_GruntTakePackage, MSGBOX_DEFAULT
	giveitem ITEM_DEVON_GOODS
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PushPlayerAsideForGrunt
	applymovement LOCALID_GRUNT, RusturfTunnel_Movement_GruntEscape
	waitmovement 0
	removeobject LOCALID_GRUNT
	delay 50
	addobject LOCALID_BRINEY
	applymovement LOCALID_BRINEY, RusturfTunnel_Movement_BrineyApproachPeeko1
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerMoveAsideForBriney
	applymovement LOCALID_BRINEY, RusturfTunnel_Movement_BrineyApproachPeeko2
	waitmovement 0
	msgbox RusturfTunnel_Text_PeekoGladToSeeYouSafe, MSGBOX_DEFAULT
	applymovement LOCALID_BRINEY, Common_Movement_FacePlayer
	waitmovement 0
	message RusturfTunnel_Text_ThankYouLetsGoHomePeeko
	waitmessage
	waitse
	playmoncry SPECIES_WINGULL, 0
	waitbuttonpress
	waitmoncry
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, RusturfTunnel_Movement_PlayerWatchBrineyExit
	applymovement LOCALID_BRINEY, RusturfTunnel_Movement_BrineyExit
	applymovement LOCALID_PEEKO, RusturfTunnel_Movement_PeekoExit
	waitmovement 0
	removeobject LOCALID_BRINEY
	removeobject LOCALID_PEEKO
	clearflag FLAG_DEVON_GOODS_STOLEN
	setflag FLAG_RECOVERED_DEVON_GOODS
	setvar VAR_RUSTBORO_CITY_STATE, 4
	setvar VAR_BRINEY_HOUSE_STATE, 1
	setflag FLAG_HIDE_ROUTE_116_MR_BRINEY
	release
	end

RusturfTunnel_Movement_PushPlayerAsideForGrunt: @ 822D178
	face_down
	lock_facing_direction
	walk_up
	unlock_facing_direction
	walk_in_place_fastest_left
	step_end

RusturfTunnel_Movement_PlayerMoveAsideForBriney: @ 822D17E
	walk_down
	walk_in_place_fastest_up
	step_end

RusturfTunnel_Movement_GruntEscape: @ 822D181
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	walk_fast_left
	step_end

RusturfTunnel_Movement_BrineyApproachPeeko1: @ 822D18B
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

RusturfTunnel_Movement_BrineyExit: @ 822D193
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RusturfTunnel_Movement_PlayerWatchBrineyExit: @ 822D19F
	delay_16
	delay_8
	delay_4
	walk_in_place_fastest_left
	step_end

RusturfTunnel_Movement_BrineyApproachPeeko2: @ 822D1A4
	delay_16
	walk_right
	step_end

RusturfTunnel_Movement_PeekoExit: @ 822D1A7
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	walk_left
	step_end

RusturfTunnel_EventScript_Mike:: @ 822D1B1
	trainerbattle_single TRAINER_MIKE_2, RusturfTunnel_Text_MikeIntro, RusturfTunnel_Text_MikeDefeat
	msgbox RusturfTunnel_Text_MikePostBattle, MSGBOX_AUTOCLOSE
	end

RusturfTunnel_Text_ComeAndGetSome: @ 822D1C8
	.string "덤빌 거야?\n"
	.string "덤빌 테면 덤벼 봐!$"
	// くるのか?ｎ
	// くるなら こいよ!

RusturfTunnel_Text_Peeko: @ 822D1F7
	.string "피코: 삐- 삐요-!$"
	// ピ-コちゃん『ピ ピひょ-!

RusturfTunnel_Text_GruntIntro: @ 822D20A
	.string "에-잇 젠장-!\p"
	.string "빼앗은 포켓몬은\n"
	.string "전혀 도움도 안 되지\p"
	.string "적당한 곳으로 도망쳤다고 생각했는데\n"
	.string "이 터널은 막혀 있잖아-!\p"
	.string "어이! 너!\n"
	.string "나랑 승부할 거지!?$"
	// え-い くっそ-!ｐ
	// うばった ポケモンはｎ
	// なんの やくにも たたないしｐ
	// いいところへ にげこめたと おもったのにｎ
	// この トンネル いきどまり じゃね-か!ｐ
	// やい! おまえ!ｎ
	// おれと しょうぶ するんだな!?

RusturfTunnel_Text_GruntDefeat: @ 822D2B0
	.string "으 으으윽-!\n"
	.string "나의 악행도 막다른 길인가!$"
	// む むぐぐ-!ｎ
	// おれの あくじも いきどまりかっ!

RusturfTunnel_Text_GruntTakePackage: @ 822D2E1
	.string "이상하네...\p"
	.string "리더의 말로는 뭔가의 화물을\n"
	.string "데봉에서 훔쳐 오기만 하면 되는\l"
	.string "편한 일이었는데...\p"
	.string "쳇!\n"
	.string "이딴 거 그냥 돌려주고 만다!$"
	// おかしいなあ……ｐ
	// リ-ダ-の はなしでは なにかの にもつをｎ
	// デボンから ぬすんでくる っていうｌ
	// らくな しごと だった はずなのに……ｐ
	// ちぇっ!ｎ
	// こんなもん かえして やらあ!

RusturfTunnel_Text_PeekoGladToSeeYouSafe: @ 822D395
	.string "피코! 무사해서 다행이구나!$"
	// ピ-コちゃん! ぶじで よかった!

RusturfTunnel_Text_ThankYouLetsGoHomePeeko: @ 822D3BA
	.string "자넨 피코의\n"
	.string "생명의 은인일세!\p"
	.string "난 하기라고 하는데\n"
	.string "자네는 이름이...?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "그렇군 {PLAYER}{K_I}라고 하는구먼!\n"
	.string "정말 고맙네!\p"
	.string "앞으로 곤란한 일이 있으면\n"
	.string "사양 말고 나한테 말하게나!\p"
	.string "평소에는 등화숲 가까이에 있는\n"
	.string "해변의 작은 집에 있으니 말이야!\p"
	.string "자 피코\n"
	.string "우리 집으로 돌아가자꾸나!\p"
	.string "피코: 삐요오--!!$"
	// あんたは ピ-コちゃんのｎ
	// いのちの おんじん じゃよ!ｐ
	// わしは ハギと いうのじゃがｎ
	// きみは……?ｐ
	// …… …… ……ｎ
	// …… …… ……ｐ
	// そうか §あ§おと いうのか!ｎ
	// ほんとうに ありがとうよ!ｐ
	// これからさき こまった ことが あったらｎ
	// えんりょなく わしに いっとくれ!ｐ
	// いつもは トウカのもりの ちかくに あるｎ
	// はまべの こやに いるからの!ｐ
	// さあ ピ-コちゃんｎ
	// わしらの おうちに かえろうな!ｐ
	// ピ-コちゃん『ピひょ-っ!!

RusturfTunnel_Text_WhyCantTheyKeepDigging: @ 822D510
	.string "......\p"
	.string "어째서 더 파지 못하는 거지...\n"
	.string "이 바위가 너무 딱딱해서 그런가?\p"
	.string "이 앞에 있는 잔디마을이라는 곳에\n"
	.string "사랑하는 여자친구가 있는데...\p"
	.string "금탄도시랑 잔디마을을 터널로 연결하면\n"
	.string "매일 여자친구를 보러 갈 수 있어\p"
	.string "그런데 이건...\n"
	.string "난 도대체 어쩌면 좋은 거야...$"
	// ……ｐ
	// どうして これいじょう ほれない……ｎ
	// この いわが かたすぎるのか?ｐ
	// このさきの シダケタウンという ところにｎ
	// あいする かのじょが いるのに……ｐ
	// カナズミと シダケを トンネルで むすべばｎ
	// まいにち かのじょに あいに いけるｐ
	// それなのに……ｎ
	// おれは どうすれば いいんだ……

RusturfTunnel_Text_ToGetToVerdanturf: @ 822D5F3
	.string "금탄도시에서 잔디마을로 가기 위해선\n"
	.string "무로마을에서 잿빛도시와 보라시티를 거쳐서\l"
	.string "지나가지 않으면 안 돼...$"
	// カナズミから シダケに いこうと するとｎ
	// ムロから カイナと キンセツを とおってｌ
	// いかなきゃ ならないんだ……

RusturfTunnel_Text_YouShatteredBoulderTakeHM: @ 822D65C
	.string "이럴 수가! 네가 이 바위를\n"
	.string "부숴준 거구나\p"
	.string "감사의 표시로\n"
	.string "이 비전머신을 너한테 줄게$"
	// なんと! きみが この いわをｎ
	// くだいて くれたんだねｐ
	// かんしゃの しるし としてｎ
	// この ひでんマシンを うけとってくれ

RusturfTunnel_Text_ExplainStrength: @ 822D6D2
	.string "거기에는 괴력이 들어 있어\n"
	.string "힘센 포켓몬에게 배우게 하면\l"
	.string "큰 바위도 움직일 수 있게 되지$"
	// そいつには かいりきが はいっているｎ
	// ちからもちの ポケモンに おぼえさせればｌ
	// おおきな いわを うごかせるよ

RusturfTunnel_Text_WandaReunion: @ 822D745
	.string "미진씨!\n"
	.string "앞으로는 언제든지 볼 수 있어요!\p"
	.string "미진: 정말... 잘됐네요\p"
	.string "자 저희 집에서\n"
	.string "푹 쉬었다 가세요$"
	// ミチルさん!ｎ
	// これから いつでも あえます!ｐ
	// ミチル『よかった…… ですｐ
	// さあ わたしの いえでｎ
	// ゆっくり やすんで ください

RusturfTunnel_Text_BoyfriendOnOtherSideOfRock: @ 822D7A3
	.string "이 바위 건너편에는...\n"
	.string "내 남자친구가 있어\p"
	.string "그는... 나를 만나려는 이유만으로\n"
	.string "이 터널을 파고 있는 건 아니야\p"
	.string "모두를 위해\n"
	.string "손을 다쳐가면서도 힘내고 있어$"
	// この いわの むこうに……ｎ
	// わたしの かれが いるのｐ
	// かれ…… わたしに あうため だけにｎ
	// トンネルを ほってるわけ じゃないわｐ
	// みんなの ためにｎ
	// てを きずつけながらも がんばってるの

RusturfTunnel_Text_MikeIntro: @ 822D84D
	.string "등산하는 사람은 등산가!\p"
	.string "그런데 왜 포켓몬이 등산하면\n"
	.string "등산포켓몬이라고 부르지 않는 거지?$"
	// おとこが やまに いるから やまおとこ!ｐ
	// なのに ポケモンが やまに いてもｎ
	// やまポケモンと いわないのは なぜだ?

RusturfTunnel_Text_MikeDefeat: @ 822D8DB
	.string "포켓몬...\n"
	.string "힘이 다했다...$"
	// ポケモン……ｎ
	// ちから つきた……

RusturfTunnel_Text_MikePostBattle: @ 822D8F9
	.string "이곳의 포켓몬을 지키기 위해\n"
	.string "개발 공사를 중지했다지?\l"
	.string "정말 훈훈한 이야기야$"
	// ここって ポケモンを まもるためｎ
	// かいはつ こうじを やめたんだろ?ｌ
	// それって いい はなし だよな

