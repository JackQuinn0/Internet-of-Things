// To create literal strings stored in flash memory enclose your HTML code between 
// F(R"=====( HTML code here )=====");
// If you have 1 reading then you probably have 2 literal strings
// If you have 2 readings then you probably have 3 literal strings etc.

String homePagePart1 = F(R"=====(<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="utf-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Temperature Reading WebServer</title>
  <style>
    body {       
      background-color: DodgerBlue;
      font-family: Arial, sans-serif;
    }
    .flex-Container {
      display: flex;
      flex-direction: column;
      align-items: center;
      background-color: DodgerBlue;
    }
    h1 {
      font-size: 40px;
      color: navy;
      text-align: center;
    }
    p {
      font-size: 25px;
      color: navy;
      text-align: center;
    }
    table {
      border-collapse: collapse;
      width: 80%;
      margin-top: 20px;
      background-color: white;
    }
    th, td {
      font-size: 25px;
      padding: 10px;
      text-align: center;
      border: 1px solid #ddd;
    }
    th {
      background-color: lightgray;
    }
  </style>
</head>
<body>
  <div class="flex-Container">
    <h1>Automated Home Irrigation System</h1>
    <p>Welcome to my website displaying live sensor data</p>
    <table>
      <tr>
        <th>Sensor</th>
        <th>Value</th>
        <th>Unit</th>
      </tr>
      <tr>
        <td>Temperature</td>
        <td>)=====");

String homePagePart2 = F(R"=====(</td>
        <td>Degree Cel</td>
      </tr>
      <tr>
        <td>Humidity</td>
        <td>)=====");

String homePagePart3 = F(R"=====(</td>
        <td>%</td>
      </tr>
      <tr>
        <td>Soil Moisture</td>
        <td>)=====");

String homePagePart4 = F(R"=====(</td>
        <td>%</td>
      </tr>
    </table>
  </div>
</body>
</html>)=====");

