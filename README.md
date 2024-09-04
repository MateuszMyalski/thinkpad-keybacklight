# Thinkpad Keyboard Backlight Controller

This repository provides a controller for managing the backlight of ThinkPad keyboards with integrated Systemd support. The controller offers extensive features including event-based backlight control, automatic brightness adjustments, and scheduling. This tool is especially useful for users who want to fine-tune their keyboard backlight settings based on input events, time, or system state.

## Features

- [X] Read events from keyboard
- [X] Read events from mouse
- [X] Set keyboard backlight on/off
- [X] Set keyboard brightness
- [X] Set timeout for backlight
- [X] Timeout configuration
- [X] Systemd integration for automatic service management
- [X] Auto on/off based on time of day
- [ ] On/Off based on battery level

## How to test
It is not needed to install the controller to test it's behavior. To run the program directly from the directory:
```bash
make thinkpad-keybacklight
sudo ./thinkpad-keybacklight
```
The program must be executed with sudo privileges as it interacts with /sys/class pseudo-filesystem.

## How to install
To install the ThinkPad Keyboard Backlight Controller, use the following command:

```bash
sudo make install
```

This will compile the necessary files and install the binary to your system, integrating with Systemd for automatic startup and management.

To uninstall the controller, use:
```bash
sudo make uninstall
```

## Configuration

The configuration file can be found in the `include/config.h` directory. This file contains several `#define` directives that allow you to customize the behavior of the backlight controller. This means to apply configuration the program should be recompiled, uninstalled and installed again.

You can customize the default settings by editing the configuration file before building the project. Each setting has a specific purpose:

- `CONFIG_DEFAULT_KEYBOARD_INPUT_EVENT`: Specifies the default input event for the keyboard.
- `CONFIG_DEFAULT_MOUSE_INPUT_EVENT`: Specifies the default input event for the mouse.
- `CONFIG_DEFAULT_TIMEOUT_MS`: Sets the default timeout (in milliseconds) before the backlight turns off after inactivity.
- `CONFIG_DEFAULT_SCHEDULE_ON_HOUR`: Sets the hour when the backlight should automatically turn on.
- `CONFIG_DEFAULT_SCHEDULE_ON_MINUTE`: Sets the minute when the backlight should automatically turn on.
- `CONFIG_DEFAULT_SCHEDULE_OFF_HOUR`: Sets the hour when the backlight should automatically turn off.
- `CONFIG_DEFAULT_SCHEDULE_OFF_MINUTE`: Sets the minute when the backlight should automatically turn off.
- `CONFIG_ENABLE_MOUSE_EVENT`: Enables the mouse event listener for backlight control.
- `CONFIG_ENABLE_KEYBOARD_EVENT`: Enables the keyboard event listener for backlight control.
- `CONFIG_ENABLE_MOUSE_LOWER_BRIGHTNESS`: Reduces brightness when only the mouse is active.
- `CONFIG_ENABLE_SCHEDULE`: Enables scheduling for automatic backlight control.
- `CONFIG_DISABLE_VERBOSE`: Disables verbose logging to reduce console output.