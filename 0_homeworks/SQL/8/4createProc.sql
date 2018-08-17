USE School;
GO

CREATE PROCEDURE AddSchoolToDB
    @schoolName nvarchar(32)
AS BEGIN

EXEC('
CREATE TABLE ' + @schoolName + 'Cabinet(
    IdCabinet TINYINT IDENTITY PRIMARY KEY,
    CabinetNumber SMALLINT NOT NULL,
	IdAppointment TINYINT NOT NULL
	
	FOREIGN KEY (IdAppointment) REFERENCES _Appointment(IdAppointment) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Class(
    IdClass TINYINT IDENTITY PRIMARY KEY,
    NameClass NVARCHAR(5) NOT NULL,
	IdCabinet TINYINT NOT NULL
	
	FOREIGN KEY (IdCabinet) REFERENCES ' + @schoolName + 'Cabinet(IdCabinet) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Adress(
    IdAdress SMALLINT IDENTITY PRIMARY KEY,
	City NVARCHAR(32) NOT NULL,
	Street NVARCHAR(32) NOT NULL,
	HouseNum TINYINT NOT NULL,
	Enterance TINYINT NOT NULL,
	FlatNum SMALLINT NOT NULL
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Parents(
    IdParents SMALLINT IDENTITY PRIMARY KEY,
	FirstName NVARCHAR(16) NOT NULL,
	SecondName NVARCHAR(16) NOT NULL,
	ThirdName NVARCHAR(16) NOT NULL,
	IdAdress SMALLINT NOT NULL
	
	FOREIGN KEY (IdAdress) REFERENCES ' + @schoolName + 'Adress(IdAdress) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Pupil(
    IdPupil SMALLINT IDENTITY PRIMARY KEY,
    IdClass TINYINT NOT NULL,
	FirstName NVARCHAR(16) NOT NULL,
	SecondName NVARCHAR(16) NOT NULL,
	ThirdName NVARCHAR(16) NOT NULL,
	Sex bit NOT NULL,
	DateОfBirth DATE NOT NULL,
	IdAdress SMALLINT NOT NULL,
	IdParentsMother SMALLINT,
	IdParentsFather SMALLINT
	
	FOREIGN KEY (IdClass) REFERENCES ' + @schoolName + 'Class(IdClass),
	FOREIGN KEY (IdAdress) REFERENCES ' + @schoolName + 'Adress(IdAdress),
	FOREIGN KEY (IdParentsMother) REFERENCES ' + @schoolName + 'Parents(IdParents),
	FOREIGN KEY (IdParentsFather) REFERENCES ' + @schoolName + 'Parents(IdParents) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'PassedMedicalPaper(
    IdMedicalPaper TINYINT NOT NULL,
	IdPupil SMALLINT NOT NULL
	
	FOREIGN KEY (IdMedicalPaper) REFERENCES _MedicalPaper(IdMedicalPaper) ,
	FOREIGN KEY (IdPupil) REFERENCES ' + @schoolName + 'Pupil(IdPupil) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Staff(
	IdStaff SMALLINT IDENTITY PRIMARY KEY,
	FirstName NVARCHAR(16) NOT NULL,
	SecondName NVARCHAR(16) NOT NULL,
	ThirdName NVARCHAR(16) NOT NULL,
	Salary SMALLINT NOT NULL,
	IdRole TINYINT NOT NULL,
	Sex bit NOT NULL,
	DateОfBirth DATE NOT NULL,
	IdAdress SMALLINT NOT NULL
	
	FOREIGN KEY (IdRole) REFERENCES _Role(IdRole) ,
	FOREIGN KEY (IdAdress) REFERENCES ' + @schoolName + 'Adress(IdAdress) 
)
');


EXEC('
CREATE TABLE ' + @schoolName + 'CabinetKeeper(
	IdStaff SMALLINT NOT NULL,
	IdCabinet TINYINT NOT NULL
	
	FOREIGN KEY (IdStaff) REFERENCES ' + @schoolName + 'Staff(IdStaff) ,
	FOREIGN KEY (IdCabinet) REFERENCES ' + @schoolName + 'Cabinet(IdCabinet) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'ClassMaster(
	IdStaff SMALLINT,
	IdClass TINYINT NOT NULL
	
	FOREIGN KEY (IdStaff) REFERENCES ' + @schoolName + 'Staff(IdStaff) ,
	FOREIGN KEY (IdClass) REFERENCES ' + @schoolName + 'Class(IdClass) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Teacher(
	IdTeacher SMALLINT IDENTITY PRIMARY KEY,
	IdStaff SMALLINT NOT NULL
	
	FOREIGN KEY (IdStaff) REFERENCES ' + @schoolName + 'Staff(IdStaff) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'SubjectTeacher(
	IdTeacher SMALLINT NOT NULL,
	IdSubject TINYINT  NOT NULL
	
	FOREIGN KEY (IdTeacher) REFERENCES ' + @schoolName + 'Teacher(IdTeacher) ,
	FOREIGN KEY (IdSubject) REFERENCES _Subject(IdSubject) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Timetable(
	IdLesson TINYINT IDENTITY PRIMARY KEY,
	StartTime TIME NOT NULL,
	EndTime  TIME NOT NULL,
	IdSubject TINYINT NOT NULL,
	IdCabinet TINYINT NOT NULL,
	IdClass  TINYINT  NOT NULL,
	IdTeacher SMALLINT NOT NULL
	
	FOREIGN KEY (IdTeacher) REFERENCES ' + @schoolName + 'Teacher(IdTeacher) ,
	FOREIGN KEY (IdSubject) REFERENCES _Subject(IdSubject) ,
	FOREIGN KEY (IdCabinet) REFERENCES ' + @schoolName + 'Cabinet(IdCabinet) ,
	FOREIGN KEY (IdClass)   REFERENCES ' + @schoolName + 'Class(IdClass) 
)
');

EXEC('
CREATE TABLE ' + @schoolName + 'Mark(
	IdMark INT IDENTITY PRIMARY KEY,
	Number TINYINT NOT NULL,
	IdPupil SMALLINT NOT NULL,
	IdTeacher SMALLINT NOT NULL,
	IdSubject TINYINT NOT NULL,
	Date DATE NOT NULL
	
	FOREIGN KEY (IdTeacher) REFERENCES ' + @schoolName + 'Teacher(IdTeacher) ,
	FOREIGN KEY (IdSubject) REFERENCES _Subject(IdSubject) ,
	FOREIGN KEY (IdPupil) REFERENCES   ' + @schoolName + 'Pupil(IdPupil) 
)
');
END
GO

CREATE PROCEDURE PrintOtlichnik
    @schoolName nvarchar(32)
AS BEGIN
EXEC('
select ' + @schoolName + 'Pupil.FirstName + '' '' + ' + @schoolName + 'Pupil.SecondName + '' '' + ' + @schoolName + 'Pupil.ThirdName as N''ПІБ'',
	x.[AVG mark] as N''Середня оцінка''
from(
	select IdPupil, 
		avg(Number) as N''AVG mark''
	from ' + @schoolName + 'Mark
	group by IdPupil
	having avg(Number) >= 10
) x
inner join ' + @schoolName + 'Pupil on x.IdPupil = ' + @schoolName + 'Pupil.IdPupil
')
END;
GO

CREATE PROCEDURE PrintBorzniki
    @schoolName nvarchar(32)
AS BEGIN
EXEC('
select ' + @schoolName + 'Pupil.FirstName + '' '' + ' + @schoolName + 'Pupil.SecondName + '' '' + ' + @schoolName + 'Pupil.ThirdName as N''Боржник'',
	N''Профогляд'' as N''Що не здано''
from ' + @schoolName + 'Pupil
left join ' + @schoolName + 'PassedMedicalPaper on ' + @schoolName + 'Pupil.IdPupil = ' + @schoolName + 'PassedMedicalPaper.IdPupil
where ' + @schoolName + 'PassedMedicalPaper.IdMedicalPaper is null
')
END;
GO

CREATE PROCEDURE PrintJournal
    @schoolName nvarchar(32),
	@className nvarchar(32),
	@subjectName nvarchar(32)
AS BEGIN
EXEC('
select NVK666Mark.Date,
	NVK666Staff.FirstName + '' '' + NVK666Staff.SecondName + '' '' + NVK666Staff.ThirdName as N''Хто'', 
	NVK666Pupil.FirstName + '' '' + NVK666Pupil.SecondName + '' '' + NVK666Pupil.ThirdName as N''Кому'',
	NVK666Mark.Number
	
from NVK666Mark
	inner join _Subject on NVK666Mark.IdSubject = _Subject.IdSubject
	inner join NVK666Pupil on NVK666Mark.IdPupil = NVK666Pupil.IdPupil
	inner join NVK666Class on NVK666Pupil.IdClass = NVK666Class.IdClass
	inner join NVK666Teacher on NVK666Teacher.IdTeacher = NVK666Mark.IdTeacher
	inner join NVK666Staff on NVK666Staff.IdStaff = NVK666Teacher.IdStaff

where	_Subject.NameSubject = N'''+@subjectName+''' and 
		NVK666Class.NameClass = N'''+@className+'''
')
END;
GO

CREATE PROCEDURE WhoHaveBirthday
    @schoolName nvarchar(32),
	@mounth int,
	@day int
AS BEGIN
exec('
select FirstName + '' '' + SecondName + '' '' + ThirdName as N''ПІБ'',
	N''Учень'' as ''Посада''
from '+@schoolName+'Pupil
where DAY(DateОfBirth) = '+@day+' and
	  MONTH(DateОfBirth) = '+@mounth+'
UNION
select FirstName + '' '' + SecondName + '' '' + ThirdName as N''ПІБ'',
	_Role.NameRole as ''Посада''
from '+@schoolName+'Staff
inner join _Role on '+@schoolName+'Staff.IdRole = _Role.IdRole
where DAY(DateОfBirth) = '+@day+' and
	  MONTH(DateОfBirth) = '+@mounth+'
')
END;
GO


CREATE PROCEDURE ANYDURE
    @schoolName nvarchar(32)
AS BEGIN
EXEC('

')
END;
GO
