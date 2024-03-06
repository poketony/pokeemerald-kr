.set LOCALID_GROUDON, 1
.set LOCALID_GRUNT_1, 2
.set LOCALID_GRUNT_2, 3
.set LOCALID_GRUNT_3, 4
.set LOCALID_TABITHA, 5
.set LOCALID_MAXIE, 6
.set LOCALID_GROUDON_SLEEPING, 7

MagmaHideout_4F_MapScripts:: @ 823A55F
	.byte 0

MagmaHideout_4F_EventScript_Maxie:: @ 823A560
	lockall
	playbgm MUS_ENCOUNTER_MAGMA, 0
	msgbox MagmaHideout_4F_Text_MaxieAwakenGroudon, MSGBOX_DEFAULT
	closemessage
	delay 20
	setvar VAR_RESULT, 1
	playse SE_M_DETECT
	dofieldeffectsparkle 18, 42, 0
	waitfieldeffect FLDEFF_SPARKLE
	setvar VAR_RESULT, 1
	playfanfare MUS_AWAKEN_LEGEND
	playse SE_ORB
	special DoOrbEffect
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestUp
	waitmovement 0
	delay 150
	removeobject LOCALID_GROUDON_SLEEPING
	addobject LOCALID_GROUDON
	waitstate
	delay 60
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonApproach
	waitmovement 0
	special FadeOutOrbEffect
	waitstate
	setvar VAR_0x8004, 1  @ vertical pan
	setvar VAR_0x8005, 1  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	applymovement LOCALID_GROUDON, MagmaHideout_4F_Movement_GroudonExit
	waitmovement 0
	removeobject LOCALID_GROUDON
	delay 4
	setvar VAR_0x8004, 2  @ vertical pan
	setvar VAR_0x8005, 2  @ horizontal pan
	setvar VAR_0x8006, 8  @ num shakes
	setvar VAR_0x8007, 5  @ shake delay
	special ShakeCamera
	waitstate
	delay 30
	applymovement LOCALID_MAXIE, MagmaHideout_4F_Movement_MaxieLookAround
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieGroudonWhatsWrong, MSGBOX_DEFAULT
	closemessage
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFastestRight
	waitmovement 0
	delay 30
	applymovement LOCALID_MAXIE, Common_Movement_FacePlayer
	waitmovement 0
	msgbox MagmaHideout_4F_Text_MaxieOhItWasYou, MSGBOX_DEFAULT
	closemessage
	trainerbattle_no_intro TRAINER_MAXIE_MAGMA_HIDEOUT, MagmaHideout_4F_Text_MaxieDefeat
	msgbox MagmaHideout_4F_Text_MaxieImGoingAfterGroudon, MSGBOX_DEFAULT
	closemessage
	clearflag FLAG_HIDE_SLATEPORT_CITY_CAPTAIN_STERN
	clearflag FLAG_HIDE_SLATEPORT_CITY_GABBY_AND_TY
	setvar VAR_SLATEPORT_CITY_STATE, 1
	setflag FLAG_GROUDON_AWAKENED_MAGMA_HIDEOUT
	setvar VAR_SLATEPORT_HARBOR_STATE, 1
	fadescreen FADE_TO_BLACK
	removeobject LOCALID_MAXIE
	removeobject LOCALID_GRUNT_1
	removeobject LOCALID_GRUNT_2
	removeobject LOCALID_GRUNT_3
	removeobject LOCALID_TABITHA
	setflag FLAG_HIDE_MAGMA_HIDEOUT_GRUNTS
	fadescreen FADE_FROM_BLACK
	releaseall
	end

MagmaHideout_4F_Movement_GroudonApproach: @ 823A672
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

MagmaHideout_4F_Movement_GroudonExit: @ 823A67D
	slide_up
	slide_up
	step_end

MagmaHideout_4F_Movement_MaxieLookAround: @ 823A680
	face_left
	delay_16
	face_right
	delay_16
	face_left
	delay_16
	face_right
	delay_16
	face_up
	delay_16
	delay_16
	step_end

MagmaHideout_4F_EventScript_Grunt11:: @ 823A68C
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_11, MagmaHideout_4F_Text_Grunt11Intro, MagmaHideout_4F_Text_Grunt11Defeat
	msgbox MagmaHideout_4F_Text_Grunt11PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt12:: @ 823A6A3
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_12, MagmaHideout_4F_Text_Grunt12Intro, MagmaHideout_4F_Text_Grunt12Defeat
	msgbox MagmaHideout_4F_Text_Grunt12PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Grunt13:: @ 823A6BA
	trainerbattle_single TRAINER_GRUNT_MAGMA_HIDEOUT_13, MagmaHideout_4F_Text_Grunt13Intro, MagmaHideout_4F_Text_Grunt13Defeat
	msgbox MagmaHideout_4F_Text_Grunt13PostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_EventScript_Tabitha:: @ 823A6D1
	trainerbattle_single TRAINER_TABITHA_MAGMA_HIDEOUT, MagmaHideout_4F_Text_TabithaIntro, MagmaHideout_4F_Text_TabithaDefeat
	msgbox MagmaHideout_4F_Text_TabithaPostBattle, MSGBOX_AUTOCLOSE
	end

MagmaHideout_4F_Text_Grunt11Intro: @ 823A6E8
	.string "나도 그란돈을 보고 싶은데\n"
	.string "쥐꼬리도 보여주질 않아서\p"
	.string "조바심이 나기 시작했어...\p"
	.string "앗!\n"
	.string "그란돈에 대해 말해버렸다!$"
	@ オレも グラ-ドンを みたいのにｎ
	@ まだ シッポすら みせて もらえなくてｐ
	@ イライラ してるんだ……ｐ
	@ あっ!ｎ
	@ グラ-ドンのこと いっちゃった!

MagmaHideout_4F_Text_Grunt11Defeat: @ 823A775
	.string "역시 냉정한 마음을\n"
	.string "잃어버리면 이길 수 없어...$"
	@ やっぱり れいせいな きもちをｎ
	@ うしなって いたら かてないな……

MagmaHideout_4F_Text_Grunt11PostBattle: @ 823A7B5
	.string "그러고 보니 그란돈한테는\n"
	.string "꼬리 같은 게 있을까...?$"
	@ そういえば グラ-ドンにはｎ
	@ シッポなんて あるんだろうか……?

MagmaHideout_4F_Text_Grunt12Intro: @ 823A7DA
	.string "우하하 곧이다! 이제 곧이다!\n"
	.string "우리들의 목적이 실현될 거다!$"
	@ ふはは もうすぐ! もうすぐだ!ｎ
	@ オレたちの もくてきが じつげん する!

MagmaHideout_4F_Text_Grunt12Defeat: @ 823A81B
	.string "크으윽 여기까지 왔는데!$"
	@ ぐうう ここまで きていながら!

MagmaHideout_4F_Text_Grunt12PostBattle: @ 823A841
	.string "마적님-!\n"
	.string "침입자가 그쪽으로-!$"
	@ マツブサさま-!ｎ
	@ しんにゅうしゃが そっちに-!

MagmaHideout_4F_Text_Grunt13Intro: @ 823A86D
	.string "아직이다-!\n"
	.string "간단하게 보내진 않아!$"
	@ まだまだ-!ｎ
	@ かんたんには おくへ いかせない!

MagmaHideout_4F_Text_Grunt13Defeat: @ 823A8A7
	.string "나 간단하게 져버린 거야?$"
	@ オレって たおすの かんたん だった?

MagmaHideout_4F_Text_Grunt13PostBattle: @ 823A8C6
	.string "하 한 판 더... 털썩$"
	@ も もう ひとしょうぶ…… がくっ

MagmaHideout_4F_Text_TabithaIntro: @ 823A8E1
	.string "우효!\n"
	.string "여기까지 왔으니 알려주마\p"
	.string "그래 이 앞에는\n"
	.string "그란돈이 잠들어 있다!\p"
	.string "마적님은 지금 막\n"
	.string "그란돈이 있는 곳으로 가셨지!\p"
	.string "곧 잠에서 깨어날 거라고!\n"
	.string "우효! 우효효!$"
	@ ウヒョ!ｎ
	@ ここまで きたんだから おしえて やろうｐ
	@ そうさ このさきにはｎ
	@ グラ-ドンが ねむって いるのさ!ｐ
	@ マツブサさまは たったいまｎ
	@ グラ-ドンの ところへ いった!ｐ
	@ もうすぐ ねむりから めをさますぞ!ｎ
	@ ウヒョ! ウヒョヒョ!

MagmaHideout_4F_Text_TabithaDefeat: @ 823A994
	.string "당했다... 우효$"
	@ やられちまったい…… ウヒョ

MagmaHideout_4F_Text_TabithaPostBattle: @ 823A9AC
	.string "...이런 식으로 너하고\n"
	.string "시간을 보내는 사이에\l"
	.string "마적님이 그란돈을... 우효$"
	@ ……と こんな ぐあいに おまえとｎ
	@ あそんで やっている あいだにｌ
	@ マツブサさまが グラ-ドンを…… ウヒョ

MagmaHideout_4F_Text_MaxieAwakenGroudon: @ 823A9F4
	.string "마적: 마그마에 잠든 그란돈이여\n"
	.string "뭘 해도 일어나지 않던 네가\l"
	.string "원하는 건 쪽빛구슬...\p"
	.string "그렇겠지?\p"
	.string "자 여기 가져왔다\n"
	.string "이 빛으로 눈을 떠라!\p"
	.string "그리고 진정한 힘을\n"
	.string "나에게 보여다오!$"
	@ マツブサ『マグマに ねむる グラ-ドンよｎ
	@ なにをしても めざめなかった おまえがｌ
	@ もとめて いたのは あいいろのたま……ｐ
	@ そうなんだろう?ｐ
	@ さあ ここに もってきて やったぞｎ
	@ この かがやきで めを さませ!ｐ
	@ そして ほんとうの ちからをｎ
	@ わたしに みせて おくれ!

MagmaHideout_4F_Text_MaxieGroudonWhatsWrong: @ 823AADA
	.string "마적: ...그란돈!\n"
	.string "대체 어떻게 된 거지!?\p"
	.string "쪽빛구슬로는 안 되는 건가?\p"
	.string "그란돈이여!\n"
	.string "어디로 사라져 버린 거냐...$"
	@ マツブサ『……グラ-ドン!ｎ
	@ いったい どうしたと いうんだ!?ｐ
	@ あいいろのたまでは だめだと いうのか?ｐ
	@ グラ-ドンよ!ｎ
	@ どこへ きえて しまったんだ……

MagmaHideout_4F_Text_MaxieOhItWasYou: @ 823AB33
	.string "마적: 네 녀석인가!\p"
	.string "이곳저곳에서 잔뜩\n"
	.string "서성거리고 다닌 모양이던데\p"
	.string "그렇군 네가 뭔가\n"
	.string "잔꾀를 부린 건가...!$"
	@ マツブサ『おまえか!ｐ
	@ あっちでも こっちでも ちょこちょことｎ
	@ うろつき まわって いたようだがｐ
	@ なるほど おまえが なにかｎ
	@ こざいくを していたんだな……!

MagmaHideout_4F_Text_MaxieDefeat: @ 823ABB5
	.string "너는 어째서 그렇게\n"
	.string "포켓몬을 잘 다룰 수 있는 거지...$"
	@ おまえは なぜ そんなにｎ
	@ ポケモンを うまく あつかえるのだ……

MagmaHideout_4F_Text_MaxieImGoingAfterGroudon: @ 823ABE2
	.string "마적: 그란돈이 도망친 데에는\n"
	.string "뭔가 이유가 있다...\l"
	.string "그렇게 말하고 싶은 건가?\p"
	.string "...... ...... ......\n"
	.string "...... ...... ......\p"
	.string "흥...\n"
	.string "그 정도는 나도 알고 있다\p"
	.string "그란돈이 없어진 이상\n"
	.string "더는 이런 산에 볼일은 없지\p"
	.string "나는 그란돈을 쫓아갈 거니까\n"
	.string "너하고는 여기서 작별이겠군!$"
	@ マツブサ『グラ-ドンが にげだしたの にはｎ
	@ なにか わけがある……ｌ
	@ そう いいたいの だろう?ｐ
	@ …… …… ……ｎ
	@ …… …… ……ｐ
	@ ふん……ｎ
	@ それぐらい わたしも わかっていたさｐ
	@ グラ-ドンが いなくなって しまえばｎ
	@ もう こんな やまに ようはないｐ
	@ わたしは グラ-ドンを おいかけるからｎ
	@ おまえとも ここで おわかれだな!
