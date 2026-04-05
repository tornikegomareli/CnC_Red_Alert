/*
 * fwd_types.h — Forward declarations for types used across headers
 * before their defining header is included in FUNCTION.H's chain.
 */
#ifndef FWD_TYPES_H
#define FWD_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif
/* Needed by jshell.h before wwlib32.h is included */
int Get_Mouse_X(void);
int Get_Mouse_Y(void);
#ifdef __cplusplus
}
#endif

#endif /* FWD_TYPES_H */
