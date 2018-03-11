#define _CRT_SECURE_NO_WARNINGS	
#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>
#include <conio.h>
using namespace std;

//class BasicTemplate {
//	string title;
//public:
//	virtual string build() const = 0;
//
//	void SetTitle(string Title) {
//		title = Title;
//	}
//	string GetTitle() const {
//		return title;
//	}
//};
//
//class VideoViewer : public BasicTemplate {
//	vector <pair<string, COORD>> videoPath;
//public:
//	 string build() const {
//		BasicBuilder b;
//		string html;
//		html = b.Html() + "\n";
//		html += b.Head() + "\n";
//		html += b.Title(GetTitle()) + "\n";
//		html += b.Head(1) + "\n";
//		html += b.Body() + "\n";
//
//		for (auto &i : videoPath)
//			html += b.Video(i.first, i.second.X, i.second.Y) + "\n";
//
//		html += b.Body(1) + "\n";
//		html += b.Html(1);
//		return html;
//	}
//
//	 void AddVideo(string path, COORD size = {360, 480}) {
//		 pair<string, COORD> v;
//		 v.first = path;
//		 v.second = size;
//		 videoPath.push_back(v);
//	 }
//};

enum Templates {IdVideoViewer = 1, IdImgViewer, IdTextViewer, TEAMPLATES_END};
enum Decorators { IdHr = 1, IdCenter, DECORATORS_END };

class BasicBuilder {
public:
	virtual string Html(bool end = 0) {
		return string("<") + string(end?"/":"") + string("html>");
	}
	virtual string Head(bool end = 0) {
		return string("<") + string(end ? "/" : "") + string("head>");
	}
	virtual string Body(bool end = 0) {
		return string("<") + string(end ? "/" : "") + string("body>");
	}
	virtual string Title() {
		string title;
		cout << "Title: "; getline(cin, title);
		return string("<title>") + title + "</title>";
	}
	virtual string Img() {
		string src, alt;
		cout << "Img->Src: "; getline(cin, src);
		cout << "Img->Alt: "; getline(cin, alt);
		return string("<img src=\"") + src + "\" alt=\"" + alt + "\" />";
	}
	virtual string Video(int width = 480, int height = 360) {
		string src;
		cout << "Video->Src: "; getline(cin, src);
		char w[32], h[32];
		_itoa(width, w, 10);
		_itoa(height, h, 10);
		return string("<iframe width=\" ") + w + "\" height = \"" + h + "\" src = \"" + src + "\" frameborder = \"0\" allowfullscreen>< / iframe>";
	}
	virtual string Text() {
		string text;
		cout << "Text: "; getline(cin, text);
		return string("<p>") + text + "</p>";
	}

	static BasicBuilder *CreateTemplate(Templates id);
};

class VideoViewer : public BasicBuilder {
public:
	string Img() {
		return "";
	}

	string Text() {
		return "";
	}
};

class ImgViewer : public BasicBuilder {
public:
	string Video(int width = 480, int height = 360) {
		return "";
	}

	string Text() {
		return "";
	}
};

class TextViewer : public BasicBuilder {
public:
	string Img() {
		return "";
	}

	string Video(int width = 480, int height = 360) {
		return "";
	}
};

class Decorator : public BasicBuilder {
	BasicBuilder *d;
public:
	Decorator(BasicBuilder *dec) {
		d = dec;
	}

	string Img() {
		return d->Img();
	}
	string Video(int width = 480, int height = 360) {
		return d->Video();
	}
	string Text() {
		return d->Text();
	}

	static BasicBuilder *CreateDecorator(Decorators id, BasicBuilder *prev);
};

class DecoratorHr : public Decorator {
public:
	DecoratorHr(BasicBuilder *dec) : Decorator(dec){}

	string Img() {
		string rez = Decorator::Img();
		if (rez[0])
			return"<hr>" + rez + "<hr>";
		return "";
	}
	string Video(int width = 480, int height = 360) {
		string rez = Decorator::Video();
		if (rez[0])
			return"<hr>" + rez + "<hr>";
		return "";
	}
	string Text() {
		string rez = Decorator::Text();
		if(rez[0])
			return"<hr>" + rez + "<hr>";
		return "";
	}
};

class DecoratorCenter : public Decorator {
public:
	DecoratorCenter(BasicBuilder *dec) : Decorator(dec) {}

	string Img() {
		string rez = Decorator::Img();
		if (rez[0])
			return"<center>" + rez + "</center>";
		return "";
	}
	string Video(int width = 480, int height = 360) {
		string rez = Decorator::Video();
		if (rez[0])
			return"<center>" + rez + "</center>";
		return "";
	}
	string Text() {
		string rez = Decorator::Text();
		if (rez[0])
			return"<center>" + rez + "</center>";
		return "";
	}
};

class Image_Site {
	string html;
public:
	Image_Site()
	{ 
		html = "";
	}

	void Html_Start()
	{
		html += string("<html>\n");
	}
	void Head_Start()
	{
		html += string("<head>\n");
	}
	void Title(string Title = "Title")
	{
		html += string("<title>") + Title + string("</title>\n");
	}
	void Head_End()
	{
		html += string("</head>\n");
	}
	void Body_Start()
	{
		html += string("<body>\n");
	}
	void Image(string Path = "path of img", string Alt = "alt text")
	{
		html += string("<img src=\"") + Path + string("\" alt=\"") + Alt + string("\">\n");
	}
	void Body_End()
	{
		html += string("</body>\n");
	}
	void Html_End()
	{
		html += string("</html>\n");
	}

	string GetHtml() 
	{
		return html;
	}
};

class AdapterImage_Site : public BasicBuilder {
	Image_Site site;
public:

	string Html(bool end = 0) {
		if (end) {
			site.Html_End();
			return site.GetHtml();
		}
		else
			site.Html_Start();
		return "";
	}
	string Head(bool end = 0) {
		if (end)
			site.Head_End();
		else
			site.Head_Start();
		return "";
	}
	string Body(bool end = 0) {
		if (end)
			site.Body_End();
		else
			site.Body_Start();
		return "";
	}
	string Title() {
		string title;
		cout << "Title: "; getline(cin, title);
		site.Title(title);
		return "";
	}
	string Img() {
		string src, alt;
		cout << "Img->Src: "; getline(cin, src);
		cout << "Img->Alt: "; getline(cin, alt);
		site.Image(src, alt);
		return "";
	}
	string Video(int width = 480, int height = 360) {
		return "";
	}
	string Text() {
		return "";
	}
};

BasicBuilder *BasicBuilder::CreateTemplate(Templates id) {
	switch (id)
	{
	case IdVideoViewer:
		return new VideoViewer;
	case IdImgViewer:
		return new ImgViewer;
	case IdTextViewer:
		return new TextViewer;
	}
	throw exception("Unknown id");
}

BasicBuilder *Decorator::CreateDecorator(Decorators id, BasicBuilder *prev) {
	switch (id)
	{
	case IdHr:
		return new DecoratorHr(prev);
	case IdCenter:
		return new DecoratorCenter(prev);
	}
	throw exception("Unknown id");
}

class HTMLBuilder {
public:
	string build(BasicBuilder *b) const {
		string html = "";
		html += b->Html() + "\n";
			html += b->Head() + "\n";
				html += b->Title() + "\n";
			html += b->Head(1) + "\n";

			html += b->Body() + "\n";
				html += b->Img() + "\n";
				html += b->Video() + "\n";
				html += b->Text() + "\n";
			html += b->Body(1) + "\n";
		html += b->Html(1);
		return html;
	}
};

class Site {
	string ip;
	string dnsName;
	string html;
public:
	Site() {
		ip = "192.168.1.155";
		dnsName = "localhost.loc";
	}

	void SetIp(string Ip) { ip = Ip; }
	void SetDnsName(string DnsName) { dnsName = DnsName; }

	string GetIp() const { return ip; }
	string GetDnsName() const { return dnsName; }

	void Open(char ** argv) {
		string pathToFile = argv[0];
		pathToFile.resize(pathToFile.find_last_of("\\") + 1);
		pathToFile += "curr.html";
		ofstream out(pathToFile);
		out << html;
		out.close();
		system(pathToFile.c_str());
		remove(pathToFile.c_str());
	}
	void Build(BasicBuilder *builder) {
		HTMLBuilder director;
		html = director.build(builder);
		//ofstream out;
		//out.close();
	}
};

class Server;
class _Server {
	vector <Site *> sites;
	string ip;
	string dnsName;
	char ** argv;
	_Server() {
		ip = "192.168.1.1";
		dnsName = "localhost";
	};
	_Server(_Server &rhs) {};
	_Server & operator=(_Server &rhs) {};
	friend class Server;
public:
	void SetIp(string Ip) { ip = Ip; }
	void SetDnsName(string DNS) { dnsName = DNS; }

	void SetArgv(char ** Argv) { argv = Argv; }

	void AddSite(Site *&site) {
		
		string siteIp = ip;
		siteIp.resize(siteIp.find_last_of('.') + 1);
		char lastStr[32];
		while (1) {
			int last = rand() % 250 + 10;
			_itoa(last, lastStr, 10);
			bool exit = 1;
			for (auto &i : sites)
				if (i->GetIp() == siteIp + lastStr)
					exit = 0;
			if (exit) {
				//cout << siteIp + lastStr << endl;
				siteIp += lastStr;
				break;
			}
		}

		site->SetIp(siteIp);
		site->SetDnsName(site->GetDnsName());

		sites.push_back(site);
		site = nullptr;
	}
	void OpenSite(const string DnsName) {
		bool find = 1;
		for (auto &i : sites) 
			if (DnsName == i->GetDnsName()) {
				i->Open(argv);
				find = 0;
			}
		if (find) {
			cout << "Cant open " << DnsName << endl;
		}
	}

	void Info() {
		cout << "Server info:" << endl;
		cout << "IP:\t\t" << ip << endl;
		cout << "DNS name:\t" << dnsName << endl << endl;
		cout << "Hosted sites:" << endl;
		for (auto &i : sites) {
			cout << i->GetDnsName() << endl;
			cout << "\t" << i->GetIp() << endl;
		}
	}

	~_Server() {
		for (auto &i : sites)
			delete i;
	}
};

class Server {
	static _Server *singletone;
public:
	_Server *Get() {
		if (singletone == nullptr)
			singletone = new _Server;
		return singletone;
	}
};
_Server* Server::singletone = nullptr;

int Menu(char cnt, char *First ...) {
	system("cls");
	char **first = nullptr;
	char choosen = 0;
	do {
		first = &First;
		cout << "w,s - move\nSpace - chose\n\n";
		for (char i = 0; i < cnt; ++i, ++first)
			cout << (i == choosen ? ">" : " ") << *first << endl;
		int in = _getch();
		switch (in) {
		case 's':
			++choosen;
			break;
		case 'w':
			--choosen;
			break;
		case VK_ESCAPE:
			exit(EXIT_SUCCESS);
			break;
		}
		if (choosen < 0)
			choosen = cnt - 1;
		else if (choosen == cnt)
			choosen = 0;
		system("cls");
		if (in == VK_SPACE)
			return choosen;
	} while (1);
}

int main(int argc, char ** argv) {
	atexit([]() {system("pause"); });
	srand(time(NULL));

	Server server;
	server.Get()->SetArgv(argv);
	server.Get()->SetIp("124.235.15.1");
	server.Get()->SetDnsName("builder.com");

	{
	char menu;
	do {
		menu = Menu(4, "Server Info", "Add site", "Open site", "Exit");
		switch (menu){
		case 0:
			server.Get()->Info();
		break;
		case 1:
		{
			cout << "Choose template:\n[1] - video\n[2] - img\n[3] - text\n[4] - adapted img\nid: ";
			Templates id; int tmp;
			do {
				cin >> tmp;
				if (tmp == 4)
					break;
			} while (tmp < 0 || tmp >= Templates::TEAMPLATES_END);
			cin.ignore();
			id = Templates(tmp);
			BasicBuilder *temp = nullptr;
			if (id != 4)
				temp = BasicBuilder::CreateTemplate(id);
			else
				temp = new AdapterImage_Site();

			cout << "Choose decorator:\n[1] - hr\n[2] - center\n[0] - none\nid: ";
			Decorators idDecor;
			do {
				cin >> tmp;
			} while (tmp < 0 || tmp >= Decorators::DECORATORS_END);
			cin.ignore();
			idDecor = (Decorators) tmp;
		
			if (idDecor)
				temp = Decorator::CreateDecorator(idDecor, temp);
			Site *s = new Site();
			s->Build(temp);
			string name;
			cout << "DnsName: "; getline(cin, name);
			s->SetDnsName(name);
			server.Get()->AddSite(s);
		}
		break;
		case 2:
		{
			string name;
			cout << "Site dns name: "; getline(cin, name);
			server.Get()->OpenSite(name);
		}
		break;
		}
		if(menu != 3)
			_getch();
	} while (menu != 3);
	}

	return EXIT_SUCCESS;
}
