#pragma once

#include "Control.h"

#include <CommCtrl.h>

/// <summary>
/// Manages a 'spin control': a numeric edit box with a up/down 'buddy' to
/// increment or decrement the current value of the box.
/// </summary>
class Spinner : public Control {
public:
    Spinner() {

    }

    Spinner(int id, HWND parent) :
    Control(id, parent) {

    }

    virtual void Enable();
    virtual void Disable();

    void Buddy(int buddyId);

    /// <summary>Sets the range (min, max) for the spin control.</summary>
    /// <param name="lo">Lower bound for the spinner.</param>
    /// <param name="hi">Upper bound for the spinner.</param>
    void Range(int lo, int hi);

    /// <summary>
    /// Unlike the standard Control.Text() method, this uses the spinner buddy
    /// to retrieve the text.
    /// </summary>
    std::wstring Text();

    /// <summary>Sets the buddy text.</summary>
    bool Text(std::wstring text);

    /// <summary>Sets the buddy text.</summary>
    bool Text(int value);

    virtual DLGPROC Notification(NMHDR *nHdr);

public:
    /* Event Handlers */
    std::function<bool(NMUPDOWN *)> OnSpin;

private:
    int _buddyId;
    HWND _buddyWnd;

};
