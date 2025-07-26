# Spartans
# 🥗 Smart Nutrition Monitoring System for Children and Students

This project is a **Smart Nutrition Monitoring System** that helps track and analyze the nutritional status of children and students. The system uses an **ultrasonic sensor** to measure height and a **digital weight machine** for weight. It calculates **BMI (Body Mass Index)** and **daily calorie needs**, and provides a user-friendly **web interface** (built using HTML and Python) to display results and export them to **Excel**.

## 🎯 Objective

To promote health awareness in children by providing an easy-to-use system for measuring height and weight, calculating BMI, and estimating calorie requirements—all accessible through a simple web application.

---

## 🚀 Key Features

- 📏 Height measurement using ultrasonic sensor
- ⚖️ Weight input via standard digital weight machine
- 🧮 Automatic BMI and calorie calculation
- 🌐 Web-based interface using HTML + Python
- 📁 Data export to Excel (.xlsx) for health records
- 🧒 Ideal for schools, health camps, and home use

---

## 🔧 Hardware Components Used

- **Ultrasonic Sensor (HC-SR04)** – for height measurement
- **Arduino Uno / ESP32** – to interface with the sensor and send data
- **Digital Weight Machine** – used manually to obtain weight
- **TTL to RS232 Converter** *(if applicable)* – for communication
- **USB cable** – to connect Arduino to computer
- **Frame/stand** – to mount the ultrasonic sensor

---

## 💻 Software Components Used

- **Arduino IDE** – for sensor code
- **Python (Flask or similar)** – backend server
- **HTML/CSS/JavaScript** – frontend webpage
- **pandas, openpyxl (Python libs)** – for Excel data export

---

## 📐 Calculation Logic

- **Height** is measured by the ultrasonic sensor and sent via serial to Python.
- **Weight** is manually entered into the webpage.
- **BMI** is calculated using the formula:
  
