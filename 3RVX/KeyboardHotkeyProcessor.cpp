// Copyright (c) 2015, Matthew Malensek.
// Distributed under the BSD 2-Clause License (see LICENSE.txt for details)

#include "KeyboardHotkeyProcessor.h"

#include <string>

#include "SyntheticKeyboard.h"
#include "HotkeyInfo.h"
#include "Logger.h"

std::unordered_map<std::wstring, unsigned short>
    KeyboardHotkeyProcessor::mediaKeyMap = CreateKeyMap();

void KeyboardHotkeyProcessor::ProcessHotkeys(HotkeyInfo &hki) {
    /* These hotkeys *require* exactly one argument: */
    if (hki.args.size() != 1) {
        return;
    }

    switch (hki.action) {
    case HotkeyInfo::MediaKey: {
        std::wstring &arg = hki.args[0];
        unsigned short vk = mediaKeyMap[arg];
        CLOG(L"Media key: %s", arg.c_str());
        SyntheticKeyboard::SimulateKeypress(vk);
        break;
    }

    case HotkeyInfo::VirtualKey: {
        unsigned short vk = (unsigned short) hki.HexArgToInt(0);
        if (vk == 0) {
            CLOG(L"Ignoring invalid VK value");
            return;
        }
        SyntheticKeyboard::SimulateKeypress(vk);
        break;
    }
    }
}

std::unordered_map<std::wstring, unsigned short>
        KeyboardHotkeyProcessor::CreateKeyMap() {
    std::unordered_map<std::wstring, unsigned short> map;
    for (unsigned int i = 0; i < HotkeyInfo::MediaKeyNames.size(); ++i) {
        map[HotkeyInfo::MediaKeyNames[i]] = HotkeyInfo::MediaKeyVKs[i];
    }
    return map;
}
