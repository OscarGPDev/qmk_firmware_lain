
# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = no            # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = yes        # Enable WS2812 RGB underlight.  Do not enable this with audio at the same time.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing

# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend


# ergoinu configs
FORCE_MASTER = no
FORCE_SLAVE = no
DISABLE_PROMICRO_LEDs = yes

ifneq ($(strip $(ERGOINU)),)
  ifeq ($(findstring promicroled, $(ERGOINU)), promicroled)
    DISABLE_PROMICRO_LEDs = no
  endif
  ifeq ($(findstring master, $(ERGOINU)), master)
    FORCE_MASTER = yes
  endif
  ifeq ($(findstring slave, $(ERGOINU)), slave)
    FORCE_SLAVE = yes
  endif
endif

ifeq ($(strip $(FORCE_MASTER)), yes)
  ifeq ($(strip $(FORCE_SLAVE)), yes)
    $(error FORSE_MASTER and FORSE_SLAVE are both 'yes')
  endif
endif

ifeq ($(strip $(DISABLE_PROMICRO_LEDs)), yes)
  OPT_DEFS += -DDISABLE_PROMICRO_LEDs
endif

ifeq ($(strip $(FORCE_MASTER)), yes)
  OPT_DEFS += -DFORSE_MASTER
endif

ifeq ($(strip $(FORCE_SLAVE)), yes)
  OPT_DEFS += -DFORSE_SLAVE
endif



# # Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )

ifndef QUANTUM_DIR
	include ../../../../Makefile
endif
