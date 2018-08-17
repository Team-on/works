USE School;

INSERT INTO _Appointment
	(NameAppointment)
values
	(N'Без призначення'),
	(N'Історичний'),
	(N'Математичний'),
	(N'Фізичний'),
	(N'Хімічний'),
	(N'Англійський'),
	(N'Біологічний'),
	(N'Спортзал')

	
INSERT INTO _MedicalPaper
	(NameMedicalPaper)
values
	(N'Профогляд')
	
INSERT INTO _Role
	(NameRole)
values
	(N'Директор школи'),
	(N'Бібліотекар'),
	(N'Гардеробник'),
	(N'Медична сестра'),
	(N'Кухар'),
	(N'Вчитель історії'),
	(N'Вчитель алгебри'),
	(N'Вчитель геометрії'),
	(N'Вчитель української мови'),
	(N'Вчитель англійської мови'),
	(N'Вчитель біології'),
	(N'Вчитель фізики'),
	(N'Вчитель хімії'),
	(N'Вчитель географії'),
	(N'Вчитель фізкультури')
	
INSERT INTO _Subject
	(NameSubject)
values
	(N'Історія'),  			--1
	(N'Алгебра'),			--2
	(N'Герметрія'),			--3
	(N'Українська мова'),	--4
	(N'Англійська мова'),	--5
	(N'Біологія'),			--6
	(N'Фізика'),			--7
	(N'Хімія'),				--8
	(N'Географія'),			--9
	(N'Фізкультура')		--10