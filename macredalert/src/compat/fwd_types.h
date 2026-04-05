/*
 * fwd_types.h — Forward declarations for types used across headers
 * before their defining header is included in FUNCTION.H's chain.
 *
 * This header is included via windows.h stub. For WIN32LIB files that
 * don't include FUNCTION.H, it provides the game types they reference.
 * For CODE/ files that DO include FUNCTION.H, these definitions are
 * compatible (same include guards prevent redefinition).
 */
#ifndef FWD_TYPES_H
#define FWD_TYPES_H

/* Mouse input event flags used in gadget/input headers */
#ifndef LEFTPRESS
#define LEFTPRESS   0x0001
#define LEFTHELD    0x0002
#define LEFTRELEASE 0x0004
#define LEFTUP      0x0008
#define RIGHTPRESS  0x0010
#define RIGHTHELD   0x0020
#define RIGHTRELEASE 0x0040
#define RIGHTUP     0x0080
#endif

#endif /* FWD_TYPES_H */
