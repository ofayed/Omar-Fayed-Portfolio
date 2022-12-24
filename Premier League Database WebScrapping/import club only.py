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

time.sleep(15)  # Wait to load page

accept_cookies = driver.find_element(
    By.XPATH, '/html/body/div[1]/div/div/div[1]/div[5]/button[1]')
accept_cookies.click()
time.sleep(3)
try:
    closepopup = driver.find_element_by_css_selector('#advertClose')
    closepopup.click()
except:
    pass
clubs = driver.find_elements_by_class_name('clubName')
numofclubs = len(clubs)
i = 5

# Loop in players for each player: name, position, nationality
club_list = []
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
    eachclub = driver.find_element(
        By.XPATH, clubpath)
    eachclub.click()

    time.sleep(3)

    time.sleep(3)
    try:
        closepopup = driver.find_element_by_css_selector('#advertClose')
        closepopup.click()
    except:
        pass
    name = driver.find_element_by_css_selector('h1.team').text
    stadium_name = driver.find_element_by_css_selector(
        '.stadium').text
    website = driver.find_element_by_css_selector(
        '.website > a:nth-child(2)').text
    club_dict = {
        "Club name": name,
        
        "website": website,
        "stadium": stadium_name

    }
    club_list.append(club_dict)
    i = i+1
    df1 = pd.DataFrame(club_list)
    
    df1.to_csv('clubs2.csv', mode='a', index=False, header=False)
    driver.back()
    driver.back()

# Create a DataFrame and Export CSV


driver.close()
