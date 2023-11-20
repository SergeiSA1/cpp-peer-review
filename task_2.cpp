#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include <vector>
#include <utility>
#include <cassert>

using namespace std;

class Domain {
public:
    // разработайте класс домена
    Domain(const string& domain_input) :domain_(domain_input) { 
        reverse(domain_.begin(), domain_.end());
        domain_.push_back('.');
    }
    // конструктор должен позволять конструирование из string, с сигнатурой определитесь сами

    bool operator < (const Domain& domain_next) const {
        return lexicographical_compare(domain_.begin(), domain_.end(), domain_next.domain_.begin(), domain_next.domain_.end());
    }

    // разработайте operator==
    bool operator == (const Domain& domain_next) const{
        if (domain_next.domain_.size() >= domain_.size() && 
            equal(domain_.begin(), domain_.end(), domain_next.domain_.begin())) {
                return true;   
        }
        return false;
    }

    // разработайте метод IsSubdomain, принимающий другой домен и возвращающий true, если this его поддомен
    bool IsSubdomain(const Domain& domain_next) const{
        return domain_next == *this;
    }
private:
    string domain_;

};

class DomainChecker {
public:
    // конструктор должен принимать список запрещённых доменов через пару итераторов
    template<typename InputIt>
    DomainChecker(InputIt domains_begin, InputIt domains_end) {
        vector <Domain> domains{};
        for (InputIt it = domains_begin; it != domains_end; ++it) {
            domains.push_back(*it);
        }
        sort(domains.begin(), domains.end(), [](const Domain& lhs, const Domain& rhs) {
            return lhs < rhs;
        });
        InputIt iter = std::unique(domains.begin(), domains.end(),[](const Domain& lhs, const Domain& rhs) {
            return rhs.IsSubdomain(lhs); 
            });
        domains.erase(iter, domains.end());
        domains_ = domains;
    }

    // разработайте метод IsForbidden, возвращающий true, если домен запрещён
    bool IsForbidden(const Domain& domain){
        if (!domains_.empty()) {
            vector<Domain>::iterator it = upper_bound(domains_.begin(), domains_.end(), domain, [](const Domain& lhs, const Domain& rhs) {
                    return lhs < rhs;
                });
            if (domains_.begin() == it) {
                return domain.IsSubdomain(domains_[0]);
            }
            else {
                return domain.IsSubdomain(domains_[it - domains_.begin()-1]);
            }
        }
        return false;
    }
    vector<Domain> GetDomains() {
        return domains_;
    }
private:
    vector<Domain> domains_{};
};

// разработайте функцию ReadDomains, читающую заданное количество доменов из стандартного входа

template <typename ReadNumber>
vector<Domain> ReadDomains(istream& input, ReadNumber number) {
    vector<Domain> domains{};
    string domain;
    int number_line = static_cast <int>(number);
    for (int i = 0; i < number_line; ++i) {
        getline(input, domain);
        domains.push_back(domain);
    }
    return domains;
}

template <typename Number>
Number ReadNumberOnLine(istream& input) {
    string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

void TestDomain() {
    istringstream domains("gdz.ru\n" "maps.me\n" "m.gdz.ru\n" "com");
    vector<string> read_domains = { "gdz.ru", "maps.me", "m.gdz.ru", "com" };
    Domain domain("gdz.ru");
    Domain sub_domain("m.gdz.ru");
    const vector<Domain> forbidden_domains = ReadDomains(domains, 4);
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());
    {
        assert(forbidden_domains.size() == 4);
        {
            assert(forbidden_domains[0] == read_domains[0]);
            assert(forbidden_domains[1] == read_domains[1]);
            assert(forbidden_domains[2] == read_domains[2]);
            assert(forbidden_domains[3] == read_domains[3]);
        }
        assert(forbidden_domains[0] < read_domains[2]);
        assert(!(forbidden_domains[2] < read_domains[0]));
        assert(forbidden_domains[0] == forbidden_domains[2]);
        assert(!(forbidden_domains[2] == forbidden_domains[0]));
        assert(sub_domain.IsSubdomain(domain));
        assert(!(domain.IsSubdomain(sub_domain)));
        assert(checker.GetDomains().size() == 3);
        assert(checker.IsForbidden(sub_domain));
        assert(!(checker.IsForbidden(Domain("gbs.ru"))));
    }
    cout << "Test Domain OK" << endl;
}

int main() {
    TestDomain();
    const std::vector<Domain> forbidden_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    const std::vector<Domain> test_domains = ReadDomains(cin, ReadNumberOnLine<size_t>(cin));
    for (const Domain& domain : test_domains) {
        cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << endl;
    }
}