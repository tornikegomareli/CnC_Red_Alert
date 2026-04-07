/*
 * force_include.h — Force-included before every source file
 * Prevents bool/true/false redefinition issues in legacy code
 */

#ifndef FORCE_INCLUDE_H
#define FORCE_INCLUDE_H

/* Prevent all the legacy bool redefinitions */
#define TRUE_FALSE_DEFINED 1

/* Prevent Borland compiler check from triggering bool redefinition */
#ifndef __BORLANDC__
#define __BORLANDC__ 1
#define _FORCE_INCLUDE_FAKED_BORLANDC
#endif

#endif // FORCE_INCLUDE_H
