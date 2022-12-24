import time
import pandas as pd
from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.service import Service
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.by import By
from selenium.webdriver.support import expected_conditions as EC

s = Service(
    'C:/Users/omar-/Desktop/Spring 2022/database/geckodriver-v0.30.0-win64')
driver = webdriver.Firefox(
    'C:/Users/omar-/Desktop/Spring 2022/database/geckodriver-v0.30.0-win64')
url = 'https://www.premierleague.com/clubs?se=210'
driver.get(url)

time.sleep(10)  # Wait to load page

accept_cookies = driver.find_element(
    By.XPATH, '/html/body/div[1]/div/div/div[1]/div[5]/button[1]')
accept_cookies.click()
time.sleep(3)
try:
    closepopup = driver.find_element_by_css_selector('#advertClose')
    closepopup.click()
except:
    pass

i = 10

# Loop in players for each player: name, position, nationality

stadium_list = []
while i < 11:
    time.sleep(2)
    try:
        closepopup = driver.find_element_by_css_selector('#advertClose')
        closepopup.click()
    except:
        pass

    x = str(i)
    print(x)
    clubpath = "/html/body/main/div[2]/div/div/div[1]/div/ul/li[" + \
        x + "]/a/div[3]/div[3]/span"

    print(clubpath)
    stadiumname = stadium = driver.find_element_by_xpath('/html/body/main/div[2]/div/div/div[1]/div/ul/li[3]/a/div[3]/div[2]/div').text
       
    eachclub = driver.find_element(
        By.XPATH, clubpath)
    eachclub.click()

    time.sleep(4)
    try:
        closepopup = driver.find_element_by_css_selector('#advertClose')
        closepopup.click()
    except:
        pass
    name = driver.find_element_by_css_selector('h1.team').text
    stadium = driver.find_element_by_css_selector(
        '.stadium')

    stadium = driver.find_element_by_css_selector('.stadium')

    stadium.click()
    time.sleep(3)
    try:
        closepopup = driver.find_element_by_css_selector('#advertClose')
        closepopup.click()
    except:
        pass
    stadium_info = driver.find_element_by_css_selector(
        '.tablist > li:nth-child(2)')
    stadium_info.click()
    time.sleep(3)

    attr = driver.find_elements(By.TAG_NAME, 'strong')

    x = len(attr)
    check = driver.find_element_by_xpath('/html/body/main/div[3]/div[3]/div[2]/p[2]/strong').text
    if check == "Record PL attendance:":
            print(x)
            
            Capacity = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[1]')
            record = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[2]')
            Built = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[3]')
            Pitch_size = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[4]')
            address = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[5]')
            
            stad_dict = {
                "Club_Name": name,
                "Stadium_Name": stadiumname,
                "Capacity:": Capacity.text,
                "Record PL attendance:": record.text,
                "Built:": Built.text,
                "Pitch size:": Pitch_size.text,
                "Stadium address:": address.text
            }
            stadium_list.append(stad_dict)
            
    else:

            print(x)
            stadiumname = driver.find_element_by_css_selector('.stadium')
            Capacity = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[1]')
            
            record = "NULL"
            Built = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[2]')
            Pitch_size = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[3]')
            address = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div[3]/div[2]/p[4]')
            stad_dict = {
                "Club_Name": name,
                "Stadium_Name": stadiumname.text,
                "Capacity:": Capacity.text,
                "Record PL attendance:": record,
                "Built:": Built.text,
                "Pitch size:": Pitch_size.text,
                "Stadium address:": address.text
            }
            stadium_list.append(stad_dict)
    
    driver.back()
    driver.back()
    i = i+1

# Create a DataFrame and Export CSV

df = pd.DataFrame(stadium_list)
df.to_csv('stadiums3.csv', mode='a', index=False, header=False)
driver.close()
