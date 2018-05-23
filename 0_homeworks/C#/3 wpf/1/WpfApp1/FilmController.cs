using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace WpfApp1{
    class FilmController{
		List<FilmInfo> filmInfo;

		public FilmController() {
			filmInfo = new List<FilmInfo>();
		}

		public void AddFilm(FilmInfo film) => filmInfo.Add(film);
		public int GetFilmCnt() => filmInfo.Count;
		public FilmInfo GetFilmById(int id) => filmInfo[id];
	}
}
