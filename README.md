# vortex-asv-firmware
Software that provides low level control of hardware on Vortex' Autonomous Surface Vehicle.

##Currently customised firmware:

* ESC-firmware
    * Optimise the settings used in the Electronic Speed Controllers for the ASV
    * Example: Limits maximum throttle and current draw.

* Fail Safe-firmware
    * Used to decode PWM-signals from FrSky-radio reciever.
    * Used to shut down and lock thruster-relays in case of emergency.
    * Used to toggle between autonomous or manual remote control operation.
    * Used to control the status light that indicates the ASV's mode of operation. 


```json
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/vortex-asv-firmware/fs-firmware-v4-c/include/**",
                "/usr/lib/avr/include/"
            ]
        }
    ],
    "version": 4
}
```