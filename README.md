# FireBeetle Web LED

<div align="right">[![Medium](https://img.shields.io/badge/Medium-12100E?logo=medium&logoColor=white)](https://medium.com/@mister.funable/making-a-local-web-server-with-the-dfrobot-firebeetle-2-esp32-e-platformio-0bbe6abfa8ab)</div>

Blink the FireBeetle 2 ESP32-E onboard LED through a lightweight WiFi web server built with PlatformIO.
Great for showing how to expose GPIO control over HTTP without bringing in heavy frameworks.

> Update the `ssid` and `password` constants in `src/main.cpp` before flashing.

## Setup
- Requirements: PlatformIO CLI 6+, DFROBOT FireBeetle 2 ESP32-E, 2.4 GHz WiFi
- Clone: `git clone https://github.com/custom/dfrobot.git && cd dfrobot`
- Docker: Not published; run PlatformIO natively
- Native: USB-connect the board, then use the commands below

```bash
git clone https://github.com/custom/dfrobot.git
cd dfrobot
pio run
pio run -t upload
```

## Commands

| Command | Description |
|---------|-------------|
| `pio run` | Compile firmware for `dfrobot_firebeetle2_esp32e` |
| `pio run -t upload` | Flash the board over USB |
| `pio device monitor -b 115200` | Watch WiFi and HTTP logs |

```bash
pio run -t upload && pio device monitor -b 115200
```

## Output

```
.
├── platformio.ini        # Target board, framework, monitor speed
└── src/
    └── main.cpp          # Web server + LED routes and WiFi config
```

## Config/API Setup
- Open `src/main.cpp` and replace `ssid`/`password` with your WiFi credentials.
- Change `LED_PIN` if you wire a different LED.
- Rebuild with `pio run` whenever you edit the sketch.
- Flash again via `pio run -t upload`, then load the serial monitor to read the IP address.
- Visit `http://<board-ip>/`, use `/on` or `/off` to toggle the LED.

## Troubleshooting

| Error | Fix |
|-------|-----|
| `Connecting to WiFi......` never stops | Ensure credentials are correct and the network is 2.4 GHz; reboot the board after updating |
| Browser hangs on `/on` or `/off` | Confirm the serial monitor shows the same IP you are using; press the EN button to restart the server |
| `Timed out waiting for packet header` during upload | Hold BOOT while tapping EN, then keep holding BOOT until upload starts |

---
Tweak the HTML in `main.cpp` to add more controls once the basics work.
