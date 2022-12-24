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
i = 3

# Loop in players for each player: name, position, nationality
club_list = []
stadium_list = []
while i < 4:
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

    squad = driver.find_element_by_xpath('/html/body/main/nav/ul/li[2]/a')
    squad.click()
    players = driver.find_elements_by_class_name('squadPlayerHeader')
    print("Number of Players", len(players))
    time.sleep(3)
    squadlist = []
    y =1
    for player in players:
       
        z= str(y)
        eachplayer = driver.find_element_by_xpath(
            "/html/body/main/div[3]/div/ul/li[" + z + "]/a/span[1]")
        eachplayer.click()
        time.sleep(4)
        try:
            position = driver.find_element_by_xpath(
                '/html/body/main/div[3]/nav/div/section[1]/div[4]').text
        except:
            position = driver.find_element_by_xpath(
                '/html/body/main/div[3]/nav/div/section[1]/div[2]').text
        try:
            country = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div/div/div[1]/section/div/ul[1]/li/div[2]').text
        except: 
            country= 'NULL'
        try:
            bd = driver.find_element_by_css_selector(
                '.pdcol2 > li:nth-child(1) > div:nth-child(2)').text
        except:
            bd = 'NULL'
        try:
            ht = driver.find_element_by_css_selector(
                'div.playerOverviewAside:nth-child(1) > section:nth-child(1) > div:nth-child(2) > a:nth-child(1)').text
        except:
            ht = 'Null'

        try:
            height = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div/div/div[1]/section/div/ul[3]/li[1]/div[2]').text
        except:
            height = 'Null'
        try:
            season1 = driver.find_element_by_xpath(
             '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[1]/td[1]/p').text

            club1 = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[1]/td[2]/a/span[2]').text
               

        except:
            season1 = '2021/2022'
            club1 = 'NULL'

        try:
            season2 = driver.find_element_by_xpath(
            '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[5]/td[1]/p').text
            club2 = driver.find_element_by_xpath(
            '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[5]/td[2]/a/span[2]').text
        except:
            season2 = '2020/2021'
            club2 = 'NULL'
        try:
            season3 = driver.find_element_by_xpath(
                '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[10]/td[1]/p').text
            club3 = driver.find_element_by_xpath(
            '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[10]/td[2]/a/span[2]').text
        except:
            season3 = '2019/2020'
            club3 = 'NULL'
        try:
            season4 = driver.find_element_by_xpath(
             '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[17]/td[1]/p').text
            club4 = driver.find_element_by_xpath(
             '/html/body/main/div[3]/div/div/div[3]/table/tbody/tr[17]/td[2]/a/span[2]').text
        except:
            season4 = '2018/2019'
            club4 = 'NULL'
        try: 
            playername = driver.find_element_by_xpath(
            '/html/body/main/section/div[2]/div[2]/h1/div').text
        except:
            
            playername= driver.find_element_by_css_selector('div.name').text
        player_dict = {
            "Club name": name,
            "name": playername,
            "position": position,
            "country": country,
            "birth_date": bd,
            "height": height,
            "First season": season1,
            "Home_team_S1": club1,
            "Second season": season2,
            "Home_team_S2": club2,
            "Third season": season3,
            "Home_team_S3": club3,
            "Fouth season": season4,
            "Home_team_S4": club4,
        }
        squadlist.append(player_dict)
        y=y+1
        driver.back()
        time.sleep(3)
    club_list.append(club_dict)
    i = i+1
    df1 = pd.DataFrame(club_list)
    df2 = pd.DataFrame(squadlist)
    df1.to_csv('clubs2.csv', mode='a', index=False, header=False)
    df2.to_csv('squadlist2.csv', mode='a', index=False, header=False)
    driver.back()
    driver.back()

# Create a DataFrame and Export CSV


driver.close()
