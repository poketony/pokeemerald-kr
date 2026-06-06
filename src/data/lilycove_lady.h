#include "constants/easy_chat.h"
#include "constants/event_objects.h"
#include "constants/items.h"
#include "constants/moves.h"

static const u16 sContestLadyMonGfxId[] =
{
    OBJ_EVENT_GFX_ZIGZAGOON_1,
    OBJ_EVENT_GFX_SKITTY,
    OBJ_EVENT_GFX_POOCHYENA,
    OBJ_EVENT_GFX_KECLEON,
    OBJ_EVENT_GFX_PIKACHU
};

static const u16 sLilycoveLadyGfxId[] =
{
    OBJ_EVENT_GFX_WOMAN_4,
    OBJ_EVENT_GFX_WOMAN_2,
    OBJ_EVENT_GFX_GIRL_2
};

// Quiz Lady data
static const u16 sQuizLadyQuestion1[] =
{
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_INFORMATION, // 정보
    EC_WORD_READY, // 뭐든지
    EC_WORD_WILL_BE_HERE, // 있습니다
    EC_WORD_FUNNY, // 기묘한
    EC_WORD_MACHINE, // 머신
    EC_WORD_CAMERA, // 카메라
    EC_WORD_POKEDEX, // 포켓몬 도감
    EC_WORD_POKENAV // 포켓내비
};

static const u16 sQuizLadyQuestion2[] =
{
    EC_WORD_GAME,  // 게임
    EC_WORD_VERSION, // 버전
    EC_WORD_NAME, // 이름
    EC_WORD_NONE, // 없는
    EC_WORD_THING, // 것
    EC_WORD_QUES, // ?
    EC_WORD_RUBY, // 루비
    EC_WORD_SAPPHIRE, // 사파이어
    EC_WORD_DARK // 악
};

static const u16 sQuizLadyQuestion3[] =
{
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_EVOLUTION, // 진화
    EC_WORD_HOW, // 어떻게
    EC_WORD_OUT, // 해요
    EC_WORD_QUES, // ?
    0xFFFF,
    EC_WORD_LEVEL, // 레벨
    EC_WORD_INSOMNIA, // 불면
    EC_WORD_CUTE_CHARM // 헤롱헤롱바디
};

static const u16 sQuizLadyQuestion4[] =
{
    EC_WORD_NO_1, // 최고
    EC_WORD_BEAUTIFUL, // 아름다운
    EC_WORD_ITEM, // 도구
    EC_WORD_TYPE, // 타입
    EC_WORD_WHAT, // 무엇
    EC_WORD_QUES, // ?
    EC_WORD_COLD, // 추운
    EC_WORD_FLOWERS, // 꽃
    EC_WORD_MACHINE // 머신
};

static const u16 sQuizLadyQuestion5[] =
{
    EC_WORD_YOURS, // 당신이
    EC_WORD_GUTS, // 근성
    EC_WORD_OWN, // 가지고
    EC_WORD_RUNS, // 달리기
    EC_WORD_LIKELY_TO, // 하곤 한다
    EC_WORD_QUES, // ?
    EC_WORD_EGG, // 알
    EC_WORD_MAIL, // 메일
    EC_WORD_PHONE // 전화
};

static const u16 sQuizLadyQuestion6[] =
{
    EC_WORD_CONFUSED, // 혼란스러운
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_NONE, // 없는
    EC_WORD_SP_ABILITY, // 특성
    EC_WORD_QUES, // ?
    0xFFFF,
    EC_WORD_ILLUMINATE,
    EC_WORD_OWN_TEMPO,
    EC_WORD_SWIFT_SWIM
};

static const u16 sQuizLadyQuestion7[] =
{
    EC_WORD_MUSIC, // 음악
    EC_WORD_TYPE, // 타입
    EC_WORD_NAME, // 이름
    EC_WORD_QUES, // ?
    EC_WORD_POPULAR, // 인기
    EC_WORD_COULD, // 많습니다
    EC_WORD_FLYING, // 비행
    EC_WORD_STEEL, // 강철
    EC_WORD_ROCK // 바위
};

static const u16 sQuizLadyQuestion8[] =
{
    EC_WORD_ESCAPE, // 도망
    EC_WORD_IMPOSSIBLE, // 불가능한
    EC_WORD_SP_ABILITY, // 특성
    EC_WORD_NAME, // 이름
    EC_WORD_QUES, // ?
    0xFFFF, 
    EC_WORD_RUN_AWAY, // 도주
    EC_WORD_SHADOW_TAG, // 그림자밟기
    EC_WORD_WONDER_GUARD // 불가사의부적
};

static const u16 sQuizLadyQuestion9[] =
{
    EC_WORD_POISON, // 독
    EC_WORD_NONE, // 없는
    EC_WORD_SP_ABILITY, // 특성
    EC_WORD_NAME, // 이름
    EC_WORD_QUES, // ?
    0xFFFF,
    EC_WORD_GUTS, // 근성
    EC_WORD_IMMUNITY, // 면역
    EC_WORD_SHED_SKIN // 탈피
};

static const u16 sQuizLadyQuestion10[] =
{
    EC_WORD_CENTER, // 센터
    EC_WORD_WORKING, // 활약한다
    EC_WORD_FAINT, // 기절
    EC_WORD_WHAT, // 무엇
    EC_WORD_QUES, // ?
    0xFFFF,
    EC_WORD_POKEDEX, // 포켓몬 도감
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_POKENAV // 포켓내비
};

static const u16 sQuizLadyQuestion11[] =
{
    EC_WORD_YOUR, // 당신의
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_HERE, // 여기
    EC_WORD_INSIDE, // 안에
    EC_WORD_QUES, // ?
    0xFFFF,
    EC_WORD_PC, // PC
    EC_WORD_DEPT_STORE, // 백화점
    EC_WORD_TELEVISION // TV
};

static const u16 sQuizLadyQuestion12[] =
{
    EC_WORD_INFORMATION, // 정보
    EC_WORD_DAUGHTER, // 네게
    EC_WORD_GIVE, // 준다
    EC_WORD_AMUSING, // 재미있는
    EC_WORD_MACHINE, // 머신
    EC_WORD_QUES, // ?
    EC_WORD_BIKE, // 자전거
    EC_WORD_LOCOMOTIVE, // 전철
    EC_WORD_TELEVISION // TV
};

static const u16 sQuizLadyQuestion13[] =
{
    EC_WORD_POKEMON, // 포켓몬
    EC_WORD_DOES, // 같은 느낌
    EC_WORD_SILKY, // 보슬보슬
    EC_WORD_CUTE, // 귀여운
    EC_WORD_THING, // 것
    EC_WORD_QUES, // ?
    EC_WORD_PHONE, // 전화
    EC_WORD_PLUSH_DOLL, // 봉제인형
    EC_WORD_LETTER // 편지
};

static const u16 sQuizLadyQuestion14[] =
{
    EC_WORD_THOSE_WERE, // 그건
    EC_WORD_STEEL, // 강철
    EC_WORD_FRONT, // 앞에
    EC_WORD_WEAK, // 약하다
    EC_WORD_ROCK_SOLID, // 딱딱
    EC_WORD_QUES, // ?
    EC_WORD_ICE, // 얼음
    EC_WORD_GROUND, // 땅
    0xFFFF
};

static const u16 sQuizLadyQuestion15[] =
{
    EC_WORD_THOSE_WERE, // 그건
    EC_WORD_DARK, // 악
    EC_WORD_FRONT, // 앞에
    EC_WORD_STRONG, // 강하다
    EC_WORD_FIGHT, // 파이트
    EC_WORD_QUES, // ?
    EC_WORD_PSYCHIC, // 에스퍼
    EC_WORD_FIGHTING, // 격투
    0xFFFF
};

static const u16 sQuizLadyQuestion16[] =
{
    EC_WORD_THOSE_WERE, // 그건
    EC_WORD_GHOST, // 고스트
    EC_WORD_FRONT, // 앞에
    EC_WORD_STRONG, // 강하다
    EC_WORD_BADLY, // 나쁜
    EC_WORD_QUES, // ?
    EC_WORD_NORMAL, // 노말
    EC_WORD_DARK, // 악
    0xFFFF
};

static const u16 *const sQuizLadyQuizQuestions[] =
{
    sQuizLadyQuestion1,
    sQuizLadyQuestion2,
    sQuizLadyQuestion3,
    sQuizLadyQuestion4,
    sQuizLadyQuestion5,
    sQuizLadyQuestion6,
    sQuizLadyQuestion7,
    sQuizLadyQuestion8,
    sQuizLadyQuestion9,
    sQuizLadyQuestion10,
    sQuizLadyQuestion11,
    sQuizLadyQuestion12,
    sQuizLadyQuestion13,
    sQuizLadyQuestion14,
    sQuizLadyQuestion15,
    sQuizLadyQuestion16
};

static const u16 sQuizLadyQuizAnswers[] =
{
    EC_WORD_POKEDEX,
    EC_WORD_DARK,
    EC_WORD_LEVEL,
    EC_WORD_FLOWERS,
    EC_WORD_EGG,
    EC_WORD_OWN_TEMPO,
    EC_WORD_ROCK,
    EC_WORD_SHADOW_TAG,
    EC_WORD_IMMUNITY,
    EC_WORD_POKEMON,
    EC_WORD_PC,
    EC_WORD_TELEVISION,
    EC_WORD_PLUSH_DOLL,
    EC_WORD_ICE,
    EC_WORD_FIGHTING,
    EC_WORD_DARK
};

static const u16 sQuizLadyPrizes[] =
{
    ITEM_GLITTER_MAIL,
    ITEM_BEAD_MAIL,
    ITEM_TROPIC_MAIL,
    ITEM_MAX_ETHER,
    ITEM_MAX_ETHER,
    ITEM_MAX_ETHER,
    ITEM_WATMEL_BERRY,
    ITEM_BELUE_BERRY,
    ITEM_DURIN_BERRY,
    ITEM_LUXURY_BALL,
    ITEM_TM15_HYPER_BEAM,
    ITEM_BIG_PEARL,
    ITEM_STAR_PIECE,
    ITEM_RARE_CANDY,
    ITEM_RARE_CANDY,
    ITEM_PREMIER_BALL
};

// Favor Lady data
static const u8 *const sFavorLadyRequests[] =
{
    gText_FavorLady_Slippery,
    gText_FavorLady_Roundish,
    gText_FavorLady_Whamish,
    gText_FavorLady_Shiny,
    gText_FavorLady_Sticky,
    gText_FavorLady_Pointy
};

static const u16 sFavorLadyAcceptedItems_Slippery[] =
{
    ITEM_REPEL,
    ITEM_SUPER_REPEL,
    ITEM_MAX_REPEL,
    ITEM_ANTIDOTE,
    ITEM_PARALYZE_HEAL,
    ITEM_BURN_HEAL,
    ITEM_BELUE_BERRY,
    ITEM_AWAKENING,
    ITEM_ICE_HEAL,
    ITEM_REVIVE,
    ITEM_MAX_REVIVE,
    ITEM_ENERGY_POWDER,
    ITEM_NONE
};

static const u16 sFavorLadyAcceptedItems_Roundish[] =
{
    ITEM_FLUFFY_TAIL,
    ITEM_PEARL,
    ITEM_BIG_PEARL,
    ITEM_HARD_STONE,
    ITEM_SMOKE_BALL,
    ITEM_SHOAL_SHELL,
    ITEM_TINY_MUSHROOM,
    ITEM_BIG_MUSHROOM,
    ITEM_PECHA_BERRY,
    ITEM_ASPEAR_BERRY,
    ITEM_ORAN_BERRY,
    ITEM_GREPA_BERRY,
    ITEM_MAGOST_BERRY,
    ITEM_WATMEL_BERRY,
    ITEM_POKE_BALL,
    ITEM_ULTRA_BALL,
    ITEM_NONE
};

static const u16 sFavorLadyAcceptedItems_Whamish[] =
{
    ITEM_REVIVAL_HERB,
    ITEM_POTION,
    ITEM_FRESH_WATER,
    ITEM_SODA_POP,
    ITEM_LEMONADE,
    ITEM_HARD_STONE,
    ITEM_LIGHT_BALL,
    ITEM_LAVA_COOKIE,
    ITEM_CHESTO_BERRY,
    ITEM_NANAB_BERRY,
    ITEM_WEPEAR_BERRY,
    ITEM_KELPSY_BERRY,
    ITEM_NOMEL_BERRY,
    ITEM_DURIN_BERRY,
    ITEM_NONE
};

static const u16 sFavorLadyAcceptedItems_Shiny[] =
{
    ITEM_HEAL_POWDER,
    ITEM_X_SPEED,
    ITEM_X_ATTACK,
    ITEM_X_DEFEND,
    ITEM_BLUE_FLUTE,
    ITEM_YELLOW_FLUTE,
    ITEM_RED_FLUTE,
    ITEM_BLACK_FLUTE,
    ITEM_WHITE_FLUTE,
    ITEM_NUGGET,
    ITEM_SUN_STONE,
    ITEM_STARDUST,
    ITEM_STAR_PIECE,
    ITEM_PEARL,
    ITEM_BIG_PEARL,
    ITEM_TWISTED_SPOON,
    ITEM_SILVER_POWDER,
    ITEM_BRIGHT_POWDER,
    ITEM_LUXURY_BALL,
    ITEM_PREMIER_BALL,
    ITEM_NONE
};

static const u16 sFavorLadyAcceptedItems_Sticky[] =
{
    ITEM_ENERGY_ROOT,
    ITEM_FULL_RESTORE,
    ITEM_MAX_POTION,
    ITEM_DIRE_HIT,
    ITEM_X_ACCURACY,
    ITEM_GUARD_SPEC,
    ITEM_WATMEL_BERRY,
    ITEM_LEFTOVERS,
    ITEM_TINY_MUSHROOM,
    ITEM_HEART_SCALE,
    ITEM_NONE
};

static const u16 sFavorLadyAcceptedItems_Pointy[] =
{
    ITEM_QUICK_CLAW,
    ITEM_POISON_BARB,
    ITEM_SHARP_BEAK,
    ITEM_DRAGON_FANG,
    ITEM_TAMATO_BERRY,
    ITEM_DURIN_BERRY,
    ITEM_PETAYA_BERRY,
    ITEM_SALAC_BERRY,
    ITEM_STARDUST,
    ITEM_STAR_PIECE,
    ITEM_NONE
};

static const u16 *const sFavorLadyAcceptedItemLists[] =
{
    sFavorLadyAcceptedItems_Slippery,
    sFavorLadyAcceptedItems_Roundish,
    sFavorLadyAcceptedItems_Whamish,
    sFavorLadyAcceptedItems_Shiny,
    sFavorLadyAcceptedItems_Sticky,
    sFavorLadyAcceptedItems_Pointy
};

static const u16 sFavorLadyPrizes[] =
{
    ITEM_LUXURY_BALL,
    ITEM_NUGGET,
    ITEM_PROTEIN,
    ITEM_HEART_SCALE,
    ITEM_RARE_CANDY,
    ITEM_PP_MAX
};


static const u8 *const sContestLadyMonNames[] =
{
    gText_ContestLady_Handsome,
    gText_ContestLady_Vinny,
    gText_ContestLady_Moreme,
    gText_ContestLady_Ironhard,
    gText_ContestLady_Muscle
};

static const u8 *const sContestLadyCategoryNames[] =
{
    gText_ContestLady_Coolness,
    gText_ContestLady_Beauty,
    gText_ContestLady_Cuteness,
    gText_ContestLady_Smartness,
    gText_ContestLady_Toughness
};

static const u8 *const sContestNames[] =
{
    gText_CoolnessContest,
    gText_BeautyContest,
    gText_CutenessContest,
    gText_SmartnessContest,
    gText_ToughnessContest
};

static const u16 sContestLadyMonSpecies[] =
{
    SPECIES_ZIGZAGOON,
    SPECIES_SKITTY,
    SPECIES_POOCHYENA,
    SPECIES_KECLEON,
    SPECIES_PIKACHU
};
