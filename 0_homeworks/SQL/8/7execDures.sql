USE School;

declare @schoolName nvarchar(32)
set @schoolName = 'NVK666';

exec PrintOtlichnik @schoolName
exec PrintBorzniki  @schoolName
exec PrintJournal   @schoolName, N'11-А', N'Алгебра'
exec WhoHaveBirthday  @schoolName, 1, 1
