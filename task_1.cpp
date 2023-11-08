#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <numeric>
#include <iomanip>
#include <limits> 
#include <numbers>

class Readers {
public:
	Readers():readers_(100001), pages_(10000){}
	
	void AddRead(const int& reader, const int& page) {
		int number_page_user = 0;
		if (readers_[reader]) {
			number_page_user = readers_[reader];
			for (int i = number_page_user; i < page; ++i) {
				++pages_[i];
			}
			readers_[reader] = page;
		}
		else {
			readers_[reader] = page;
			for (int i = number_page_user; i < page; ++i) {
				++pages_[i];
			}
			++number_readers_;
		}
	}

	std::vector<int> GetReaders() {
		return readers_;
	}

	std::vector<int> GetPages() {
		return pages_;
	}
	int GetNumberReaders() {
		return number_readers_;
	}

	double ProcessingRequestCheer(const int& reader) {
		if (!readers_[reader]) {
			return 0.0;
		}
		else {
			if (number_readers_ == 1) {
				return 1.0;
			}
			else {
				// номер страницы которую читает пользователь в запросе;
				int number_page_user = readers_[reader];
				return (number_readers_ - pages_[number_page_user - 1]) / (number_readers_ * 1.0 - 1);
			}
		}
	}

private:
	//пользователь, номер страницы
	std::vector<int> readers_{};
	// страница, количество пользователей
	std::vector<int> pages_{};
	int number_readers_{};
};

void ReadLine(Readers& readers, std::istream& input, std::ostream& output) {
	std::string token_request_type{};
	std::string token_reader{};
	std::string token_page{};
	std::getline(input, token_request_type, ' ');
	
	if (token_request_type == "READ") {
		std::getline(input, token_reader, ' ');
		std::getline(input, token_page);
		readers.AddRead(stoi(token_reader), stoi(token_page));
	}
	if (token_request_type == "CHEER") {
		std::getline(input, token_reader);
		output << readers.ProcessingRequestCheer(std::stoi(token_reader)) << std::endl;
	}
	
}

void EBookReaders(std::istream& input = std::cin, std::ostream& output = std::cout) {
	std::setprecision(6);
	Readers readers;
	std::string number_requests{};
	std::getline(input, number_requests);
	for (int i = 0; i < stoi(number_requests); ++i) {
		ReadLine(readers, input, output);
	}
}

int main() {
	EBookReaders(std::cin, std::cout);	
}