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
		public FilmInfo[] GetFilmsArray(int idFirst, int length) {
			FilmInfo[] rez = new FilmInfo[length];
			int i = 0;
			int shift = 0;

			if (idFirst == -1) {
				idFirst = 0;
				shift = 1;
				rez[0] = filmInfo[filmInfo.Count - 1];
			}

			for (; i + shift < length; ++i)
				rez[i + shift] = filmInfo[(i + idFirst) % filmInfo.Count] ;
			return rez;
		}
	}
}
