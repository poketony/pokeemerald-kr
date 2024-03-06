LilycoveCity_House1_MapScripts:: @ 821ECCD
	.byte 0

LilycoveCity_House1_EventScript_ExpertM:: @ 821ECCE
	msgbox LilycoveCity_House1_Text_PokemonPartnersNotTools, MSGBOX_NPC
	end

LilycoveCity_House1_EventScript_Kecleon:: @ 821ECD7
	lock
	faceplayer
	waitse
	playmoncry SPECIES_KECLEON, 0
	msgbox LilycoveCity_House1_Text_Kecleon, MSGBOX_DEFAULT
	waitmoncry
	release
	end

LilycoveCity_House1_Text_PokemonPartnersNotTools: @ 821ECEA
	.string "포켓몬은 인간의 파트너지\n"
	.string "절대 인간의 도구가 아니다\p"
	.string "그걸 이해 못 하는\n"
	.string "인간들도 가끔 있단 말이지...$"
	@ ポケモンは にんげんの パ-トナ-であってｎ
	@ けっして にんげんの どうぐ じゃないよｐ
	@ そこを かんちがい しておるｎ
	@ にんげんも たまに いるんだよ……

LilycoveCity_House1_Text_Kecleon: @ 821ED63
	.string "켈리몬: 루로로...?$"
	@ カクレオン『るろろ……?

