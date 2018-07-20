Create Database Lab8
USE [Lab8]
GO
/****** Object:  Table [dbo].[Students]    Script Date: 02/03/2017 12:58:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Students](
	[StudentID] [int] NOT NULL,
	[StudentName] [varchar](30) NULL,
	[StudentBatch] [int] NULL,
	[CGPA] [float] NULL,
PRIMARY KEY CLUSTERED 
(
	[StudentID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[Students] ([StudentID], [StudentName], [StudentBatch], [CGPA]) VALUES (1, N'Ali', 2013, 3.3)
INSERT [dbo].[Students] ([StudentID], [StudentName], [StudentBatch], [CGPA]) VALUES (2, N'Aysha', 2013, 4)
INSERT [dbo].[Students] ([StudentID], [StudentName], [StudentBatch], [CGPA]) VALUES (3, N'Ahmed', 2013, 2.2)
/****** Object:  Table [dbo].[Instructors]    Script Date: 02/03/2017 12:58:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Instructors](
	[InstructorID] [int] NOT NULL,
	[InstructorsName] [varchar](30) NULL,
PRIMARY KEY CLUSTERED 
(
	[InstructorID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[Instructors] ([InstructorID], [InstructorsName]) VALUES (1, N'Zafar')
INSERT [dbo].[Instructors] ([InstructorID], [InstructorsName]) VALUES (2, N'Sadia')
INSERT [dbo].[Instructors] ([InstructorID], [InstructorsName]) VALUES (3, N'Saima')
/****** Object:  Table [dbo].[Courses]    Script Date: 02/03/2017 12:58:21 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
SET ANSI_PADDING ON
GO
CREATE TABLE [dbo].[Courses](
	[CourseID] [int] NOT NULL,
	[CourseName] [varchar](30) NULL,
	[CourseCreditHours] [int] NULL,
	[InstructorID] [int] NULL,
PRIMARY KEY CLUSTERED 
(
	[CourseID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
SET ANSI_PADDING OFF
GO
INSERT [dbo].[Courses] ([CourseID], [CourseName], [CourseCreditHours], [InstructorID]) VALUES (1, N'Computer Programming', 3, 1)
INSERT [dbo].[Courses] ([CourseID], [CourseName], [CourseCreditHours], [InstructorID]) VALUES (2, N'Computer Organization', 3, 2)
INSERT [dbo].[Courses] ([CourseID], [CourseName], [CourseCreditHours], [InstructorID]) VALUES (3, N'Computer Programming Lab', 1, NULL)
/****** Object:  Table [dbo].[Registration]    Script Date: 02/03/2017 12:58:22 ******/
SET ANSI_NULLS ON
GO
SET QUOTED_IDENTIFIER ON
GO
CREATE TABLE [dbo].[Registration](
	[StudentID] [int] NOT NULL,
	[CourseID] [int] NOT NULL,
	[GPA] [float] NULL,
PRIMARY KEY CLUSTERED 
(
	[StudentID] ASC,
	[CourseID] ASC
)WITH (PAD_INDEX  = OFF, STATISTICS_NORECOMPUTE  = OFF, IGNORE_DUP_KEY = OFF, ALLOW_ROW_LOCKS  = ON, ALLOW_PAGE_LOCKS  = ON) ON [PRIMARY]
) ON [PRIMARY]
GO
INSERT [dbo].[Registration] ([StudentID], [CourseID], [GPA]) VALUES (1, 1, 3)
INSERT [dbo].[Registration] ([StudentID], [CourseID], [GPA]) VALUES (1, 3, 3)
INSERT [dbo].[Registration] ([StudentID], [CourseID], [GPA]) VALUES (2, 2, 0)
/****** Object:  ForeignKey [FK__Courses__Instruc__08EA5793]    Script Date: 02/03/2017 12:58:22 ******/
ALTER TABLE [dbo].[Courses]  WITH CHECK ADD FOREIGN KEY([InstructorID])
REFERENCES [dbo].[Instructors] ([InstructorID])
GO
/****** Object:  ForeignKey [FK__Registrat__Cours__0EA330E9]    Script Date: 02/03/2017 12:58:22 ******/
ALTER TABLE [dbo].[Registration]  WITH CHECK ADD FOREIGN KEY([CourseID])
REFERENCES [dbo].[Courses] ([CourseID])
GO
/****** Object:  ForeignKey [FK__Registrat__Stude__0DAF0CB0]    Script Date: 02/03/2017 12:58:22 ******/
ALTER TABLE [dbo].[Registration]  WITH CHECK ADD FOREIGN KEY([StudentID])
REFERENCES [dbo].[Students] ([StudentID])
GO




Select * From Courses
Select * From Instructors
Select * From Registration
Select * From Students

Drop Proc New
--1
Go
Create PROC New
(@studentId int,@CourseId int)
as
Begin
begin transaction
save transaction savepoint;
Declare @gpa float;
Select @gpa=CGPA From Students Where StudentID=@studentId;

print @gpa

	Insert Into Registration 
	Values(@studentId,@CourseId,0);
if(@gpa<2.5)
begin
	print 'The student can only register in courses in which he have to improve';
	rollback transaction savepoint;
end


commit transaction
End
	
Exec New 3,3;