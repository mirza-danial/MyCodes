Use Project

--=============================================================================================================
--										ADMIN Procedures
--=============================================================================================================

--===========
--	ADMIN
--===========
GO
create procedure AddAdmin
@id int, @output int output
as 
begin
	set @output=0
	select UserID from [User] where UserID=@id
	if @@ROWCOUNT=0
	begin
		set @output=1
	end
	else if exists(select adminID from Admin where adminID=@id)
	begin
		set @output=2
	end
	else
		insert into [Admin] values(@id);
end 

--test run
go
--exec AddAdmin 'waqarzaqa@lhr.nu.edu.pk','iamkewl','waqar','zaqa','sargodha','1231231','male'
go

--drop procedure AddAdmin

GO
create PROCEDURE [UpdateAdminInfo]
@id int,
@NewFName varchar(20),
@NewLName varchar(20),
@NewCity varchar(20),
@NewPhone int,
@NewPassword varchar(30)
as
begin
	Update [User]
	Set [FirstName]=@NewFName,[LastName]=@NewLName,City=@NewCity,[Password]=@NewPassword,MobileNo=@NewPhone
	where UserID=@id
end
go

--test run
go
--exec UpdateAdminInfo 5,'Ahman','Bajwa','Kakul','3221122','pakistan'
go


--===========
--	CINEMA
--===========
--drop procedure addCinema

GO
create procedure addCinema
@Name varchar(50),
@location varchar(100),
@ContactNo int,
@output int output
as
begin
	set @output=0

	--checking for duplication
	if @Name in (select Name from Cinema)
	begin
		if @location in (select Location from Cinema where Name=@Name)
		begin
			set @output=1
		end
	end

	----checking if number is out of bounds
	--if @ContactNo < 1111111111 OR @ContactNo > 9999999999
	--begin
	--	set @output=2
	--end

	else
	begin
		insert into Cinema(Name,Location,contactNo) values
		(@Name,@location,@ContactNo)
	end
end
go

create procedure deleteCinema
@Id int
as
begin
	delete from Cinema where CinemaId=@Id
end
go

--test run
go
--exec addCinema 'CineStar','Township, Lahore',1111456789
go

--===========
--	CONCERT
--===========
GO
create procedure addConcert
@venue varchar(100),@DayTime datetime,@performer varchar(30),@organizer varchar(20),@seats int,@cost int, @ImageLink varchar(100), @output int output
as
begin
	set @output=0

	--checking for duplication
	if @venue in (select venue from Concert)
	begin
		if @DayTime in (select [DayTime] from Concert where venue=@venue)
		begin
			if @performer in (select performer from Concert where venue=@venue AND [DayTime]=@DayTime)
			begin
				if @organizer in (select organizers from Concert where performer=@performer AND venue=@venue AND [DayTime]=@DayTime)
				begin
					if @seats in (select availableTickets from Concert where organizers=@organizer AND performer=@performer AND venue=@venue AND [DayTime]=@DayTime)
					begin
						if @cost in (select cost from Concert where cost=@cost AND organizers=@organizer AND performer=@performer AND venue=@venue AND [DayTime]=@DayTime)
						begin
							set @output=1
						end
					end
				end
			end
		end
	end

	----checking if number of available tickets is out of bounds
	--if @seats < 0
	--begin
	--	print 'Number of available tickets cannot be less than 0.'
	--	return
	--end

	----checking if cost is out of bounds
	--if @cost < 0 
	--begin
	--	print 'Invalid cost specified.'
	--	return
	--end

	else
	begin
		declare @concertid int;
		insert into Concert (venue , [DayTime] , performer , organizers , availableTickets , cost , ImageLink) values (@venue, @DayTime, @performer, @organizer, @seats, @cost, @ImageLink)
		
		select @concertid=concertId from Concert where venue=@venue AND [DayTime]=@DayTime AND performer=@performer AND @organizer=organizers AND availableTickets=@seats AND cost=@cost

		insert into Tickets(categoryId, Id) values
		(3, @concertId)

		print 'Concert has been added into the list.'
	end
end

--test run
go
--exec addConcert 'Royal Palm,Lahore','2018-6-10 22:00:00','Ed Sheeran','Mad Decent Party',800,3000

--drop procedure addConcert
go

create procedure updateConcert
@CconcertId int,
@Cvenue varchar(100),
@CDayTime datetime,
@Cperformer varchar(30),
@Corganizers varchar(20),
@CavailableTickets int,
@Ccost int,
@ImageLink varchar(100)
as
begin
	--checking in Concert id is out of bounds
	if @CconcertId < 0
	begin
		print 'Invalid Concert id enterded.'
	end

	--checking if number of available tickets is out of bounds
	if @CavailableTickets < 0
	begin
		print 'Number of available tickets cannot be less than 0.'
	end

	--checking if cost is out of bounds
	if @Ccost < 0 OR @Ccost>1000
	begin
		print 'Invalid cost specified.'
	end

	else
	begin
		update Concert
		set venue=@Cvenue, [DayTime]=@CDayTime, performer=@Cperformer, organizers=@Corganizers, availableTickets=@CavailableTickets, cost=@Ccost, ImageLink=@ImageLink
		where concertId=@CconcertId
	end
end
go

GO
create procedure removeConcert
@ConcertId int, @output int output
as
begin
	set @output=0
	select concertId from [Concert] where concertId=@ConcertId

	if @@ROWCOUNT=0
		set @output=1

	else
	delete from Concert
	where concertId=@ConcertId
end

--test run
go
--exec removeConcert 4

--drop procedure removeConcert
go

--select * from Concert

--===========
--	EVENT
--===========

GO
create procedure addEvent
@Name varchar(30),@type varchar(20),@organizer varchar(20),@venue varchar(100),@day_time datetime,@tickets int,@cost int, @ImageLink varchar(100), @output int output
as
begin
	set @output=0

	--checking for duplication
	if @Name in (select eventName from [Event])
		begin
			if @type in (select eventType from [Event] where eventName=@Name)
			begin
				if @organizer in (select organizers from [Event] where eventType=@type AND eventName=@Name)
				begin
					if @venue in (select venue from [Event] where organizers=@organizer AND eventType=@type AND eventName=@Name)
					begin
						if @day_time in (select [Day_Time] from [Event] where venue=@venue AND organizers=@organizer AND eventType=@type AND eventName=@Name)
						begin
								if @tickets in (select ticketsAvailable from [Event] where [Day_Time]=@day_time AND venue=@venue AND organizers=@organizer AND eventType=@type AND eventName=@Name)
								begin
									if @cost in (select cost from [Event] where ticketsAvailable=@tickets AND [Day_Time]=@day_time  AND venue=@venue AND organizers=@organizer AND eventType=@type AND eventName=@Name)
									begin
										set @output=1
									end
								end
							
						end
					end
				end
			end
		end
	

	--checking if day has already passed
	if @day_time < (SELECT CAST(GETDATE() AS DATE))
	begin
		set @output=2
	end

	----checking if available tickets are less than zero
	--if @tickets < 0
	--begin
	--	print 'Tickets available cannot be less than 0.'
	--end

	----checking if cost is less than zero
	--if @cost < 0
	--begin
	--	print 'Cost cannot be less than 0.'
	--end

	else
		insert into [Event](eventName,eventType,organizers,venue,[Day_Time],ticketsAvailable,cost,ImageLInk) values
		(@Name,@type,@organizer,@venue,@day_time,@tickets,@cost,@ImageLink)
		declare @eId int;
		select @eId=E.eventId from [Event] E where E.eventName=@Name AND E.eventType=@type AND E.Day_Time=@day_time 
		insert into Tickets(categoryId,Id)
		values(2,@eId)
end
go

--drop procedure addEvent

select* from [Event]
exec addEvent 'Karachi Eat','Food','Pepsico','Karachi','2018-05-16 17:00:00',1000,400,'images/karachi_eat.jpg'
select* from [Event]

go

go
create procedure updateEvent
@EeventId int,
@EeventName varchar(30),
@EeventType varchar(20),
@Eorganizers varchar(20),
@Evenue varchar(100),
@EDay date,
@ETime time,
@EticketsAvailable int,
@Ecost int,
@ImageLink varchar(100)
as
begin
	--checking if day has already passed
	if @EDay < (SELECT CAST(GETDATE() AS DATE))
	begin
		print 'Event day has already passed.'
	end

	--checking if available tickets are less than zero
	if @EticketsAvailable < 0
	begin
		print 'Tickets available cannot be less than 0.'
	end

	--checking if cost is less than zero
	if @Ecost < 0
	begin
		print 'Cost cannot be less than 0.'
	end

	else
	begin
		update Event
		set eventName=@EeventName, eventType=@EeventType,organizers=@Eorganizers, venue=@Evenue,[Day]=@EDay,[Time]=@ETime,ticketsAvailable=@EticketsAvailable,cost=@Ecost,ImageLink=@ImageLink
		where eventId=@EeventId
	end
end
go

GO
create procedure removeEvent
@Eventid int, @output int output
as
begin
	set @output=0
	select eventId from Event where eventId=@Eventid

	if @@ROWCOUNT=0
		set @output=1

	else
	delete from [Event]
	where eventId=@Eventid
end
go

--drop procedure removeEvent
--select* from [Event]
--exec removeEvent 4
--select* from [Event]

--===========
--	Movie
--===========

go
create procedure AddMovie
@movieName varchar(30),
@director varchar(20),
@writer varchar(20),
@runningTime time,
@rDate date,
@genre varchar(20),
@mainCast varchar(100),
@ImageLink varchar(100),
@output int output
as
begin
	set @output=0
	
	--checking for duplication
	if @movieName in (select movieName from Movie)
	begin
		if @director in (select director from Movie where movieName=@movieName)
		begin
			if @writer in (select writer from Movie where director=@director AND  movieName=@movieName)
			begin
				if @runningTime in (select runningTime from Movie where writer=@writer AND director=@director AND  movieName=@movieName)
				begin
					if @rDate in (select ReleaseDate from Movie where runningTime=@runningTime AND writer=@writer AND director=@director AND  movieName=@movieName)
					begin
						if @genre in (select genre from Movie where ReleaseDate=@rDate AND runningTime=@runningTime AND writer=@writer AND director=@director AND  movieName=@movieName)
						begin
							if @mainCast in (select mainCast from Movie where genre=@genre AND ReleaseDate=@rDate AND runningTime=@runningTime AND writer=@writer AND director=@director AND  movieName=@movieName)
							begin
								set @output=1
							end
						end
					end
				end
			end
		end
	end

	--checking if running time is out of bounds
	if convert(time(7),@runningTime,8) < '00:00:00.000'
	begin
		print 'Running time cannot be less than 0.'
	end

	--checking if release date has passed
	--if @rDate < (SELECT CAST(GETDATE() AS DATE))
	--begin
	--	print 'Release date has already passed.'
	--end

	insert into Movie(movieName,director,writer,runningTime,ReleaseDate,genre,mainCast,ImageLink)
	values (@movieName,@director,@writer,@runningTime,@rDate,@genre,@mainCast,@ImageLink)
end
--exec AddMovie 'Muala Jutt 2','Bilal Lashari','Bilal Lashari','02:00:00','2018-11-29','Action/Drama','Fawad Khan,Hamza Ali Abbassi, Mahira Khan','images/Maula_Jatt_2.jpg';
go

--drop procedure AddMovie

--select * from Movie

GO
create procedure DelMovie
@id int, @output int output
as
begin
	set @output=0
	select movieId from Movie where movieId=@id

	if @@ROWCOUNT=0
		set @output=1

	else
		delete from Movie where movieId = @id
end

--test run
go
--delete procedure MovieDelete
go

go
create procedure updateMovie
@MmovieId int,
@MmovieName varchar(30),
@Mdirector varchar(20),
@Mwriter varchar(20),
@MrunningTime Time,
@MReleaseDate Date,
@Mgenre varchar(20),
@MmainCast varchar(100)
as
begin
	--checking in Movie id is out of bounds
	if @MmovieId < 0
	begin
		print 'Invalid Movie id enterded.'
	end

	--checking if running time is out of bounds
	if convert(time(7),@MrunningTime,8) < '00:00:00.000'
	begin
		print 'Running time cannot be less than 0.'
	end

	--checking if release date has passed
	if @MReleaseDate < (SELECT CAST(GETDATE() AS DATE))
	begin
		print 'Release date has already passed.'
	end

	else
	begin
		update Movie
		set movieName=@MmovieName, director=@Mdirector, writer=@Mwriter, runningTime=@MrunningTime, ReleaseDate=@MReleaseDate, genre=@Mgenre, mainCast=@MmainCast
		where movieId=@MmovieId
	end
end
go

--===========
-- Showtime
--===========

--select * from Movie

--select * from Showtime

--select * from Cinema

--exec addShowtime 1,1,'2018-04-28 14:00:00',500,400,'2D'
--exec addShowtime 6,1,'2018-04-28 14:00:00',500,400,'2D'

--drop procedure addShowtime

GO
create procedure addShowtime
@movieId int,@CinemaId int,@date_time datetime,@seats int,@cost int,@screentype char(2), @output int output
as
begin
	declare @Sshowid int
	set @output=0

	--checking for duplication
	if @movieId in (select movieId from Showtime)
	begin
		if @CinemaId in (select cinemaId from Showtime where movieId=@movieId)
		begin
			if @date_time in (select date_time from Showtime where movieId=@movieId AND cinemaId=@CinemaId)
			begin
				if @screentype in (select ScreeningType from Showtime where movieId=@movieId AND cinemaId=@CinemaId AND date_time=@date_time)
				begin
					if @seats in (select availableSeats from Showtime where movieId=@movieId AND cinemaId=@CinemaId AND date_time=@date_time AND ScreeningType=@screentype)
					begin
						if @cost in (select cost from Showtime where movieId=@movieId AND cinemaId=@CinemaId AND date_time=@date_time AND ScreeningType=@screentype AND availableSeats=@seats)
						begin
							set @output=1
						end
					end
				end
			end
		end
	end

	--checking if screeningtype is 2d or 3d
	if @screentype!='2d' AND @screentype!='3d'
	begin
		set @output=2
	end

	select * from Cinema where CinemaId=@CinemaId

	if @@ROWCOUNT=0
	begin
		set @output=3
	end

	select * from Movie where movieId=@movieId

	if @@ROWCOUNT=0
	begin
		set @output=4
	end

	insert into Showtime(movieId,cinemaId,date_time,availableSeats,cost,ScreeningType) values
	(@movieId,@CinemaId,@date_time,@seats,@cost,@screentype)

	select @Sshowid=showId from Showtime where movieId=@movieId AND cinemaId=@CinemaId AND date_time=@date_time AND availableSeats=@seats AND cost=@cost AND ScreeningType=@screentype

	insert into Tickets (categoryId,ID) values (1, @SshowId)

end
go

GO
create procedure updateShowtime
@movieId int,@CinemaId int,@date_time datetime,@seats int,@cost int,@screentype char(2), @Sshowid int
as
begin
	--checking if number of available seats is out of bounds
	if @seats < 0
	begin
		print 'Number of available seats cannot be less than 0.'
	end

	--checking if cost is out of bounds
	if @cost < 0 OR @cost>1000
	begin
		print 'Invalid cost specified.'
	end

	--checking if screeningtype is 2d or 3d
	if @screentype!='2d' AND @screentype!='3d'
	begin
		print 'Invalid Screening type specified.'
	end

	update Showtime
	set movieId=@movieId, cinemaId=@CinemaId, date_time=@date_time, availableSeats=@seats, cost=@cost, ScreeningType=@screentype
	where @showId=@Sshowid
end
go

GO
create procedure removeShowtime
@Showid int, @output int output
as
begin
	set @output=0
	select * from Showtime where showId=@Showid

	if @@ROWCOUNT=0
		set @output=1

	else
	delete from Showtime
	where Showtime.showId=@Showid
end
go

--drop procedure removeShowtime
