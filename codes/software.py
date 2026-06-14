import tkinter as tk
from tkinter import ttk, scrolledtext
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC
from selenium.common.exceptions import TimeoutException
import threading
import random
from PIL import Image, ImageTk
#from PIL.Image import open
import time
from re import I
import re

import sys
import glob
from turtle import bgcolor
from idna import valid_contextj
from pyparsing import oneOf
import serial
import time
global resultport
class StellariumApp:
    def __init__(self, master):
        self.master = master
        master.title("Stellarium Web Scraper")
        master.geometry("600x400")
        master.configure(bg='navy')

        self.sky_objects = [
            "Sun", "Moon", "Mercury", "Venus", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune",
            "Pluto", "Sirius", "Betelgeuse", "Rigel", "Vega", "Antares", "Aldebaran", "Pollux",
            "Spica", "Arcturus", "Capella", "Procyon", "Achernar", "Deneb", "Regulus", "Altair",
            "Pleiades", "Orion Nebula", "Andromeda Galaxy", "Crab Nebula", "Whirlpool Galaxy",
            "Triangulum Galaxy", "Sombrero Galaxy", "Centaurus A", "Carina Nebula", "Eagle Nebula",
            "Omega Centauri", "47 Tucanae", "Horsehead Nebula", "Crab Pulsar", "Beehive Cluster",
            "Dumbbell Nebula", "Ring Nebula", "Pinwheel Galaxy", "Bode's Galaxy", "Cigar Galaxy",
            "Tarantula Nebula", "Helix Nebula", "Lagoon Nebula", "Trifid Nebula", "Pillars of Creation"
        ]

        self.set_background_image() 
        self.create_widgets()
        self.animate_background()

    def serial_ports(self):
        global resultport
        if sys.platform.startswith('win'):
            ports = ['COM%s' % (i + 1) for i in range(256)]
        else:
            raise EnvironmentError('Unsupported platform')

        resultport = []
        for port in ports:
            try:
                s = serial.Serial(port)
                s.close()
                resultport.append(port)
            except (OSError, serial.SerialException):
                pass
        if len(resultport)==0:
            b ="... "
            resultport.append("No device is connected")

        return resultport

    def set_background_image(self):
        bg_image_path = "C:\\Users\\akous\\Downloads\\milky-way-starry-sky-night-sky-star-956981.jpeg" 
        bg_image = Image.open(bg_image_path)
        bg_image = bg_image.resize((1200, 800), Image.Resampling.LANCZOS)  
        self.bg_photo = ImageTk.PhotoImage(bg_image)
        
        self.canvas = tk.Canvas(self.master, width=800, height=600)
        self.canvas.pack(fill="both", expand=True)
        self.bg_image_id = self.canvas.create_image(0, 0, image=self.bg_photo, anchor="nw")

    def create_widgets(self):
        frame = tk.Frame(self.master, bg='#151f36')
        frame.place(relx=0.5, rely=0.5, anchor='center')
        
        ttk.Label(frame, text="Select a sky object:", background='#151f36', foreground='white').pack(pady=10)

        x = self.serial_ports()
        self.object_var2 = tk.StringVar()
        self.object_combo = ttk.Combobox(frame, textvariable=self.serial_ports, values= x)
        self.object_combo.pack(pady=6)
        self.object_combo.set("select the port")

        self.object_var = tk.StringVar()
        self.object_combo = ttk.Combobox(frame, textvariable=self.object_var, values=self.sky_objects)
        self.object_combo.pack(pady=5)
        self.object_combo.set(self.sky_objects[0])

        ttk.Button(frame, text="Search", command=self.start_search).pack(pady=10)

        self.result_text = scrolledtext.ScrolledText(frame, width=50, height=10, bg='#2e437c', fg='white')
        self.result_text.pack(pady=10)

    def start_search(self):
        self.result_text.delete('1.0', tk.END)
        self.result_text.insert(tk.END, "Searching... Please wait.\n")
        threading.Thread(target=self.search_object, daemon=True).start()

 

    def search_object(self): 
        
        chosenport = self.object_var2.get()
        print("######################################################################")
        print(chosenport)
        print("######################################################################")
        arduino = serial.Serial(port= resultport[0], baudrate=115200, timeout=1)

        name1 = self.object_var.get()
        
        service = Service(executable_path='C:\\Users\\akous\\Downloads\\chromedriver-win64\\chromedriver.exe')
        options = webdriver.ChromeOptions()
        options.add_argument("--headless=new")
        driver = webdriver.Chrome(service=service, options=options)

        try:
            driver.get('https://stellarium-web.org/')
            
            WebDriverWait(driver, 20).until(
                EC.presence_of_element_located((By.CSS_SELECTOR, 'body'))
            )
            
            try:
                close_button = WebDriverWait(driver,0.5).until(
                    EC.element_to_be_clickable((By.CSS_SELECTOR, 'button[title="Close"]'))
                )
                close_button.click()
            except TimeoutException:
                pass
            
            search_box = WebDriverWait(driver, 10).until(
                EC.presence_of_element_located((By.ID, 'input-33'))
            )
            search_box.send_keys(name1)
            search_box.send_keys(u'\ue007')
            
            object_element = WebDriverWait(driver, 20).until(
                EC.element_to_be_clickable((By.XPATH, f"//div[contains(text(), '{name1}')]"))
            )
            object_element.click()
            
            object_info = WebDriverWait(driver, 20).until(
                EC.presence_of_element_located((By.CSS_SELECTOR, '.row.no-gutters'))
            )
            
            radec_vals = driver.find_elements(By.CLASS_NAME, "radecVal")
            az_angle, az_min, az_sec = radec_vals[9].text.strip(), radec_vals[10].text.strip(), radec_vals[11].text.strip()
            alt_angle, alt_min, alt_sec = radec_vals[6].text.strip(), radec_vals[7].text.strip(), radec_vals[8].text.strip()

            #result = f"Object: {name1}\n"
            result = f"{az_angle} {az_min} {az_sec}\n"
            result += f"{alt_angle} {alt_min} {alt_sec}\n"
            
            arduino.write(bytes(result, 'utf-8')) 
            time.sleep(0.05) 

            self.master.after(0, self.update_result, result)

        except TimeoutException as e:
            self.master.after(0, self.update_result, f"An error occurred: {str(e)}")
        finally:
            driver.quit()

    def update_result(self, result):
        self.result_text.delete('1.0', tk.END)
        self.result_text.insert(tk.END, result)

    def animate_background(self):
        x, y = self.canvas.coords(self.bg_image_id)
        new_x = x - 0.5
        if new_x <= -800:  # Reset to the starting position when the image moves out of view
            new_x = 0
        self.canvas.coords(self.bg_image_id, new_x, y)
        self.master.after(50, self.animate_background)

root = tk.Tk()
app = StellariumApp(root)
root.mainloop()
