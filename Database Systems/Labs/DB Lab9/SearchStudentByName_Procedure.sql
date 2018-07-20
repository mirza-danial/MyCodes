create procedure SearchStudentByName
@name varchar(40)
/*
GOOD PRACTICE: write the execution statment of procedure as comment in procedure
Execute  SearchStudentByName  'Ali'
*/
as
begin    

	select * From Students 
	where StudentName like '%'+@name+'%' 
	
end