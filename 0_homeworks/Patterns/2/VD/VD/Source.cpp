#include <iostream>
using namespace std;

#include <vector>
#include <algorithm>

//class Item {
//protected:
//	string name;
//public:
//	void SetName(string Name) { name = Name; }
//	string GetName() const { return name; }
//};
//
//class AGift {
//protected:
//	Item item;
//	string congratulations;
//public:
//	void SetItem(Item item) { this->item = item; }
//	void SetCongratulations(string Congratulations) { congratulations = Congratulations; }
//
//	string GetInfo() {
//		string rez;
//		rez = congratulations + string("\nGift: ") + item.GetName();
//		return rez;
//	}
//};
//
//class AFactoryGift {
//public:
//	virtual AGift * CreateGift() = 0;
//};
//
//class FactoryGiftPens : public AFactoryGift {
//public:
//	AGift * CreateGift(){
//		AGift *gift = new AGift;
//		Item giftItem;
//		giftItem.SetName("Pens");
//		gift->SetCongratulations("Congratulations!!!");
//		gift->SetItem(giftItem);
//		return gift;
//	}
//};
//
//class FactoryGiftNotepad : public AFactoryGift {
//public:
//	AGift * CreateGift() {
//		AGift *gift = new AGift;
//		Item giftItem;
//		giftItem.SetName("Notepad");
//		gift->SetCongratulations("Congratulations!!!");
//		gift->SetItem(giftItem);
//		return gift;
//	}
//};
//
//class FactoryGiftGlobus : public AFactoryGift {
//public:
//	AGift * CreateGift() {
//		AGift *gift = new AGift;
//		Item giftItem;
//		giftItem.SetName("Globus");
//		gift->SetCongratulations("Congratulations!!!");
//		gift->SetItem(giftItem);
//		return gift;
//	}
//};
//
//class FactoryGiftStationery : public AFactoryGift {
//public:
//	AGift * CreateGift() {
//		AGift *gift = new AGift;
//		Item giftItem;
//		giftItem.SetName("Stationery");
//		gift->SetCongratulations("Congratulations!!!");
//		gift->SetItem(giftItem);
//		return gift;
//	}
//};
//
//class ASocialNetwork {
//protected:
//	string name;
//public:
//	void SetName(string &Name) { name = Name; }
//	string GetName() const { return name; }
//};
//
//class AFactorySocialNetwork {
//	virtual ASocialNetwork * CreateSocialNetwork() = 0;
//};
//
//enum HairColors{Black, White, HairColorsEnd};
//
//class Person {
//protected:
//	string name;
//	bool isMale;
//	HairColors hairColor;
//public:
//	void SetName(const string &Name) { name = Name; }
//	void SetIsMale(const bool &IsMale) { isMale = IsMale; }
//	void SetHairColor(const HairColors &HairColor) { hairColor = HairColor; }
//
//	string GetName() const { return name; }
//	bool GetIsMale() const { return isMale; }
//	HairColors GetHairColor() const {return hairColor;}
//
//	void GenerateRandomName() {
//		char golosni[] = "aaaeeeiiouyy";
//		char prigolosni[] = "bbbcdddffgghjkllmmmnnnppqrrssstttvwxz";
//		char newName[40] = "";
//		char nameLenght = rand() % 10 + 2;
//		bool isprigolosna = 1;
//		for (int i = 0; i < nameLenght; i++) {
//			if (isprigolosna == 1) {
//				if (rand() % 100 < 10) {
//					strncat(newName, &prigolosni[rand() % 37], 1);
//					strncat(newName, &prigolosni[rand() % 37], 1);
//					i++;
//				}
//				else {
//					strncat(newName, &prigolosni[rand() % 37], 1);
//				}
//				isprigolosna = 0;
//			}
//			else {
//				if (rand() % 100 < 10) {
//					strncat(newName, &golosni[rand() % 12], 1);
//					strncat(newName, &golosni[rand() % 12], 1);
//					i++;
//				}
//				else {
//					strncat(newName, &golosni[rand() % 12], 1);
//				}
//				isprigolosna = 1;
//			}
//		}
//
//		SetName(newName);
//	}
//};
//
//class SchoolPerson : public Person {
//	AGift * gift;
//	ASocialNetwork *socialNetwork;
//public:
//	void GetGift(AGift *Gift) { gift = Gift; }
//
//	void PostAboutGift();
//};
//
//class SchoolClass {
//
//};
//
//class AFactorySchoolClass {
//
//};

/*
1.(Задача День Валентина) Є два 11-х класи в першому навчаються брюнети хлопці та блондинки дівчата, в другому ж навпаки, 
блондини хлопці та брюнетки дівчата. На День Святого Валентина ці класи замовили подарунки на фабриці шкільного приладдя 
і щоб заощадити на доставці вирішили упакувати всі подарунки (набори ручок,набори канцелярського приладдя, блокноти,
глобуси,) в одну коробку. Зробіть щоб учні були щасливими: роздайте подарунки та дозвольте учням зробити пости про свої 
подарунки у своїх соцмережах. Блондини у фейсбуці, брюнети у контакті. Передбачити можливість розширення функціоналу 
програми (більше кольорів, типів подарунків, соц мереж).
*/

//-----------------------------------------

class ASocialNetwork {
public:
	virtual void Info() = 0;
};

class Facebook : public ASocialNetwork {
public:
	void Info() {
		cout << "Facebook" << endl;
	}
};

class VKontacte : public ASocialNetwork {
public:
	void Info() {
		cout << " VKontacte" << endl;
	}
};

class SocialNetworkFactory {
public:
	virtual ASocialNetwork * Create() = 0;
};

class FacebookFactory {
public:
	ASocialNetwork * Create() {
		return new Facebook;
	}
};

class VKontacteFactory {
public:
	ASocialNetwork * Create() {
		return new VKontacte;
	}
};

//-----------------------------------------

class Hair {
protected:
	ASocialNetwork * usedSocialNetwork;
public:
	void SetUsedSocialNetwork(ASocialNetwork * UsedSocialNetwork) {
		usedSocialNetwork = UsedSocialNetwork;
	}

	virtual void PostInSocialNetwork() = 0;
};

class WhiteHair : public Hair {
public:
	void PostInSocialNetwork() {
		cout << "Post in ";
		usedSocialNetwork->Info();
	}
};

class BlackHair : public Hair {
public:
	void PostInSocialNetwork() {
		cout << "Post in";
		usedSocialNetwork->Info();
	}
};

class HairFactory {
public:
	virtual Hair * Create() = 0;
};

class WhiteHairFactory {
public:
	Hair * Create() {
		WhiteHair *hair = new WhiteHair;
		FacebookFactory ff;
		hair->SetUsedSocialNetwork(ff.Create());
		return hair;
	}
};

class BlackHairFactory {
public:
	Hair * Create() {
		BlackHair *hair = new BlackHair;
		VKontacteFactory vkf;
		hair->SetUsedSocialNetwork(vkf.Create());
		return hair;
	}
};

//-----------------------------------------

class AGift {
public:
	virtual void info() = 0;
};

class GiftPens : public AGift {
public:
	void info() {
		cout << "Pens" << endl;
	}
};

class GiftNotepads : public AGift {
public:
	void info() {
		cout << "Notepads" << endl;
	}
};

class GiftGlobus : public AGift {
public:
	void info() {
		cout << "Globus" << endl;
	}
};

class GiftStationery : public AGift {
public:
	void info() {
		cout << "Stationery" << endl;
	}
};

class AGiftFactory {
public:
	enum GiftId { Pens, Notepads, Stationery, Globus, GiftIdEnd };


	virtual AGift * Create() = 0;

	static AGift *CreateGift(GiftId id);
};
AGift *AGiftFactory::CreateGift(GiftId id) {
	switch (id)
	{
	case Pens:
		return new GiftPens();
	case Notepads:
		return new GiftNotepads;
	case Stationery:
		return new GiftStationery;
	case Globus:
		return new GiftGlobus;
	default:
		throw exception("Error. Unknown id in AGift *AGiftFactory::CreateGift(GiftId id)");
	}
}


class GiftFactoryPens {
public:
	virtual AGift * Create() {
		return new GiftPens;
	}
};

class GiftFactoryNotepads {
public:
	virtual AGift * Create() {
		return new GiftNotepads;
	}
};

class GiftFactoryStationery {
public:
	virtual AGift * Create() {
		return new GiftStationery;
	}
};

class GiftFactoryGlobus {
public:
	virtual AGift * Create() {
		return new GiftGlobus;
	}
};

//-----------------------------------------

class Human {
	AGift *gift;
public:
	virtual void info() = 0;
	virtual void Post() = 0;
	void GetGift(AGift *Gift) {gift = Gift;}
	void infoGift() { cout << "Gift: "; gift->info(); }
};

class Boy : public Human {
};

class Girl : public Human {
};

class WhiteBoy : public Boy, public WhiteHair {
public:
	void info() {
		cout << "White Boy ";
	}
	void Post() {
		this->PostInSocialNetwork();
	}
};

class BlackBoy : public Boy, public BlackHair {
public:
	void info() {
		cout << "Black Boy ";
	}
	void Post() {
		this->PostInSocialNetwork();
	}
};

class WhiteGirl : public Girl, public WhiteHair {
public:
	void info() {
		cout << "White Girl ";
	}
	void Post() {
		this->PostInSocialNetwork();
	}
};

class BlackGirl : public Girl, public BlackHair {
public:
	void info() {
		cout << "Black Girl ";
	}
	void Post() {
		this->PostInSocialNetwork();
	}
};


class BoyFactory {
public:
	virtual Boy * Create() = 0;
};

class GirlFactory {
public:
	virtual Girl * Create() = 0;
};

class WhiteBoyFactory : public BoyFactory {
public:
	Boy * Create() {
		WhiteBoy * boy = new WhiteBoy;
		FacebookFactory ff;
		boy->SetUsedSocialNetwork(ff.Create());
		return boy;
	}
};

class BlackBoyFactory : public BoyFactory {
public:
	Boy * Create() {
		BlackBoy * boy = new BlackBoy;
		VKontacteFactory ff;
		boy->SetUsedSocialNetwork(ff.Create());
		return boy;
	}
};

class WhiteGirlFactory : public GirlFactory {
public:
	Girl * Create() {
		WhiteGirl * boy = new WhiteGirl;
		FacebookFactory ff;
		boy->SetUsedSocialNetwork(ff.Create());
		return boy;
	}
};

class BlackGirlFactory : public GirlFactory {
public:
	Girl * Create() {
		BlackGirl * boy = new BlackGirl;
		VKontacteFactory ff;
		boy->SetUsedSocialNetwork(ff.Create());
		return boy;
	}
};

//-----------------------------------------

class SchoolClassFactory {
protected:
	BoyFactory * bf;
	GirlFactory *gf;
public:
	virtual Boy * CreateBoy() = 0;
	virtual Girl * CreateGirl() = 0;
};

class Factory11A : public  SchoolClassFactory {
public:
	Factory11A() {
		bf = new WhiteBoyFactory;
		gf = new BlackGirlFactory;
	}
	Boy * CreateBoy() {
		return bf->Create();
	}
	Girl * CreateGirl() {
		return gf->Create();
	}
};

class Factory11B : public  SchoolClassFactory {
public:
	Factory11B() {
		bf = new BlackBoyFactory;
		gf = new WhiteGirlFactory;
	}
	Boy * CreateBoy() {
		return bf->Create();
	}
	Girl * CreateGirl() {
		return gf->Create();
	}
};

class SchoolClass {
	unsigned size;
	vector <Human *> childrens;
public:
	SchoolClass(unsigned Size = 10) {
		size = Size;
	}
	~SchoolClass() {
		for (auto &i : childrens)
			delete i;
	}

	//SchoolClass &operator=(SchoolClass &rhs) = delete;
	//SchoolClass &operator=(SchoolClass &rhs) = default;

	virtual void Fill(SchoolClassFactory *factory) {
		for (unsigned i = 0; i < size; ++i)
			if (rand() % 2)
				childrens.push_back(factory->CreateBoy());
			else
				childrens.push_back(factory->CreateGirl());
	}
	void Gift() {
		for (auto &i : childrens)
			i->GetGift(AGiftFactory::CreateGift(AGiftFactory::GiftId( rand() % AGiftFactory::GiftId::GiftIdEnd )));
	}
	void info() {
		for (auto &i : childrens) {
			i->info(); 
			i->Post();
			i->infoGift();
		}
	}
};

//------------------------------------------

int main() {
	const unsigned char size = 2;
	SchoolClass school[size];
	SchoolClassFactory *factory[size] = {new Factory11A, new Factory11B};

	for (unsigned char i = 0; i < size; ++i) {
		if(i)
			cout << "========================================" << endl;
		cout << "\t Class " << (int) i << endl;
		school->Fill(factory[i]);
		school->Gift();
		school->info();
	}

	system("pause");
	return EXIT_SUCCESS;
}