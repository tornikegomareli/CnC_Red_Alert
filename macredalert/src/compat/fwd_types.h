/*
 * fwd_types.h — Forward declarations and typedefs for types used across headers
 * before their defining header is included in FUNCTION.H's chain.
 * Force-included before FUNCTION.H to break the circular dependency.
 */
#ifndef FWD_TYPES_H
#define FWD_TYPES_H

/* From KEY.H */
typedef enum KeyASCIIType {
    KA_NONE = 0,
    KA_MORE = 1,
    KA_SETBKGDCOL = 2,
    KA_SETFORECOL = 6,
    KA_BACKSPACE = 8,
    KA_TAB = 9,
    KA_RETURN = 13,
    KA_DELETE = 127,
    KA_FORMFEED = 12,
    KA_SPACE = 32,
    KA_ESC = 27,
    KA_LMOUSE = 0x701,
    KA_RMOUSE = 0x702,
} KeyASCIIType;

/* From SHAPE.H */
typedef enum ShapeFlags_Type {
    SHAPE_NORMAL    = 0x0000,
    SHAPE_HORZ_REV  = 0x0001,
    SHAPE_VERT_REV  = 0x0002,
    SHAPE_SCALING   = 0x0004,
    SHAPE_VIEWPORT_REL = 0x0010,
    SHAPE_WIN_REL   = 0x0010,
    SHAPE_CENTER    = 0x0020,
    SHAPE_TRANS     = 0x0040,
    SHAPE_FADING    = 0x0100,
    SHAPE_PREDATOR  = 0x0200,
    SHAPE_COMPACT   = 0x0400,
    SHAPE_PRIORITY  = 0x0800,
    SHAPE_GHOST     = 0x1000,
    SHAPE_SHADOW    = 0x2000,
    SHAPE_PARTIAL   = 0x4000,
    SHAPE_COLOR     = 0x8000,
} ShapeFlags_Type;

/* Mouse input event flags used in gadget/input headers */
#define LEFTPRESS   0x0001
#define LEFTHELD    0x0002
#define LEFTRELEASE 0x0004
#define LEFTUP      0x0008
#define RIGHTPRESS  0x0010
#define RIGHTHELD   0x0020
#define RIGHTRELEASE 0x0040
#define RIGHTUP     0x0080

#endif /* FWD_TYPES_H */
