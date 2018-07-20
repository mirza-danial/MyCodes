
create table Customer
(
	CustomerID int primary key,
	CustomerName varchar(50),
	Phone varchar(50)
	
)

go
create table Product
(
	ProductID int primary key,
	ProductName varchar(50),
	Price int
	
)
go
create table [Order]
(
	OrderID int primary key,
	CustomerID int
	Foreign key (CustomerID) references Customer(CustomerID)
)
go
create table OrderItem
(
	ID int primary key,
	ProductID int,
	OrderID int,
	quantity int
	Foreign key (OrderID) references [Order](OrderID),
	Foreign key (ProductID) references [dbo].[Product](ProductID)
)

go
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (1, 'Ali', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (2, 'hassan' , '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (3, 'Maha', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (4, 'waleed', '123-123-123' )
Insert into Customer(CustomerID, CustomerName, Phone) VALUES (5, 'hamza', '123-123-123' )

go
Insert into Product (ProductID, ProductName, Price) VALUES (1,'Laptop',50000)
Insert into Product (ProductID, ProductName, Price) VALUES (2,'Tab',20000)
Insert into Product (ProductID, ProductName, Price) VALUES (3,'Mobile',40000)
Insert into Product (ProductID, ProductName, Price) VALUES (4,'USB',1000)
Insert into Product (ProductID, ProductName, Price) VALUES (5,'Smart Watch',30000)
 
 go
Insert into [Order](OrderID,CustomerID) VALUES (1,1)
Insert into [Order](OrderID,CustomerID) VALUES (2,2)
Insert into [Order](OrderID,CustomerID) VALUES (3,3)
Insert into [Order](OrderID,CustomerID) VALUES (4,1)
Insert into [Order](OrderID,CustomerID) VALUES (5,2)
go
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (1,1,1,5)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (2,1,3,4)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (3,1,2,6)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (4,2,4,4)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (5,3,5,3)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (6,4,2,1)
Insert into OrderItem (ID, ProductID, OrderID, quantity) VALUES (7,4,3,2)

GO
alter function lovesThisProduct(@user int)
returns varchar(50)
as
begin
	declare @retval varchar(50);
	select top 1 @retval=T.Product From (select P.ProductName as Product,sum(OI.quantity) as blk from [Order] O join OrderItem OI on O.OrderID=OI.OrderID join Customer C on C.CustomerID=O.CustomerID join Product P on P.ProductID=OI.ProductID where C.CustomerID=@user group by P.ProductName) as T
	return @retval
end

select dbo.lovesThisProduct(6)
--1
go
create FUNCTION ProductSales2(@Pid int)
RETURNS int
AS
BEGIN

Declare @returnvalue int
Declare @new int
select @new=P.Price from Product P where P.ProductID=@Pid
Select @returnvalue=SUM(quantity) from OrderItem OI   where OI.ProductID=@Pid 
set @returnvalue=@returnvalue*@new
RETURN   @returnvalue  
END
go	


Execution:
select dbo.ProductSales2(1)

--2

go
create FUNCTION OrderedByUser(@Uid int)
RETURNS Table
AS
RETURN Select DISTINCT Product.ProductName   from OrderItem join Product ON OrderItem.ProductID=Product.ProductID join [Order] on OrderItem.OrderID=[Order].OrderID  where [Order].CustomerID=@Uid 
go


Execution:
select* from dbo.OrderedByUser(3)

--3

go
create FUNCTION q3()
RETURNS Table
AS
RETURN Select Product.ProductID,Product.ProductName,dbo.ProductSales2(Product.ProductID) as Sales
	   from Product
go

select* from q3()

create PROC q3Proc
AS
BEGIN
	Select Product.ProductID,Product.ProductName,dbo.ProductSales2(Product.ProductID) as Sales
	   from Product
END
 exec q3Proc

create Proc new 
as
begin
	select * from q3();
end

exec new


alter function productsNeverSold()
returns Table
as
return select P.ProductID from Product P left outer join OrderItem O on O.ProductID=P.ProductID group by P.ProductID having count(O.OrderID)=0

select * from productsNeverSold()

alter proc decreasePrice
as
begin
	update Product
	set Price=Price/2
	where ProductID in (select * from productsNeverSold()) --productsNeverSold()
end

exec decreasePrice

go
create trigger up on Product
after update
as
begin
	select ProductID from inserted
	print 'is changed'
end

select * from Product