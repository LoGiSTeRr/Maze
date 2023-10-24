#include "console.h"
#include <sstream>

namespace app
{
	namespace console
	{
		console& operator<<(console& con, std::function<void(console& con)> manip)
		{
			manip(con);

			return con;
		}

		template<typename T> T ssconverter(std::string in)
		{
			std::stringstream ss(in);

			T out;

			ss >> out;

			return out;
		}

		console& console::operator<<(color __right)
		{
			SetConsoleTextAttribute(this->stdhandle, static_cast<WORD>(__right));

			return *this;
		}

		console& console::operator<<(std::string __right)
		{
			WriteConsoleA(this->stdhandle, __right.c_str(), __right.size(), NULL, NULL);

			return *this;
		}

		console& console::operator<<(double __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(float __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(short __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(int __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(long __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(long long __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator<<(char __right)
		{
			WriteConsoleA(this->stdhandle, &__right, 1, NULL, NULL);

			return *this;
		}

		console& console::operator<<(size_t __right)
		{
			return *this << std::to_string(__right);
		}

		console& console::operator>>(std::string& __right)
		{
			__right.assign(this->read());

			return *this;
		}

		console& console::operator>>(double& __right)
		{
			__right = ssconverter<double>(this->read());

			return *this;
		}

		console& console::operator>>(float& __right)
		{
			__right = ssconverter<float>(this->read());

			return *this;
		}

		console& console::operator>>(short& __right)
		{
			__right = ssconverter<short>(this->read());

			return *this;
		}

		console& console::operator>>(int& __right)
		{
			__right = ssconverter<int>(this->read());

			return *this;
		}

		console& console::operator>>(long& __right)
		{
			__right = ssconverter<long>(this->read());

			return *this;
		}

		console& console::operator>>(long long& __right)
		{
			__right = ssconverter<long long>(this->read());

			return *this;
		}

		console& console::operator>>(char& __right)
		{
			auto read = this->read();

			if (read.length() > 0)
			{
				__right = read[0];
			}

			return *this;
		}

		console& console::operator>>(size_t& __right)
		{
			__right = ssconverter<size_t>(this->read());

			return *this;
		}

		console& console::operator>>(bool& __right)
		{
			__right = ssconverter<bool>(this->read());

			return *this;
		}

		void console::repeat(const coord x, const coord y, const std::string& __arg, const size_t t)
		{
			coord _x = x;

			for (size_t i = 0; i < t; i++)
			{
				this->scpos(_x, y);
				*this << __arg;
				_x += __arg.length();
			}
		}

		void console::repeat(const coord x, const coord y, char __arg, const size_t t)
		{
			coord _x = x;

			for (size_t i = 0; i < t; i++)
			{
				this->scpos(_x, y);
				*this << __arg;
				_x++;
			}
		}

		void console::repeat(const coord x, const std::string& __arg, const size_t t)
		{
			coord y;

			this->gcpos(nullptr, &y);
			this->repeat(x, y, __arg, t);
		}

		void console::repeat(const coord x, char __arg, const size_t t)
		{
			coord y;

			this->gcpos(nullptr, &y);
			this->repeat(x, y, __arg, t);
		}

		void console::repeat(const std::string& __arg, const size_t t)
		{
			for (size_t i = 0; i < t; i++)
			{
				*this << __arg;
			}
		}

		void console::repeat(char __arg, const size_t t)
		{
			for (size_t i = 0; i < t; i++)
			{
				*this << __arg;
			}
		}

		void console::vrepeat(const coord x, const coord y, const std::string& __arg, const size_t t)
		{
			coord _y = y;

			for (size_t i = 0; i < t; i++)
			{
				this->scpos(x, _y);
				*this << __arg;
				_y++;
			}
		}

		void console::vrepeat(const coord x, const coord y, char __arg, const size_t t)
		{
			coord _y = y;

			for (size_t i = 0; i < t; i++)
			{
				this->scpos(x, _y);
				*this << __arg;
				_y++;
			}
		}

		void console::vrepeat(const coord x, const std::string& __arg, const size_t t)
		{
			coord y;

			this->gcpos(nullptr, &y);
			this->vrepeat(x, y, __arg, t);
		}

		void console::vrepeat(const coord x, char __arg, const size_t t)
		{
			coord y;

			this->gcpos(nullptr, &y);
			this->vrepeat(x, y, __arg, t);
		}

		void console::vrepeat(const std::string& __arg, const size_t t)
		{
			this->vrepeat(0, __arg, t);
		}

		void console::vrepeat(char __arg, const size_t t)
		{
			this->vrepeat(0, __arg, t);
		}

		void console::drepeat(const coord x, const coord y, const std::string& __arg, const size_t t, diag_direction direction)
		{

			coord _x = x;
			coord _y = y;
			auto output_size = static_cast<coord>(__arg.size());


			switch (direction)
			{
				case diag_direction::NW:
				{
					for (size_t i = 0; i < t; i++)
					{
						if (_x - output_size < -1 || _y < 0)
						{
							break;
						}

						this->scpos(_x, _y);
						*this << __arg;

						_x -= output_size;
						_y--;

					}

					break;
				}

				case diag_direction::NE:
				{
					coord xbnd;

					this->getbnd(&xbnd, nullptr);

					for (size_t i = 0; i < t; i++)
					{
						if (_x + output_size > xbnd || _y < 0)
						{
							break;
						}

						this->scpos(_x, _y);
						*this << __arg;

						_x += output_size;
						_y--;

					}

					break;
				}

				case diag_direction::SE:
				{
					coord xbnd;
					coord ybnd;

					this->getbnd(&xbnd, &ybnd);

					for (size_t i = 0; i < t; i++)
					{
						if (_x + output_size > xbnd || _y + 1 > ybnd)
						{
							break;
						}

						this->scpos(_x, _y);
						*this << __arg;

						_x += output_size;
						_y++;

					}

					break;
				}

				case diag_direction::SW:
				{
					coord ybnd;

					this->getbnd(nullptr, &ybnd);

					for (size_t i = 0; i < t; i++)
					{
						if (_x - output_size < 0 || _y + 1 > ybnd)
						{
							break;
						}

						this->scpos(_x, _y);
						*this << __arg;

						_x -= output_size;
						_y++;

					}
				}
			}
		}

		void console::scpos(const coord x, const coord y)
		{
			SetConsoleCursorPosition(this->stdhandle, { x, y });
		}

		void console::svcpos()
		{
			this->gcpos(&this->sx, &this->sy);
		}

		void console::rcpos()
		{
			this->scpos(this->sx, this->sy);
		}

		void console::gcpos(coord* x, coord* y)
		{
			CONSOLE_SCREEN_BUFFER_INFO info;

			GetConsoleScreenBufferInfo(this->stdhandle, &info);

			if (x != nullptr)
			{
				*x = info.dwCursorPosition.X;
			}

			if (y != nullptr)
			{
				*y = info.dwCursorPosition.Y;
			}
		}

		void console::mvup()
		{
			coord x;
			coord y;

			this->gcpos(&x, &y);

			if (y != 0)
			{
				this->scpos(x, y - 1);
			}
		}

		void console::mvright()
		{
			coord x;
			coord y;
			coord xbnd;

			this->getbnd(&xbnd, nullptr);
			this->gcpos(&x, &y);

			if (x != xbnd)
			{
				this->scpos(x + 1, y);
			}
		}

		void console::mvdown()
		{
			coord x;
			coord y;

			this->gcpos(&x, &y);
			this->scpos(x, y + 1);
		}

		void console::mvleft()
		{
			coord x;
			coord y;

			this->gcpos(&x, &y);

			if (x != 0)
			{
				this->scpos(x - 1, y);
			}
		}

		void console::mvx0()
		{
			coord y;

			this->gcpos(nullptr, &y);
			this->scpos(0, y);
		}

		void console::mvy0()
		{
			coord x;

			this->gcpos(&x, nullptr);
			this->scpos(x, 0);
		}

		void console::mvxy0()
		{
			this->scpos(0, 0);
		}

		void console::at(const coord x, const coord y, const std::string& __arg)
		{
			this->svcpos();
			this->scpos(x, y);
			*this << __arg;
			this->rcpos();
		}

		console& console::get()
		{
			static console instance;

			return instance;
		}

		console& console::get(int width, int height)
		{
			static console instance(width, height);

			return instance;
		}

		std::string console::read(size_t read_length)
		{
			std::string _out;
			auto flag = true;
			size_t lim = 0;

			do
			{
				auto rawk = this->readch();
				auto k = static_cast<key>(rawk);
				auto symbol = static_cast<char>(rawk);

				switch (k)
				{
					case key::ESCAPE:
					{
						return std::string();
					}
					case key::ENTER:
					{
						if (_out.size() != 0)
						{
							flag = false;
						}

						break;
					}
					case key::TAB:
					{
						if (lim + 4 <= read_length)
						{
							for (size_t i = 0; i < 4; i++)
							{
								_out.push_back(' ');
								*this << ' ';
								lim++;
							}
						}

						break;
					}
					case key::BACKSPACE:
					{
						if (_out.size() == 0)
						{
							break;
						}

						coord _x;
						coord _y;
						coord _bx;

						this->getbnd(&_bx, nullptr);
						this->gcpos(&_x, &_y);
						static auto endtrigger = true;

						//Пофикси BACKSPACE 
						if (_x == 0)
						{
							this->scpos(_bx - 1, _y - 1);
							this->erase(_bx - 1, _y - 1);
						}
						else
						{
							if (_x == _bx - 1 && endtrigger)
							{
								this->scpos(_bx - 1, _y);
								this->erase(_bx - 1, _y);
								endtrigger = false;
							}
							else
							{
								this->scpos(_x - 1, _y);
								this->erase(_x - 1, _y);
							}
							lim--;
						}

						_out.pop_back();

						break;
					}
					default:
					{
						if (lim + 1 <= read_length)
						{
							coord _x;
							coord _y;

							this->gcpos(&_x, &_y);
							_out.push_back(symbol);
							*this << symbol;
							lim++;
						}
					}
				}
			} while (flag);

			return _out;
		}

		key console::readk()
		{
			return static_cast<key>(this->readch());
		}

		void console::readk(key k)
		{
			do
			{
				if (this->readk() == k)
				{
					break;
				}
			} while (true);
		}

		key console::readk(bool(*predicate)(key k))
		{
			do
			{
				auto k = this->readk();

				if (predicate == nullptr)
				{
					return k;
				}
				if (predicate(k))
				{
					return k;
				}

			} while (true);
		}

		char console::grabch()
		{
			TCHAR s;
			CONSOLE_SCREEN_BUFFER_INFO info;
			DWORD cbRead = 0;

			GetConsoleScreenBufferInfo(this->stdhandle, &info);

			coord x;
			coord y;

			this->gcpos(&x, &y);

			auto res = ReadConsoleOutputCharacter(this->stdhandle, &s, 1, { x, y }, &cbRead);

			if (res)
			{
				return s;
			}

			return '\0';
		}

		char console::grabch(coord x, coord y)
		{
			TCHAR s;
			DWORD cbRead = 0;

			auto res = ReadConsoleOutputCharacter(this->stdhandle, &s, 1, { x, y }, &cbRead);

			if (res)
			{
				return s;
			}

			return '\0';
		}

		void console::erase(coord x, coord y)
		{
			this->erase(x, y, 1);
		}

		void console::erase(coord x, coord y, size_t count)
		{
			COORD coord = { x, y };
			DWORD written;

			FillConsoleOutputCharacter(this->stdhandle, ' ', count, coord, &written);
			FillConsoleOutputAttribute(this->stdhandle, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE, count, coord, &written);
		}

		void console::getbnd(coord* x, coord* y)
		{
			CONSOLE_SCREEN_BUFFER_INFO info;

			GetConsoleScreenBufferInfo(this->stdhandle, &info);

			if (x != nullptr)
			{
				*x = info.dwSize.X;
			}

			if (y != nullptr)
			{
				*y = info.dwSize.Y;
			}
		}

		//private
		console::console(int width, int height) : stdhandle(GetStdHandle(STD_OUTPUT_HANDLE)), window(GetConsoleWindow()), sx(0), sy(0)
		{
			::setlocale(0, "");

			SetWindowLong(this->window, GWL_STYLE, GetWindowLong(this->window, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);

			CONSOLE_CURSOR_INFO info;
			RECT rect;

			GetWindowRect(this->window, &rect);
			MoveWindow(this->window, rect.left, rect.top, width, height, TRUE);
			GetConsoleCursorInfo(this->stdhandle, &info);
			info.bVisible = FALSE;
			SetConsoleCursorInfo(this->stdhandle, &info);
		}

		console::console() : console(CONSOLE_WIDTH, CONSOLE_HEIGHT) {}

		int console::readch()
		{
			return ::_getch();
		}

		console& io = console::get();
	}
}