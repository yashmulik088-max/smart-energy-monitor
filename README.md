
# ⚡ Smart Energy Monitor

A responsive Smart Energy Monitor dashboard created using HTML, CSS and JavaScript.

## Features

- Voltage monitoring
- Current monitoring
- Power monitoring
- Energy consumption
- Electricity cost calculation
- Live power usage graph
- Appliance ON/OFF control
- Dark mode
- Mobile responsive design
- ESP32 + PZEM-004T integration ready

## Project Structure

```text
smart-energy-monitor/
│
├── index.html
├── style.css
├── script.js
└── README.md

Technologies

- HTML5
- CSS3
- JavaScript
- Chart.js
- GitHub Pages

Hardware Integration

Future hardware version:

AC Appliance
     ↓
PZEM-004T
     ↓
ESP32
     ↓
Wi-Fi
     ↓
Smart Energy Monitor
     ↓
Web Dashboard

Electricity Cost

The demo uses:

Electricity Rate = ₹8 / kWh

Cost is calculated using:

Cost = Energy × Electricity Rate

GitHub Pages

To publish:

1. Open repository Settings.
2. Select Pages.
3. Under Build and deployment, select:
   "Deploy from a branch"
4. Select branch:
   "main"
5. Select folder:
   "/ (root)"
6. Click Save.

Your website will then be available through your GitHub Pages address.

Future Improvements

- Real ESP32 data
- Real PZEM-004T readings
- Firebase database
- User login
- Daily/monthly reports
- Electricity bill prediction
- Multiple appliance monitoring