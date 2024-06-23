#include "utils.h"
#include "valid.h"
#include <iostream>
#include <limits>
#include <variant>

Book_1 Utils::getLastbook()
{
	return lastbook;
}

VideoCD_2 Utils::getLastcd()
{
	return lastcd;
}
Picture_2 Utils::getLastpic()
{
	return lastpic;
}


bool Utils::addBookItem(Book_1 book)
{
	if (!(this->IdExist(book.getId())))
	{
		books[book.getId()] = book;
		return true;
	}
	return false;

}

bool Utils::addCDItem(VideoCD_2 cd)
{
	if (!(this->IdExist(cd.getId())))
	{
		cds[cd.getId()] = cd;
		return true;
	}
	return false;
}

bool Utils::addPicItem(Picture_2 pic)
{
	if (!(this->IdExist(pic.getId())))
	{
		pics[pic.getId()] = pic;
		return true;
	}
	return false;

}

bool Utils::IdExist(int index)
{
	for (Book_1 book : books)
	{
		if (index == book.getId())
		{
			return true;
		}
	}

	for (VideoCD_2 cd : cds)
	{
		if (index == cd.getId())
		{
			return true;
		}
	}
	for (Picture_2 pic : pics)
	{
		if (index == pic.getId())
		{
			return true;
		}
	}
	return false;
}

std::vector<Book_1> Utils::getBooks()
{
	return books;
}

std::vector<VideoCD_2> Utils::getCds()
{
	return cds;
}

std::vector<Picture_2> Utils::getPics()
{
	return pics;
}

bool Utils::deleteItem(int id)
{
	if (id <= 0 || id >= SIZE)
	{
		return false;
	}
	for (Book_1& book : books)
	{
		if (book.getId() == id)
		{
			book.setId(0);
			return true;
		}
	}

	for (VideoCD_2& cd : cds)
	{
		if (cd.getId() == id)
		{
			cd.setId(0);
			return true;
		}
	}

	for (Picture_2& pic : pics)
	{
		if (pic.getId() == id)
		{
			pic.setId(0);

			return true;
		}
	}

	return false;
}


std::vector<int> Utils::statistic()
{
	for (Book_1 book : books)
	{
		if (book.getId() != 0)
		{
			sum[0]++;
			sum[1]++;
		}
	}

	for (VideoCD_2 cd : cds)
	{
		if (cd.getId() != 0)
		{
			sum[0]++;
			sum[2]++;
		}
	}

	for (Picture_2 pic : pics)
	{
		if (pic.getId() != 0)
		{
			sum[0]++;
			sum[3]++;
		}
	}
	return sum;
}

bool Utils::searchBookItem(int id)
{
	Book_1 book;
	for (Book_1 book : books)
	{
		if (id == book.getId())
		{
			lastbook = book;
			return true;
		}
	}

	return false;
}

bool Utils::searchBookItem(QString title)
{
	Book_1 book;
	for (Book_1 book : books)
	{
		if (title == book.getTitle())
		{
			lastbook = book;
			return true;
		}
	}

	return false;
}

bool Utils::searchCDItem(int id)
{
	VideoCD_2 cd;
	for (VideoCD_2 cd : cds)
	{
		if (id == cd.getId())
		{
			lastcd = cd;
			return true;
		}
	}

	return false;
}

bool Utils::searchCDItem(QString title)
{
	VideoCD_2 cd;
	for (VideoCD_2 cd : cds)
	{
		if (title == cd.getTitle())
		{
			lastcd = cd;
			return true;
		}
	}

	return false;
}

bool Utils::searchPicItem(int id)
{
	Picture_2 pic;
	for (Picture_2 pic : pics)
	{
		if (id == pic.getId())
		{
			lastpic = pic;
			return true;
		}
	}

	return false;
}

bool Utils::searchPicItem(QString title)
{
	Picture_2 pic;
	for (Picture_2 pic : pics)
	{
		if (title == pic.getTitle())
		{
			lastpic = pic;
			return true;
		}
	}

	return false;
}

bool Utils::isFull()
{
	if (this->statistic()[0] == SIZE)
	{
		return true;
	}

	return false;
}