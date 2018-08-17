USE School;

declare @schoolName nvarchar(32)
set @schoolName = N'NVK666';

EXEC AddSchoolToDB @schoolName