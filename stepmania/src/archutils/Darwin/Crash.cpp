/*
 *  Crash.cpp
 *  stepmania
 *
 *  Created by Steve Checkoway on Thu Jul 31 2003.
 *  Copyright (c) 2003 Steve Checkoway. All rights reserved.
 *
 */

#include "StdString.h"
#include "Crash.h"
#include "archutils/Unix/CrashHandler.h"
#include <Carbon/Carbon.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void InformUserOfCrash( const CString &sPath )
{
    CFStringRef error = CFStringCreateWithCString(NULL,
                                                  "StepMania has crashed.  Debug information has been output to\n"
                                                  "\n"
                                                  "    " + sPath + "\n"
                                                  "\n"
                                                  "Please report a bug at:\n"
                                                  "\n"
                                                  "    http://sourceforge.net/tracker/?func=add&group_id=37892&atid=421366",
                                                  kCFStringEncodingASCII);
    CFStringRef OK = CFStringCreateWithCString(NULL, "Open crashinfo", kCFStringEncodingASCII);
    CFStringRef Cancel = CFStringCreateWithCString(NULL, "Cancel", kCFStringEncodingASCII);
    struct AlertStdCFStringAlertParamRec params = {kStdCFStringAlertVersionOne, true, false, OK, Cancel, NULL,
        kAlertStdAlertOKButton, kAlertStdAlertCancelButton, kWindowAlertPositionParentWindowScreen, NULL};
    DialogRef dialog;
    SInt16 button;

    CreateStandardAlert(kAlertStopAlert, error, NULL, &params, &dialog);
    AutoSizeDialog(dialog);
    RunStandardAlert(dialog, NULL, &button);
    switch (button)
    {
        case kAlertStdAlertOKButton:
            // This is lazy, and easy, and it _should_ work.
            if (system(NULL))
                system("open '" + sPath + "'");
            else
                SysBeep(30);
            break;
    }
    CFRelease(OK);
    CFRelease(Cancel);
    CFRelease(error);
}
