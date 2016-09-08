#include <array>
#include <vector>
#include <exception>
#include <iostream>
#include <fstream>

std::array<std::array<short, 9>, 9> board;

struct Exactcover {
	std::vector<std::vector<bool>> cover;
	int num_rows;
	int num_cols;
	bool *active_rows;
	bool *active_cols;

	Exactcover(int rows, int cols)
		: num_rows(rows)
		, num_cols(cols)
	{
		cover.resize(rows);
		for (std::vector<bool> iter : cover)
			iter.resize(cols, false);
		active_rows = new bool[rows]{true};
		active_cols = new bool[cols]{true};
	}

	bool getcell(int row, int col) {
		if (!active_rows[row]) {
			if (!active_cols[col])
				throw std::exception("Row and Col not active");
			throw std::exception("Row not active");
		}
		else if (!active_cols[col])
			throw std::exception("Col not active");

		return cover[row][col];
	}

	void addrow(int row) {
		if (active_rows[row]) throw std::exception("Row already added");
		active_rows[row] = true;
	}
	void addcol(int col) {
		if (active_cols[col]) throw std::exception("Col already added");
		active_cols[col] = true;
	}
	void removerow(int row) {
		if (!active_rows[row]) throw std::exception("Row already removed");
		active_rows[row] = false;
	}
	void removecol(int col) {
		if (!active_cols[col]) throw std::exception("Col already removed");
		active_cols[col] = false;
	}
} *exactcover;

#define ROWS 730 // 9 * 9 * 9 + 1	-- permutations
#define COLS 324 // 9 * 9 * 4		-- constraints

void createboard();
void printboard();

struct node
{
	bool data;
	node *left;
	node *right;
	node *up;
	node *down;
} *head;
std::array<node *, 236520> nodes;

void dancinglinkstofile();
void dancinglinkstofile(node *, char *file);
void getdancinglinksize(node *, int &, int &);

void boardtodancinglinks();

void Solve();

int main()
{
	for (std::array<short, 9> iter : board)
	for (short _iter : iter)
		_iter = 0;

	createboard();
	printboard();

	exactcover = new Exactcover(ROWS, COLS);
	for (int )
}

void createboard()
{
	std::ifstream ifs;
	ifs.open("board.txt");

	for (std::array<short, 9> &iter : board)
	{
		for (short &_iter : iter)
		{
			char lmao;
			ifs >> lmao;
			_iter = lmao - 48;
		}
	}

	ifs.close();
}

void printboard()
{
	int count = 0;
	for (std::array<short, 9> iter : board)
	{
		int _count = 0;
		for (short _iter : iter)
		{
			std::cout << _iter;
			if (++_count % 3 == 0) std::cout << (char)179;
			else std::cout << " ";
		}
		std::cout << "\b ";
		std::cout << std::endl;
		if (++count % 3 == 0) std::cout << "-----------------" << std::endl;
	}
}

void dancinglinkstofile()
{
	std::ofstream ofs;
	ofs.open("dancinglinks.txt");

	for (int row = 0; row < 730; ++row)
	{
		for (int col = 0; col < 324; ++col)
		{
			if (nodes[row * 324 + col]->data) ofs << 1;
			else ofs << " ";
			if (col % 81 == 80) ofs << "|";
		}
		ofs << std::endl;
		if (row % 9 == 8)
		{
			for (int col = 0; col < 324; ++col) ofs << "-";
			ofs << std::endl;
		}
	}

	ofs.close();
}

void dancinglinkstofile(node *head, char *file)
{
	std::ofstream ofs;
	ofs.open(file);

	int width, height;
	getdancinglinksize(head, width, height);

	node *current = head;
	for (int row = 0; row < height; ++row)
	{
		node *_current = current;
		for (int col = 0; col < width; ++col)
		{
			if (_current->data) ofs << 1;
			else ofs << " ";
			ofs << ",";
			_current = _current->right;
		}
		ofs << std::endl;
		current = current->down;
	}

	ofs.close();
}

void getdancinglinksize(node *head, int &width, int &height)
{
	node *current = head;
	width = 0;
	do {
		++width;
		current = current->right;
	} while (current != head);
	height = 0;
	do {
		++height;
		current = current->down;
	} while (current != head);
}

void boardtodancinglinks()
{
	node* boardnode = nodes[236196];
	int count = 0;
	for (std::array<short, 9> iter : board)
	{
		int _count = 0;
		for (short _iter : iter)
		{
			if (_iter != 0)
			{
				node *row = nodes[(count * 81 + _count * 9 + _iter - 1) * 324];
				node *current = row;
				node *_current = boardnode;
				do {
					if (current->data)
					{
						if (!_current->data)
							_current->data = true;
						else throw "invalid board";
					}
					current = current->right;
					_current = _current->right;
				} while (current != row);
			}
			++_count;
		}
		++count;
	}
	dancinglinkstofile(boardnode, "addedboard.txt");

	int width, height;
	getdancinglinksize(boardnode, width, height);

	node *current = boardnode;
	for (int count = width; count > 0; --count)
	{
		if (current->data == 1)
		{
			node *_current = current->down;
			for (int _count = height - 1; _count > 0; --_count)
			{
				if (_current->data)
				{
					node *__current = _current;
					for (int __count = 0; __count < width; ++__count)
					{
						__current->up->down = __current->down;
						__current->down->up = __current->up;
						__current = __current->right;
					}
					--height;
				}
				_current = _current = _current->down;
			}
			if (current == boardnode) boardnode = current->right;
			_current = current;
			for (int _count = height; _count > 0; --_count)
			{
				_current->left->right = _current->right;
				_current->right->left = _current->left;
				_current = _current->down;
			}
			--width;
		}
		current = current->right;
	}
	head = boardnode->down;
}

void Solve()
{

}