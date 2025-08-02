#pragma once
#include <stdint.h>
#include <raylib.h>

// https://projectarrhythmia.wiki.gg/wiki/VGD_format
// https://projectarrhythmia.wiki.gg/wiki/VGP_format
// https://projectarrhythmia.wiki.gg/wiki/VGT_format

// TODO: Replace UnknownSizeInt with correct data types
// TODO?: Possibly names should be replaced.
// TODO: Clean out all editor data after confirming they are not needed for playing levels \
//  Possibly keep some of them for level editor (?)

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

// Keyframes
typedef struct {
    float t;
    EasingType ct;
    RandomizationType r;
    Vector3 er;
    Vector2 ev;
} MovementKeyframe;

typedef MovementKeyframe ScaleKeyframe;

typedef struct {
    float t;
    EasingType ct;
    RandomizationType r;
    Vector3 er;
    float ev;
} RotationKeyframe;

typedef struct {
    float t;
    EasingType ct;
    Vector3 ev;
} ColorKeyframe;

typedef struct {
    float t;
    EasingType ct;
    union {
        float* ev;
        char* theme;
    } data;
} EventKeyframe;

// Game Objects
typedef struct {
    char *id;
    struct {
        uint8_t s, so;
    } s;
    UnknownSizeInt c;
    struct {
        Vector2 p, s;
        float r;
    } t;

    struct {
        float l, ld;
        bool ap, as, ar;
        Vector2 p, s;
        float r;
    } an;
} ParallaxObject;

typedef struct {
    char *id, *pre_id, *pre_iid, *n;
    ObjectType t;
    float st;
    AutokillType ak_t;
    float ak_o;
    GradientType gt;
    uint8_t s, so;
    UnknownSizeInt d;
    char *p_id;
    uint8_t p_t; // 8 bits. MSB 5 is unused. Rest's MSB to LSB in respective order Position, Scale, Rotation
    Vector3 p_o;
    // Object Ed Data Seemed Useless
    Vector2 o;

    // Flattened
    MovementKeyframe *movement_keyframes;
    ScaleKeyframe *scale_keyframes;
    RotationKeyframe *rotation_keyframes;
    ColorKeyframe *color_keyframes;
} GameObject;

typedef struct {
    char *id, *pid;
    // ed data not included

    // Flattened
    Vector2 position, scale;
    float rotation;
} PrefabObject; // PrefabInstance

// .VGP & .VGT
typedef struct {
    char *n, *description, preview;
    PrefabType type;
    float o;
    // TODO: Objects
} PrefabData;

typedef struct {
    char *id;
    PrefabData data;
} PrefabDataWithID;

typedef struct {
    char *name;

    // TODO: Check these
    char *base_bg, *base_gui, *base_gui_accent;
    char *pla[4];
    char *obj[9];
    char *fx[9];
    char *bg[9];
} ThemeData;

typedef struct {
    char *id;
    ThemeData data;
} ThemeDataWithID;

// Level Related
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
    char *id, *n, *d;
    UnknownSizeInt c;
    float t;
} Marker;

// Level Data
typedef struct {
    EditorData editor;
    Trigger *triggers;
    // editor_prefab_spawn is deemed unneeded
    struct {
        UnknownSizeInt d, c;
        ParallaxObject *o;
    } parallax_settings[5];
    CheckPoint *checkpoints;
    GameObject *objects;
    PrefabObject *prefab_objects;
    PrefabDataWithID *prefabs;
    ThemeDataWithID *themes;
    Marker *markers;
    EventKeyframe **events;
} LevelData;
