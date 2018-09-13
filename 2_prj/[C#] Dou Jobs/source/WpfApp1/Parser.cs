using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using HtmlAgilityPack;

namespace WpfApp1 {
	//https://jobs.dou.ua/vacancies/?category=.NET&search=Jun&city=Киев
	class Parser {
		HtmlWeb web;
		HtmlDocument doc;
		string mainUrl;

		List<Vacancy> parsed;

		public List<Vacancy> Parsed => parsed;

		public Parser() {
			web = new HtmlWeb();
			parsed = new List<Vacancy>(20);
		}

		public void Parse(string category, string search, string city) {
			parsed.Clear();

			mainUrl = "https://jobs.dou.ua/vacancies/?";
			if (!category?.Equals("") ?? false)
				mainUrl += $"category={category}";
			if (!search?.Equals("") ?? false) {
				if (mainUrl.LastChar() != '?')
					mainUrl += '&';
				mainUrl += $"search={search}";
			}
			if (!city?.Equals("") ?? false) {
				if (mainUrl.LastChar() != '?')
					mainUrl += '&';
				mainUrl += $"city={city}";
			}

			doc = web.Load(mainUrl);

			var vacancyNodes = doc.GetElementbyId("vacancyListId").Descendants("div").Where((a) => a.HasClass("vacancy"));

			Vacancy vacancy;
			HtmlNode titleNode, aNode;

			foreach (var vacancyDiv in vacancyNodes) {
				vacancy = new Vacancy();
				/*
				<div class="vacancy" _id="73959">
					<div class="title">
						<a class="vt" href="https://jobs.dou.ua/companies/fiducia-software/vacancies/73959/?from=list_hot">PHP developer (Google partner project)</a>

						<strong>в
							<a class="company" href="https://jobs.dou.ua/companies/fiducia-software/vacancies/?from=list_hot">
								<img>FiduciaSoft
							</a>
						</strong>
						<span class="salary">$1000–2000</span>
						<span class="cities">Киев</span>
					</div>

					<div class="sh-info">
						DESCRIPTION
					</div>
				</div>
				*/
				try {
					vacancy.IdDou = vacancyDiv.GetAttributeValue("_id", 1);
					vacancy.ShortDescription = vacancyDiv.ChildNodes.FirstOrDefault((a) => a.HasClass("sh-info"))?.InnerText?.Trim()?.ClearFromHTML();

					titleNode = vacancyDiv.ChildNodes.FirstOrDefault((a) => a.HasClass("title"));
					aNode = titleNode.ChildNodes.FindFirst("a");

					vacancy.Title = aNode.InnerText;
					vacancy.Link = aNode.GetAttributeValue("href", null);
					if (vacancy.Link != null) {
						short len = (short)(vacancy.Link.IndexOf('?'));
						if (len > 0)
							vacancy.Link = vacancy.Link.Substring(0, len);
					}

					vacancy.Company = titleNode.ChildNodes.FindFirst("strong").ChildNodes.FindFirst("a").InnerText.ClearFromHTML();

					vacancy.City = titleNode.ChildNodes.FirstOrDefault((a) => a.HasClass("cities"))?.InnerText?.ClearFromHTML();
					vacancy.Salary = titleNode.ChildNodes.FirstOrDefault((a) => a.HasClass("salary"))?.InnerText?.ClearFromHTML();

					vacancy.Date = null;

					System.Windows.Application.Current.Dispatcher.Invoke(() => {
						parsed.Add(vacancy);
						if (VacancyContext.db.Vacancies.FirstOrDefault((a) => a.IdDou == vacancy.IdDou) == null)
							VacancyContext.db.Vacancies.Add(vacancy);
					});
				}
				catch (Exception ex) {
					if (System.Windows.MessageBox.Show($"{ex.Message}\n\n{ex.StackTrace}", "Error", System.Windows.MessageBoxButton.OKCancel) == System.Windows.MessageBoxResult.Cancel)
						break;
				}
			}

			System.Windows.Application.Current.Dispatcher.Invoke(() => VacancyContext.db.SaveChanges());
			System.Windows.MessageBox.Show("Done parsing!");
		}

	}
}
