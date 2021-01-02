MossdeepCity_House1_MapScripts:: @ 8221FD5
	.byte 0

MossdeepCity_House1_EventScript_BlackBelt:: @ 8221FD6
	lock
	faceplayer
	bufferleadmonspeciesname 0
	msgbox MossdeepCity_House1_Text_HmmYourPokemon, MSGBOX_DEFAULT
	specialvar VAR_RESULT, GetPokeblockNameByMonNature
	compare VAR_RESULT, 0
	goto_if_eq MossdeepCity_House1_EventScript_NeutralNature
	msgbox MossdeepCity_House1_Text_ItLikesXPokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_NeutralNature:: @ 8221FFC
	msgbox MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks, MSGBOX_DEFAULT
	release
	end

MossdeepCity_House1_EventScript_Woman:: @ 8222006
	msgbox MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes, MSGBOX_NPC
	end

MossdeepCity_House1_Text_HmmYourPokemon: @ 822200F
	.string "으음!\n"
	.string "자네의 {STR_VAR_1}...$"

MossdeepCity_House1_Text_ItLikesXPokeblocks: @ 822201D
	.string "{STR_VAR_1}{K_EULREUL}\n"
	.string "좋아하는구먼!\p"
	.string "아냐 틀림없이 {STR_VAR_1}{K_EULREUL}\n"
	.string "좋아하는 거라네!$"

MossdeepCity_House1_Text_DoesntLikeOrDislikePokeblocks: @ 8222068
	.string "포켓몬스넥을 좋아하지도\n"
	.string "싫어하지도 않는 것 같군$"

MossdeepCity_House1_Text_HusbandCanTellPokeblockMonLikes: @ 8222099
	.string "우리 남편은 보는 것만으로\n"
	.string "포켓몬이 좋아하는\l"
	.string "포켓몬스넥을 알 수 있어$"

