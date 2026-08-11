// ================================
// SMART ENERGY MONITOR
// ================================

// Electricity rate
const electricityRate = 8;

// Initial values
let voltage = 230;
let current = 2.35;
let power = 540;
let energy = 4.82;

let applianceON = true;


// ================================
// DISPLAY DATA
// ================================

function updateDisplay() {

    document.getElementById("voltage").textContent =
        voltage.toFixed(0);

    document.getElementById("current").textContent =
        current.toFixed(2);

    document.getElementById("power").textContent =
        power.toFixed(0);

    document.getElementById("energy").textContent =
        energy.toFixed(2);

    document.getElementById("todayEnergy").textContent =
        energy.toFixed(2);

    document.getElementById("cost").textContent =
        (energy * electricityRate).toFixed(2);

    document.getElementById("applianceStatus").textContent =
        applianceON ? "ON" : "OFF";
}


// ================================
// POWER BUTTON
// ================================

const powerBtn = document.getElementById("powerBtn");

powerBtn.addEventListener("click", function () {

    applianceON = !applianceON;

    if (applianceON) {

        powerBtn.textContent = "Turn OFF";
        powerBtn.classList.add("on");

        power = 540;

        current = 2.35;

    } else {

        powerBtn.textContent = "Turn ON";
        powerBtn.classList.remove("on");

        power = 0;

        current = 0;
    }

    updateDisplay();
});


// ================================
// REFRESH BUTTON
// ================================

document.getElementById("refreshBtn")
.addEventListener("click", function () {

    if (applianceON) {

        voltage = 220 + Math.random() * 20;

        current = 1.8 + Math.random() * 1;

        power = voltage * current;

        // Small simulated energy increase
        energy += power / 100000;

    } else {

        voltage = 230;
        current = 0;
        power = 0;
    }

    updateDisplay();

    addChartData(power);
});


// ================================
// DARK MODE
// ================================

document.getElementById("themeBtn")
.addEventListener("click", function () {

    document.body.classList.toggle("dark");

    if (document.body.classList.contains("dark")) {
        this.textContent = "☀️";
    } else {
        this.textContent = "🌙";
    }
});


// ================================
// CHART
// ================================

const ctx = document
    .getElementById("energyChart")
    .getContext("2d");

const chartLabels = [
    "10:00",
    "10:05",
    "10:10",
    "10:15",
    "10:20",
    "10:25"
];

const chartData = [
    450,
    510,
    480,
    550,
    520,
    540
];

const energyChart = new Chart(ctx, {

    type: "line",

    data: {

        labels: chartLabels,

        datasets: [{
            label: "Power (W)",
            data: chartData,

            borderWidth: 3,

            tension: 0.3,

            fill: false
        }]
    },

    options: {

        responsive: true,

        maintainAspectRatio: false,

        scales: {

            y: {
                beginAtZero: true
            }
        }
    }
});


// ================================
// ADD CHART DATA
// ================================

function addChartData(newPower) {

    const now = new Date();

    const time =
        now.getHours().toString().padStart(2, "0")
        + ":" +
        now.getMinutes().toString().padStart(2, "0");

    energyChart.data.labels.push(time);

    energyChart.data.datasets[0].data.push(
        Math.round(newPower)
    );

    // Keep only last 10 values
    if (energyChart.data.labels.length > 10) {

        energyChart.data.labels.shift();

        energyChart.data.datasets[0].data.shift();
    }

    energyChart.update();
}


// ================================
// AUTOMATIC DATA UPDATE
// ================================

setInterval(function () {

    if (!applianceON) {
        return;
    }

    voltage = 220 + Math.random() * 20;

    current = 1.8 + Math.random();

    power = voltage * current;

    energy += power / 100000;

    updateDisplay();

    addChartData(power);

}, 5000);


// First display
updateDisplay();