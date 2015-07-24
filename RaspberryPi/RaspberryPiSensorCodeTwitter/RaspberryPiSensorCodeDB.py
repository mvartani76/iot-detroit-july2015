import urllib
import RPi.GPIO as GPIO
import os
import glob
import time
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')
base_dir = '/sys/bus/w1/devices/'
device_folder = glob.glob(base_dir + '28*')[0]
device_file = device_folder + '/w1_slave'

DEBUG=1
GPIO.setmode(GPIO.BCM)

preurl = "http://www.iot-detroit.org/iot-detroit-july2015/php/SensorRead_MySQL/addsensordata.php"

def read_temp_raw():
	f = open(device_file, 'r')
	lines = f.readlines()
	f.close()
	return lines

def read_temp():
	lines = read_temp_raw()
	while lines[0].strip()[-3:] != 'YES':
		time.sleep(0.2)
		lines = read_temp_raw()
	equals_pos = lines[1].find('t=')
	if equals_pos != -1:
		temp_string = lines[1][equals_pos+2:]
		temp_c = float(temp_string) / 1000.0
		temp_f = temp_c * 9.0 / 5.0 + 32.0
		return temp_c


def RCtime (RCpin):
	reading = 0
	GPIO.setup(RCpin, GPIO.OUT)
	GPIO.output(RCpin, GPIO.LOW)
	time.sleep(0.1)

	GPIO.setup(RCpin, GPIO.IN)
	# This takes about 1 ms per loop cycle
	while (GPIO.input(RCpin) == GPIO.LOW):
		reading += 1
	return reading

while True:
	temp1 = str(read_temp())
	photo1 = str(RCtime(18))
	params = "?temp1="+temp1+"&photo1="+photo1+"&DeviceType=RaspberryPi"
	url = preurl+params
	print(url)
	response = urllib.urlopen(url).read()
	time.sleep(5)


