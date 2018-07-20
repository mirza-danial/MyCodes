use Project

--=============================================================================================================
--										USER Procedures
--=============================================================================================================

--===========
--	RATING
--===========

GO
create procedure RatingDelete
@userID int, @ticketID int
as
begin
	delete from RatingReview where userID = @userID and ticket_id = @ticketID
end
go

--test run
go
--exec RatingDelete 2,2
go

go
create procedure AddRating
@user varchar(30),
@ticket_id int,
@rating int,
@review varchar(100),
@out int output
as
begin
	declare @userId int;
	select @userId=[User].UserID From [User] Where [User].Email=@user;
	if exists (select * from RatingReview where ticket_id = @ticket_id and userID = @userId)
	begin
		update RatingReview set rating = @rating where ticket_id = @ticket_id and userID = @userId
		update RatingReview set review = @review where ticket_id = @ticket_id and userID = @userId
		set @out = 2
	end
	else 
	begin
		insert into RatingReview values (@userId,@ticket_id,@rating,@review)
		set @out = 1
	end
end
go


--test run
go
--declare @outp int
--exec AddRating 1,2,5,'GOOD :)',@outp output
--print @outp
go

--===========
--	USER
--===========

GO
create procedure signup
@fname varchar(20),@lname varchar(20),@email varchar(30),@phone bigint,@city varchar (20),@gender char(1),@password varchar(32),
@output int OUTPUT
as 
begin 
	set @output=0;

	--checking if valid email is given
	if @email not like '%@%'
	begin
		print 'Invalid email specified.'
	    set @output=1
	end

	 --checking if account already exists
	else if exists(select Email from [User] where Email=@email)
	begin
		print 'User already exists'
		set @output=2
	end
	
	--checking if valid mobile number is given
	else if @phone<923001111111 OR @phone>923499999999
	begin
		print 'Invalid mobile number specified.'
		set @output=3
	end

	--checking if invalid gender is entered
	else if @gender='0'
	begin
		print 'Invalid gender specified.'
		set @output=4
	end

	else
	begin
		insert into [User] (FirstName,LastName,Email,MobileNo,City,Gender,[Password]) values (@fname,@lname,@email,@phone,@city,@gender,@password)
		--select * from inserted
		print 'User has been added into the list.'
	end

end 
go

--test run
--go
--declare @o int;
--exec signup 'Danial','Mirza','DANIAL@yahoo.com',09007860111,'Lahore','male','nhiprhamenepurasaal',@o OUTPUT
--print @o
--select * from [User]
--delete from [User]
--where UserID=5
--go

GO
create procedure logincheck
@email varchar(30), @password varchar(32),
@output  int output
as 
begin
	set @output=-1

	--checking if User exists or not
	if exists (select * from [User] where Email=@email AND [Password]=@password)
	begin	
		set @output=0   
	end

	if exists (select * from [Admin] join [User] U on adminID=UserID where U.Email=@email and U.[Password]=@password)
	BEGIN 
		set @output=3
		print 'admins view'
	END	

	if @output=-1
	begin
		print 'user not found' 
	end
	
	else if @output=0
	begin 
		print 'logged in :)'   
	end
end

--test run
go
--declare @OUT int
--exec logincheck 'danialmirza@yahoo.com','nhiprhamenepurasaal',@OUT output
--print @OUT
go

GO
create PROCEDURE [UpdateUserInfo]
@email varchar(30),
@NewFName varchar(20),
@NewLName varchar(20),
@NewCity varchar(20),
@NewPhone int,
@NewPassword varchar(30)
as
begin
	Update [User]
	Set [FirstName]=@NewFName,City=@NewCity,[Password]=@NewPassword,MobileNo=@NewPhone
	where Email=@email

end
--test run
go
--exec UpdateUserInfo 'danialmirza@yahoo.com','Daniyal','Mirza','Islamabad','34343434','123456'
go

--===========
--	CART
--===========

Go
alter procedure [addToCart]
@user varchar(30),
@ticket_id int,
@amount int,
@ex int output,
@done int output
as
begin
	set @ex=1;
	set @done=1;
	if @amount>0
	begin
		declare @user_id int;
		select @user_id=U.UserID from [User] U where U.Email=@user; 
	
		declare @categoryId int;
		declare @id int;
		select @categoryId=T.categoryId from Tickets T where ticketId=@ticket_id;
	
		declare @cname varchar(10);
		select @cname=categoryName from Category where categoryId=@categoryId;
    
		declare @available int;
		declare @orderId int;
		declare @check int;
	
		set @check=0;
		if exists( select * from Cart C where C.user_id=@user_id)
		begin
			select @orderId=C.orderId from Cart C where C.user_id=@user_id;
			set @check=1;
		end 		
	
			if @cname='Movies'
			begin
				begin transaction t1
			
				begin try
					select @id=ID from Tickets where ticketId=@ticket_id;
					select @available=availableSeats from Showtime where showId=@id
					print 'Movie'
					print @available
					if (@available-@amount) >= 0
					begin
						update Showtime
						set availableSeats=availableSeats-@amount
						where showId=@id
						if @check = 0
						begin
							insert into dbo.[Cart]([user_id]) values(@user_id) 
							select @orderId=orderId from Cart where [user_id]=@user_id
						end
						insert into dbo.[Cart_Details](order_Id,ticketId,amount) values (@orderId,@ticket_id,@amount) 
					end	
					else 
					begin
						set @done=-1;
						print 'Not enough seats available!'
					end
					commit transaction t1 
				end try
				begin catch
					set @ex=-1;
					rollback transaction t1
				end catch
			end
			else if @cname='Events'
			begin
				begin transaction t2
				begin try	
					select @id=ID from Tickets where ticketId=@ticket_id;
					print @id
					select @available=E.ticketsAvailable from [Event] E where eventId=@id
					print 'Event'
					print @available
					if (@available-@amount) >= 0
					begin
						update [Event]
						set ticketsAvailable=ticketsAvailable-@amount
						where eventId=@id

						if @check = 0
						begin
							insert into dbo.[Cart]([user_id]) values(@user_id) 
							select @orderId=orderId from Cart where [user_id]=@user_id
						end
						insert into dbo.[Cart_Details](order_Id,ticketId,amount) values (@orderId,@ticket_id,@amount) 
					end	
					else 
					begin
						set @done=-1;
						print 'Not enough tickets available!'
					end
					commit transaction t2
				end try
				begin catch
					set @ex=-1;
					rollback transaction t2;
				end catch
			end
			else if @cname='Concerts'
			begin
				begin transaction t3
			
				begin try
					select @id=ID from Tickets where ticketId=@ticket_id;
					print @id
					select @available=C.availableTickets from Concert C where concertId=@id
					print 'Concert'
					print @available
					if (@available-@amount) >= 0
					begin
						update [Concert]
						set availableTickets=availableTickets-@amount
						where concertId=@id

						if @check = 0
						begin
							insert into dbo.[Cart]([user_id]) values(@user_id) 
							select @orderId=orderId from Cart where [user_id]=@user_id
						end
						insert into dbo.[Cart_Details](order_Id,ticketId,amount) values (@orderId,@ticket_id,@amount) 
					end	
					else 
					begin
						set @done=-1;
						print 'Not enough tickets available!'
					end
					commit transaction t3
				end try
				begin catch
					set @ex=-1;
					rollback transaction t3
				end catch
			end
	end
	else
	begin
		set @ex=-1;
	end
end
go

--test run
--declare @ex int
--declare @a int
--exec addToCart 'mrk@gmail.com',11,-90,@ex Output,@a Output
--print @ex
--print @a
go

Go
create procedure [dropCart]
@user varchar(30)
as
begin
	declare @orderId int;
	select @orderId=C.orderId From Cart C join [User] U on U.UserID=C.user_id  where U.Email=@user ;
	
	declare @no_of_enteries int
	declare @ticket_id int
	select @no_of_enteries=Count(*) from Cart_Details where order_Id=@orderId
	while @no_of_enteries > 0
	begin
		select @ticket_id = ticketId from Cart_Details where order_Id=@orderId
		
		EXEC dropItem @user,@ticket_id

		set @no_of_enteries=@no_of_enteries-1;
	end 
	delete from Cart Where orderId=@orderId
end
go

--test run
--Select * from Cart
--Select * from Cart_Details
--Select * from [Event]
--exec dropCart 'mrk@gmail.com'
--Select * from Cart
--Select * from Cart_Details
--Select * from [Event]
--test run
go
--exec dropCart 1
go

Go
alter procedure [dropItem]
@user varchar(30),
@ticketId int
as
begin
	declare @orderId int;
	select @orderId=C.orderId From Cart C join [User] U on U.UserID=C.user_id  where U.Email=@user ;
	declare @no_of_items int;
	select @no_of_items=COUNT(CD.ticketId) from Cart_Details CD where CD.order_Id=@orderId
	if @no_of_items>=1
	begin
		declare @amount int
		declare @catId int
		declare @catname varchar(20)
		declare @id int
		select @amount=amount from Cart_Details where order_Id=@orderId AND ticketId=@ticketId
		select @catId=T.categoryId from Tickets T where T.ticketId=@ticketId
		select @catname=C.categoryName from Category C where C.categoryId=@catId
		if @catname='Movies'
		begin
			select @id=T.ID from Tickets T where T.ticketId=@ticketId 
			update Showtime 
			set availableSeats=availableSeats+@amount
			where showId=@id

			delete from Cart_Details
			where order_Id=@orderId AND ticketId=@ticketId

		end
		else if @catname='Events'
		begin
			select @id=T.ID from Tickets T where T.ticketId=@ticketId 
			update [Event]
			set ticketsAvailable=ticketsAvailable+@amount
			where eventId=@id

			delete from Cart_Details
			where order_Id=@orderId AND ticketId=@ticketId
	
		end
		else if @catname='Concerts'
		begin
			select @id=T.ID from Tickets T where T.ticketId=@ticketId 
			update Concert
			set availableTickets=availableTickets+@amount
			where concertId=@id

			delete from Cart_Details
			where order_Id=@orderId AND ticketId=@ticketId
		end
	end

end
go
--test run
--select * from [Event]
--exec dropItem 'mrk@gmail.com',7
--select * from Cart_Details


Go
create procedure [ConfirmOrder]
@user varchar(30)
as
begin
	declare @orderId int
	select @orderId=C.orderId from [User] U join Cart C on U.UserID=C.user_id where U.Email=@user

	insert into Orders(orderId,[user_id]) 
	select C.orderId,C.user_id from Cart C where C.orderId=@orderId

	insert into Order_Details(order_Id,ticketId,amount)
	select CD.order_Id, CD.ticketId,CD.amount from Cart_Details CD where CD.order_Id=@orderId

	delete from Cart_Details where order_Id=@orderId  
	delete from Cart where orderId=@orderId 
	
	print 'Your order has been placed!'
end
go

--===========
--	MISC
--===========

GO
create procedure ContactMessage
@email varchar(30),@message varchar(200), @output int output
as
begin
	set @output=0
	if @email not like '%@%'
	begin
		print 'Invalid email specified.'
		set @output=1
	end

	else 
	begin
		insert into Contact values
		(@email,@message)
	end
end

--drop procedure ContactMessage

--select* from Contact
--exec ContactMessage 'abcd@gmail.com','Awesom'

select* from Contact

--=============================================================================================================

--=============================================================================================================

--=============================================================================================================
create procedure updateShowtime
@SshowId int,
@SmovieId int, 
@ScinemaId int,
@Sdate_time datetime,
@SScreeningType char(2),
@Savailableseats int,
@Scost int
as
begin
	--checking in show id is out of bounds
	if @SshowId < 0
	begin
		print 'Invalid Showtime id enterded.'
	end

	--checking in movie id is out of bounds
	if @SmovieId < 0
	begin
		print 'Invalid Movie id enterded.'
	end

	--checking in Cinema id is out of bounds
	if @ScinemaId < 0
	begin
		print 'Invalid Cinema id enterded.'
	end

	--checking if screeningtype is 2d or 3d
	if @SScreeningType!='2d' AND @SScreeningType!='3d'
	begin
		print 'Invalid Screening type specified.'
	end

	--checking if number of available seats is out of bounds
	if @Savailableseats < 0
	begin
		print 'Number of available seats cannot be less than 0.'
	end

	--checking if cost is out of bounds
	if @Scost < 0 OR @Scost>1000
	begin
		print 'Invalid cost specified.'
	end

	else
	begin
		update Showtime
		set movieId=@SmovieId, cinemaId=@ScinemaId, date_time=@Sdate_time, availableSeats=@Savailableseats, cost=@Scost, ScreeningType=@SScreeningType
		where showId=@SshowId
	end
end
go


--===========================
--procedures added afterwards
--===========================
--=============================================================================================================
go
create proc viewInfo
@email varchar(30),@fname varchar(20) OUTPUT,@lname varchar(20) OUTPUT,@phone bigint OUTPUT,@city varchar(20) OUTPUT
as
begin
	select @fname=U.FirstName from  [User] U where Email=@email;
	select @lname=U.LastName from  [User] U where Email=@email;
	select @phone=U.MobileNo from  [User] U where Email=@email;
	select @city=U.City from  [User] U where Email=@email;	
end

select* from [User]
--=============================================================================================================
go
create proc changePassword
@email varchar(30),@opass varchar(32),@npass varchar(32),@output int OUTPUT
as 
begin
	set @output=-1;
	if not exists (select* from [User] U where U.Email=@email)
	begin
		print 'no such user found '
		return
	end
	else
	begin
		if exists (select* from [User] U where U.Email=@email AND U.Password=@opass)
		begin
			update [User]
			set [Password]=@npass
			where Email=@email

			set @output=1;
			return;
		end
		else 
		begin
			print 'password does not match'
			set @output=-2;
			return;
		end
	end
end
--declare @out int;
--exec changePassword 'mirza_danial70@yahoo.com','123456','654321',@out OUTPUT
--print 

--=============================================================================================================

GO
alter procedure eventCount
@email varchar(30),@output int OUTPUT
as
begin
	declare @location varchar(20);
	select @location=City from [User] where Email=@email;
	select @output=COUNT(*) FROM [Event] E where E.venue like '%'+@location+'%' and datediff(month,getdate(),E.Day_Time)<=1 and E.Day_Time>getdate(); 
	select @output=@output+COUNT(*) FROM [Concert] C where C.venue like '%'+@location+'%' and datediff(month,getdate(),C.DayTime)<=1 and C.DayTime>getdate(); 

end

--=============================================================================================================
GO
ALTER procedure nearbyEvents
@email varchar(30)
as
begin
	declare @city varchar(20);
	select @city=U.City from [User] U where U.Email=@email;
	
	select * from Merged M where M.Venue like ('%'+@city+'%') and datediff(month,getdate(),M.DayTime)<=1 and M.DayTime>getdate()	 
end

--exec nearbyEvents 'mrk@gmail.com'
--select * from Concert
--=============================================================================================================
Go
create proc selectEvents 
as
begin
	select * from EventInfo  ;
end
GO

--exec selectEvents


--=============================================================================================================
go
create Proc displayCart
@user varchar(30)
as
begin
	declare @id int;
	select @id=UserId from [User] where Email=@user;

	select E.eventName [Name],E.cost cost,O.amount amount ,O.order_Id orderId,E.ticketId from( CartInfo O join EventInfo E  on E.ticketId=O.ticketId )   where O.user_id=@id
	Union
	select M.movieName [Name],S.cost cost,O.amount amount ,O.order_Id orderId,T.ticketId from( CartInfo O join Tickets T on T.ticketId=O.ticketId ) join [Showtime] S on categoryId=1 and S.showId=T.ID join Movie M on M.movieId=S.movieId   where O.user_id=@id
	Union
	select Co.performer [Name],Co.cost cost,O.amount amount ,O.order_Id orderId,Co.ticketId  from( CartInfo O join ConcertInfo Co on Co.ticketId=O.ticketId ) where O.user_id=@id
	

end
--=============================================================================================================
Go
create proc selectConcerts 
as
begin
	select * from ConcertInfo  ;
end
GO

--exec selectConcerts
--=============================================================================================================
go
alter proc upcoming
as
begin
	select M.Name [name],M.DayTime comingdate,ImageLink from Merged M where M.DayTime > GETDATE()
	Union
	select M.movieName [name],M.ReleaseDate comingdate,ImageLink from Movie M where M.ReleaseDate > GETDATE()
end

--exec upcoming
--=============================================================================================================
Go 
create proc selectCinemas
as
begin
	select * from Cinema C where 0<(select Count(*) from Showtime S where S.cinemaId=C.CinemaId );
end
--=============================================================================================================

Go
create proc selectMovies 
@cinemaId int
as
begin
	select * from Tickets T join Showtime S on T.ID=S.showId AND T.categoryId=1 join Movie M on S.movieId=M.movieId where S.cinemaId=@cinemaId;
end
GO

--exec selectMovies 1

--=============================================================================================================
GO
create proc getOrderDetails
@user varchar(30)
as
begin
	declare @id int;
	select @id=UserId from [User] where Email=@user;
	
	
	select E.eventName [Name],E.cost cost,O.amount amount ,O.order_Id orderId,E.ticketId from( OrderInfo O join EventInfo E  on E.ticketId=O.ticketId )   where O.user_id=@id
	Union
	select M.movieName [Name],S.cost cost,O.amount amount ,O.order_Id orderId,T.ticketId from( OrderInfo O join Tickets T on T.ticketId=O.ticketId ) join [Showtime] S on categoryId=1 and S.showId=T.ID join Movie M on M.movieId=S.movieId   where O.user_id=@id
	Union
	select Co.performer [Name],Co.cost cost,O.amount amount ,O.order_Id orderId,Co.ticketId  from( OrderInfo O join ConcertInfo Co on Co.ticketId=O.ticketId ) where O.user_id=@id
	 
end
--=============================================================================================================
--										Views
--=============================================================================================================
 


 GO
 create view Merged as 
 (
 select E.eventName Name,E.Day_Time DayTime,E.venue Venue,E.ImageLink  from [Event] E
 UNION
 select C.performer Name,C.DayTime DayTime,C.venue Venue,C.ImageLink from [Concert] C
 )
 select * from Merged

 create view MovieInfo
 as
 select * from Tickets T join Showtime S on T.ID=S.showId and T.categoryId=1 join Movie M on M.movieId=S.movieId 

 create view EventInfo
 as
 select * from Tickets T join [Event] E on T.ID=E.eventId and T.categoryId=2 
 

 create view ConcertInfo
 as
 select * from Tickets T join [Concert] C on T.ID=C.concertId and T.categoryId=3

 create view CartInfo
 as
 select * from Cart C join Cart_Details CD on C.orderId=CD.order_Id

 create view OrderInfo
 as
 select * from [Orders] O join Order_Details OD on O.orderId=OD.order_Id



 --=============================================================================================================
--										Triggers
--=============================================================================================================


--============ Cinema==========================================================================================

create trigger insertCinema on Cinema
instead of insert
as begin
	declare @CName varchar(50)
	declare @CLoc varchar(100)
	declare @CContact int 
	select @CName=Name from inserted
	select @CLoc=Location from inserted
	select @CContact=contactNo from inserted

	--checking for duplication
	if @CName in (select Name from Cinema)
	begin
		if @CLoc in (select Location from Cinema where Name=@CName)
		begin
			print 'Cinema already exists.'
		end
	end

	--checking if number is out of bounds
	if @CContact < 1111111111 OR @CContact > 9999999999
	begin
		print 'Invalid Contact number specified.'
	end

	else
	begin
		insert into Cinema (Name,Location,contactNo) values (@CName,@CLoc,@CContact)
		--select * from inserted
		print 'Cinema has been added into the list.'
	end
end
go
--=============================================================================================================
create trigger deleteCinema on Cinema
instead of delete
as begin
	print 'Cinema cannot be deleted.'
end
go

--=============================================================================================================

--============ Showtime
--=============================================================================================================
create trigger insertShowtime on Showtime
instead of insert
as begin
	declare @SshowId int
	declare @SmovieId int 
	declare @ScinemaId int
	declare @Sdate_time datetime 
	declare @SScreeningType char(2)
	declare @Savailableseats int
	declare @Scost int

	select @SshowId=showId  from inserted
	select @SmovieId=movieId  from inserted
	select @ScinemaId=cinemaId from inserted
	select @Sdate_time=date_time from inserted
	select @SScreeningType=ScreeningType from inserted
	select @Savailableseats=availableseats from inserted

	--checking for duplication
	if @SmovieId in (select movieId from Showtime)
	begin
		if @ScinemaId in (select cinemaId from Showtime where movieId=@SmovieId)
		begin
			if @Sdate_time in (select date_time from Showtime where movieId=@SmovieId AND cinemaId=@ScinemaId)
			begin
				if @SScreeningType in (select ScreeningType from Showtime where movieId=@SmovieId AND cinemaId=@ScinemaId AND date_time=@Sdate_time)
				begin
					print 'Showtime already exists.'
				end
			end
		end
	end

	--checking if number of available seats is out of bounds
	if @Savailableseats < 0
	begin
		print 'Number of available seats cannot be less than 0.'
	end

	--checking if cost is out of bounds
	if @Scost < 0 OR @Scost>1000
	begin
		print 'Invalid cost specified.'
	end

	--checking if screeningtype is 2d or 3d
	if @SScreeningType!='2d' AND @SScreeningType!='3d'
	begin
		print 'Invalid Screening type specified.'
	end

	else
	begin
		insert into Showtime (movieId, cinemaId, date_time, availableSeats, cost, ScreeningType) values (@SmovieId, @ScinemaId, @Sdate_time, @Savailableseats, @Scost, @SScreeningType)
		insert into Tickets (categoryId,movieId,eventId,concertId) values (1, @SshowId, NULL, NULL)
		print 'Showtime has been added into the list.'
	end
end
go

--===========================================================================================================
--============ RatingReview
--=============================================================================================================
create trigger insertRatingReview on [RatingReview]
instead of insert
as begin
	declare @Rrating int
	select @Rrating=rating from inserted

	declare @Rreview varchar(100)
	select @Rreview=review from inserted

	declare @RuserID int  
	select @RuserID=userID  from inserted

	declare @Rticket_id  int
	select @Rticket_id=ticket_id from inserted

	if @Rrating < 0 OR @Rrating > 5
	begin
		print 'Invalid rating entered.'
	end

	else
	begin
		insert into [RatingReview] (userID , ticket_id , rating , review) values (@Rrating, @Rticket_id, @Rrating, @Rreview)
		--select * from inserted
		print 'Rating has been added into the list.'
	end
end
go

--=============================================================================================================
--============User
--=============================================================================================================
create trigger insertUser on [User]
instead of insert
as begin
	declare @UUserID int
	select @UUserID=UserID from inserted

	declare @UFirstName varchar(20)
	select @UFirstName=FirstName from inserted

	declare @ULastName varchar(20)
	select @ULastName=LastName from inserted

	declare @UEmail varchar(30)
	select @UEmail=Email from inserted

	declare @UMobileNo int
	select @UMobileNo=MobileNo from inserted

	declare @UCity varchar(20)
	select @UCity=City from inserted

	declare @UGender varchar(10)
	select @UGender=Gender from inserted
	
	declare @UPassword varchar(32)
	select @UPassword=[Password] from inserted 

	--checking if valid email is given
	if @UEmail not like '%@%'
	begin
		print 'Invalid email specified.'
	end

	--checking if valid mobile number is given
	if @UMobileNo<923001111111 OR @UMobileNo>923499999999
	begin
		print 'Invalid mobile number specified.'
	end

	--checking if valid gender is given
	if @UGender!='Male' OR @UGender!='Female' OR @UGender!='Unspecified'
	begin
		print 'Invalid gender specified.'
	end

	else
	begin
		insert into [User] (UserID,FirstName,LastName,Email,MobileNo,City,Gender,[Password]) values (@UUserID,@UFirstName,@ULastName,@UEmail,@UMobileNo,@UCity,@UGender,@UPassword)
		--select * from inserted
		print 'User has been added into the list.'
	end

end
go
--=============================================================================================================
--============Concert
--=============================================================================================================

create trigger insertConcert on Concert
instead of insert
as begin
	declare @CconcertId int
	declare @Cvenue varchar(100)
	declare @CDayTime datetime
	declare @Cperformer varchar(30)
	declare @Corganizers varchar(20)
	declare @CavailableTickets int
	declare @Ccost int

	select @CconcertId=concertId from inserted
	select @Cvenue=venue from inserted
	select @CDayTime=[DayTime] from inserted
	select @Cperformer=performer from inserted
	select @Corganizers=organizers from inserted
	select @CavailableTickets=availableTickets from inserted
	select @Ccost=cost from inserted

	--checking for duplication
	if @Cvenue in (select venue from Concert)
	begin
		if @CDayTime in (select [DayTime] from Concert where venue=@Cvenue)
		begin
			if @Cperformer in (select performer from Concert where venue=@Cvenue AND [DayTime]=@CDayTime)
			begin
				if @Corganizers in (select organizers from Concert where performer=@Cperformer AND venue=@Cvenue AND [DayTime]=@CDayTime)
				begin
					print 'Concert already exists.'
				end
			end
		end
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
		insert into Concert (venue , [DayTime] , performer , organizers , availableTickets , cost ) values (@Cvenue, @CDayTime, @Cperformer, @Corganizers, @CavailableTickets, @Ccost)
		insert into Tickets (categoryId,movieId,eventId,concertId) values (3, NULL,NULL,@CconcertId)
		print 'Concert has been added into the list.'
	end

end
go
--=============================================================================================================

--=============================================================================================================
--============ Movie
--=============================================================================================================
create trigger insertMovie on Movie
instead of insert
as begin
	declare @MmovieId int
	declare @MmovieName varchar(30)
	declare @Mdirector varchar(20)
	declare @Mwriter varchar(20)
	declare @MrunningTime Time
	declare @MReleaseDate Date
	declare @Mgenre varchar(20)
	declare @MmainCast varchar(100)

	select @MmovieId=movieId from inserted
	select @MmovieName=movieName from inserted
	select @Mdirector=director from inserted
	select @Mwriter=writer from inserted
	select @MrunningTime=runningTime from inserted
	select @MReleaseDate=ReleaseDate from inserted
	select @Mgenre=genre from inserted
	select @MmainCast=mainCast from inserted

	--checking for duplication
	if @MmovieName in (select movieName from Movie)
	begin
		if @Mdirector in (select director from Movie where movieName=@MmovieName)
		begin
			if @Mwriter in (select writer from Movie where director=@Mdirector AND  movieName=@MmovieName)
			begin
				if @MrunningTime in (select runningTime from Movie where writer=@Mwriter AND director=@Mdirector AND  movieName=@MmovieName)
				begin
					if @MReleaseDate in (select ReleaseDate from Movie where runningTime=@MrunningTime AND writer=@Mwriter AND director=@Mdirector AND  movieName=@MmovieName)
					begin
						if @Mgenre in (select genre from Movie where ReleaseDate=@MReleaseDate AND runningTime=@MrunningTime AND writer=@Mwriter AND director=@Mdirector AND  movieName=@MmovieName)
						begin
							if @MmainCast in (select mainCast from Movie where genre=@Mgenre AND ReleaseDate=@MReleaseDate AND runningTime=@MrunningTime AND writer=@Mwriter AND director=@Mdirector AND  movieName=@MmovieName)
							begin
								print 'Movie already exists.'
							end
						end
					end
				end
			end
		end
	end

	--checking if running time is out of bounds
	if @MrunningTime < 0
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
		insert into Movie (movieName, director, writer, runningTime, ReleaseDate, genre, mainCast) values (@MmovieName, @Mdirector, @Mwriter, @MrunningTime, @MReleaseDate, @Mgenre, @MmainCast)
		print 'Movie has been added into the list.'
	end

end
go
--=============================================================================================================

--============ Event
--=============================================================================================================

create trigger insertEvent on Event
instead of insert
as begin
	declare @EeventId int
	declare @EeventName varchar(30)
	declare @EeventType varchar(20)
	declare @Eorganizers varchar(20)
	declare @Evenue varchar(100)
	declare @EDay date
	declare @ETime time
	declare @EticketsAvailable int
	declare @Ecost int

	select @EeventId=eventId from inserted
	select @EeventName=eventName from inserted
	select @EeventType=eventType from inserted
	select @Eorganizers=organizers from inserted
	select @Evenue=venue from inserted
	select @EDay=[Day] from inserted
	select @ETime=[Time] from inserted
	select @EticketsAvailable=ticketsAvailable from inserted
	select @Ecost=cost from inserted

	--checking for duplication
	if @EeventId in (select eventId from [Event])
	begin
		if @EeventName in (select eventName from [Event] where eventId=@EeventId)
		begin
			if @EeventType in (select eventType from [Event] where eventName=@EeventName AND  eventId=@EeventId)
			begin
				if @Eorganizers in (select organizers from [Event] where eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
				begin
					if @Evenue in (select venue from [Event] where organizers=@Eorganizers AND eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
					begin
						if @EDay in (select [Day] from [Event] where venue=@Evenue AND organizers=@Eorganizers AND eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
						begin
							if @ETime in (select [Time] from [Event] where [Day]=@EDay AND venue=@Evenue AND organizers=@Eorganizers AND eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
							begin
								if @EticketsAvailable in (select ticketsAvailable from [Event] where [Time]=@ETime AND [Day]=@EDay AND venue=@Evenue AND organizers=@Eorganizers AND eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
								begin
									if @Ecost in (select cost from [Event] where ticketsAvailable=@EticketsAvailable AND [Time]=@ETime AND [Day]=@EDay AND venue=@Evenue AND organizers=@Eorganizers AND eventType=@EeventType AND eventName=@EeventName AND  eventId=@EeventId)
									begin
										print 'Event already exists.'
									end
								end
							end
						end
					end
				end
			end
		end
	end

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
		insert into [Event] (eventName, eventType, organizers, venue, [Day], [Time], ticketsAvailable, cost) values (@EeventId, @EeventType, @Eorganizers, @Evenue, @EDay, @ETime, @EticketsAvailable, @Ecost)
		insert into Tickets (categoryId,movieId,eventId,concertId) values (2, NULL,@EeventId,NULL)
		print 'Event has been added into the list.'
	end

end
go
--=============================================================================================================
