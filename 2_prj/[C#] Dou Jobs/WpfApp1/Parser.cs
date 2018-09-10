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

        public Parser()
        {
            web = new HtmlWeb();
        }

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

        }

    }
}
