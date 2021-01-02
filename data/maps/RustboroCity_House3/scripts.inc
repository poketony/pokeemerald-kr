RustboroCity_House3_MapScripts:: @ 8216190
	.byte 0

RustboroCity_House3_EventScript_OldMan:: @ 8216191
	msgbox RustboroCity_House3_Text_IGivePerfectlySuitedNicknames, MSGBOX_NPC
	end

RustboroCity_House3_EventScript_OldWoman:: @ 821619A
	msgbox RustboroCity_House3_Text_NamingPikachuPekachu, MSGBOX_NPC
	end

@ Misspelling on purpose, see nickname
RustboroCity_House3_EventScript_Pekachu:: @ 82161A3
	lock
	faceplayer
	waitse
	playmoncry SPECIES_PIKACHU, 0
	msgbox RustboroCity_House3_Text_Pekachu, MSGBOX_DEFAULT
	waitmoncry
	release
	end

RustboroCity_House3_Text_IGivePerfectlySuitedNicknames: @ 82161B6
	.string "자신의 포켓몬에게\n"
	.string "딱 어울리는 별명을\l"
	.string "지어주는 게다!\p"
	.string "그게 바로 오리지널리티지!$"

RustboroCity_House3_Text_NamingPikachuPekachu: @ 821622A
	.string "그렇다고 피카츄에게\n"
	.string "“페카츄”라는 별명을 붙이는 건\l"
	.string "조금...\p"
	.string "뭐... 이해하기 쉬운\n"
	.string "이름을 붙이는 것도\l"
	.string "별명의 중요한 점이긴 하지만$"

RustboroCity_House3_Text_Pekachu: @ 82162AB
	.string "페카츄: 페카!$"

