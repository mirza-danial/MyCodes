

CREATE DATABASE L164204_Q2

USE L164204_Q2


CREATE TABLE Team(
TeamNum integer CHECK(TeamNum>0),
TeamName varchar(25),
City varchar(25),
Manager varchar(25),
CONSTRAINT pk_Team PRIMARY KEY(TeamNum)
);

CREATE TABLE Coach(
TeamNum integer CHECK (TeamNum>0),
CoachName varchar(25),
Address varchar(200),
CONSTRAINT pk_Coach PRIMARY KEY(TeamNum,CoachName),
CONSTRAINT fk_Coach FOREIGN KEY(TeamNum) REFERENCES Team
);

CREATE TABLE WorkExperience(
TeamNum integer CHECK (TeamNum>0),
CoachName varchar(25),
ExperienceType varchar(25), 
YearsExperience integer CHECK (YearsExperience>0 AND YearsExperience<100),
CONSTRAINT pk_WE PRIMARY KEY(TeamNum,CoachName,ExperienceType),
CONSTRAINT fk_WE FOREIGN KEY (TeamNum,CoachName) REFERENCES Coach ON DELETE CASCADE ON UPDATE CASCADE 
);

CREATE TABLE Players(
PlayerNum integer CHECK(PlayerNum>=0) ,
PlayerName varchar(25),
Age integer CHECK(Age>0),
CONSTRAINT pk_Players PRIMARY KEY(PlayerNum),
); 
CREATE TABLE Affliation(
PlayerNum integer CHECK(PlayerNum>=0),
TeamNum integer CHECK(TeamNum>0),
Years integer CHECK(Years>0 AND Years<100),
BattingAvg float,
CONSTRAINT fk_Aff1 FOREIGN KEY (PlayerNum) REFERENCES Players ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT fk_Aff2 FOREIGN KEY (TeamNum) REFERENCES Team ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT pk_Aff PRIMARY KEY(PlayerNum,TeamNum),

); 

--1
SELECT PlayerName
FROM Players
WHERE age<18

--2
SELECT CoachName
FROM WorkExperience
WHERE ExperienceType='college' AND YearsExperience BETWEEN 5 AND 10

--3
SELECT CoachName,SUM(YearsExperience) Years
FROM WorkExperience
WHERE TeamNum=23
GROUP BY CoachName

--4
SELECT P.PlayerName
FROM (Players P JOIN Affliation A ON  P.PlayerNum=A.PlayerNum) JOIN Team T ON A.TeamNum=T.TeamNum
WHERE A.Years>=5 AND TeamName='Dodgers'

--5
SELECT CoachName,SUM(YearsExperience) TotalEXP
FROM WorkExperience W JOIN Team T ON W.TeamNum=T.TeamNum
WHERE TeamName='Dodgers' 
Group BY CoachName
HAVING SUM(YearsExperience)>8

--6
SELECT PlayerName
FROM Players
WHERE age in(
			SELECT MIN(age)
			FROM Players
			)
--7
SELECT  P.PlayerNum,P.PlayerName,COUNT(TeamNum) [No. Of Teams]
FROM Players P Join Affliation ON P.PlayerNum=Affliation.PlayerNum
GROUP BY P.PlayerNum,P.PlayerName
HAVING COUNT(TeamNUM)>2

--8
SELECT P.PlayerNum,P.PlayerName
FROM Players P

EXCEPT

SELECT Q.PlayerNum,Q.PlayerName
FROM Players Q JOIN Affliation ON Q.PlayerNum=Affliation.PlayerNum

--9
SELECT  P.PlayerNum,P.PlayerName,COUNT(TeamNum) [No. Of Teams]
FROM Players P LEFT Join Affliation ON P.PlayerNum=Affliation.PlayerNum
GROUP BY P.PlayerNum,P.PlayerName

--10
SELECT A.TeamNum , AVG(A.BattingAvg) [Average Batting Avg.]
FROM Affliation A
GROUP BY A.TeamNum