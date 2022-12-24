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
url = 'https://www.premierleague.com/clubs?se=363'
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
i = 1

# Loop in players for each player: name, position, nationality
matches_list = []

while i < 21:
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


    results = driver.find_element_by_xpath('/html/body/main/nav/ul/li[4]/a')
    results.click()
    matches = driver.find_elements_by_class_name('overview')
    print("Number of Players", len(matches_list))
    time.sleep(3)
    match_list = []
    m= 1
    a = 2
    y = 1
    season = driver.find_element_by_css_selector('div.dropDown:nth-child(4) > div:nth-child(2)').text 
    
    time.sleep(3)
    try:
        closepopup = driver.find_element_by_css_selector('#advertClose')
        closepopup.click()
    except:
        pass
    filter = driver.find_element_by_css_selector('div.dropDown:nth-child(4) > div:nth-child(2)')
    filter.click()
    time.sleep(6)
    filter2 = driver.find_element_by_css_selector('div.dropDown:nth-child(4) > ul:nth-child(3) > li:nth-child(2)')
    filter2.click()
    time.sleep(4)
    while y<39: 
        l = str(m)
        z= str(y)
        b = str(a)
        ht = driver.find_element_by_xpath("/html/body/main/div[4]/div/div[1]/div[2]/section/div["+z+"]/ul/li/div/span/span[1]/span[1]/span[1]/span[1]").text

        at= driver.find_element_by_xpath(
        "/html/body/main/div[4]/div/div[1]/div[2]/section/div[" + z +"]/ul/li/div/span/span[1]/span[3]/span[2]/span[1]").text
        
        date = driver.find_element_by_xpath("/html/body/main/div[4]/div/div[1]/div[2]/section/time[" + l+ "]/strong").text
        result = driver.find_element_by_xpath("/html/body/main/div[4]/div/div[1]/div[2]/section/div[" + z+ "]/ul/li/div/span/span[1]/span[2]").text

        stadium= driver.find_element_by_xpath("html/body/main/div[4]/div/div[1]/div[2]/section/div[" + z + "]/ul/li/div/span/span[2]").text
    
        goalsht = result[ :1]
        goalsat = result[2: ]
        time.sleep(3)
        match_dict = {
            "Season": season,
            "Date":date,
            "Result":result,
            "Goals_Home_Team":goalsht,
            "Goals_away_Team":goalsat,
            "Home_Team":ht, 
            "Away_Team":at,
            "Stadium":stadium
            }
        
        match_list.append(match_dict)
        df = pd.DataFrame(match_list)
        y = y+1
        m = m+2
        a=a+1
        time.sleep(5)
    df.to_csv('matchesseasons.csv', mode='a', index=False, header=False)
    i=i+1
    driver.back()
    driver.back()
    driver.back()
    

# Create a DataFrame and Export CSV


driver.close()


