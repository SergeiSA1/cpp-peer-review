#include <iostream>
#include <vector>
#include <iomanip>

class Readers {
public:
	Readers():readers_(100001), pages_(1000){}
	
	void AddRead(const int& reader, const int& page) {
		int& number_page_user = readers_[reader];
			for (int i = number_page_user; i < page; ++i) {
				++pages_[i];
			}
			readers_[reader] = page;
	}

	double ProcessingRequestCheer(const int& reader) {
		if (!readers_[reader]) {
			return 0.0;
		}
		else {
			// количество "читающих" читателей
			int& number_readers = pages_[0];
			if (number_readers == 1) {
				return 1.0;
			}
			else {
				// номер страницы которую читает читатель из запроса;
				int& number_page_user = readers_[reader];
				return (number_readers - pages_[number_page_user - 1]) / (number_readers * 1.0 - 1);
			}
		}
	}

private:
	//пользователь, номер страницы
	std::vector<int> readers_{};
	// страница, количество пользователей
	std::vector<int> pages_{};
};

void ReadLine(Readers& readers, std::istream& input, std::ostream& output) {
	std::string token_request_type{};
	int token_reader{};
	int token_page{};
	input >> token_request_type;
	
	if (token_request_type == "READ") {
		input >> token_reader;
		input >> token_page;
		readers.AddRead(token_reader, token_page);
	}
	else {
		input >> token_reader;
		output << std::setprecision(6) << readers.ProcessingRequestCheer(token_reader) << std::endl;
	}
	
}

void EBookReaders(std::istream& input = std::cin, std::ostream& output = std::cout) {
	Readers readers;
	int number_requests{};
	input >> number_requests;
	for (int i = 0; i < number_requests; ++i) {
		ReadLine(readers, input, output);
	}
}

int main() {
	EBookReaders(std::cin, std::cout);	
}