.set LOCALID_KYOGRE, 1
.set LOCALID_ARCHIE, 2
.set LOCALID_MAXIE, 3
.set LOCALID_GRUNT_1, 4
.set LOCALID_GRUNT_2, 5
.set LOCALID_KYOGRE_SLEEPING, 7

SeafloorCavern_Room9_MapScripts:: @ 8234DC8
	.byte 0

SeafloorCavern_Room9_EventScript_ArchieAwakenKyogre:: @ 8234DC9
	lockall
	setvar VAR_0x8004, LOCALID_ARCHIE
	setvar VAR_0x8005, LOCALID_MAXIE
	setvar VAR_0x8006, LOCALID_GRUNT_1
	setvar VAR_0x8007, LOCALID_GRUNT_2
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	applymovement OBJ_EVENT_ID_PLAYER, SeafloorCavern_Room9_Movement_Delay32
	waitmovement 0
	playbgm MUS_ENCOUNTER_AQUA, 0
	msgbox SeafloorCavern_Room9_Text_ArchieHoldItRightThere, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8004
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieApproachPlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieSoItWasYou, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieBeholdKyogre, MSGBOX_DEFAULT
	applymovement VAR_0x8004, Common_Movement_FacePlayer
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieYouMustDisappear, MSGBOX_DEFAULT
	trainerbattle_no_intro TRAINER_ARCHIE, SeafloorCavern_Room9_Text_ArchieDefeat
	msgbox SeafloorCavern_Room9_Text_ArchieWithThisRedOrb, MSGBOX_DEFAULT
	setweather WEATHER_NONE
	doweather
	special Script_FadeOutMapMusic
	waitstate
	msgbox SeafloorCavern_Room9_Text_RedOrbShinesByItself, MSGBOX_DEFAULT
	special WaitWeather
	waitstate
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 16, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	closemessage
	setvar VAR_RESULT, 0
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestUp
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 150
	removeobject LOCALID_KYOGRE_SLEEPING
	addobject LOCALID_KYOGRE
	waitstate
	delay 60
	applymovement LOCALID_KYOGRE, SeafloorCavern_Room9_Movement_KyogreApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_KYOGRE, SeafloorCavern_Room9_Movement_KyogreExit
	waitmovement 0
	removeobject LOCALID_KYOGRE
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	setvar VAR_0x8004, LOCALID_ARCHIE
	setvar VAR_0x8005, LOCALID_MAXIE
	setvar VAR_0x8006, LOCALID_GRUNT_1
	setvar VAR_0x8007, LOCALID_GRUNT_2
	msgbox SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo, MSGBOX_DEFAULT
	playse SE_PC_LOGIN
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieAMessageFromOutside, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieListenMessage
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard, MSGBOX_DEFAULT
	closemessage
	playse SE_PC_OFF
	delay 20
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestDown
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear, MSGBOX_DEFAULT
	closemessage
	addobject VAR_0x8005
	addobject VAR_0x8006
	addobject VAR_0x8007
	applymovement VAR_0x8007, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8006, SeafloorCavern_Room9_Movement_MagmaGruntArrive
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieArrive
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_WalkInPlaceFastestLeft
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought, MSGBOX_DEFAULT
	playse SE_PIN
	applymovement VAR_0x8004, Common_Movement_ExclamationMark
	waitmovement 0
	applymovement VAR_0x8004, Common_Movement_Delay48
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty, MSGBOX_DEFAULT
	msgbox SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue, MSGBOX_DEFAULT
	closemessage
	applymovement VAR_0x8005, SeafloorCavern_Room9_Movement_MaxieExit
	applymovement VAR_0x8004, SeafloorCavern_Room9_Movement_ArchieExit
	waitmovement 0
	msgbox SeafloorCavern_Room9_Text_MaxieComeOnPlayer, MSGBOX_DEFAULT
	setvar VAR_ROUTE128_STATE, 1
	setvar VAR_SOOTOPOLIS_CITY_STATE, 1
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_STEVEN
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_ARCHIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_MAXIE
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_RESIDENTS
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_GROUDON
	clearflag FLAG_HIDE_SOOTOPOLIS_CITY_KYOGRE
	setflag FLAG_HIDE_SOOTOPOLIS_CITY_MAN_1
	setflag FLAG_LEGENDARIES_IN_SOOTOPOLIS
	clearflag FLAG_HIDE_ROUTE_128_ARCHIE
	clearflag FLAG_HIDE_ROUTE_128_MAXIE
	setflag FLAG_SYS_WEATHER_CTRL
	setflag FLAG_KYOGRE_ESCAPED_SEAFLOOR_CAVERN
	setflag FLAG_HIDE_MOSSDEEP_CITY_STEVENS_HOUSE_STEVEN
	setvar VAR_STEVENS_HOUSE_STATE, 2
	setvar VAR_SEAFLOOR_CAVERN_STATE, 1
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_ARCHIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAXIE
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_MAGMA_GRUNTS
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_ROOM_9_KYOGRE_1
	setflag FLAG_HIDE_SEAFLOOR_CAVERN_AQUA_GRUNTS
	setflag FLAG_HIDE_MAP_NAME_POPUP
	warp MAP_ROUTE128, 255, 38, 22
	waitstate
	releaseall
	end

SeafloorCavern_Room9_Movement_ArchieApproachPlayer: @ 823502A
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_Unused1: @ 8235032
	walk_left
	walk_left
	step_end

SeafloorCavern_Room9_Movement_ArchieListenMessage: @ 8235035
	walk_left
	delay_16
	step_end

SeafloorCavern_Room9_Movement_Unused2: @ 8235038
	walk_right
	step_end

SeafloorCavern_Room9_Movement_ArchieExit: @ 823503A
	face_up
	lock_facing_direction
	walk_down
	unlock_facing_direction
	walk_in_place_fastest_right
	step_end

SeafloorCavern_Room9_Movement_KyogreApproach: @ 8235040
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	walk_slow_down
	delay_16
	delay_16
	delay_16
	step_end

SeafloorCavern_Room9_Movement_KyogreExit: @ 823504B
	slide_up
	slide_up
	step_end

SeafloorCavern_Room9_Movement_MaxieArrive: @ 823504E
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_MaxieExit: @ 8235054
	walk_right
	walk_right
	step_end

SeafloorCavern_Room9_Movement_MagmaGruntArrive: @ 8235057
	walk_fast_right
	walk_fast_right
	walk_fast_right
	walk_fast_right
	step_end

SeafloorCavern_Room9_Movement_Delay32: @ 823505C
	delay_16
	delay_16
	step_end

SeafloorCavern_Room9_Text_ArchieHoldItRightThere: @ 823505F
	.string "아강: ...거기 멈춰라!$"
	// アオギリ『……まつんだ!

SeafloorCavern_Room9_Text_ArchieSoItWasYou: @ 823507C
	.string "아강: 후후후...\n"
	.string "역시 너였던 건가$"
	// アオギリ『ふふふ……ｎ
	// やはり おまえ だったか

SeafloorCavern_Room9_Text_ArchieBeholdKyogre: @ 82350A6
	.string "아강: 어떠냐 봐라!\p"
	.string "초 고대포켓몬 가이오가가\n"
	.string "조용히 잠들어 있는\l"
	.string "이 아름다운 모습을!\p"
	.string "난 이 날이 오기만을\n"
	.string "오랫동안 기다려왔다...$"
	// アオギリ『どうだ みてみろ!ｐ
	// ちょう こだいポケモン カイオ-ガがｎ
	// しずかに ねむる うつくしい すがたを!ｐ
	// おれは この ひが くるのをｎ
	// ながい あいだ まっていた……

SeafloorCavern_Room9_Text_ArchieYouMustDisappear: @ 823512C
	.string "아강: 그건 그렇고 설마 네가\n"
	.string "여기까지 왔을 줄이야!\p"
	.string "하지만 그것도 끝이다\n"
	.string "내 목적 달성을 위해\l"
	.string "너는 여기서 사라져 줘야겠다!$"
	// アオギリ『それにしても まさかｎ
	// ここまで くいついて くるとはな!ｐ
	// だが それも もう おわりｎ
	// おれの もくてき たっせいの ためｌ
	// おまえには ここで きえてもらう!

SeafloorCavern_Room9_Text_ArchieDefeat: @ 82351BC
	.string "뭐라고!?\n"
	.string "너같은 녀석한테 내가...!?$"
	// なにっ!?ｎ
	// おまえ ごときに おれが……?

SeafloorCavern_Room9_Text_ArchieWithThisRedOrb: @ 82351E5
	.string "아강: 후후후...\p"
	.string "역시나라고 해야 하나...\n"
	.string "너의 그 힘은 인정하마!\p"
	.string "허나...!\n"
	.string "내게는 이것이 있다!\p"
	.string "이 주홍구슬이 있으면\n"
	.string "가이오가를...$"
	// アオギリ『フフフ……ｐ
	// さすが というべきか……ｎ
	// おまえの その ちからは みとめよう!ｐ
	// だが……!ｎ
	// おれには これが ある!ｐ
	// この べにいろのたまが あればｎ
	// カイオ-ガを……

SeafloorCavern_Room9_Text_RedOrbShinesByItself: @ 8235279
	.string "주홍구슬이...\n"
	.string "멋대로 빛나기 시작했다...!?$"
	// べにいろのたまが……ｎ
	// かってに かがやき はじめた……!?

SeafloorCavern_Room9_Text_ArchieWhereDidKyogreGo: @ 82352A7
	.string "아강: ..!?\p"
	.string "나는 아무것도 하지 않았는데\n"
	.string "어째서 주홍구슬이...?\p"
	.string "가이오가는 어디로 사라졌지?$"
	// アオギリ『……!?ｐ
	// おれは なにも していないのにｎ
	// なぜ べにいろのたまが……?ｐ
	// カイオ-ガは どこへ きえた?

SeafloorCavern_Room9_Text_ArchieAMessageFromOutside: @ 82352F6
	.string "아강: 밖에 있는\n"
	.string "단원한테로군$"
	// アオギリ『そとに いるｎ
	// だんいん からの れんらくか

SeafloorCavern_Room9_Text_ArchieWhatRainingTooHard: @ 823532B
	.string "아강: 뭔가...?\p"
	.string "흠...\n"
	.string "폭우가 내리고 있다고...\p"
	.string "그렇겠지... 그것이야말로\n"
	.string "우리들 아쿠아단의 목적\l"
	.string "바다를 넓히기 위해 가이오가를\l"
	.string "깨운 이유니까 말이다\p"
	.string "뭐라고!\p"
	.string "예상한 것 이상의 폭우로 이대로라면\n"
	.string "우리들도 위험하다고!?\p"
	.string "설마 그럴 리가...\n"
	.string "그럴 리가 없을 텐데...\p"
	.string "어쨌든 계속 상태를 보고 있어라!$"
	// アオギリ『どうした……?ｐ
	// ふうむ……ｎ
	// おおあめが ふっている……ｐ
	// そうだろう…… それこそがｎ
	// われわれ アクアだんの もくてきｌ
	// うみを ふやすために カイオ-ガをｌ
	// めざめさせた りゆう なのだからなｐ
	// なんだと!ｐ
	// よそう いじょうの あめでｎ
	// このままでは われわれも キケンだと?ｐ
	// そんな ばかな……ｎ
	// とにかく ようすを みているんだ!

SeafloorCavern_Room9_Text_ArchieWhyDidKyogreDisappear: @ 823546F
	.string "아강: 이상해...\p"
	.string "주홍구슬로 가이오가가 눈을 뜨고\n"
	.string "그리고 컨트롤할 수 있었을 텐데...\p"
	.string "그런데... 어째서...\n"
	.string "가이오가는 여기서 없어졌다!?\p"
	.string "어째서지!?$"
	// アオギリ『おかしい……ｐ
	// べにいろのたまで カイオ-ガが めざめるｎ
	// そして コントロ-ル できるはず……ｐ
	// なのに…… どうして……ｎ
	// カイオ-ガは いなくなった!?ｐ
	// なぜなんだ!?

SeafloorCavern_Room9_Text_MaxieWhatHaveYouWrought: @ 82354F0
	.string "마적: 무슨 일이란 말인가...\p"
	.string "아강... 너도 결국\n"
	.string "가이오가를 눈 뜨게 해버린 건가!\p"
	.string "이대로 영원히\n"
	.string "폭우가 쏟아져 내린다면\l"
	.string "세계는 대체 어떻게 되겠는가!\p"
	.string "모든 대지가\n"
	.string "물 깊숙히 가라앉게 되는 거다...$"
	// マツブサ『なんてことだ……ｐ
	// アオギリよ…… おまえらもｎ
	// カイオ-ガを めざめさせて しまったな!ｐ
	// このまま えいえんにｎ
	// おおあめが ふりつづけたらｌ
	// せかいは いったい どうなる!ｐ
	// すべての だいちはｎ
	// みずの そこに しずむぞ……

SeafloorCavern_Room9_Text_ArchieDontGetAllHighAndMighty: @ 82355C2
	.string "아강: 뭐 뭐라고!?\n"
	.string "멋대로 말하지 마라!\p"
	.string "너희 마그마단이야말로 그란돈을\n"
	.string "깨워버리지 않았는가!\p"
	.string "난 이 주홍구슬이 있으면\n"
	.string "가이오가를 컨트롤할 수...\p"
	.string "할 수 있을 거라고 생각했는데...$"
	// アオギリ『な なんだと!?ｎ
	// かってな ことを いわないでくれ!ｐ
	// おまえら マグマだんこそ グラ-ドンをｎ
	// おこらせて しまった じゃないか!ｐ
	// おれは この べにいろのたまさえ あればｎ
	// カイオ-ガを コントロ-ル できるはず……ｐ
	// できる はず なんだ……

SeafloorCavern_Room9_Text_MaxieWeDontHaveTimeToArgue: @ 8235692
	.string "마적: 어쨌든 지금은 여기서\n"
	.string "말다툼하고 있을 때가 아니다!\p"
	.string "밖으로 나가서 확인하도록 해라!\n"
	.string "눈앞에 펼쳐진 게\l"
	.string "우리가 원하던 세계인지 아닌지를$"
	// マツブサ『とにかく いまは ここでｎ
	// いいあらそいを している ひまはない!ｐ
	// そとに でて たしかめると いい!ｎ
	// めのまえに ひろがっているのがｌ
	// われわれの のぞんだ せかいか どうか!

SeafloorCavern_Room9_Text_MaxieComeOnPlayer: @ 8235723
	.string "마적: {PLAYER}... 너도\n"
	.string "서둘러 밖으로 나가거라!$"
	// マツブサ『§あ…… おまえもｎ
	// はやく そとに でるんだ!
