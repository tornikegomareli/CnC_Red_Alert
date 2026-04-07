/*
 * phone.h — Reconstructed PhoneEntryClass for macOS port
 *
 * PhoneEntryClass was missing from the EA open-source release.
 * Reconstructed from usage in NULLDLG.CPP and SESSION.CPP.
 */

#ifndef PHONE_H
#define PHONE_H

#include "session.h"  // for SerialSettingsType

class PhoneEntryClass
{
public:
    enum {
        PHONE_MAX_NAME = 21,
        PHONE_MAX_NUM  = 21
    };

    PhoneEntryClass(void) {
        Name[0] = '\0';
        Number[0] = '\0';
        memset(&Settings, 0, sizeof(Settings));
        Settings.IRQ = -1;
        Settings.Baud = -1;
    }

    char Name[PHONE_MAX_NAME];
    char Number[PHONE_MAX_NUM];
    SerialSettingsType Settings;
};

#endif // PHONE_H
