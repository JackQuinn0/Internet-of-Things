// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html> 
<html lang="en">

<head>
  <meta charset="utf-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Automated Irrigation System</title>
  <link href='https://unpkg.com/boxicons@2.1.4/css/boxicons.min.css' rel='stylesheet'>
  <script src="https://cdn.jsdelivr.net/npm/chart.js"></script>
  
  <style>
  * {
    margin: 0;
    padding: 0;
    box-sizing: border-box;
    font-family: "Poppins", sans-serif;
  }
  body {
    background: linear-gradient(to bottom, #d2f8d2, #a1e3a1);
    transition: background 0.5s ease, color 0.5s ease;
  }
  body.dark-mode {
    background: linear-gradient(to bottom, #0f3d0f, #1a4b1a);
  }
  h1 {
    font-size: 40px;
    margin: 20px 0 10px;
    text-align: center;
  }
  p {
    font-size: 25px;
    text-align: center;
    margin-bottom: 20px;
  }
  .toggle {
    position: absolute;
    top: 20px;
    right: 20px;
    padding: 10px 20px;
    background: linear-gradient(to right, #00c853, #64dd17);
    border: none;
    font-size: 16px;
    color: white;
    border-radius: 25px;
    cursor: pointer;
    transition: background 0.3s ease;
    z-index: 10;
  }
  .toggle:hover {
    background: linear-gradient(to right, #00b94c, #52c300);
  }
  body.dark-mode .toggle {
    background: linear-gradient(to right, #004d40, #1b5e20);
  }
  .sensor-container {
    display: grid;
    grid-template-columns: repeat(auto-fit, minmax(200px, 1fr));
    gap: 20px;
    padding: 20px;
    max-width: 1000px;
    margin: 0 auto;
  }
  .sensor-card {
  min-width: 200px;
  height: 240px;
  background: rgba(255, 255, 255, 0.95);
  padding: 15px;
  border-radius: 15px;
  box-shadow: 0 5px 15px rgba(0, 128, 0, 0.2);
  text-align: center;
  transition: transform 0.3s;
}
  .sensor-card:hover {
    transform: scale(1.03);
  }
  body.dark-mode .sensor-card {
    background: rgba(0, 32, 0, 0.85);
    box-shadow: 0 5px 20px rgba(0, 255, 100, 0.2);
    color: #d0ffd0;
  }
  .center-card {
  grid-column: 2 / span 2;
  justify-self: center;
}
.description-full {
  width: 100%;
  background: #f9fff9;
  padding: 60px 0;
  margin-top: 40px;
  border-top: 2px solid #c5e1c5;
}
body.dark-mode .description-full {
  background: #0f2f0f;
  border-top: 2px solid #3a5d3a;
}
.description-content {
  max-width: 1000px;
  margin: auto;
  padding: 0 40px;
  color: #1b5e20;
  text-align: left;
}

body.dark-mode .description-content {
  color: #d0ffd0;
}
.description-content h2 {
  font-size: 30px;
  margin-top: 20px;
  color: #2e7d32;
  text-align: center;
}

body.dark-mode .description-content h2 {
  color: #a5d6a7;
}

.description-content p {
  font-size: 18px;
  line-height: 1.7;
  margin: 12px 0;
}

.description-content table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 25px;
}

.description-content th,
.description-content td {
  padding: 12px 16px;
  border: 1px solid #c8e6c9;
  text-align: left;
}

.description-content th {
  background-color: #a5d6a7;
  color: #1b5e20;
}

.description-content td {
  background-color: #f1f8f2;
  color: #1b3d1a;
}

body.dark-mode .description-content th {
  background-color: #2e7d32;
  color: #c8facc;
}

body.dark-mode .description-content td {
  background-color: #1b4020;
  color: #d0ffd0;
  border-color: #3a5d3a;
}


</style>

</head>

<body>
  <button class="toggle" onclick="toggleTheme()">Toggle Light/Dark Mode</button>

  <h1>Automated Home Irrigation System</h1>
  <p>Live Sensor Data Dashboard</p>

  <div class="sensor-container">
    <div class="sensor-card">
      <canvas id="tempGauge" width="150" height="150"></canvas>
      <p>Temperature (<span id="tempValue">--</span> °C)</p>
    </div>
    <div class="sensor-card">
      <canvas id="humidityGauge" width="150" height="150"></canvas>
      <p>Humidity (<span id="humidityValue">--</span> %)</p>
    </div>
    <div class="sensor-card">
      <canvas id="soilGauge" width="150" height="150"></canvas>
      <p>Soil Moisture (<span id="soilValue">--</span> %)</p>
    </div>
    <div class="sensor-card">
      <canvas id="ldrGauge" width="150" height="150"></canvas>
      <p>Light Intensity (<span id="ldrValue">--</span>)</p>
    </div>
    <div class="sensor-card center-card">
      <canvas id="ultrasonicGauge" width="150" height="150"></canvas>
      <p>Water Level (<span id="ultrasonicValue">--</span> cm)</p>
    </div>
  </div>
  
<section class="description-full">
  <div class="description-content">
    <h2>Project Description</h2>
    <p>
      Household plants enhance indoor environments by improving air quality, increasing humidity, and reducing stress.
      However, maintaining plant health, particularly watering, can be difficult for busy individuals.
    </p>
    <p>
      This project aims to develop an automated irrigation system for household plants, monitored via a webpage.
      The system uses sensors to monitor soil moisture, temperature, humidity, and light, ensuring plants are watered efficiently.
    </p>

    <h2>Main Components Used</h2>
    <table>
      <thead>
        <tr>
          <th>Component</th>
          <th>Function</th>
        </tr>
      </thead>
      <tbody>
        <tr><td>ESP32</td><td>Controls the system and hosts the web server</td></tr>
        <tr><td>DHT11</td><td>Measures temperature and humidity</td></tr>
        <tr><td>Soil Moisture Sensor</td><td>Detects soil moisture content</td></tr>
        <tr><td>LDR</td><td>Measures ambient light</td></tr>
        <tr><td>Ultrasonic Sensor</td><td>Monitors tank water content level</td></tr>
        <tr><td>Water Pump</td><td>Waters plants based on moisture content reading</td></tr>
        <tr><td>RGB LCD</td><td>Displays real-time data</td></tr>
      </tbody>
    </table>
  </div>
</section>



  <script>
    function toggleTheme() {
      document.body.classList.toggle('dark-mode');
    }

    const tempGauge = createGauge('tempGauge', 'Temperature', 0, 50);
    const humidityGauge = createGauge('humidityGauge', 'Humidity', 0, 100);
    const soilGauge = createGauge('soilGauge', 'Soil Moisture', 0, 100);
    const ldrGauge = createGauge('ldrGauge', 'Light Intensity', 0, 100);  
    const ultrasonicGauge = createGauge('ultrasonicGauge', 'Water Level', 0, 100);

    function createGauge(canvasId, label, min, max) {
      return new Chart(document.getElementById(canvasId).getContext('2d'), {
        type: 'doughnut',
        data: {
          labels: [label],
          datasets: [{
            data: [0, max],
            backgroundColor: ['#66bb6a', '#e0e0e0'], 
            borderWidth: 1
          }]
        },
        options: {
          responsive: false,
          cutoutPercentage: 70,
          rotation: -90,
          circumference: 180,
          legend: { display: false },
          tooltips: { enabled: false }
        }
      });
    }

    function updateGauge(gauge, value, max) {
      gauge.data.datasets[0].data = [value, max - value];
      gauge.update();
    }

    function fetchData() {
  fetch('/sensor-data')
    .then(response => response.json())
    .then(data => {
      updateGauge(tempGauge, data.temperature, 50);
      document.getElementById("tempValue").innerText = data.temperature;

      updateGauge(humidityGauge, data.humidity, 100);
      document.getElementById("humidityValue").innerText = data.humidity;

      updateGauge(soilGauge, data.soilMoisture, 100);
      document.getElementById("soilValue").innerText = data.soilMoisture;

      updateGauge(ldrGauge, data.ldr, 100);
      document.getElementById("ldrValue").innerText = data.ldr;

      updateGauge(ultrasonicGauge, 100-data.ultrasonic, 100);
      document.getElementById("ultrasonicValue").innerText = data.ultrasonic;
    })
    .catch(error => console.error('Error fetching data:', error));
}

    setInterval(fetchData, 2000);
  </script>
</body>

</html>
)=====");
