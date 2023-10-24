#ifndef __CONSOLE__
#define __CONSOLE__
#define CONSOLE_WIDTH 900
#define CONSOLE_HEIGHT 600
#include "resource.h"
#include <windows.h>
#include <conio.h>
#include <functional>



namespace app
{
	namespace console
	{
		typedef SHORT coord;

		class console
		{
			friend console& operator<<(console& con, std::function<void(console& con)>);
		public:
			/*
				Убираем copy constructor и copy assignment.
			 */
			console(const console&) = delete;
			void operator=(const console&) = delete;


			/*
				Перегрузка оператора для смены цвета последущих выведенных символов.
			 */
			console& operator<<(color __right);


			/*
				Перегрузки операторов для вывода на экран. Поддерживаемые типы: double, float, short, int, long, long long, char, bool, size_t.
			 */
			console& operator<<(std::string __right);
			console& operator<<(double __right);
			console& operator<<(float __right);
			console& operator<<(short __right);
			console& operator<<(int __right);
			console& operator<<(long __right);
			console& operator<<(long long __right);
			console& operator<<(char __right);

			/*
				Любый вывод const char* считается как bool, поэтому в обход этому - шаблон.
			 */
			template <typename _, typename T = std::enable_if_t<std::is_same<_, bool>()>> console& operator<<(_ __right)
			{
				return this->operator<<(std::string(__right ? "true" : "false"));
			}
			console& operator<<(size_t __right);


			/*
				Перегрузки операторов для ввода с клавиатуры. Поддерживаемые типы: double, float, short, int, long, long long, char, bool, size_t.
			 */
			console& operator>>(std::string& __right);
			console& operator>>(double& __right);
			console& operator>>(float& __right);
			console& operator>>(short& __right);
			console& operator>>(int& __right);
			console& operator>>(long& __right);
			console& operator>>(long long& __right);
			console& operator>>(char& __right);
			console& operator>>(bool& __right);
			console& operator>>(size_t& __right);

			/*
				Повторение строки горизонтально. Строка начинает выводиться с значения осей X и Y.

				x - значение оси X;
				y - значение оси Y;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void repeat(const coord x, const coord y, const std::string& __arg, const size_t t);


			/*
				Повторение символа горизонтально. Символ начинает выводиться с значения осей X и Y.

				x - значение оси X;
				y - значение оси Y;
				__arg - символ, который будет повторяться;
				t - количество повторений.
			 */
			void repeat(const coord x, const coord y, char __arg, const size_t t);


			/*
				Повторение строки горизонтально. Строка начинает выводиться с оси X. Ось Y зависит от текущей позиции курсора.

				x - значение оси X;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void repeat(const coord x, const std::string& __arg, const size_t t);


			/*
				Повторение символа горизонтально. Символ начинает выводиться с оси X. Ось Y зависит от текущей позиции курсора.

				x - значение оси X;
				__arg - символ, который будет повторяться;
				t - количество повторений.
			 */
			void repeat(const coord x, char __arg, const size_t t);


			/*
				Повторение строки горизонтально начиная текущей позиции курсора.

				__arg - строка, что будет повторяться;
				t - количество повторений.
			 */
			void repeat(const std::string& __arg, const size_t t);


			/*
				Повторение символа горизонтально начиная текущей позиции курсора.

				__arg - символ, что будет повторяться;
				t - количество повторений.
			 */
			void repeat(char __arg, const size_t t);


			/*
				Из-за неоднозначности преобразования из int в char - данный метод был вырезан.
			 */
			void repeat(int, const size_t) = delete;


			/*
				Повторение строки вертикально. Строка начинает выводиться с значения осей X и Y.

				x - значение оси X;
				y - значение оси Y;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(const coord x, const coord y, const std::string& __arg, const size_t t);


			/*
				Повторение символа вертикально. Символ начинает выводиться с значения осей X и Y.

				x - значение оси X;
				y - значение оси Y;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(const coord x, const coord y, char __arg, const size_t t);


			/*
				Повторение строки вертикально. Строка начинает выводиться с оси X. Ось Y зависит от текущей позиции курсора.

				x - значение оси X;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(const coord x, const std::string& __arg, const size_t t);


			/*
				Повторение символа вертикально. Символ начинает выводиться с оси X. Ось Y зависит от текущей позиции курсора.

				x - значение оси X;
				__arg - строка, которая будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(const coord x, char __arg, const size_t t);


			/*
				Повторение строки вертикально начиная текущей позиции курсора.

				__arg - строка, что будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(const std::string& __arg, const size_t t);


			/*
				Повторение символа вертикально начиная текущей позиции курсора.

				__arg - строка, что будет повторяться;
				t - количество повторений.
			 */
			void vrepeat(char __arg, const size_t t);

			/*
				Из-за неоднозначности преобразования из int в char - данный метод был вырезан.
			 */
			void vrepeat(int, const size_t) = delete;


			/*
				Повторение строки по диагонали начиная заданных координат.

				x - значение оси X;
				y - значение оси Y;
				__arg - строка, что будет повторяться;
				t - количество повторений;
				direction - направление: NW - северо-запад; NE - северо-восток; SW - юго-запад; SE - юго-восток.


				NW (северо-запад)

				//
				//  *
				//   *
				//    *
				//     0
				//
				//
				//

				NE (северо-восток)

				//
				//       *
				//      *
				//     *
				//    0
				//
				//
				//

				SE (юго-восток)

				//
				//
				//
				//
				//    0
				//     *
				//      *
				//       *

				SE - (юго-восток)
				//
				//
				//
				//    0
				//   *
				//  *
				// *
			 */
			void drepeat(const coord x, const coord y, const std::string& __arg, const size_t t, diag_direction direction);

			/*
				Ставит курсор на заданную позицию.

				x - ось X;
				y - ось Y;
			 */
			void scpos(const coord x, const coord y);


			/*
				Сохраняет текущую позицию курсора. Можно будет вернуться к этой позиции через rcpos.
			 */
			void svcpos();


			/*
				Ставит курсор на ранее сохранённую позицию от svcpos.
			 */
			void rcpos();


			/*
				Получает текущие координаты курсора. Если нужна только одна ось, то можно передать nullptr.

				x - пустое значение оси X, в которое будет записано значение;
				y - пустое значение оси Y, в которое будет записано значение;
			 */
			void gcpos(coord* x, coord* y);


			/*
				Передвигает курсор вверх по оси Y. 
			 */
			void mvup();


			/*
				Передвигает курсор вправо по оси X.
			 */
			void mvright();


			/*
				Передвигает курсор вниз по оси Y.
			 */
			void mvdown();


			/*
				Передвигает курсор влево по оси X.
			 */
			void mvleft();


			/*
				Ставит курсор по оси X на нулевое положение.
			 */
			void mvx0();


			/*
				Возвращает курсор по оси Y на нулевое положение.
			 */
			void mvy0();


			/*
				Возвращает курсор по оси X и Y на нулевое положение.
			 */
			void mvxy0();


			/*
				На заданной координате вставляет строку.

				x - ось X;
				y - ось Y;
				__arg - сама строка.
			 */
			void at(const coord x, const coord y, const std::string& __arg);


			/*
				Считывает всё введённое с клавиатуры.

				read_length - лимит симолов на считывание (опционально). Если установить к примеру 4, то нельзя будет ввести больше 4 символов.
			 */
			std::string read(size_t read_length = std::string::npos);


			/*
				Считывает и возвращает один введённый символ с клавиаутры как enum.
			 */
			key readk();


			/*
				Заставляет пользователя ввести заданный символ. Пока ввод нужного символа не будет осуществлён, программа будет заморожена.

				k - символ, который пользователь должен ввести.
			 */
			void readk(key k);


			/*
				Заставляет пользователя ввести заданный(ые) символ(ы) по предикату. Предикат, т.е указатель на функцию имеет параметр типа key и должен возвращать bool.

				predicate - предикат (указатель на функцию, возвращающий bool).
			 */
			key readk(bool(*predicate)(key k));


			/*
				Возвращает символ, который находится на текущих координатах.
			 */
			char grabch();


			/*
				Возвращает символ, который находится на координатах, которые установлены условным пользователем (программистом).

				x - значение оси X;
				y - значение оси Y.
			 */
			char grabch(coord x, coord y);


			/*
				Стирает один символ на заданных координатах.

				x - значение оси X;
				y - значение оси Y.
			 */
			void erase(coord x, coord y);


			/*
				Стирает N-ое количество символов начиная с заданных координат.

				x - значение оси X;
				y - значение оси Y;
				count - количество символов для удаления.
			 */
			void erase(coord x, coord y, size_t count);


			/* (get boundary)
				Получае максимальные значения оси Х и Y. Можно выбрать только одну ось, другой передав nullptr. К примеру io.getbnd(&x, nullptr);.

				x - значение оси X;
				y - значение оси Y;
			 */

			void getbnd(coord* x, coord* y);

			/*
				...
			 */
			static console& get();
			static console& get(int width, int height);
		private:
			console();
			console(int width, int height);
			HANDLE stdhandle;
			HWND window;
			coord sx;
			coord sy;
			int readch();
		};
		extern console& io;
	}
}
#endif
