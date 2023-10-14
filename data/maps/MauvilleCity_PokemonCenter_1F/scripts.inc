.set LOCALID_NURSE, 1

MauvilleCity_PokemonCenter_1F_MapScripts:: @ 8210E5B
	map_script MAP_SCRIPT_ON_TRANSITION, MauvilleCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

MauvilleCity_PokemonCenter_1F_OnTransition: @ 8210E66
	setrespawn HEAL_LOCATION_MAUVILLE_CITY
	call Common_EventScript_UpdateBrineyLocation
	goto MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_SetMauvilleOldManGfx:: @ 8210E74
	special ScrSpecial_SetMauvilleOldManObjEventGfx
	end

MauvilleCity_PokemonCenter_1F_EventScript_Nurse:: @ 8210E78
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman1:: @ 8210E86
	msgbox MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Woman2:: @ 8210E8F
	msgbox MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_EventScript_Youngster:: @ 8210E98
	msgbox MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun, MSGBOX_NPC
	end

MauvilleCity_PokemonCenter_1F_Text_ManOverThereSaysWeirdThings: @ 8210EA1
	.string "저기 있는 아저씨는\n"
	.string "이상한 말을 할 때가 있어!\p"
	.string "그런데 그 말이 재미있어서\n"
	.string "잊어버릴 수가 없더라구!$"
	// あそこに いる オヤジｎ
	// へんなこと いったり するの!ｐ
	// なんだか おもしろくってｎ
	// わすれられない そんざい だわ!

MauvilleCity_PokemonCenter_1F_Text_MyDataUpdatedFromRecordCorner: @ 8210F06
	.string "레코드코너를 썼더니\n"
	.string "무로마을에서 유행하는 게\l"
	.string "친구와 같아졌어!$"
	// レコ-ドコ-ナ-を つかったらねｎ
	// ムロタウンで はやっている ものがｌ
	// ともだちと いっしょに なったのよ!

MauvilleCity_PokemonCenter_1F_Text_RecordCornerSoundsFun: @ 8210F8A
	.string "포켓몬센터 2층에\n"
	.string "레코드코너가 생겼대!\p"
	.string "잘 모르지만 재밌어 보이지 않아?\n"
	.string "아무튼 한번 해봐야지!$"
	// ポケモンセンタ-の 2かいにｎ
	// レコ-ドコ-ナ-が できたんだってさ!ｐ
	// よく わからないけど おもしろそうだろ?ｎ
	// とにかく やってみるよ!

