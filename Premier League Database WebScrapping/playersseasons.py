import time
import pandas as pd
from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.common.by import By
from selenium.webdriver.firefox.service import Service

# Open browser
s = Service(
    'C:/Users/omar-/Desktop/Spring 2022/database/geckodriver-v0.30.0-win64')
driver = webdriver.Firefox(
    'C:/Users/omar-/Desktop/Spring 2022/database/geckodriver-v0.30.0-win64')
url = 'https://www.premierleague.com/players?se=210&cl=-1'
driver.get(url)

# Accept on Cookies
time.sleep(3)  # Wait to load page

accept_cookies = driver.find_element(
    By.XPATH, '/html/body/div[1]/div/div/div[1]/div[5]/button[1]')
accept_cookies.click()
time.sleep(4)
i = 2
while i < 22:
    x= str(i)
    filter = driver.find_element_by_xpath(
         '/html/body/main/div[2]/div[1]/div/section/div[2]/div[2]')
    filter.click()
    team = driver.find_element_by_xpath(
        "/html/body/main/div[2]/div[1]/div/section/div[2]/ul/li[" + x+"]")
        
    team.click()
    team = driver.find_element_by_xpath(
        '/html/body/main/div[2]/div/div/section/div[2]/div[2]').text
# Scroll down
    current_height = driver.execute_script("return document.body.scrollHeight")
    while True:
        driver.execute_script(
            "window.scrollTo(0, document.body.scrollHeight);") 	# Scroll step
        time.sleep(3) 	# Wait to load page
        try:
            new_height = driver.execute_script(
                "return document.body.scrollHeight")  # Calculate new scroll height
        except:
            print("Failed: ", new_height)
        if new_height == current_height:  # Compare with last scroll height
            break
        current_height = new_height

    print("scorlled till", current_height)

# Get all players
    players = driver.find_elements(
        By.XPATH, '//*[@id="mainContent"]/div[2]/div[1]/div/div/table/tbody/tr')
    print("Number of Players", len(players))

    player_list = []
# Loop in players for each player: name, position, nationality
    for player in players:
        attr = player.find_elements(By.TAG_NAME, 'td')
        [name, position, country] = attr  # Object Destruction
        player_dict = {
            "name": name.text,
            "club": team,
            "position": position.text,
            "country": country.text
        }
        player_list.append(player_dict)
        df = pd.DataFrame(player_list)
    i = i+1
    df.to_csv('Playersseason4.csv', mode='a', index=False, header=False)



# Create a DataFrame and Export CSV


driver.close()
