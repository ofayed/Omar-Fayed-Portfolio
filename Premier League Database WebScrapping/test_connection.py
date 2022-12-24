import mysql.connector

mydb = mysql.connector.connect(
    host="127.0.0.1" ,
    user="root" ,
    password="Omarfayed1-2-3" ,
    database="milestone3"
)
# print(mydb)
mycursor = mydb.cursor()

print("""
Welcome to the Barclays Premier League application
select the action you want to take
1. Register for a new user
2. Add/view user review
3. Retrieve data


""")

inp = int(input("Select operation needed: "))

if inp == 1:
    email = str(input("Enter email address: "))
    user = str(input("Enter username: "))
    age = int(input("Enter age: "))
    gender = str(input("Enter gender(male\female): "))
    birthdate = str(input("Enter birthdate(YYYY/MM/DD): "))
    fav = str(input("Enter favourite team: "))
    val = (email,user,age,birthdate,fav,gender)
    mycursor.execute(' INSERT INTO fans (Email,Username,Age,Birthdate,`Favorite team`, Gender) VALUES (%s,%s,%s,%s,%s,%s)',val)
    mydb.commit()
elif inp == 2:
    inp2= int(input("""Do you want to
     1. Add review
     2. View review
    """))
    if inp2 == 1:
        home_team = str(input("Enter home team: "))
        away_team = str(input("Enter away team: "))
        season =str(input("Enter season (Ex. 2021/2022): "))
        textual = str(input("Write your full review below: "))
        rate = int(input("Enter your rating for the match: "))
        val = (home_team,away_team,season,textual,rate)
        mycursor.execute(' INSERT INTO review (`Home team`,`Away team`,Season,Textual,Rating) VALUES (%s,%s,%s,%s,%s)',val)
        mydb.commit()
    else:
        home_team = str(input("Enter home team: "))
        away_team = str(input("Enter away team: "))
        season =str(input("Enter season (Ex. 2021/2022): "))
        val = (home_team,away_team,season)
        mycursor.execute('SELECT * FROM `review` WHERE `Home team` = %s AND `Away team` = %s  AND `Season` = %s' ,val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
elif inp == 3:
    inp2= int(input("""Do you want to
        1. Get information of a club
		2. Get information of a player
		3. Get the home team of a stadium
		4. List all the players in a certain position 
		5. Get all clubs from a certain region in UK
		6. Get clubs that won the most matches in the last 4 seasons
		7. Get the top 10 teams by matches won, home matches won, yellow cards, fouls, and shots
		8. Choose a certain nationality and get all the players and their home teams history 
    
    """))
    if inp2 ==1:
        club = str(input("Enter club name: "))
        val = (club,); 
        mycursor.execute('SELECT * FROM clubs WHERE Name = %s',val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
    elif inp2 == 2:
        player = (input("Enter player name: "))
     
        val = (player,)
        mycursor.execute('SELECT * FROM `players` WHERE `Name` = %s',val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
    elif inp2 == 3:
        stadium = str(input("Enter stadium name: "))
        val = (stadium,)
        mycursor.execute('SELECT `Club Name` FROM `stadiums` WHERE `Stadium Name` = %s',val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
    elif inp2 == 4:
        pos = str(input("Enter Position: "))
        val = (pos,)
        mycursor.execute('SELECT `Name` FROM `players` WHERE `Position` = %s',val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
    elif inp2 == 5:
        region = str(input("Enter region: "))
        val = (region,); 
        mycursor.execute('SELECT Name FROM clubs WHERE Region = %s',val)
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1
    elif inp2 == 7:
        #max shots ( I found that the top 10 shots are for home teams)
        print('Most 10 teams with shots in a match')
        mycursor.execute('SELECT `Home team`,`Shots for home team`  FROM matches Order by  `Shots for home team` DESC LIMIT 10')
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1


    elif inp2 == 8:
        stadium = str(input("Enter Nationality: "))
  
        i = 1
        result = mycursor.fetchall()
        for r in result:
            print(i,r)
            i = i + 1

