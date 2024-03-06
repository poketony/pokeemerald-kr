LilycoveCity_DepartmentStore_2F_MapScripts:: @ 821FB2C
	.byte 0

LilycoveCity_DepartmentStore_2F_EventScript_Cook:: @ 821FB2D
	msgbox LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_PokefanF:: @ 821FB36
	msgbox LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_Sailor:: @ 821FB3F
	msgbox LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems, MSGBOX_NPC
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkLeft:: @ 821FB48
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart1
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart1: @ 821FB60
	.2byte ITEM_POKE_BALL
	.2byte ITEM_GREAT_BALL
	.2byte ITEM_ULTRA_BALL
	.2byte ITEM_ESCAPE_ROPE
	.2byte ITEM_FULL_HEAL
	.2byte ITEM_ANTIDOTE
	.2byte ITEM_PARALYZE_HEAL
	.2byte ITEM_BURN_HEAL
	.2byte ITEM_ICE_HEAL
	.2byte ITEM_AWAKENING
	.2byte ITEM_FLUFFY_TAIL
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_EventScript_ClerkRight:: @ 821FB7A
	lock
	faceplayer
	message gText_HowMayIServeYou
	waitmessage
	pokemart LilycoveCity_DepartmentStore_2F_Pokemart2
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
	release
	end

	.align 2
LilycoveCity_DepartmentStore_2F_Pokemart2: @ 821FB94
	.2byte ITEM_POTION
	.2byte ITEM_SUPER_POTION
	.2byte ITEM_HYPER_POTION
	.2byte ITEM_MAX_POTION
	.2byte ITEM_REVIVE
	.2byte ITEM_REPEL
	.2byte ITEM_SUPER_REPEL
	.2byte ITEM_MAX_REPEL
	.2byte ITEM_WAVE_MAIL
	.2byte ITEM_MECH_MAIL
	.2byte ITEM_NONE
	release
	end

LilycoveCity_DepartmentStore_2F_Text_LearnToUseItemsProperly: @ 821FBAC
	.string "도구의 기본은 능숙하게 사용할 것\n"
	.string "이게 제일 중요한 거야$"
	@ どうぐの きほんは うまく つかいこなすことｎ
	@ これ いちばん だいじ なのヨ

LilycoveCity_DepartmentStore_2F_Text_GoodGiftForHusband: @ 821FBDF
	.string "집에서 기다리고 있는 남편한테\n"
	.string "줄 선물로 뭐가 좋을까?$"
	@ いえで まってる ダンナのｎ
	@ おみやげ なんだけど どれが いいかしら?

LilycoveCity_DepartmentStore_2F_Text_StockUpOnItems: @ 821FC23
	.string "이제부터 먼 곳으로\n"
	.string "여행을 떠날 거니까\l"
	.string "여기서 한가득 도구를 사 놓을 거야$"
	@ これから とおい ところへｎ
	@ たびに いくからなｌ
	@ ここで どっさり どうぐを かっておくのさ

