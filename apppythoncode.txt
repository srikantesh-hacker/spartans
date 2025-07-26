from flask import Flask, render_template, request, redirect
import serial
import time
import csv
from datetime import datetime
import os

app = Flask(__name__)
csv_file = 'data.csv'

def write_csv_header():
    with open(csv_file, mode='w', newline='') as file:
        writer = csv.writer(file)
        writer.writerow(['Name', 'Age', 'Gender', 'Height (cm)', 'Weight (kg)', 'BMI', 'BMI Category', 'Daily Calories (kcal)', 'Timestamp'])

if not os.path.exists(csv_file) or os.stat(csv_file).st_size == 0:
    write_csv_header()

def get_arduino_data():
    try:
        arduino = serial.Serial('COM4', 9600, timeout=2)
        time.sleep(2)
        arduino.reset_input_buffer()
        arduino.write(b'GET\n')
        start_time = time.time()
        while time.time() - start_time < 5:
            if arduino.in_waiting:
                line = arduino.readline().decode().strip()
                arduino.close()
                return line
        arduino.close()
        return None
    except serial.SerialException as e:
        print("Serial error:", e)
        return None

def get_bmi_category(bmi):
    if bmi < 18.5:
        return "Underweight"
    elif 18.5 <= bmi < 25:
        return "Normal weight"
    elif 25 <= bmi < 30:
        return "Overweight"
    else:
        return "Obese"

def calculate_calories(weight, height, age, gender):
    if gender.lower() == 'male':
        bmr = 10 * weight + 6.25 * height - 5 * age + 5
    else:
        bmr = 10 * weight + 6.25 * height - 5 * age - 161
    return round(bmr * 1.2, 2)  # sedentary activity

@app.route('/', methods=['GET', 'POST'])
def index():
    result = None
    if request.method == 'POST':
        name = request.form['name']
        age = int(request.form['age'])
        gender = request.form['gender']
        try:
            sensor_height = float(request.form['sensor_height'])
        except ValueError:
            result = {'error': 'Invalid sensor height'}
            return render_template('index.html', result=result)

        line = get_arduino_data()
        if line is None:
            result = {'error': 'No response from Arduino or COM4 busy.'}
        else:
            try:
                parts = line.split(',')
                dist = float(parts[0].split(':')[1])
                weight = float(parts[1].split(':')[1])
                height = round(sensor_height - dist, 2)
                bmi = round(weight / ((height / 100) ** 2), 2)
                bmi_cat = get_bmi_category(bmi)
                calories = calculate_calories(weight, height, age, gender)
                timestamp = datetime.now().strftime('%Y-%m-%d %H:%M:%S')

                with open(csv_file, mode='a', newline='') as file:
                    writer = csv.writer(file)
                    writer.writerow([name, age, gender, height, weight, bmi, bmi_cat, calories, timestamp])

                result = {
                    'name': name,
                    'age': age,
                    'gender': gender,
                    'height': height,
                    'weight': weight,
                    'bmi': bmi,
                    'bmi_category': bmi_cat,
                    'calories': calories,
                    'timestamp': timestamp
                }
            except Exception as e:
                result = {'error': f'Invalid data from Arduino: {line}'}

    return render_template('index.html', result=result)

@app.route('/refresh', methods=['POST'])
def refresh():
    write_csv_header()
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
