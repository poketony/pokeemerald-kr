.set LOCALID_NURSE, 1

FortreeCity_PokemonCenter_1F_MapScripts:: @ 82173D8
	map_script MAP_SCRIPT_ON_TRANSITION, FortreeCity_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FortreeCity_PokemonCenter_1F_OnTransition: @ 82173E3
	setrespawn HEAL_LOCATION_FORTREE_CITY
	end

FortreeCity_PokemonCenter_1F_EventScript_Nurse:: @ 82173E7
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FortreeCity_PokemonCenter_1F_EventScript_Gentleman:: @ 82173F5
	msgbox FortreeCity_PokemonCenter_1F_Text_GoToSafariZone, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Man:: @ 82173FE
	msgbox FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_EventScript_Boy:: @ 8217407
	msgbox FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav, MSGBOX_NPC
	end

FortreeCity_PokemonCenter_1F_Text_GoToSafariZone: @ 8217410
	.string "너\n"
	.string "포켓몬 도감을 만들고 있나?\p"
	.string "흠 121번 도로의\n"
	.string "사파리존에 가보는 건 어떤가?$"

FortreeCity_PokemonCenter_1F_Text_RecordCornerIsNeat: @ 821746D
	.string "레코드코너 이용하고 있어?\p"
	.string "레코드가 기록이란 뜻이잖아\n"
	.string "기록이 여러 가지 섞여서...\p"
	.string "잘 모르겠지만 굉장하단 말이지!\n"
	.string "두근두근거려!$"

FortreeCity_PokemonCenter_1F_Text_DoYouKnowAboutPokenav: @ 821751F
	.string "어 포켓내비 가지고 있네!\n"
	.string "나랑 같은 거구나\p"
	.string "포켓내비의 엔트리콜을 쓰면\n"
	.string "다시 한 번 승부하고 싶어하는\l"
	.string "트레이너를 알 수 있거나\l"
	.string "언제든지 얘기할 수 있는 게\l"
	.string "굉장하단 말이지! 역시 데봉이야!$"
	// おっ ポケナビ もってるな!ｎ
	// おれと おんなじ だｐ
	// ポケナビの エントリ-コ-ル つかうとｎ
	// もういちど しょうぶ したがってるｌ
	// トレ-ナ-が わかったりｌ
	// いつでも はなしが できるってのがｌ
	// すぐれもの だよな! さすが デボンだぜ!
