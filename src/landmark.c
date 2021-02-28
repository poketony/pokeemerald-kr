#include "global.h"
#include "event_data.h"
#include "constants/region_map_sections.h"

struct Landmark
{
    const u8 *name;
    u16 flag;
};

struct LandmarkList
{
    u8 mapSection;
    u8 id;
    const struct Landmark *const *landmarks;
};

static const u8 LandmarkName_FlowerShop[] = _("플라워숍");
static const u8 LandmarkName_PetalburgWoods[] = _("등화숲");
static const u8 LandmarkName_MrBrineysCottage[] = _("하기노인의 작은 집");
static const u8 LandmarkName_AbandonedShip[] = _("버려진 배");
static const u8 LandmarkName_SeashoreHouse[] = _("바다의 집");
static const u8 LandmarkName_SlateportBeach[] = _("잿빛도시의 해변");
static const u8 LandmarkName_CyclingRoad[] = _("사이클링 로드");
static const u8 LandmarkName_NewMauville[] = _("뉴보라");
static const u8 LandmarkName_TrickHouse[] = _("미궁의 대저택");
static const u8 LandmarkName_OldLadysRestShop[] = _("건강할머니");
static const u8 LandmarkName_Desert[] = _("사막");
static const u8 LandmarkName_WinstrateFamily[] = _("연승가족");
static const u8 LandmarkName_CableCar[] = _("케이블카 승강장");
static const u8 LandmarkName_GlassWorkshop[] = _("유리 세공 가게");
static const u8 LandmarkName_WeatherInstitute[] = _("날씨 연구소");
static const u8 LandmarkName_MeteorFalls[] = _("유성의 폭포");
static const u8 LandmarkName_TunnelersRestHouse[] = _("터널공사자 대기실");
static const u8 LandmarkName_RusturfTunnel[] = _("금잔터널");
static const u8 LandmarkName_PokemonDayCare[] = _("포켓몬 키우미집");
static const u8 LandmarkName_SafariZoneEntrance[] = _("사파리존 입구");
static const u8 LandmarkName_MtPyre[] = _("송화산");
static const u8 LandmarkName_ShoalCave[] = _("여울의 동굴");
static const u8 LandmarkName_SeafloorCavern[] = _("해저동굴");
static const u8 LandmarkName_GraniteCave[] = _("바위 동굴");
static const u8 LandmarkName_OceanCurrent[] = _("해류");
static const u8 LandmarkName_LanettesHouse[] = _("유미의 집");
static const u8 LandmarkName_FieryPath[] = _("불꽃샛길");
static const u8 LandmarkName_JaggedPass[] = _("울퉁불퉁 산길");
static const u8 LandmarkName_SkyPillar[] = _("하늘기둥");
static const u8 LandmarkName_BerryMastersHouse[] = _("나무열매 명인의 집");
static const u8 LandmarkName_IslandCave[] = _("작은 섬 옆굴");
static const u8 LandmarkName_DesertRuins[] = _("사막유적");
static const u8 LandmarkName_ScorchedSlab[] = _("가뭄의 암굴");
static const u8 LandmarkName_AncientTomb[] = _("고대의 무덤");
static const u8 LandmarkName_SealedChamber[] = _("고시의 석실");
static const u8 LandmarkName_FossilManiacsHouse[] = _("화석마니아의 집");
static const u8 LandmarkName_HuntersHouse[] = _("헌터의 작은 집");
static const u8 LandmarkName_MagmaHideout[] = _("마그마단아지트");
static const u8 LandmarkName_MirageTower[] = _("환영탑");
static const u8 LandmarkName_AlteringCave[] = _("변형동굴");
static const u8 LandmarkName_DesertUnderpass[] = _("사막의 지하도");
static const u8 LandmarkName_TrainerHill[] = _("트레이너힐");

static const struct Landmark Landmark_FlowerShop = {LandmarkName_FlowerShop, FLAG_LANDMARK_FLOWER_SHOP};
static const struct Landmark Landmark_PetalburgWoods = {LandmarkName_PetalburgWoods, -1};
static const struct Landmark Landmark_MrBrineysCottage = {LandmarkName_MrBrineysCottage, FLAG_LANDMARK_MR_BRINEY_HOUSE};
static const struct Landmark Landmark_AbandonedShip = {LandmarkName_AbandonedShip, FLAG_LANDMARK_ABANDONED_SHIP};
static const struct Landmark Landmark_SeashoreHouse = {LandmarkName_SeashoreHouse, FLAG_LANDMARK_SEASHORE_HOUSE};
static const struct Landmark Landmark_SlateportBeach = {LandmarkName_SlateportBeach, -1};
static const struct Landmark Landmark_CyclingRoad = {LandmarkName_CyclingRoad, -1};
static const struct Landmark Landmark_NewMauville = {LandmarkName_NewMauville, FLAG_LANDMARK_NEW_MAUVILLE};
static const struct Landmark Landmark_TrickHouse = {LandmarkName_TrickHouse, FLAG_LANDMARK_TRICK_HOUSE};
static const struct Landmark Landmark_OldLadysRestShop = {LandmarkName_OldLadysRestShop, FLAG_LANDMARK_OLD_LADY_REST_SHOP};
static const struct Landmark Landmark_Desert = {LandmarkName_Desert, -1};
static const struct Landmark Landmark_WinstrateFamily = {LandmarkName_WinstrateFamily, FLAG_LANDMARK_WINSTRATE_FAMILY};
static const struct Landmark Landmark_CableCar = {LandmarkName_CableCar, -1};
static const struct Landmark Landmark_GlassWorkshop = {LandmarkName_GlassWorkshop, FLAG_LANDMARK_GLASS_WORKSHOP};
static const struct Landmark Landmark_WeatherInstitute = {LandmarkName_WeatherInstitute, -1};
static const struct Landmark Landmark_MeteorFalls = {LandmarkName_MeteorFalls, -1};
static const struct Landmark Landmark_TunnelersRestHouse = {LandmarkName_TunnelersRestHouse, FLAG_LANDMARK_TUNNELERS_REST_HOUSE};
static const struct Landmark Landmark_RusturfTunnel = {LandmarkName_RusturfTunnel, -1};
static const struct Landmark Landmark_PokemonDayCare = {LandmarkName_PokemonDayCare, FLAG_LANDMARK_POKEMON_DAYCARE};
static const struct Landmark Landmark_SafariZoneEntrance = {LandmarkName_SafariZoneEntrance, -1};
static const struct Landmark Landmark_MtPyre = {LandmarkName_MtPyre, -1};
static const struct Landmark Landmark_ShoalCave = {LandmarkName_ShoalCave, -1};
static const struct Landmark Landmark_SeafloorCavern = {LandmarkName_SeafloorCavern, FLAG_LANDMARK_SEAFLOOR_CAVERN};
static const struct Landmark Landmark_GraniteCave = {LandmarkName_GraniteCave, -1};
static const struct Landmark Landmark_OceanCurrent = {LandmarkName_OceanCurrent, -1};
static const struct Landmark Landmark_LanettesHouse = {LandmarkName_LanettesHouse, FLAG_LANDMARK_LANETTES_HOUSE};
static const struct Landmark Landmark_FieryPath = {LandmarkName_FieryPath, FLAG_LANDMARK_FIERY_PATH};
static const struct Landmark Landmark_JaggedPass = {LandmarkName_JaggedPass, -1};
static const struct Landmark Landmark_BerryMastersHouse = {LandmarkName_BerryMastersHouse, FLAG_LANDMARK_BERRY_MASTERS_HOUSE};
static const struct Landmark Landmark_IslandCave = {LandmarkName_IslandCave, FLAG_LANDMARK_ISLAND_CAVE};
static const struct Landmark Landmark_DesertRuins = {LandmarkName_DesertRuins, FLAG_LANDMARK_DESERT_RUINS};
static const struct Landmark Landmark_ScorchedSlab = {LandmarkName_ScorchedSlab, FLAG_LANDMARK_SCORCHED_SLAB};
static const struct Landmark Landmark_AncientTomb = {LandmarkName_AncientTomb, FLAG_LANDMARK_ANCIENT_TOMB};
static const struct Landmark Landmark_SealedChamber = {LandmarkName_SealedChamber, FLAG_LANDMARK_SEALED_CHAMBER};
static const struct Landmark Landmark_FossilManiacsHouse = {LandmarkName_FossilManiacsHouse, FLAG_LANDMARK_FOSSIL_MANIACS_HOUSE};
static const struct Landmark Landmark_HuntersHouse = {LandmarkName_HuntersHouse, FLAG_LANDMARK_HUNTERS_HOUSE};
static const struct Landmark Landmark_SkyPillar = {LandmarkName_SkyPillar, FLAG_LANDMARK_SKY_PILLAR};
static const struct Landmark Landmark_MirageTower = {LandmarkName_MirageTower, FLAG_LANDMARK_MIRAGE_TOWER};
static const struct Landmark Landmark_AlteringCave = {LandmarkName_AlteringCave, FLAG_LANDMARK_ALTERING_CAVE};
static const struct Landmark Landmark_DesertUnderpass = {LandmarkName_DesertUnderpass, FLAG_LANDMARK_DESERT_UNDERPASS};
static const struct Landmark Landmark_TrainerHill = {LandmarkName_TrainerHill, FLAG_LANDMARK_TRAINER_HILL};

static const struct Landmark *const Landmarks_Route103_2[]  =
{
    &Landmark_AlteringCave,
    NULL,
};

static const struct Landmark *const Landmarks_Route104_0[]  =
{
    &Landmark_FlowerShop,
    NULL,
};

static const struct Landmark *const Landmarks_Route104_1[]  =
{
    &Landmark_PetalburgWoods,
    &Landmark_MrBrineysCottage,
    NULL,
};

static const struct Landmark *const Landmarks_Route105_0[]  =
{
    &Landmark_IslandCave,
    NULL,
};

static const struct Landmark *const Landmarks_Route106_1[]  =
{
    &Landmark_GraniteCave,
    NULL,
};

static const struct Landmark *const Landmarks_Route108_0[]  =
{
    &Landmark_AbandonedShip,
    NULL,
};

static const struct Landmark *const Landmarks_Route109_0[]  =
{
    &Landmark_SeashoreHouse,
    &Landmark_SlateportBeach,
    NULL,
};

static const struct Landmark *const Landmarks_Route110_0[]  =
{
    &Landmark_CyclingRoad,
    &Landmark_NewMauville,
    NULL,
};

static const struct Landmark *const Landmarks_Route110_1[]  =
{
    &Landmark_CyclingRoad,
    NULL,
};

static const struct Landmark *const Landmarks_Route110_2[]  =
{
    &Landmark_CyclingRoad,
    &Landmark_TrickHouse,
    NULL,
};

static const struct Landmark *const Landmarks_Route111_0[]  =
{
    &Landmark_OldLadysRestShop,
    NULL,
};

static const struct Landmark *const Landmarks_Route111_1[]  =
{
    &Landmark_Desert,
    NULL,
};

static const struct Landmark *const Landmarks_Route111_2[]  =
{
    &Landmark_MirageTower,
    &Landmark_Desert,
    NULL,
};

static const struct Landmark *const Landmarks_Route111_3[]  =
{
    &Landmark_DesertRuins,
    &Landmark_Desert,
    NULL,
};

static const struct Landmark *const Landmarks_Route111_4[]  =
{
    &Landmark_TrainerHill,
    &Landmark_WinstrateFamily,
    &Landmark_Desert,
    NULL,
};

static const struct Landmark *const Landmarks_Route112_0[]  =
{
    &Landmark_FieryPath,
    &Landmark_JaggedPass,
    NULL,
};

static const struct Landmark *const Landmarks_Route112_1[]  =
{
    &Landmark_CableCar,
    &Landmark_FieryPath,
    NULL,
};

static const struct Landmark *const Landmarks_Route113_1[]  =
{
    &Landmark_GlassWorkshop,
    NULL,
};

static const struct Landmark *const Landmarks_Route114_1[]  =
{
    &Landmark_DesertUnderpass,
    &Landmark_FossilManiacsHouse,
    NULL,
};

static const struct Landmark *const Landmarks_Route114_2[]  =
{
    &Landmark_LanettesHouse,
    NULL,
};

static const struct Landmark *const Landmarks_MeteorFalls[]  =
{
    &Landmark_MeteorFalls,
    NULL,
};

static const struct Landmark *const Landmarks_Route116_1[]  =
{
    &Landmark_TunnelersRestHouse,
    &Landmark_RusturfTunnel,
    NULL,
};

static const struct Landmark *const Landmarks_Route116_2[]  =
{
    &Landmark_RusturfTunnel,
    NULL,
};

static const struct Landmark *const Landmarks_Route117_2[]  =
{
    &Landmark_PokemonDayCare,
    NULL,
};

static const struct Landmark *const Landmarks_Route119_1[]  =
{
    &Landmark_WeatherInstitute,
    NULL,
};

static const struct Landmark *const Landmarks_Route120_0[]  =
{
    &Landmark_ScorchedSlab,
    NULL,
};

static const struct Landmark *const Landmarks_Route120_2[]  =
{
    &Landmark_AncientTomb,
    NULL,
};

static const struct Landmark *const Landmarks_Route121_2[]  =
{
    &Landmark_SafariZoneEntrance,
    NULL,
};

static const struct Landmark *const Landmarks_Route122_0[]  =
{
    &Landmark_MtPyre,
    NULL,
};

static const struct Landmark *const Landmarks_Route123_0[]  =
{
    &Landmark_BerryMastersHouse,
    NULL,
};

static const struct Landmark *const Landmarks_Route124_7[]  =
{
    &Landmark_HuntersHouse,
    NULL,
};

static const struct Landmark *const Landmarks_Route125_2[]  =
{
    &Landmark_ShoalCave,
    NULL,
};

static const struct Landmark *const Landmarks_Route128_1[]  =
{
    &Landmark_SeafloorCavern,
    NULL,
};

static const struct Landmark *const Landmarks_Route131_1[]  =
{
    &Landmark_SkyPillar,
    NULL,
};

static const struct Landmark *const Landmarks_OceanCurrent[]  =
{
    &Landmark_OceanCurrent,
    NULL,
};

static const struct Landmark *const Landmarks_Route134_2[]  =
{
    &Landmark_SealedChamber,
    &Landmark_OceanCurrent,
    NULL,
};

static const struct Landmark *const Landmarks_MtChimney_2[]  =
{
    &Landmark_CableCar,
    &Landmark_JaggedPass,
    NULL,
};

static const struct LandmarkList gLandmarkLists[] =
{
    {MAPSEC_ROUTE_103, 2, Landmarks_Route103_2},
    {MAPSEC_ROUTE_104, 0, Landmarks_Route104_0},
    {MAPSEC_ROUTE_104, 1, Landmarks_Route104_1},
    {MAPSEC_ROUTE_105, 0, Landmarks_Route105_0},
    {MAPSEC_ROUTE_106, 1, Landmarks_Route106_1},
    {MAPSEC_ROUTE_108, 0, Landmarks_Route108_0},
    {MAPSEC_ROUTE_109, 0, Landmarks_Route109_0},
    {MAPSEC_ROUTE_110, 0, Landmarks_Route110_0},
    {MAPSEC_ROUTE_110, 1, Landmarks_Route110_1},
    {MAPSEC_ROUTE_110, 2, Landmarks_Route110_2},
    {MAPSEC_ROUTE_111, 0, Landmarks_Route111_0},
    {MAPSEC_ROUTE_111, 1, Landmarks_Route111_1},
    {MAPSEC_ROUTE_111, 2, Landmarks_Route111_2},
    {MAPSEC_ROUTE_111, 3, Landmarks_Route111_3},
    {MAPSEC_ROUTE_111, 4, Landmarks_Route111_4},
    {MAPSEC_ROUTE_112, 0, Landmarks_Route112_0},
    {MAPSEC_ROUTE_112, 1, Landmarks_Route112_1},
    {MAPSEC_ROUTE_113, 1, Landmarks_Route113_1},
    {MAPSEC_ROUTE_114, 1, Landmarks_Route114_1},
    {MAPSEC_ROUTE_114, 2, Landmarks_Route114_2},
    {MAPSEC_ROUTE_114, 3, Landmarks_MeteorFalls},
    {MAPSEC_ROUTE_115, 0, Landmarks_MeteorFalls},
    {MAPSEC_ROUTE_115, 1, Landmarks_MeteorFalls},
    {MAPSEC_ROUTE_116, 1, Landmarks_Route116_1},
    {MAPSEC_ROUTE_116, 2, Landmarks_Route116_2},
    {MAPSEC_ROUTE_117, 2, Landmarks_Route117_2},
    {MAPSEC_ROUTE_119, 1, Landmarks_Route119_1},
    {MAPSEC_ROUTE_120, 0, Landmarks_Route120_0},
    {MAPSEC_ROUTE_120, 2, Landmarks_Route120_2},
    {MAPSEC_ROUTE_121, 2, Landmarks_Route121_2},
    {MAPSEC_ROUTE_122, 0, Landmarks_Route122_0},
    {MAPSEC_ROUTE_123, 0, Landmarks_Route123_0},
    {MAPSEC_ROUTE_122, 1, Landmarks_Route122_0},
    {MAPSEC_ROUTE_124, 7, Landmarks_Route124_7},
    {MAPSEC_ROUTE_125, 2, Landmarks_Route125_2},
    {MAPSEC_ROUTE_128, 1, Landmarks_Route128_1},
    {MAPSEC_ROUTE_131, 1, Landmarks_Route131_1},
    {MAPSEC_ROUTE_132, 0, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_132, 1, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_133, 0, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_133, 1, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_133, 2, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_134, 0, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_134, 1, Landmarks_OceanCurrent},
    {MAPSEC_ROUTE_134, 2, Landmarks_Route134_2},
    {MAPSEC_MT_CHIMNEY, 2, Landmarks_MtChimney_2},
    {MAPSEC_NONE, 0, NULL},
};

static const struct Landmark *const *GetLandmarks(u8 mapSection, u8 id);

const u8 *GetLandmarkName(u8 mapSection, u8 id, u8 count)
{
    const struct Landmark *const *landmarks = GetLandmarks(mapSection, id);

    if (!landmarks)
        return NULL;

    while (1)
    {
        const struct Landmark *landmark = *landmarks;

        if (landmark->flag == 0xFFFF || FlagGet(landmark->flag) == TRUE)
        {
            if (count == 0)
                break;
            else
                count--;
        }

        landmarks++;
        if (!*landmarks)
            return NULL;
    }

    return (*landmarks)->name;
}

static const struct Landmark *const *GetLandmarks(u8 mapSection, u8 id)
{
    u16 i = 0;

    for (; gLandmarkLists[i].mapSection != MAPSEC_NONE; i++)
    {
        if (gLandmarkLists[i].mapSection > mapSection)
            return NULL;
        if (gLandmarkLists[i].mapSection == mapSection)
            break;
    }

    if (gLandmarkLists[i].mapSection == MAPSEC_NONE)
        return NULL;

    for (; gLandmarkLists[i].mapSection == mapSection; i++)
    {
        if (gLandmarkLists[i].id == id)
            return gLandmarkLists[i].landmarks;
    }

    return NULL;
}
