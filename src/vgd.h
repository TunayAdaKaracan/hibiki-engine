#pragma once
#include <stdint.h>
#include <raylib.h>

typedef int32_t UnknownSizeInt;

// Enums
typedef enum {
    AT_Time = 0,
    AT_PlayerHit,
    AT_PlayerDeath,
    AT_LevelStart,
    AT_LevelRestart,
    AT_LevelRewind
} ActivationTrigger;

typedef enum {
    // VN_Ink and VN_Timeline is not used on custom levels
    ET_PlayerBubble = 2,
    ET_PlayerLocation,
    ET_PlayerDash,
    ET_PlayerXMovement,
    ET_PlayerYMovement,
    ET_BGSpin,
    ET_BGMove,
    ET_PlayerDashDirection,
    ET_TimeGoTo,
    ET_TimeSpeed
} EventType;

typedef enum {
    ET_Linear = 0,  ET_Instant,
    ET_InSine,      ET_OutSine,     ET_InOutSine,
    ET_InElastic,   ET_OutElastic,  ET_InOutElastic,
    ET_InBack,      ET_OutBack,     ET_InOutBack,
    ET_InBounce,    ET_OutBounce,   ET_InOutBounce,
    ET_InQuad,      ET_OutQuad,     ET_InOutQuad,
    ET_InCirc,      ET_OutCirc,     ET_InOutCirc,
    ET_InExpo,      ET_OutExpo,     ET_InOutExpo
} EasingType;

typedef enum {
    OT_Hit = 4,
    OT_NoHit,
    OT_Empty
} ObjectType;

typedef enum {
    GT_None = 0,
    GT_Linear,
    GT_InvertedLinear,
    GT_Radial,
    GT_InvertedRadial
} GradientType;

typedef enum {
    AT_LastKF = 1,
    AT_LastKFOffset,
    AT_FixedTime,
    AT_SongTime
} AutokillType;

typedef enum {
    RT_None = 0,
    RT_Linear,
    RT_Toggle = 3,
    RT_Relative
} RandomizationType;

typedef enum {
    PT_Character = 0,
    PT_CharacterPart,
    PT_Prop,
    PT_Bullet,
    PT_Pulse,
    PT_Bomb,
    PT_Spinner,
    PT_Beam,
    PT_Static,
    PT_Misc1,
    PT_Misc2,
    PT_Misc3
} PrefabType;

// Game Objects


// .VGP & .VGT
typedef struct {
    char *n, *description, preview;
    PrefabType type;
    float o;
    // TODO: Objects
} PrefabData;

typedef struct {
    char *name;

    // TODO: Check these
    char *base_bg, *base_gui, *base_gui_accent;
    char *pla[4];
    char *obj[9];
    char *fx[9];
    char *bg[9];
} ThemeData;

// Other stuff
typedef struct {
    ActivationTrigger event_trigger;
    Vector2 event_trigger_time;
    UnknownSizeInt event_retrigger;
    EventType event_type;
    char **event_data; // TODO: Figure out this
} Trigger;

typedef struct {
    char *id, *n;
    float t;
    Vector2 p;
} CheckPoint;



// Editor Data
typedef struct {
    struct {
        UnknownSizeInt complexity;
        UnknownSizeInt theme;
        uint8_t test_mode;
        bool text_select_objects;
        bool text_select_backgrounds;
        uint8_t outline_mode;
        float collapse_length;
    } general;

    struct {
        struct {
            bool objects;
            bool checkpoints;
        } snap;
        float bpm_value;
        float bpm_offset;
        float BPMValue;
    } bpm;

    struct {
        Vector2 scale;
        UnknownSizeInt thickness;
        float opacity;
        UnknownSizeInt color;
    } grid;

    struct {
        float cam_zoom_offset;
        UnknownSizeInt cam_zoom_offset_color;
    } preview;

    struct {
        UnknownSizeInt as_max;
        UnknownSizeInt as_interval;
    } autosave;
} EditorData;

typedef struct {
    bool expanded;
    bool active;
    char *prefab;
    char **keycodes;
} EditorPrefabSpawnData;

typedef struct {
    char *id, *n, *d;
    UnknownSizeInt c;
    float t;
} Marker;

// Level Data
typedef struct {
    EditorData editor;
    Trigger *triggers;
    EditorPrefabSpawnData editor_prefab_spawn[6];
    // parallax_settings
    CheckPoint *checkpoints;
    // ...
    Marker *markers;
} LevelData;
