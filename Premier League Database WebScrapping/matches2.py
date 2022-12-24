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
url = 'https://www.premierleague.com/clubs'
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
i = 6

# Loop in players for each player: name, position, nationality
matches_list = []

while i < 7:
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
    y = 3
    season = driver.find_element_by_css_selector('div.dropDown:nth-child(4) > div:nth-child(2)').text 
    while y < 33:
       
        z= str(y)
        
        try:
            matchpath = "/html/body/main/div[4]/div/div[1]/div[2]/section/div[" + z +"]/ul/li/div/span"
            
        
            eachmatch = driver.find_element(
                By.XPATH, matchpath)
            eachmatch.click()
    
            time.sleep(3)

            time.sleep(3)
            try:
                closepopup = driver.find_element_by_css_selector('#advertClose')
                closepopup.click()
            except:
                pass 
            ht = driver.find_element_by_css_selector('div.team:nth-child(1) > a:nth-child(2) > span:nth-child(1)').text
            at= driver.find_element_by_css_selector(
                '.teamsContainer > div:nth-child(3) > a:nth-child(2) > span:nth-child(1)').text
        
            date = driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/section/div[1]/div/div[1]/div[1]').text
            result = driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/section/div[3]/div/div/div[1]/div[2]/div/div').text
            stats = driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[1]/div/div/ul/li[3]')
            stats.click()
            time.sleep(3)
            try:
                check = driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[12]/td[2]')
            
            except: 
                check= "NULL"
            if check == "NULL":
                pht =driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[1]/td[1]/p').text
                pat =driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[1]/td[3]/p').text
                yellow_cardht= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[10]/td[1]/p').text
                yellow_cardat= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[10]/td[3]/p').text
            
                
                goalsht = result[ :1]
                goalsat = result[2: ]
               
                shotsht=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[3]/td[1]/p').text
                shotsat=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[3]/td[3]/p').text
                fouls_at=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[3]/p').text
                fouls_ht=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[1]/p').text
                stadium= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/section/div[1]/div/div[1]/div[3]').text
                red_cardat="NULL"
                red_cardht="NULL"
                
                match_dict = {
                    "Season": season,
                    "Date":date,
                    "Result":result,
                    "Goals_Home_Team":goalsht,
                    "Goals_away_Team":goalsat,
                    "Home_Team":ht, 
                    "Away_Team":at,
                    "Possession_home_team":pht,
                    "Possession_away_team":pat,
                    "Yellow_Card_Home_Team":yellow_cardht,
                    "Yellow_Card_Away_Team":yellow_cardat,
                    "Red_Card_Home_Team":red_cardht,
                    "Red_Card_Away_Team":red_cardat,
                    "Shots_Home_Team":shotsht,
                    "Shots_away_Team":shotsat,
                    "Fouls_Home_Team":fouls_ht,
                    "Fouls_Away_Team":fouls_at,
                    "Stadium":stadium
                }
            else:
                pht =driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[1]/td[1]/p').text
                pat =driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[1]/td[3]/p').text
                yellow_cardht= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[10]/td[1]/p').text
                yellow_cardat= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[10]/td[3]/p').text
            
                goalsht = result[ :1]
                goalsat = result[2: ]
                shotsht=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[3]/td[1]/p').text
                shotsat=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[3]/p').text
                fouls_at=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[3]/p').text
                fouls_ht=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[1]/p').text
                stadium= driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/section/div[1]/div/div[1]/div[3]').text
                red_cardht=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[1]/p').text
                red_cardat=driver.find_element_by_xpath('/html/body/main/div/section[2]/div[2]/div[2]/div[2]/section[3]/div[2]/div[2]/table/tbody/tr[11]/td[3]/p').text
                
                
                match_dict = {
                    "Season": season,
                    "Date":date,
                    "Result":result,
                    "Goals_Home_Team":goalsht,
                    "Goals_away_Team":goalsat,
                    "Home_Team":ht, 
                    "Away_Team":at,
                    "Possession_home_team":pht,
                    "Possession_away_team":pat,
                    "Yellow_Card_Home_Team":yellow_cardht,
                    "Yellow_Card_Away_Team":yellow_cardat,
                    "Red_Card_Home_Team":red_cardht,
                    "Red_Card_Away_Team":red_cardat,
                    "Shots_Home_Team":shotsht,
                    "Shots_away_Team":shotsat,
                    "Fouls_Home_Team":fouls_ht,
                    "Fouls_Away_Team":fouls_at,
                    "Stadium":stadium
                }

        except:
            pass
        match_list.append(match_dict)
        df = pd.DataFrame(match_list)
        y = y+1
        driver.back()
        time.sleep(5)
    i=i+1
       
   
    df.to_csv('matches.csv', mode='a', index=False, header=False)
    
       
    driver.back()

# Create a DataFrame and Export CSV


driver.close()


