using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using HtmlAgilityPack;

namespace WpfApp1
{
    //https://jobs.dou.ua/vacancies/?category=.NET&search=Jun&city=Киев
    class Parser
    {
        HtmlWeb web;
        HtmlDocument doc;
        string mainUrl;

        List<Vacancy> list;

        public Parser()
        {
            web = new HtmlWeb();
            list = new List<Vacancy>(1000);
        }

        public List<Vacancy> GetList() => list;

        public void Parse(string category, string search, string city)
        {
            mainUrl = "https://jobs.dou.ua/vacancies/?";
            if (!category?.Equals("") ?? false)
                mainUrl += $"category={category}";
            if (!search?.Equals("") ?? false)
            {
                if (mainUrl.LastChar() != '?')
                    mainUrl += '&';
                mainUrl += $"search={search}";
            }
            if (!city?.Equals("") ?? false)
            {
                if (mainUrl.LastChar() != '?')
                    mainUrl += '&';
                mainUrl += $"city={city}";
            }

            doc = web.Load(mainUrl);


            using(VacancyContext db = new VacancyContext())
            {
                db.Vacancies.Add(new Vacancy() {Title="Job" });
                db.SaveChanges();
                System.Windows.MessageBox.Show(db.Vacancies.First().Title);
            }

        }

    }
}
