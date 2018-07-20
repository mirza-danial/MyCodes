--1
select Name,Count(CourseID) as [No.of.Courses]
from Students join Registration on RollNo=RollNumber
group by Name
--2
select AVG(GPA) as AverageGPA,Max(GPA)as MaxGPA,Min(GPA) as MinGPA,STDEV(GPA) as StandardDeviation
from registration
--3

select  top 1 Name,Sum(C.CreditHours) as Credits
from (Students join Registration as R on RollNo=RollNumber) join Courses as C on R.CourseID=C.CourseID
Group by Name
order by Credits desc
--4
select  TOP 2 [Name],Sum(C.CreditHours) as Credits
from (Students join Registration as R on RollNo=RollNumber) join Courses as C on R.CourseID=C.CourseID
Group by Name

Except

select  top 1 [Name],Sum(C1.CreditHours) as Credits1
from (Students join Registration as R1 on RollNo=RollNumber) join Courses as C1 on R1.CourseID=C1.CourseID
Group by Name

--5
Select I.Name,CS.CourseID,Count(CS.Section) as [No. of Sections]
from Instructors as I join Courses_Semester as CS on I.InstructorID=CS.InstructorID
group by I.Name,Cs.CourseID
having count(CS.Section)>1

--6
select CS.Semester,C.CourseID,count(cs.CourseID) as numSubjects
from (Courses as C join Courses_Semester as CS on C.CourseID=CS.CourseID)
group by Cs.Semester,C.CourseID

--7
select RollNo,Name 
from Students
Except
Select RollNo,Name
from Students
where WarningCount>0

--8
select S1.RollNo,S1.Name
from Students as S1
where Exists (select S2.RollNo
from Students as S2
where S2.WarningCount=0 and S1.RollNo=S2.RollNo
)

--9
select count(S1.Name) as [No. of Students with name not starting with A]
from Students as S1
where Not Exists(select *
from Students as S2
where S2.Name like 'A%' and S1.Name=S2.Name
)
--10
select Sum(A.TotalDues) as Total
from ChallanForm as A
where Exists (select *
from ChallanForm as B
where B.Status='Paid'
)

