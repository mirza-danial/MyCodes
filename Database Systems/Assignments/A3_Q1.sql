CREATE DATABASE L164204_Q1

Use L164204_Q1


CREATE TABLE Developer(
developer_id integer CHECK(developer_id>0 AND developer_id<10000),
developer_name varchar(25),
age integer CHECK(age>0 AND age<100),
country varchar(20),
CONSTRAINT pk_developer PRIMARY KEY(developer_id)
);

CREATE TABLE Users(
user_id varchar(30),
user_name varchar(30),
country varchar(20),
CONSTRAINT pk_user PRIMARY KEY(user_id)
);

CREATE TABLE App(
app_id integer  CHECK(app_id>0),
app_name varchar(20),
developer_id integer CHECK(developer_id>0 AND developer_id<10000) , 
cost integer CHECK(cost>=0),
category varchar(20),
CONSTRAINT pk_app PRIMARY KEY(app_id),
CONSTRAINT fk_app FOREIGN KEY (developer_id) REFERENCES Developer(developer_id) ON DELETE CASCADE ON UPDATE CASCADE 
);

CREATE TABLE Downloads(
app_id integer  CHECK(app_id>0)  ,
user_id varchar(30),
rating integer CHECK(rating>=1 AND rating<=5),
review varchar(200),
CONSTRAINT fk_download1 FOREIGN KEY (app_id) REFERENCES APP(app_id) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT fk_download2 FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE ON UPDATE CASCADE,
CONSTRAINT pk_downloads PRIMARY KEY(app_id,user_id),

); 

--1
SELECT developer_name
FROM Developer
WHERE age<18 AND country='Pakistan'

--2
SELECT app_name
FROM App join Developer on App.developer_id=Developer.developer_id
WHERE developer_name='Ali-Shah'

--3
SELECT user_id
FROM (APP join Downloads on App.app_id=Downloads.app_id) join Developer on Developer.developer_id=App.developer_id
Where category='Kids' AND Developer.country='Pakistan'

--4
SELECT user_name,Users.user_id
FROM (Downloads join App on Downloads.app_id=App.app_id) join Users on Users.user_id=Downloads.user_id
WHERE category='Productivity'

Intersect

SELECT user_name,Users.user_id
FROM (Downloads join App on Downloads.app_id=App.app_id) join Users on Users.user_id=Downloads.user_id
WHERE category='Entertainment'

--5
SELECT user_id
From Downloads join App on App.app_id=Downloads.app_id
WHERE  app_name='The Zone'

UNION

SELECT user_id
From Downloads join App on App.app_id=Downloads.app_id
WHERE  app_name='The Fighter'

--6
SELECT DISTINCT user_id
FROM (Downloads JOIN App on App.app_id=Downloads.app_id) JOIN Developer on App.developer_id=Developer.developer_id
WHERE  developer_name='Ahmed'

--7
SELECT DISTINCT user_id
FROM Downloads U
WHERE NOT EXISTS(
				SELECT DISTINCT app_id
				FROM App JOIN Developer ON APP.developer_id=Developer.developer_id
				WHERE developer_name='Ali-Shah' 	
				
				EXCEPT

				SELECT DISTINCT App.app_id
				FROM (Downloads D JOIN App ON D.app_id=App.app_id) JOIN Developer ON App.developer_id=Developer.developer_id 
				WHERE U.user_id=D.user_id AND developer_name='Ali-Shah'
				)

--8
SELECT app_id
FROM Downloads
GROUP BY app_id
HAVING COUNT(user_id)>1

--9
SELECT DISTINCT app_id
FROM Downloads
WHERE rating IN (
				SELECT MAX(rating)
				FROM Downloads
				)

--10
SELECT DISTINCT app_name
FROM App 
WHERE cost IN (
				SELECT MAX(cost)
				FROM App
				)

--11
SELECT DISTINCT app_name
FROM App JOIN Developer ON Developer.developer_id=App.developer_id
WHERE developer_name='Reeta' AND cost IN (
										SELECT MAX(cost)
										FROM App
										)
--12
SELECT app_id,app_name,Developer.developer_name
FROM App JOIN Developer ON App.developer_id=Developer.developer_id
WHERE cost=0

--13
SELECT App.app_id
FROM App JOIN Downloads ON App.app_id=Downloads.app_id
WHERE cost=0
GROUP BY App.app_id
HAVING AVG(rating)>3

--14
SELECT Developer.developer_id,COUNT(app_id) NoOfAppMade
FROM App JOIN Developer ON App.developer_id=Developer.developer_id
GROUP BY Developer.developer_id

--15
SELECT App.developer_id,SUM(cost) IncomeEarned
FROM App JOIN Developer ON App.developer_id=Developer.developer_id
GROUP BY App.developer_id

--16
SELECT country,SUM(cost) IncomeEarned
FROM App JOIN Developer ON App.developer_id=Developer.developer_id
GROUP BY country

--17
SELECT category, A.app_id , A.app_name
FROM App as A
WHERE EXISTS(
			SELECT B.category,MAX(B.cost)
			FROM App as B
			WHERE A.category=B.category
			GROUP BY B.category
			HAVING A.cost=MAX(B.cost)
			)

--18
SELECT Developer.developer_id,Developer.developer_name,COUNT(App.app_id) [No. Of Apps]
FROM Developer LEFT OUTER JOIN App ON App.developer_id=Developer.developer_id
GROUP BY Developer.developer_id,Developer.developer_name


--19
SELECT D.developer_id,D.developer_name
FROM Developer D
WHERE EXISTS (
				SELECT I.developer_id,COUNT(app_id) 
				FROM App JOIN Developer as I ON App.developer_id=I.developer_id
				WHERE category='games' AND D.developer_id=I.developer_id
				GROUP BY I.developer_id
				HAVING	COUNT(app_id)=3
				)

--20
SELECT Developer.developer_name,App.app_name
FROM Developer left outer join App ON App.developer_id=Developer.developer_id


