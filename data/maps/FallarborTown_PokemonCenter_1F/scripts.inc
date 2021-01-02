.set LOCALID_NURSE, 1
.set LOCALID_LANETTE, 4

FallarborTown_PokemonCenter_1F_MapScripts:: @ 8200BCD
	map_script MAP_SCRIPT_ON_TRANSITION, FallarborTown_PokemonCenter_1F_OnTransition
	map_script MAP_SCRIPT_ON_RESUME, CableClub_OnResume
	.byte 0

FallarborTown_PokemonCenter_1F_OnTransition: @ 8200BD8
	setrespawn HEAL_LOCATION_FALLARBOR_TOWN
	call Common_EventScript_UpdateBrineyLocation
	end

FallarborTown_PokemonCenter_1F_EventScript_Nurse:: @ 8200BE1
	setvar VAR_0x800B, LOCALID_NURSE
	call Common_EventScript_PkmnCenterNurse
	waitmessage
	waitbuttonpress
	release
	end

FallarborTown_PokemonCenter_1F_EventScript_Girl:: @ 8200BEF
	msgbox FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_ExpertM:: @ 8200BF8
	msgbox FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees, MSGBOX_NPC
	end

FallarborTown_PokemonCenter_1F_EventScript_Lanette:: @ 8200C01
	lock
	faceplayer
	msgbox FallarborTown_PokemonCenter_1F_Text_LanetteGreeting, MSGBOX_DEFAULT
	closemessage
	switch VAR_FACING
	case DIR_NORTH, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth
	case DIR_WEST, FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitNorth:: @ 8200C28
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExitWest:: @ 8200C38
	applymovement LOCALID_LANETTE, FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest
	waitmovement 0
	goto FallarborTown_PokemonCenter_1F_EventScript_LanetteExited
	end

FallarborTown_PokemonCenter_1F_EventScript_LanetteExited:: @ 8200C48
	playse SE_SLIDING_DOOR
	removeobject LOCALID_LANETTE
	clearflag FLAG_HIDE_LANETTES_HOUSE_LANETTE
	release
	end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitNorth: @ 8200C53
	walk_right
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Movement_LanetteExitWest: @ 8200C60
	walk_down
	walk_down
	walk_left
	walk_left
	walk_left
	walk_down
	walk_down
	walk_down
	walk_down
	delay_8
	step_end

FallarborTown_PokemonCenter_1F_Text_LanetteGreeting: @ 8200C6B
	.string "당신은...?\p"
	.string "{PLAYER}{K_I}라고 하는군요\n"
	.string "당신 트레이너군요\p"
	.string "그렇다는 건 내가 만든\n"
	.string "보관 시스템 사용하고 계신 거죠?\p"
	.string "왜냐면 사용하고 싶으니까\n"
	.string "PC 앞에 있는 나한테\l"
	.string "말을 걸었을 거 아니에요\l"
	.string "간단한 추리예요\p"
	.string "아 전 보은이라고 해요\p"
	.string "보관 시스템을 사용하고 있는\n"
	.string "트레이너를 만나 너무 기뻐요\p"
	.string "괜찮으시다면 저희 집에도\n"
	.string "놀러 와 주세요\l"
	.string "114번도로에 있으니까요$"

FallarborTown_PokemonCenter_1F_Text_FossilManiacEdgeOfTown: @ 8200E22
	.string "오랜 옛날의 포켓몬은\n"
	.string "어떤 모습을 하고 있었을까?\p"
	.string "이 마을 외곽에 있는\n"
	.string "화석마니아라면 알려줄지도$"

FallarborTown_PokemonCenter_1F_Text_PlantHardyTrees: @ 8200E8B
	.string "여기 단풍마을의 밭에는\n"
	.string "화산재 안에서도 자랄 정도로\l"
	.string "튼튼한 나무의 모종을 심어놨단다$"

