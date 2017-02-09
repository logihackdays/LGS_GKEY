# LGS_GKEY
The Logitech Gaming G-key SDK enables to get the current state of G-keys and extra mouse buttons for supported Logitech gaming mice and keyboards.

It can be used via callback or polling. It only works when the Logitech Gaming Software is running (8.55 or later).

# SDK Package

The following files are included:

● LogitechGkeyLib.h: C/C++ header file containing function prototypes

● LogitechGkeyLib.lib: companion lib file to access DLL exported functions (32 and 64 bit)

# Requirements

The Logitech Gaming G-key SDK can be used on the following platforms:

● Windows XP SP2 (32-bit and 64-bit)

● Windows Vista (32-bit and 64-bit)

● Windows 7 (32-bit and 64-bit)

● Windows 8 (32-bit and 64-bit)

# Do’s and Don’ts

These are a few guidelines that may help you implement 'better' support in your game:

● If using the callback works for you, use it rather than polling. When polling if a user clicks and releases a button within a single game loop the button press will not be seen.
