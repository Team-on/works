void CreateConsole()
{
if (AllocConsole()) 
{ 
int hCrt = _open_osfhandle((long)GetStdHandle(STD_OUTPUT_HANDLE), 4); 
*stdout = *(::_fdopen(hCrt, "w")); 
::setvbuf(stdout, NULL, _IONBF, 0); 
*stderr = *(::_fdopen(hCrt, "w")); 
::setvbuf(stderr, NULL, _IONBF, 0);
std::ios::sync_with_stdio();
}


////////////////////////////////////////////////////////

//��������� ������� �������� ������ � ������ ������ � �������� �� ����� ��� � � ���������� �����������. �������� ���������� ��� � ������ � cout/wcout.
//��� ����������������� ������� ���� ���������� �������� � ����� ��������� �����:
//#include <fcntl.h>
//#include #include <io.h>
//� �������� ������������ ���� std � ���������� ������������ ���:
//using namespace std;
//������� ��, ���� �� �� ������ ����� ������, �� ������ �������� std:: �� ���� ��������� ������� � ��� ���������.