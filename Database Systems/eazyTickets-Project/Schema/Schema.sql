create database Project

use Project

--=============================================================================================================
--											SCHEMA
--=============================================================================================================
Create Table Category
(
categoryId int primary key,
categoryName varchar(10)
)

insert into Category values
(1,'Movies'),
(2,'Events'),
(3,'Concerts')
--=============================================================================================================
Create Table[User]
(
UserID int identity(1,1) NOT NULL,
FirstName varchar(20) NOT NULL,
LastName varchar(20) NOT NULL,
Email varchar(30)  Unique NOT NULL,
MobileNo Char(11) NOT NULL,
City varchar(20),
Gender varchar (10),
[Password] varchar (32) NOT NULL,
Constraint pk_user Primary Key (UserID)
)
alter table [User]
alter column MobileNo bigint;
go

--test run
go
--declare @output int

--exec Signup 'Abdullah','Siddiqui','abdullahsiddiqui9823@gmail.com',923004567890,'Lahore','Male','abcdefgh', @output
--exec Signup 'Asad','Abrar','asad.abrar97@gmail.com',923337654321,'Lahore','Male','ijklmno', @output
--exec Signup 'Ayesha','Siddiqah','ayesha@gmail.com',923993141516,'Lahore','Female','helloworld', @output

--delete from [User]

--select * from [User]
go
--=============================================================================================================
create table [Admin]
(
adminID int primary key,

)
Alter table [Admin] add constraint fk_admin foreign key (adminID) references [User](UserID) on delete no action on update cascade

--test run
go
--insert into [Admin] values
--(5)
go
--=============================================================================================================
Create Table Concert
(
concertId int identity(1,1) Primary Key,
venue varchar(100) NOT NULL,
[DayTime] datetime NOT NULL,
performer varchar(30) NOT NULL,
organizers varchar(20) NOT NULL,
availableTickets int NOT NULL,
cost int NOT NULL
)
alter table Concert add ImageLink varchar(100) NOT NULL


--test run
go
--exec addConcert 'Lake City, Lahore','2018-8-16 10:34:09','Ali Zafar','OB(Gr-3)',47,2300,'images/ali_zafar.jpg'
--exec addConcert 'National Stadium, Karachi','2018-5-20  23:34:09','Asrar','Fun Boyz',250,500,'images/asrar.jpg'
--exec addConcert 'FAST-NU, Lahore','2018-11-3 21:34:09','Qurat-ul-Ain Baloch','Fast Music Society',200,1200,'images/QB.jpg'

go
--=============================================================================================================

Create Table Movie
(
movieId int identity(1,1),
movieName varchar(30) NOT NULL,
director varchar(20),
writer varchar(20),
runningTime Time(7) NOT NULL,
ReleaseDate Date NOT NULL,
genre varchar(20) NOT NULL,
mainCast varchar(100),
Constraint pk_Movie Primary Key (movieID)
)
alter table Movie add ImageLink varchar(100) NOT NULL

--test run
go
--insert into Movie(movieName,director,writer,runnigTime,ReleaseDate,genere,mainCast) values
--('Avengers:Infinity War','Russo Brothers','Stan Lee','02:40:00','2018-4-27','Science fiction','Josh Brolin'),
--('Deadpool','David','Stan Lee','02:00:00','2018-05-16','Fantasy/Action','Ryan Reynolds'),
--('Ant-Man And The Wasp','Peyton Reed','Stan Lee','02:00:00','2018-07-05','Science fiction','Paul Rudd')
go
--=============================================================================================================
Create Table [Event]
(
eventId int identity(1,1) Primary Key,
eventName varchar(30) NOT NULL,
eventType varchar(20) NOT NULL,
organizers varchar(20) NOT NULL,
venue varchar(100) NOT NULL,
[Day_Time] datetime NOT NULL,
ticketsAvailable int NOT NULL ,
cost int NOT NULL
)
alter table [Event] add ImageLink varchar(100) NOT NULL

--test run

--exec addEvent 'Coke Fest','Concert/Food','Coca Cola, Pakistan', 'Royal Palm, Lahore','2018-07-31 16:00:00',1000,400,'images/coke_fest.jpg'
--exec addEvent 'Lahore Eat','Food','Pepsico','Fortress Stadium, Lahore','2018-08-20 17:00:00',1000,400,'images/lahore_eat.jpg'
--exec addEvent 'Lahore Literary Fest','Literary','Faiz Club','Al-Hamra, Lahore','2018-05-10 10:00:00',1000,200,'images/lahore_literary_fest.jpg'
--select*from [Event]
--select * from [Tickets]

--=============================================================================================================
Create Table Contact
(
email varchar(30) NOT NULL,
message varchar(200),
primary key(email,message)

)
--test run
go
--insert into Contact values
--('abdullahsiddiqui9823@gmail.com','Bekaar website. Mazay ka interface nahi hai'),
--('asad.abrar97@gmail.com','Website iz gud, but u need 2 make it beautiful'),
--('danial.amir.mirza@gmail.com','Best Website Ever')
go
--=============================================================================================================
Create Table Cinema
(
CinemaId int identity(1,1) Primary Key,
Name varchar(50) NOT NULL,
[Location] varchar(100) NOT NULL,
contactNo int NOT NULL
)
--test run
--go
--insert into Cinema(Name,Location,contactNo) values
--('Angoori Cinema','Angoori Bagh, Lahore',123456789),
--('Universal Cinema','Emporium Mall,Lahore',1234),
--('Imperial Cinema','Barki Road, Lahore',987654321),
--('PAF Cinema','Sarfaraz Rafiqui Road, Lahore',9876523)
--go
--=============================================================================================================
Create Table Showtime
(
showId int identity(1,1) Primary Key,
movieId int foreign key references Movie on delete cascade on update cascade NOT NULL,
cinemaId int foreign key references Cinema on delete cascade on update cascade NOT NULL,
date_time datetime NOT NULL,
availableSeats int not null,
cost int not null,
ScreeningType char(2) NOT NULL,
)

--test run
go
--insert into Showtime(movieId,cinemaId,date_time,availableSeats,cost,ScreeningType) values
--(1,1,'2018-04-27 14:00:00',500,200,'3D'),
--(1,2,'2018-04-28 14:00:00',500,400,'2D'),
--(1,3,'2018-04-29 17:00:00',500,400,'2D'),
--(2,1,'2018-05-16 17:00:00',500,800,'3D'),
--(3,2,'2018-07-20 14:00:00',500,200,'2D')
go
--=============================================================================================================
Create Table Tickets(
ticketId int identity(1,1) ,
categoryId int NOT NULL,
ID int NOT NULL,
Primary Key(ticketId)
)
Alter table Tickets add Constraint fk_C Foreign Key(categoryId) References Category(categoryId) on delete cascade on update cascade;

--Alter table Tickets add Constraint fk_TM Foreign Key(movieId) References ShowTime(showId) on delete cascade on update cascade;
--Alter table Tickets add Constraint fk_TE Foreign Key(eventId) References [Event](eventID) on delete cascade on update cascade;
--Alter table Tickets add Constraint fk_TC Foreign Key(concertId) References Concert on delete cascade on update cascade;

--test run
go
--insert into Tickets(categoryId,movieId,eventId,concertId) values
--(1,1,NULL,NULL),
--(1,1,null,null),
--(2,null,3,null),
--(3,null,null,1)
go
--=============================================================================================================
Create Table [Orders]
(
orderId int primary key,
user_id int foreign key references  [User]([UserID]) on delete no action on update no action
)
--=============================================================================================================
Create Table Order_Details
(
order_Id int foreign key references [Orders] on delete cascade on update cascade,
ticketId int foreign key references Tickets on delete no action on update cascade,
amount int,
Primary Key(order_Id,ticketId)
)
--=============================================================================================================
Create Table [RatingReview]
(
userID int  foreign key references [User]([UserID]) on delete no action on update cascade,
ticket_id int foreign key references [Tickets] on delete cascade on update cascade,
rating int Not Null,
review varchar(100),
primary key(userID,ticket_id)
)

--test run
go
--insert into RatingReview values
--(1,1,5,'Best movie ever. Thanos is awsome.'),
--(2,2,5,Null),
--(3,3,3,'Bht mazay ka event tha.'),
--(1,4,2,'Bekaar Managment singer late aya.')
go
--=============================================================================================================
Create Table [Cart]
(
orderId int identity(1,1) primary key,
user_id int foreign key references  [User]([UserID]) on delete no action on update no action
)
--=============================================================================================================
Create Table Cart_Details
(
order_Id int foreign key references [Cart](orderId) on delete cascade on update cascade,
ticketId int foreign key references Tickets on delete no action on update cascade,
amount int,
Primary Key(order_Id,ticketId)
)