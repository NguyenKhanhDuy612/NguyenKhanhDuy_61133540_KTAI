import speech_recognition
import pyttsx3
import os
import pygame
from datetime import date, datetime
import webbrowser
from youtube_search import YoutubeSearch

BLACK = (  0,   0,   0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

xrb= 300
yrb= 300
z=0
while True:
	robot_Listen = speech_recognition.Recognizer()
	robot_speak = pyttsx3.init()
	voices = robot_speak.getProperty('voices')
	robot_speak.setProperty('voice', voices[1].id)
	with speech_recognition.Microphone() as mic:
		print("Robot: Tôi đang nghe bạn nói")
		robot_Listen.adjust_for_ambient_noise(mic, duration = 0.5) 
		audio = robot_Listen.listen(mic)
		# audio = robot_Listen.record(mic, duration = 3)

	print("...")

	try:
		you = robot_Listen.recognize_google(audio)
	except:
		you = ""
	print("You: " + you)

	if you == "":
		robot = "Tôi không nghe bạn nói gì, thử lại!"
	elif "hello" in you:
		robot = "Hello Duy"
	elif "Tôi muốn nghe bài hát của nhạc sĩ Trịnh Công Sơn" in you:
		robot = "Bạn muốn nghe ca sĩ nào hát ?"
	elif "Ca sĩ Lệ Thu" in you:
		robot = "Robot Bài hát Xin Còn Gọi Tên Nhau được không"
	elif "okay" in you:
		# robot = "Mời bạn lắng nghe"
		mysong = "Xin Còn Gọi Tên Nhau"
		while True:
			result = YoutubeSearch(mysong, max_results=10).to_dict()
			if result:
				break
		url = 'https://www.youtube.com' + result[0]['url_suffix']
		webbrowser.open(url)
		speak("Bài hát bạn yêu cầu đã được mở.")
	
	elif "bye" in you:
		robot = "bye"
		print ("Robot: " + robot)
		print ("")
		robot_speak.say(robot)
		robot_speak.runAndWait()
		break
	else:
		robot = "Xin lỗi tôi k nghe bạn nói gì, thử lại"
	print ("Robot: " + robot)
	print ("")
	if(z==0):
		robot_speak.say(robot)
		robot_speak.runAndWait()
	z=0