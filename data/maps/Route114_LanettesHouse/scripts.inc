Route114_LanettesHouse_MapScripts:: @ 822B2C8
	map_script MAP_SCRIPT_ON_TRANSITION, Route114_LanettesHouse_OnTransition
	.byte 0

Route114_LanettesHouse_OnTransition: @ 822B2CE
	setflag FLAG_LANDMARK_LANETTES_HOUSE
	end

Route114_LanettesHouse_EventScript_Lanette:: @ 822B2D2
	lock
	faceplayer
	goto_if_set FLAG_RECEIVED_DOLL_LANETTE, Route114_LanettesHouse_EventScript_OfferAdvice
	setflag FLAG_SYS_PC_LANETTE
	msgbox Route114_LanettesHouse_Text_EverythingClutteredKeepThis, MSGBOX_DEFAULT
	givedecoration DECOR_LOTAD_DOLL
	compare VAR_RESULT, FALSE
	goto_if_eq Common_EventScript_ShowNoRoomForDecor
	setflag FLAG_RECEIVED_DOLL_LANETTE
	release
	end

Route114_LanettesHouse_EventScript_OfferAdvice:: @ 822B2FF
	msgbox Route114_LanettesHouse_Text_OrganizeYourBoxes, MSGBOX_DEFAULT
	release
	end

Route114_LanettesHouse_EventScript_Notebook:: @ 822B309
	lockall
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage1, MSGBOX_YESNO
	compare VAR_RESULT, YES
	goto_if_eq Route114_LanettesHouse_EventScript_NotebookPage2
	msgbox Route114_LanettesHouse_Text_ClosedTheNotebook, MSGBOX_DEFAULT
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage2:: @ 822B327
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage2, MSGBOX_YESNO
	compare VAR_RESULT, YES
	call_if_eq Route114_LanettesHouse_EventScript_NotebookPage3
	releaseall
	end

Route114_LanettesHouse_EventScript_NotebookPage3:: @ 822B33C
	msgbox Route114_LanettesHouse_Text_ResearchNotesPage3, MSGBOX_DEFAULT
	return

Route114_LanettesHouse_EventScript_PC:: @ 822B345
	msgbox Route114_LanettesHouse_Text_EmailFromBill, MSGBOX_SIGN
	end

Route114_LanettesHouse_Text_EverythingClutteredKeepThis: @ 822B34E
	.string "유미: 앗! {PLAYER}{K_AYA}!\p"
	.string "어질러져 있어서 미안해요...\n"
	.string "연구에 집중하다 보면\l"
	.string "항상 이렇게 된답니다...\p"
	.string "창피하니까 비밀로 해 주세요\n"
	.string "이거 드릴 테니까...$"
	// マユミ『あっ! §あ§おｐ
	// ちらかっていて ごめんなさい……ｎ
	// けんきゅうに むちゅうに なるとｌ
	// つい こう なっちゃうんです……ｐ
	// はずかしいから ヒミツに してくださいねｎ
	// これ あげますから……

Route114_LanettesHouse_Text_OrganizeYourBoxes: @ 822B407
	.string "보관 시스템을 만든\n"
	.string "제가 충고를 해드리자면\p"
	.string "어느 박스에 어떤 포켓몬을\n"
	.string "맡겼는지 알 수 있도록\l"
	.string "깔끔히 정리하는 편이 좋아요!$"
	// あずかりシステムを つくったｎ
	// あたしからの アドバイス ですｐ
	// どの ボックスに どの ポケモンをｎ
	// あずけたか わかるようにｌ
	// きちんと せいり したほうが いいですよ!

Route114_LanettesHouse_Text_ResearchNotesPage1: @ 822B485
	.string "연구용 노트다\n"
	.string "박스에 대해 적혀 있다!\p"
	.string "박스 1개에 30마리의\n"
	.string "포켓몬을 맡길 수 있게 한다\p"
	.string "PC에는 전부 합쳐서 420마리의\n"
	.string "포켓몬을 맡길 수 있게 한다\p"
	.string "계속해서 읽겠습니까?$"
	// けんきゅう ようの ノ-トだｎ
	// ボックスに ついて かかれている!ｐ
	// ボックス1つに 30ぴきのｎ
	// ポケモンを あずけられる ようにするｐ
	// パソコンには ぜんぶで 420ひきのｎ
	// ポケモンを あずけられる ようにするｐ
	// つづきを よみますか?

Route114_LanettesHouse_Text_ResearchNotesPage2: @ 822B53C
	.string "포켓몬에 마킹을 하면\n"
	.string "박스를 정리하기 편하게 된다\p"
	.string "박스의 이름과 벽지를\n"
	.string "바꿀 수 있도록 해서 맡겨진\l"
	.string "포켓몬이 기뻐할 수 있도록 한다\p"
	.string "계속해서 읽겠습니까?$"
	// ポケモンを マ-キングすると ボックスがｎ
	// せいり しやすくなる ようにするｐ
	// ボックスの なまえ かべがみをｎ
	// かえられる ようにして あずけられたｌ
	// ポケモンが よろこぶ ようにするｐ
	// つづきを よみますか?

Route114_LanettesHouse_Text_ResearchNotesPage3: @ 822B5EF
	.string "포켓몬이 전송되는 박스는\n"
	.string "마지막에 본 박스로 한다\p"
	.string "그 박스가 가득 찰 경우에는\n"
	.string "다음 박스로 전송된다\p"
	.string "즉 박스를 보면\n"
	.string "포켓몬을 전송시키고 싶은 박스로\l"
	.string "전환될 수 있도록 한다$"
	// ポケモンが てんそう される ボックスはｎ
	// さいごに みた ボックスにするｐ
	// その ボックスが いっぱいの ときはｎ
	// つぎの ボックスに てんそう するｐ
	// つまり ボックスを みることでｎ
	// ポケモンを てんそう したい ボックスにｌ
	// きりかえられる ようにする

Route114_LanettesHouse_Text_ClosedTheNotebook: @ 822B6E4
	.string "{PLAYER}{K_EUNNEUN} 노트를 닫았다$"
	// §あは ノ-トを とじた

Route114_LanettesHouse_Text_EmailFromBill: @ 822B6FC
	.string "PC를 보니\n"
	.string "무려 전자 메일이 와 있다!\p"
	.string "“...... ...... ......\p"
	.string "너의 보관 시스템\n"
	.string "꽤 편리하네\p"
	.string "다양한 곳에서\n"
	.string "여성다운 배려가 보여서\l"
	.string "즐겁게 사용할 수 있어\p"
	.string "함께 개발한\n"
	.string "동료로서 정말 기쁜걸!\p"
	.string "그럼 앞으로도 보관 시스템의\n"
	.string "연구에 힘내도록 해\p"
	.string "...... ...... ......”$"
	// パソコンを みるとｎ
	// なんと でんしメ-ルが きていた!ｐ
	// 「…… …… ……ｐ
	// きみの あずかり システムｎ
	// なかなか べんり やなｐ
	// いろんな ところにｎ
	// じょせい らしい きくばりが あってｌ
	// つかってて たのしいしｐ
	// いっしょに かいはつ したｎ
	// なかま として うれしいわ!ｐ
	// ほな これからも あずかりシステムのｎ
	// けんきゅう がんばってなｐ
	// …… …… ……」

