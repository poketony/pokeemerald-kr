SootopolisCity_House4_MapScripts:: @ 8226D15
	.byte 0

SootopolisCity_House4_EventScript_Man:: @ 8226D16
	msgbox SootopolisCity_House4_Text_AncientTreasuresWaitingInSea, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Woman:: @ 8226D1F
	msgbox SootopolisCity_House4_Text_StrollUnderwaterWithPokemon, MSGBOX_NPC
	end

SootopolisCity_House4_EventScript_Azumarill:: @ 8226D28
	lock
	faceplayer
	waitse
	playmoncry SPECIES_AZUMARILL, 0
	msgbox SootopolisCity_House4_Text_Azumarill, MSGBOX_DEFAULT
	waitmoncry
	release
	end

SootopolisCity_House4_Text_AncientTreasuresWaitingInSea: @ 8226D3B
	.string "좋은 걸 알려주지\p"
	.string "이 주변 바닷속에는\n"
	.string "고대의 유적이 있다고 한다!\p"
	.string "잘하면 고대의 보물을\n"
	.string "마구마구 발견하게 될지도 모른다고!$"
	// いいことを おしえてやろうｐ
	// この あたりの うみの そこにはｎ
	// こだいの いせきが あるそうだ!ｐ
	// ひょっとしたら むかしの おたからがｎ
	// ざくざく みつかるかも しれないぜ!

SootopolisCity_House4_Text_StrollUnderwaterWithPokemon: @ 8226DEA
	.string "보물이라...\p"
	.string "그야 있으면 좋겠지만\n"
	.string "없다고 해도 포켓몬과 함께\l"
	.string "바닷속을 산책할 수 있다니 멋져!$"
	// たからもの かぁ……ｐ
	// あると いいけどｎ
	// そうでなくても ポケモンと いっしょにｌ
	// かいていを おさんぽ なんて す®て®き!

SootopolisCity_House4_Text_Azumarill: @ 8226E7F
	.string "마릴리: 마루리-$"
	// マリルリ『まるり-

