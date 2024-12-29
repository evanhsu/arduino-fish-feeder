# arduino-fish-feeder

This firmware project was created using [Particle Developer Tools](https://www.particle.io/developer-tools/) and is compatible with all [Particle Devices](https://www.particle.io/devices/).

This is intended to accompany the 3D-printed fish feeder from <https://www.thingiverse.com/thing:2539750>

Built using a Particle Photon 2 with TowerPro SG92R Micro Servo
(Make sure to bind the servo ground to the Particle device ground to avoid facepalm)

## Prerequisites To Use This Repository

To use this software/firmware on a device, you'll need:

- A [Particle Device](https://www.particle.io/devices/).
- Windows/Mac/Linux for building the software and flashing it to a device.
- [Particle Development Tools](https://docs.particle.io/getting-started/developer-tools/developer-tools/) installed and set up on your computer.

## Getting Started

1. If your Photon microcontroller is not yet hooked up to your dev machine, run the [device setup process](https://setup.particle.io/) on your Particle device first. This ensures your device's firmware is up-to-date and you have a solid baseline to start from.

2. With the Particle Workbench VSCode Extension, run the [compile and flash](https://docs.particle.io/getting-started/developer-tools/workbench/#cloud-build-and-flash) command to send the firmware to your device. Ensure your device's USB port is connected to your computer.

3. Verify the device's operation by monitoring its logging output:

   - In Visual Studio Code with the Particle Plugin, open the [command palette](https://docs.particle.io/getting-started/developer-tools/workbench/#particle-commands) and choose "Particle: Serial Monitor".
   - Or, using the Particle CLI, execute:

   ```
   particle serial monitor --follow
   ```
