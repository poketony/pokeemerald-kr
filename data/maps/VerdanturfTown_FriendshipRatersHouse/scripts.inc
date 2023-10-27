VerdanturfTown_FriendshipRatersHouse_MapScripts:: @ 8203030
	.byte 0

VerdanturfTown_FriendshipRatersHouse_EventScript_FriendshipRater:: @ 8203031
	lock
	faceplayer
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetLeadMonFriendshipScore
	switch VAR_RESULT
	case 0, VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou
	case 1, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary
	case 2, VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou
	case 3, VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou
	case 4, VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot
	case 5, VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy
	case 6, VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_DetestsYou:: @ 8203094
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryWary:: @ 820309E
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryWary, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_NotUsedToYou:: @ 82030A8
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_GettingUsedToYou:: @ 82030B2
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_LikesYouQuiteALot:: @ 82030BC
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_VeryHappy:: @ 82030C6
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_AdoresYou:: @ 82030D0
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou, MSGBOX_DEFAULT
	release
	end

VerdanturfTown_FriendshipRatersHouse_EventScript_Pikachu:: @ 82030DA
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, 0
	msgbox VerdanturfTown_FriendshipRatersHouse_Text_Pikachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

VerdanturfTown_FriendshipRatersHouse_Text_SeeHowMuchPokemonLikesYou: @ 82030ED
	.string "당신의 포켓몬이\n"
	.string "어느 정도 따르고 있는지 봐줄게\p"
	.string "어머...\n"
	.string "당신의 포켓몬$"
	// あなたの ポケモンがｎ
	// どれくらい なついているか みてあげるｐ
	// あら……ｎ
	// あなたの ポケモン

VerdanturfTown_FriendshipRatersHouse_Text_AdoresYou: @ 8203141
	.string "더 이상은 없을 정도로\n"
	.string "당신을 따르고 있네\l"
	.string "보고 있는 이쪽도 행복해지는걸!$"
	// これいじょうは ない ってぐらいｎ
	// あなたに なついているわねｌ
	// みている こっちも しあわせに なるわ!

VerdanturfTown_FriendshipRatersHouse_Text_VeryHappy: @ 8203192
	.string "왠지 행복해 보여\n"
	.string "굉장히 당신을 따르고 있네$"
	// なんだか しあわせそうｎ
	// すごく あなたに なついているわね

VerdanturfTown_FriendshipRatersHouse_Text_LikesYouQuiteALot: @ 82031D1
	.string "꽤 따르고 있네\n"
	.string "당신에게 어리광 부리고 싶은가 봐$"
	// かなり なついているわねｎ
	// あなたに あまえたそうに しているわよ

VerdanturfTown_FriendshipRatersHouse_Text_GettingUsedToYou: @ 8203213
	.string "조금 따르기 시작한 느낌이야\n"
	.string "당신을 믿고 있는 것 같아$"
	// ちょっと なついてきた って かんじ かなｎ
	// あなたのこと しんじている みたい

VerdanturfTown_FriendshipRatersHouse_Text_NotUsedToYou: @ 8203249
	.string "아직 당신을 따르지는 않는 것 같아\n"
	.string "보통 관계라는 느낌이 들어$"
	// まだ あなたに なれていない ようねｎ
	// ふつうの かんけい って かんじが するわ

VerdanturfTown_FriendshipRatersHouse_Text_VeryWary: @ 8203288
	.string "...왠지 경계하고 있는 듯해\n"
	.string "눈초리도 조금 무섭고\l"
	.string "전혀 당신을 따르지 않고 있어$"
	// …… なんだか けいかい しているみたいｎ
	// めつきも ちょっと こわいしｌ
	// ぜんぜん あなたに なついていないわ

VerdanturfTown_FriendshipRatersHouse_Text_DetestsYou: @ 82032DF
	.string "...좀 말하기 그렇지만\p"
	.string "당신 자기 포켓몬에게\n"
	.string "그렇게 미움받아도 괜찮아?$"
	// …… ちょっと いいづらいんだけどｐ
	// あなた じぶんの ポケモンにｎ
	// そんなに きらわれていて だいじょうぶ?

VerdanturfTown_FriendshipRatersHouse_Text_Pikachu: @ 820334A
	.string "피카츄: 피카 피카!$"

